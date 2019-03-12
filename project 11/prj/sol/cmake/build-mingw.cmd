@REM CMake it


call .\vars.cmd

@SET SOLNAME=mingw

@REM 
REM %CMAKERUN% .

@echo  Preparing dirs
@REM %CMAKERUN% . -G "MinGW Makefiles" -T "./confs/win32-mingw"
@REM %CMAKERUN% . -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=./confs/win32-mingw

@REM check if sol dir already exists
@IF NOT EXIST sol-%SOLNAME% GOTO NOSOLDIR
rmdir sol-%SOLNAME% /s
:NOSOLDIR
md sol-%SOLNAME%

cd sol-%SOLNAME%
@echo  CMake'ing
%CMAKERUN% .. -G "MinGW Makefiles"

@echo  Make'ing
%MAKERUN%

cd ..