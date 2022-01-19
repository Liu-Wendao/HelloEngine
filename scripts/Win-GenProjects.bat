@echo off
pushd %~dp0\..\
call 3rdParty\bin\premake\premake5.exe vs2019
popd
PAUSE