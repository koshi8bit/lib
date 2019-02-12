@echo off
set source="G:\kent_brockman4\prog\C\Qt\lib\kb4\prj\lib\kb4"
set dest=%cd%\kb4\
echo %dest%
rd %dest% /Q /S
xcopy %source% %dest% /E /Y
attrib %dest%* /S +R