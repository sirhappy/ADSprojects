@REM CMake it


call .\vars.cmd


@SET SOLNAME=default

@REM check if sol dir already exists
@IF NOT EXIST sol-%SOLNAME% GOTO NOSOLDIR
rmdir sol-%SOLNAME% /s
:NOSOLDIR
md sol-%SOLNAME%

cd sol-%SOLNAME%

@echo  CMake'ing
%CMAKERUN% ..

@echo  Make'ing
%CMAKERUN% --build .

cd ..