#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266SSDP.h>
#include <FS.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define CONTROL_PIN 5   //D1 on Wemos D1 mini
#define NUM_LEDS    36  //Number of LEDs in strip
CRGB leds[NUM_LEDS];    //LED strip

IPAddress apIP(192,168,4,1);
ESP8266WebServer HTTP(80);

String ssid = "hse";
String password = "hsepassword";
String ssidAP = "WiFi";
String passwordAP = "";
String SSDP_NAME = "LED Strip";
int timezone = 0;


enum class State
{
    initial,intermediate,dot,strips,switchOff,switchToColor
};
State state = State::initial;

void setup()
{
    Serial.begin(115200);
    Serial.println("");
    Serial.println("Start WiFi");
    FSinit();
    loadConfig();
    WiFiInit();
    if(WiFi.waitForConnectResult() == WL_CONNECTED)
        SSDPinit();
    HTTPinit();
}

void loop()
{
    HTTP.handleClient();
}

//=====================================================================
void FSinit()
{
  SPIFFS.begin();
}

String getContentType(String filename) {
  if (HTTP.hasArg("download")) return "application/octet-stream";
  else if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".json")) return "application/json";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool readFile(String path)
{
  //if(path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path))
  {
    if(SPIFFS.exists(pathWithGz))
      path += ".gz";

    File file = SPIFFS.open(path,"r");
    size_t sent = HTTP.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}
//=====================================================================
bool loadConfig()
{
  File configFile = SPIFFS.open("/config.json","r");

  if(!configFile)
  {
    saveConfig();
    return false;
  }

  size_t size = configFile.size();
  if(size > 1024)
  {
    Serial.println("Config file is too large");
    return false;
  }

  String jsonConfig = "{}";
  jsonConfig = configFile.readString();
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(jsonConfig);

  ssid = root["ssidName"].as<String>();
  password = root["ssidPassword"].as<String>();
  ssidAP = root["ssidAPName"].as<String>();
  passwordAP = root["ssidAPPassword"].as<String>();
  timezone = root["timezone"];
  SSDP_NAME = root["SSDP_NAME"].as<String>();
  configFile.close();
  return true;
}

bool saveConfig()
{
  DynamicJsonBuffer jsonBuffer;
  String jsonConfig = "{}";
  JsonObject& json = jsonBuffer.parseObject(jsonConfig);

  json["SSDP_NAME"] = SSDP_NAME;
  json["ssidAPName"] = ssidAP;
  json["ssidAPPassword"] = passwordAP;
  json["ssidName"] = ssid;
  json["ssidPassword"] = password;
  json["timezone"] = timezone;

  json.printTo(jsonConfig);
  File configFile = SPIFFS.open("/config.json","w");

  if(!configFile)
    return false;
  json.printTo(configFile);
  configFile.close();
  return true;
}
//=====================================================================
void HTTPinit()
{
  HTTP.on("/",handleRoot);
  HTTP.on("/restart",handleRestart);
  HTTP.on("/configs.json",handleConfigsJSON);
  HTTP.on("/ssid",handleSetSSID);
  HTTP.on("/ssidap", handleSetSSIDAP);
  HTTP.on("/ssdp", handleSetSSDP);
  HTTP.on("/TimeZone",handleTimezone);
  HTTP.on("/switchToColor",handleSwitchToColor);
  HTTP.on("/switchOff",handleSwitchOff);
  HTTP.on("/dot",handleDot);
  HTTP.on("/strips",handleStrips);
  HTTP.onNotFound([]()
  {
    if(!readFile(HTTP.uri()))
      HTTP.send(404, "text/plain", "File Not Found");
  });
  HTTP.begin();
}

void handleRoot()
{
  readFile("/index.htm");
}

void handleSetSSDP()
{
  if(!HTTP.hasArg("ssdp"))
    return HTTP.send(500,"text/plain","BAD ARGS");

  SSDP_NAME = HTTP.arg("ssdp");
  saveConfig();
  HTTP.send(200,"text/plain","OK");
}

void handleSetSSID()
{
  if(!HTTP.hasArg("ssid") || !HTTP.hasArg("password"))
    return HTTP.send(500,"text/plain","BAD ARGS");

  ssid = HTTP.arg("ssid");
  password = HTTP.arg("password");
  saveConfig();
  HTTP.send(200,"text/plain","OK");
}

void handleSetSSIDAP()
{
  if(!HTTP.hasArg("ssidAP") || !HTTP.hasArg("passwordAP"))
    HTTP.send(500,"text/plain","BAD ARGS");

  ssidAP = HTTP.arg("ssidAP");
  passwordAP = HTTP.arg("passwordAP");
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}

void handleTimezone()
{
  if(!HTTP.hasArg("timezone"))
    return HTTP.send(500,"text/plain","BAD_ARGS");

  timezone = HTTP.arg("timezone").toInt();
  HTTP.send(200,"text/plain","OK");
}

void handleRestart()
{
  String argument = "";

  if(HTTP.hasArg("device"))
    argument = HTTP.arg("device");

  if(argument == "ok")
  {
    HTTP.send(200,"text/plain","Restarted");
    delay(10);
    ESP.restart();
  }
  else
  {
    HTTP.send(200,"text/plain","To restart ESP specify /restart?device=ok");
    delay(10);
  }
}

void handleConfigsJSON()
{
  String json = "{";

  json += "\"SSDP\":\"";
  json += SSDP_NAME;

  json += "\",\"ssid\":\"";
  json += ssid;

  json += "\",\"password\":\"";
  json += password;

  json += "\",\"ssidAP\":\"";
  json += ssidAP;

  json += "\",\"passwordAP\":\"";
  json += passwordAP;

  json += "\",\"ip\":\"";
  json += WiFi.localIP().toString();

  json += "\",\"timezone\":";
  json += timezone;

  json += "}";

  HTTP.send(200,"text/json",json);
}

void handleSwitchToColor()
{
  state = State::switchToColor;
  if(!HTTP.hasArg("r") || !HTTP.hasArg("g") || !HTTP.hasArg("b"))
    HTTP.send(500,"text/plain","BAD_ARGS");

  int r = HTTP.arg("r").toInt();
  int g = HTTP.arg("g").toInt();
  int b = HTTP.arg("b").toInt();

  if(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    HTTP.send(500,"text/plain","BAD_ARGS");

  switchToColor(r,g,b);
  HTTP.send(200,"text/plain","OK");
}

void handleSwitchOff()
{
  state = State::switchOff;
  HTTP.send(200,"text/plain","OK");
  switchOff();
}

void handleDot()
{
  if(!HTTP.hasArg("r") || !HTTP.hasArg("g") || !HTTP.hasArg("b"))
    HTTP.send(500,"text/plain","BAD_ARGS");

  int r = HTTP.arg("r").toInt();
  int g = HTTP.arg("g").toInt();
  int b = HTTP.arg("b").toInt();

  if(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    HTTP.send(500,"text/plain","BAD_ARGS");

  state = State::dot;
  HTTP.send(200,"text/plain","OK");
  dot(HTTP,r,g,b);
}

void handleStrips()
{
  if( !HTTP.hasArg("r") || !HTTP.hasArg("g") || !HTTP.hasArg("b") ||
      !HTTP.hasArg("length") || !HTTP.hasArg("space") || !HTTP.hasArg("wait"))
    HTTP.send(500,"text/plain","BAD_ARGS");

  int r = HTTP.arg("r").toInt();
  int g = HTTP.arg("g").toInt();
  int b = HTTP.arg("b").toInt();
  int len = HTTP.arg("length").toInt();
  int space = HTTP.arg("space").toInt();
  int wait = HTTP.arg("wait").toInt();

  if(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    HTTP.send(500,"text/plain","BAD_ARGS");

  HTTP.send(200,"text/plain","OK");
  switchOff();
  state = State::strips;
  strips(HTTP, r, g, b, len, space, wait);
}
//=====================================================================
void SSDPinit()
{
  HTTP.on("/description.xml",HTTP_GET,[]()
  {
    SSDP.schema(HTTP.client());
  });

  SSDP.setDeviceType("upnp:rootdevice");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName(SSDP_NAME);
  SSDP.setSerialNumber("0001");
  SSDP.setURL("/");
  SSDP.setModelNumber("1");
  SSDP.setManufacturer("ZV");
  SSDP.begin();
}
//=====================================================================
void resetClient()
{
  HTTP.client().stop();
  HTTP.begin();
  HTTP.handleClient();
}

void stripInit()
{
  delay(3000);
  FastLED.addLeds<NEOPIXEL,CONTROL_PIN>(leds,NUM_LEDS);
}

void switchToColor(uint8_t r, uint8_t g, uint8_t b)
{
  fill_solid(&(leds[0]),NUM_LEDS,CRGB(r,g,b));
  FastLED.show();
}

void dot(ESP8266WebServer& server,uint8_t r, uint8_t g, uint8_t b)
{
  while(true)
  {
    for(int i = 0; i < NUM_LEDS; ++i)
    {
      leds[i].setRGB(r,g,b);
      FastLED.show();
      delay(30);
      leds[i] = CRGB::Black;
    }
    resetClient();
    if(state != State::dot)
      break;
  }
}

void strips(ESP8266WebServer& server, uint8_t r, uint8_t g, uint8_t b, int len, int space , int wait)
{
  int k = 0;
  while(true)
  {
    int curColor = k;
    for(int i = 0; i < NUM_LEDS; ++i)
    {
      if(curColor < len)
        leds[i].setRGB(r,g,b);
      else
        leds[i] = CRGB::Black;

      if(++curColor > len + space - 1)
        curColor = 0;
    }

    if(--k < 0)
      k = len + space - 1;

    FastLED.show();
    delay(wait);

    resetClient();
    delay(1);
    if(state != State::strips)
      break;
  }
}

void switchOff()
{
  fill_solid(&(leds[0]),NUM_LEDS,CRGB::Black);
  FastLED.show();
}
//=====================================================================
void WiFiInit()
{
  WiFi.mode(WIFI_STA);
  int tries = 10;

  WiFi.begin(ssid.c_str(),password.c_str());
  while(tries > 0 && WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    tries--;
    delay(500);
  }
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("");
    Serial.println("Connection failed. Switching to AP: " + ssidAP);
    StartAP();
    Serial.print("Access point IP: ");
    Serial.println(WiFi.softAPIP());
  }
  else
  {
    Serial.println("");
    Serial.print("Connected to " + (String)ssid + " IP:");
    Serial.print( WiFi.localIP());
    stripInit();  //starting LED strip
  }
}

void StartAP()
{
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP,apIP,IPAddress(255,255,255,0));
  WiFi.softAP(ssidAP.c_str(),passwordAP.c_str());
}