::COPY TO lib\
@echo off

echo SCRIPT DISABLED! DELETE THIS 3 LINES
pause
exit

::set source="G:\kent_brockman4\prog\C\Qt\lib\kb4\prj\lib\kb4"
::set source="D:\Users\kb4\Prog\C\Qt\Lib\kb4\prj\lib\kb4"
set source="G:\koshi8bit\prog\c\qt\lib\kb4\prj\lib\kb4"

set dest=%cd%\kb4\
:RESTARTT
rd %dest% /Q /S
IF EXIST %dest% (
	echo ACHTUNG! Folder deletion failed!
    timeout /t 1
    GOTO RESTARTT
)
xcopy %source% %dest% /E /Y
attrib %dest%* /S +R
