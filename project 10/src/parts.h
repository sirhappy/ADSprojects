#ifndef _PARTS_H_
#define _PARTS_H_

#include <vector>
#include <map>
#include <string>

//**************** Part ****************
class Part 
{
public:
    int count_howmanyUp(Part* const p);

    Part(std::string const& n) : name(n) {};
    Part(std::string const& n, Part* p): name(n),parent(p){};
    void describe();
    int count_howmany(Part const* p);

    //name of part
    std::string name;

    //pointer to parent
    Part* parent = nullptr;

    //map containing pointers to subparts and their quantity
    std::map<Part*,int> subparts;
};

//**************** NameContainer ****************
class NameContainer  
{
public:
    //Default constructor
    NameContainer() {};

    //Copy constructor
    NameContainer(const NameContainer& other);

    //Destructor
    ~NameContainer();

    //Method for searching part by name
    Part* lookup(std::string const &name);

    //Method for adding elements to container
    void add_part(std::string const &x, int q, std::string const &y);

    //Assignment operator
    NameContainer& operator = (const NameContainer& other);

private:
    //Support method for swapping NameContainers
    static void swap(NameContainer& first, NameContainer& second);
private:
    //Container for Parts
    std::map<std::string, Part*> name_map;
};

#endif
