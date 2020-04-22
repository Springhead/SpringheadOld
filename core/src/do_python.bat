@echo off
setlocal enabledelayedexpansion
:: ============================================================================
::  SYNOPSIS
::	set _SPRTOP_=<Springhead�̃g�b�v�f�B���N�g��>
::	do_python.bat script.py [args..]	�iWindows ��p�j
::
::  DESCRIPTION
::	Python script �����s���邽�߂� Windows �p�A�_�v�^�B
::	"Springhead/buildtool" �����p�ł���Ƃ��́A������g���Ď��s����B
::	�����Ȃ���΁A�f�t�H���g�ŗ��p�ł��� python ���g���Ď��s����B
::	�f�t�H���g�� python �����p�ł��Ȃ��ꍇ�A�܂��� python �̃o�[�W������
::	3 ���Â��ꍇ�́A���b�Z�[�W��\�����ď����𒆎~����B
::	
::	���̃t�@�C���� Windows ��p�ł���B�܂�Springehad�̃g�b�v�f�B���N�g��
::	���擾���邽�߂Ɋ��ϐ� "_SPRTOP_" ���g�p����B�{�X�N���v�g���ĂԑO��
::	���̊��ϐ���ݒ肵�Ă������ƁB
::	unix �̏ꍇ�̓f�t�H���g�� Python ���g�p�ł���悤�ɂ��Ă����Ȃ����
::	�Ȃ�Ȃ��B
::
::  VERSION
::	Ver 1.0  2019/10/10 F.Kanehori	RunSwig ����ړ�. -SprTop �͔p�~.
::	Ver 1.1  2020/04/16 F.Kanehori	_SPRTOP_ �̃f�t�H���g��ύX
:: ============================================================================
set verbose=0

::----------------------------------------------
::  buildtool �̑��΃p�X
::	"%1"=="-src"�Ȃ�A"_SPRTOP_=..\..\"�Ƃ���
::
if "%_SPRTOP_%" equ "" (
	set _SPRTOP_=..\..
	rem echo Need environment variable "_SPRTOP_" be set".
	rem endlocal
	rem exit /b
)
set TOOLPATH=%_SPRTOP_%\buildtool\win32

:: �����͂��̂܂ܓn��
set ARGS=%*

::----------------------------------------------
::  Python �����s�ł���悤�ɂ���
::
if exist "%TOOLPATH%\python.exe" (
	PATH=!TOOLPATH!;!PATH!
) else (
	where python >NUL 2>& 1
	if !ERRORLEVEL! neq 0 (
		echo Python not found.
		endlocal
		exit /b
	)
	for /f "tokens=*" %%a in ('python -V') do set OUT=%%a
	set VER=!OUT:Python =!
	set MAJOR=!VER:~0,1!
	set MINOR=!VER:~2,1!
	if !MAJOR! neq 3 (
		echo !OUT! found.
		echo Use Python 3 or later version.
		endlocal
		exit /b
	)
)
if %verbose% geq 1 (
	rem where python
	python -V
)

::----------------------------------------------
::  Python �����s����
::
if %verbose% geq 2 (
	echo cwd: %CD%
	echo python %ARGS%
)
rem if %verbose% geq 1 (
rem 	echo.
rem )
rem echo python %ARGS%
python %ARGS%

endlocal
exit /b
