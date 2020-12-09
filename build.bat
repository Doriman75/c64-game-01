@echo off
set basedir=.
set emulator=\prg\vice\x64sc.exe
set compiler=C:\prg\cc65-snapshot-win32\bin\cl65.exe
cd %basedir%
echo "generating assets ..."
for %%I in (*.txt) do (
	node data.js %%I > %%~nI.h
)
echo "compiling ..."
%compiler% -Or -o main.prg .\main.c 
if %ERRORLEVEL% == 1 goto error

echo "starting ..."
%emulator% main.prg
goto end


:error
pause

:end