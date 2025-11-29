@echo off
setlocal

cls

if not exist Build mkdir Build

cd Clib
Clib.exe ../Source ../Include ../Library PiXELGraph-v2.a || exit /b 1 

cd ..

g++ -c main.cpp -IInclude
g++ main.o -o Build/PiXELGraph Library/PiXELGraph-v2.a 
del main.o

R