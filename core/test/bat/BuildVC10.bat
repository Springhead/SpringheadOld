set ORG_PATH=%PATH%

set X64PATH=C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE
set X32PATH=C:\Program Files\Microsoft Visual Studio 10.0\Common7\IDE
set ADDPATH=..\..\Springhead2Test\src\Foundation
set PROG=devenv.exe
if exist "%X32PATH%\%PROG%" set PATH=%X32PATH%;%ADDPATH%;%PATH%
if exist "%X64PATH%\%PROG%" set PATH=%X64PATH%;%ADDPATH%;%PATH%

rem �J�����g�f�B���N�g�������ϐ��ɓo�^����
for /F usebackq %%f in (`cd`) do set CURRENTDIR=%%f

if "%DAILYBUILD_EXECUTE_BUILDRUN%" neq "skip" echo   tests: %~n3: %2

rem �r���h�����ă��O��"Build.log"�ɏo��
echo *** %~n3: %2 *** >> log\Build.log
devenv %1\%210.sln /build  Debug > log\BuildTemp.log
type log\BuildTemp.log >> log\Build.log
echo. >> log\Build.log
echo. >> log\Build.log

rem �G���[������s����"BuildError.log"�ɏo��
echo *** %~n3: %2 *** >> log\BuildError.log
type log\BuildTemp.log | find " error " >> log\BuildError.log
echo. >> log\BuildError.log
echo. >> log\BuildError.log
del log\BuildTemp.log

if exist %1\Debug\%2.exe set BUILD_S=�r���h����
if exist %1\Debug\%2.exe set BUILD_LIST=%BUILD_LIST%%~n3:%2,
if not exist %1\Debug\%2.exe set BUILD_F=�r���h���s
if not exist %1\Debug\%2.exe set BUILD_F_LIST=%BUILD_F_LIST%%~n3:%2,
if not exist %1\Debug\%2.exe goto NEXT

rem ���s���ă��O��"Run.log"�ɏo��
cd %1
echo *** %~n3: %2 *** >> %CURRENTDIR%\log\Run.log
set BINPATH=..\..\..\..\bin
set PATH=%BINPATH%\win64;%BINPATH%\win32;%PATH%
set ERRORLEVEL=0
if exist Debug\%2.exe Debug\%2.exe > %CURRENTDIR%\log\RunTemp.log
if exist Debug\%2.exe set ERROR=%ERRORLEVEL%
cd %CURRENTDIR%
type log\RunTemp.log >> log\Run.log
echo. >> log\Run.log
echo. >> log\Run.log

rem ***** �G���[������s����"RunError.log"�ɏo�� ***** 
echo *** %~n3: %2 *** >> log\RunError.log
if not "%ERROR%"=="0"  type log\RunTemp.log | find " error " >> log\RunError.log
echo. >> log\RunError.log
echo. >> log\RunError.log

if "%ERROR%"=="0" set RUN_S=���s����
if "%ERROR%"=="0" set RUN_LIST=%RUN_LIST%%~n3:%2,
if not "%ERROR%"=="0" set RUN_F=���s���s
if not "%ERROR%"=="0" set RUN_F_LIST=%RUN_F_LIST%%~n3:%2,

del log\RunTemp.log

:NEXT
set PATH=%ORG_PATH%
set ORG_PATH=
set ERROR=
