@echo off
setlocal enabledelayedexpansion
:: ============================================================================
::  SYNOPSIS
::	BuildVC_ArgCheck %*
::
::  DESCRIPTION
::	BuildVC �ɓn���ꂽ�����̃`�F�b�N���s�Ȃ�.
::	
::  ARGUMENTS
::	BuildVC �Ɠ���
::
::  RETURNS
::	$status	    0: args OK, others: some arg is wrong
::
::  VERSION
::	Ver 1.0  2013/09/12 F.Kanehori	�o�b�`�t�@�C���̍č\��
:: ============================================================================
set PROG=BuildVC
set RET=0

::----------------------------------------------
:: ����1
::
call :must_be_specified toolset-ID %1 
if not %RET% == 0 goto :done
shift

::----------------------------------------------
:: ����2
::
call :must_be_specified testset-name %1 
if not %RET% == 0 goto :done
shift

::----------------------------------------------
:: ����3
::
call :must_be_specified category-naem %1 
if not %RET% == 0 goto :done
shift

::----------------------------------------------
:: ����4
::
call :must_be_specified solution-directory %1 
if not %RET% == 0 goto :done
call :must_be_exist solution-directory %1
if not %RET% == 0 goto :done
shift

::----------------------------------------------
:: ����5
::
call :must_be_specified build-configuration %1 
if not %RET% == 0 goto :done
shift

::----------------------------------------------
:: ����6
::
call :must_be_specified build-platform %1 
if not %RET% == 0 goto :done
call :must_be_one_of %1 win32 x64
if not %RET% == 0 goto :done
shift

::----------------------------------------------
:: ����7
::
call :must_be_specified build-option %1
if not %RET% == 0 goto :done
call :must_be_yes_or_no build-option %1
if not %RET% == 0 goto :done
shift

::----------------------------------------------
:: ����8
::
call :must_be_specified run-option %1 
if not %RET% == 0 goto :done
call :must_be_yes_or_no run-option %1
if not %RET% == 0 goto :done
shift

::----------------------------------------------
:: ����9&10
::
call :must_be_specified build-log-file-name %1 
if not %RET% == 0 goto :done
shift
call :must_be_specified build-error-log-file-name %1 
if not %RET% == 0 goto :done
shift

::----------------------------------------------
:: ����11&12
::
call :must_be_specified run-log-file-name %1 
if not %RET% == 0 goto :done
shift
call :must_be_specified run-error-log-file-name %1 
if not %RET% == 0 goto :done
shift

::----------------------------------------------
:: �`�F�b�N����
::
:done
endlocal && set $status=%RET%
exit /b

:: ============================================================================
::  ����T�u���[�`��
::	�ʓ|�Ȃ̂Ŏ��̊��ϐ��͌ďo�����Ƌ��L	--  RET, PAT, MSG1, MSG2
:: ============================================================================
:must_be_specified
    if "%2" equ "" (
	set MSG=%1
	echo %PROG%: !MSG:-= ! must be specified.
	set RET=-1
    )
exit /b

:must_be_exist
    if not exist %2 (
	set MSG=%1
	echo %PROG%: !MSG:-= ! '%2' not exist.
	set RET=-1
    )
exit /b

:must_be_yes_or_no
    if /i "%2" equ "yes" exit /b
    if /i "%2" equ "no"  exit /b
    set MSG=%1
    echo %PROG%: !MSG:-= ! '%2' must be 'yes' or 'no'.
    set RET=-1
exit /b

:must_be_one_of
    set PAT=%1
    set RET=-1
    set N=0
    for %%s in (%*) do (
	set /a N=N+1
	if not !N! == 1 (
	    if /i "%PAT%" equ "%%s" set RET=0
	)
    )
exit /b
