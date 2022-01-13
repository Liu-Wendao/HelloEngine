@echo off
pushd ..\
call 3rdParty\bin\premake\premake5.exe vs2019
popd
PAUSE