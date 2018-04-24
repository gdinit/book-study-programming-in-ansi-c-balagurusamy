@ECHO OFF

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: MAKE CLEAN
:: 
:: Delete all matching files
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

IF EXIST "*.EXE<" (
   DEL /Q /F *.EXE
) 

IF EXIST "*.O<" (
   DEL /Q /F *.O
) 

IF EXIST "*.OBJ<" (
   DEL /Q /F *.OBJ
) 

:: EOF
