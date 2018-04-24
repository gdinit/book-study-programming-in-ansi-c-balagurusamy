:: Find all files matching a given extension in a specific subdirectory ('ch01')
:: and clang-format them in-place.
@ECHO OFF

:: This BAT is launched either from top-level directory or perhaps from inside
:: 'process-utils' subdirectory. We need to be at top-level directory.
IF EXIST process-utils (ECHO At top-level directory already.) ELSE (ECHO Going up to top-level directory && CD ..)

:: Provide initial feedback
ECHO ****************************************
ECHO BEGIN clang-formatting

:: Chapter 01
ECHO.
CD ch01
FOR %%* in (.) DO ECHO STARTED Processing: %%~nx*
FOR %%f in (*.c *.h) DO clang-format -style=file -i %%f
FOR %%* in (.) DO ECHO COMPLETED Processing: %%~nx*
CD ..
ECHO.

:: Chapter 02
ECHO.
CD ch02
FOR %%* in (.) DO ECHO STARTED Processing: %%~nx*
FOR %%f in (*.c *.h) DO clang-format -style=file -i %%f
FOR %%* in (.) DO ECHO COMPLETED Processing: %%~nx*
CD ..
ECHO.

:: Chapter 03
ECHO.
CD ch03
FOR %%* in (.) DO ECHO STARTED Processing: %%~nx*
FOR %%f in (*.c *.h) DO clang-format -style=file -i %%f
FOR %%* in (.) DO ECHO COMPLETED Processing: %%~nx*
CD ..
ECHO.

:: Chapter 04
ECHO.
CD ch04
FOR %%* in (.) DO ECHO STARTED Processing: %%~nx*
FOR %%f in (*.c *.h) DO clang-format -style=file -i %%f
FOR %%* in (.) DO ECHO COMPLETED Processing: %%~nx*
CD ..
ECHO.

:: Chapter 05
ECHO.
CD ch05
FOR %%* in (.) DO ECHO STARTED Processing: %%~nx*
FOR %%f in (*.c *.h) DO clang-format -style=file -i %%f
FOR %%* in (.) DO ECHO COMPLETED Processing: %%~nx*
CD ..
ECHO.

:: Chapter 06
ECHO.
CD ch06
FOR %%* in (.) DO ECHO STARTED Processing: %%~nx*
FOR %%f in (*.c *.h) DO clang-format -style=file -i %%f
FOR %%* in (.) DO ECHO COMPLETED Processing: %%~nx*
CD ..
ECHO.

:: Provide final feedback
ECHO END clang-formatting
ECHO ****************************************

:: EOF
