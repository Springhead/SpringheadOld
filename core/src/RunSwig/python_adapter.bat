@echo off
setlocal enabledelayedexpansion
:: ============================================================================
::  SYNOPSIS
::	python_adapter.bat script [-SprTop dir] [args..]	�iWindows ��p�j
::
::  DESCRIPTION
::	Python script �����s���邽�߂� Windows �p�A�_�v�^�B
::	"Springhead/buildtool" �����p�ł���Ƃ��́A������g���Ď��s����B
::	�����Ȃ���΁A�f�t�H���g�ŗ��p�ł��� python ���g���Ď��s����B
::	�f�t�H���g�� python �����p�ł��Ȃ��ꍇ�A�܂��� python �̃o�[�W������
::	3 ���Â��ꍇ�́A���b�Z�[�W��\�����ď����𒆎~����B
::	
::	���̃t�@�C���� Windows ��p�ł���Bunix �̏ꍇ�̓f�t�H���g�� Python ��
::	�g�p�ł���悤�ɂ��Ă����Ȃ���΂Ȃ�Ȃ��B
::
::  VERSION
::	Ver 1.0  2017/07/24 F.Kanehori	����
::	Ver 1.1  2017/08/02 F.Kanehori	���� -SprTop �ǉ�.
::	Ver 2.0  2017/09/07 F.Kanehori	�p�X�̌������@��ύX.
::	Ver 2.01 2017/09/11 F.Kanehori	����i�R�[�h�̐����j.
::	Ver 3.0  2017/11/06 F.Kanehori	directory���ύX (buildtools -> buildtool)
:: ============================================================================
set verbose=0

::----------------------------------------------
::  buildtool �̑��΃p�X
::
set TOOLPATH=..\..\..\buildtool\win32
if "%1" equ "-SprTop" (
	set TOOLPATH=%2\buildtool\win32
	shift && shift
)
:: �����̒���
set ARGS=
:next_arg
if "%1" == "" goto :end_arg
	rem echo (((%1)))
	set ARGS=!ARGS! %1
	shift
	goto :next_arg
:end_arg
if "%ARGS%" neq "" set ARGS=!ARGS:~1!

::----------------------------------------------
::  Python �����s�ł���悤�ɂ���
::
if exist "%TOOLPATH%\python.exe" (
	PATH=!TOOLPATH!;!PATH!
) else (
	where python >NUL 2>& 1
	if !ERRORLEVEL! neq 0 (
		echo Python not found.
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
if %verbose% geq 0 (
	rem where python
	rem python -V
)

::----------------------------------------------
::  CMake �̂��߂̓��ʏ���
::	�o�b�`�t�@�C���̈����� "a=b" �Ə����Ă�1�̈����Ƃ͌��􂳂�Ȃ��B
::	���̂��� "a@b" �Ƃ����������������炻��� "a=b" �Ə����������ƂƂ���B
::
set ARGS=%ARGS:@=^=%

::----------------------------------------------
::  Python �����s����
::
if %verbose% geq 2 (
	echo cwd: %CD%
	echo python %ARGS%
)
if %verbose% geq 1 (
	echo.
)
rem where python
rem python -V
rem echo python %ARGS%
python %ARGS%
rem echo %ERRORLEVEL%

endlocal
exit /b
