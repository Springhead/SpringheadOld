﻿/*
 *  Copyright (c) 2003-2012, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */

#include "PHOpDemo.h"

#include "dailybuild_SEH_Handler.h"

/**
	シンプルなSprfileローダー
	シミュレーションはglutIdleFuncで進める
	q, ESC	: アプリケーション終了
	r		: ファイルのリロード
	w		: カメラ行列の初期化
	d		: デバック表示切り替え
*/

PHOpDemo app;
int SPR_CDECL main(int argc, char* argv[]){
	SEH_HANDLER_DEF
	SEH_HANDLER_TRY

	app.Init(argc, argv);
	app.StartMainLoop();

	SEH_HANDLER_CATCH
	return 0;
}
