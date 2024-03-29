@echo off
setlocal enabledelayedexpansion
:: ============================================================================
::  SYNOPSIS
::	set _SPRTOP_=<Springheadのトップディレクトリ>
::	do_python.bat script.py [args..]	（Windows 専用）
::
::  DESCRIPTION
::	Python script を実行するための Windows 用アダプタ。
::	"Springhead/buildtool" が利用できるときは、それを使って実行する。
::	さもなければ、デフォルトで利用できる python を使って実行する。
::	デフォルトで python が利用できない場合、または python のバージョンが
::	3 より古い場合は、メッセージを表示して処理を中止する。
::	
::	このファイルは Windows 専用である。またSpringehadのトップディレクトリ
::	を取得するために環境変数 "_SPRTOP_" を使用する。本スクリプトを呼ぶ前に
::	この環境変数を設定しておくこと。
::	unix の場合はデフォルトで Python が使用できるようにしておかなければ
::	ならない。
::
::  VERSION
::	Ver 1.0  2019/10/10 F.Kanehori	RunSwig から移動. -SprTop は廃止.
::	Ver 1.1  2020/04/16 F.Kanehori	_SPRTOP_ のデフォルトを変更
::	Ver 2.0  2020/05/09 F.Kanehori	_SPRTOP_ は廃止.
:: ============================================================================
set verbose=0

::----------------------------------------------
::  buildtool の相対パス
::	現在の位置から上へたどって最初に見つけた"core"ディレクトリの
::	一段上位のディレクトリをSpringheadのトップディレクトリとする
::
set CWD=%CD%
:loop
	call :leaf %CD%
	if "%_ret_%" equ "" goto :exec
	if "%_ret_%" equ "core" goto :found
	cd ..
	goto :loop
:found
cd ..
if exist buildtool\ (
	set TOOLPATH=%CD%\buildtool\win32
	if %verbose% geq 1 (
		echo buildtool found at "%CD%\buildtool"
	)
)
:exec
cd %CWD%

:: 引数はそのまま渡す
set ARGS=%*

::----------------------------------------------
::  Python を実行できるようにする
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
::  Python を実行する
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

::----------------------------------------------
:leaf
	set _ret_=%~nx1
	exit /b

