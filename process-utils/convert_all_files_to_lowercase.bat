@ECHO OFF

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: RENAME FILES TO LOWERCASE
:: 
:: Here is the break-down in case someone wants to modify/improve :
:: 
::     for /f - For every line
::     "Tokens=*" - Process each item in every line.
::     %f in (...) - %f is your variable name for every item.
::     dir - lists every file and subdirectory in a directory.
::     /l - (parameter for dir) Uses lowercase.
::     /b - (parameter for dir) Uses bare format, only the file/directory names, no size, no headers.
::     /a-d - (parameter for dir) Do not list directories. (a stands for attribute, - stands for not and d stands for directory).
::     rename "%f" "%f"- rename the file with its own name, which is actually lowercased by the dir command and /l combination.
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

FOR /F "TOKENS=*" %%F IN ('DIR /L/B/A-D') DO (RENAME "%%F" "%%F")

:: EOF
