﻿/*
 *  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
#ifndef SPR_FWAPP_H
#define SPR_FWAPP_H

#include <Foundation/SprUTTimer.h>
#include <HumanInterface/SprHIKeyMouse.h>
#include <Framework/SprFWWin.h>

namespace Spr{;
/** \addtogroup gpFramework */
//@{

struct FWSdkIf;
struct PHSceneIf;
class FWGraphicsHandler;
struct GRDeviceIf;

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

/** @brief アプリケーションクラスのベース
	ウィンドウを持たず、FWSceneとタイマー関連のみを持つ。
	ウィンドウを持つ他のアプリケーションに組み込む用途を想定
*/

class FWAppBase : public UTRefCount, public DVKeyMouseCallback {
protected:
	UTRef<FWSdkIf>				fwSdk;		///< Framework SDK	
	typedef std::vector< UTRef<UTTimerIf> > Timers;
	Timers timers;							///< Timers to call periodic processing
public:
	FWAppBase();
	virtual ~FWAppBase();

	// 派生クラスで定義する必要がある仮想関数 -----------------------------

	/** @brief 初期化
	FWAppオブジェクトの初期化を行う．最初に必ず呼ぶ．
	*/
	virtual void Init();
						 
	// ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
	// 派生クラスで定義することのできる仮想関数

	/** @brief ユーザ関数
	メインループ実行中にユーザが処理を加えたい場合，ここに記述する．
	物理シミュレーションのステップの前に呼ばれる．
	*/
	virtual void UserFunc() {}

	/** @brief タイマー処理
	繰り返し実行を行う．
	デフォルトではid = 0でコールバック
	*/
	virtual void TimerFunc(int id);

	// ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
	// FWAppのインタフェース

	/** @brief SDKを取得する
	*/
	FWSdkIf*	GetSdk() { return fwSdk; }

	/** @brief SDKを作成する
	*/
	void		CreateSdk();

#if (!defined(SWIG_PY_SPR) && !defined(SWIG_CS_SPR))
	/** @brief タイマーを作成する
	@param	mode	タイマの種類
	@return			タイマオブジェクト
	*/
	UTTimerIf* CreateTimer(UTTimerIf::Mode mode = UTTimerIf::FRAMEWORK);
#endif

	/** @breif タイマーを取得する
	@param タイマー番号
	@return タイマーオブジェクト
	*/
	UTTimerIf* GetTimer(int i);
	int	NTimers() { return (int)timers.size(); }
};

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

/** @brief アプリケーションクラス
	Springheadのクラスは基本的に継承せずに使用するように設計されているが，
	FWAppおよびその派生クラスは例外であり，ユーザはFWAppあるいはその派生クラスを継承し，
	仮想関数をオーバライドすることによって独自機能を実装する．
 */
class FWApp : public FWAppBase {
protected:
	static FWApp* instance;			///<	唯一のFWAppインスタンス
	bool bThread;					///<	GLUTを別スレッドで動かす場合 true
	volatile bool bPostRedisplay;	///<	別スレッドに再描画の要求をするためのフラグ true で再描画
	volatile bool bEndThread;		///<	別スレッドの場合にスレッドを終了させる。

	// ウィンドウ
	typedef std::vector< UTRef<FWWinIf> > Wins;
	Wins wins;
	
	/** @brief ウィンドウにシーンを与える
		@param win シーンを割り当てるウィンドウ
		winに，既存のウィンドウが割り当てられていないシーンを割り当てる．
		該当するシーンが見つからない場合，あるいはwinに既にシーンが割り当てられている場合は何もしない．
	*/
	void AssignScene(FWWinIf* win);
	///	Initialize in new thead
	void StartInThread();
	friend class FWAppThreadCall;
	void CheckAndPostRedisplay();

public:
	FWApp();
	virtual ~FWApp();

	// 派生クラスで定義する必要がある仮想関数 -----------------------------

	/** @brief 初期化
		FWAppオブジェクトの初期化を行う．最初に必ず呼ぶ．
	 */
	virtual void Init(); // C# API用. （引数を持つInitのみを%ignoreしたいので）
	virtual void Init(int argc, char* argv[] = NULL);
	///	Create new thead and start.
	void InitInNewThread();
	void EndThread();

	/** @brief シーンの描画
		シーンが表示されるときに呼ばれる．
		描画処理をカスタマイズしたい場合にオーバライドする．
		デフォルトではFWSdk::Drawが呼ばれる．
	 */
	virtual void Display();

	/** @brief IdleFuncの呼び出しを有効化/無効化する
		glutの場合，glutIdleFuncに対応する．

		＊一般性を持たせ、かつ他とあわせるためにEnableIdleFuncを追加しました。
		DisableIdleFuncも残していますがobsoleteとしたいと思います。
	 */
	void DisableIdleFunc(){ EnableIdleFunc(false); }
	void EnableIdleFunc(bool on = true);
	
	/** @brief メインループの実行
		glutの場合，glutMainLoopの実行
	 */
	void StartMainLoop();
	/** @brief メインループの終了
		freeglutの場合，glutLeaveMainLoopを実行、それ以外の場合は exit(0)
	 */
	void EndMainLoop();

	// 派生クラスで定義することのできる仮想関数 -----------------------------

	/** @brief アイドル処理
		イベントが何もない場合にバックグラウンド処理を行う．
	 */
	virtual void IdleFunc(){}

	/** @brief タイマー処理
		繰り返し実行を行う．
		デフォルトではid = 0でコールバック
	 */
	virtual void TimerFunc(int id);

	/** @brief 描画領域のサイズ変更
		@param w 描画領域の横幅
		@param h 描画領域の縦幅
		ユーザによってウィンドウサイズが変更されたときなどに呼ばれる．
	 */
	virtual void Reshape(int w, int h);

	/** @brief キーボードイベントのハンドラ
		@param key キーコード
		@param x カーソルｘ座標
		@param y カーソルｙ座標
		特殊キーのキーコードは使用するグラフィクスライブラリに依存する．
		
		＊GLUTの場合，glutKeyboardFuncコールバックとglutSpecialFuncコールバックで
		キーコードが重複している．そこでglutSpecialFuncコールバックに渡されたキーコードには
		256が加算されてKeyboardに渡される．
	 */
	virtual void Keyboard(int key, int x, int y){}

	/** @brief マウスイベントのハンドラ
	 */
	virtual void MouseButton(int button, int state, int x, int y);

	/** @brief マウスイベントのハンドラ
		デフォルトでは左ドラッグで視点変更，右ドラッグでズームイン/アウト
	 */
	virtual void MouseMove(int x, int y);

	/** @brief ジョイスティックのハンドラ
	*/
	virtual void Joystick(unsigned int buttonMask, int x, int y, int z){}

	/** @brief 終了処理ハンドラ
	 */
	virtual void AtExit(){ }

	/** DVKeyMouseHandlerの仮想関数
		デフォルトではFWAppの従来のイベントハンドラを呼びだすのみ．
		こちらを直接オーバライドしてもよい．
	 **/
	virtual bool OnMouse(int button, int state, int x, int y){
		MouseButton(button, state, x, y);
		return true;
	}
	virtual bool OnMouseMove(int button, int x, int y, int zdelta){
		MouseMove(x, y);
		return true;
	}
	virtual bool OnDoubleClick(int button, int x, int y){
		return false;
	}
	virtual bool OnKey(int state, int key, int x, int y){
		Keyboard(key, x, y);
		return true;
	}

	/** @brief GUI系イベントハンドラ
		@param ctrl	更新が生じたコントロール
		更新イベントの発生条件は以下のとおり：
		FWButtonIf:				ボタンが押された
		FWTextBoxIf:			テキストが変更された
		FWRotationControlIf:	回転した
		FWTranslationControlIf:	平行移動した
	 **/
	virtual void OnControlUpdate(FWControlIf* ctrl){}

	/** @brief FWAppインスタンスを取得する */
	static FWApp* GetApp(){ return instance; }

	/** @brief ウィンドウに対応するコンテキストを作る
		@param desc		ディスクリプタ
		@param parent	親ウィンドウ
		ウィンドウを作成する．対応するレンダラは新しく作成され，
		既存のウィンドウが割り当てられていないシーンが関連づけられる．
		parentが指定された場合はparentを親ウィンドウとする子ウィンドウを作成する
	 */
	FWWinIf*	CreateWin(const FWWinDesc& desc = FWWinDesc(), FWWinIf* parent = 0);
	/** @brief ウィンドウの数 */
	int			NWin(){ return (int)wins.size(); }
	
	/**	@brief ウィンドウをIDから探す
		@param wid ウィンドウID
		glutの場合，widはglutGetWindowが返す識別子．
	*/
	FWWinIf*	GetWinFromId(int wid);

	/** @brief ウィンドウを取得する
		@param index 何番目のウィンドウを取得するか
		indexで指定されたウィンドウを取得する．
		DestroyWinを呼ぶとインデックスは変化するので注意が必要．
	 */
	FWWinIf*	GetWin(int index);

	/** @brief 現在のウィンドウを取得する
	*/
	FWWinIf*	GetCurrentWin();

	/** @brief ウィンドウを削除する
	 */
	void DestroyWin(FWWinIf* win);

	/** @brief 現在のウィンドウを設定する
	 */
	void SetCurrentWin(FWWinIf* win);

	/** @brief カレントウィンドウのノーマルプレーンを，再描画の必要に応じてマークする
	 */
	void PostRedisplay();

	/** @brief Ctrl, Shift, Altの状態を返す
		個々の派生クラスで実装される
	 */
	int	GetModifier();
	
	enum{
		TypeNone,	///< アダプタ無し
		TypeGLUT,	///< GLUT
		TypeGLUI,	///< GLUI
	};
	/** @brief 描画の設定
		FWGraphicsHandlerを設定する．最初に必ず呼ぶ．
	 */
	void SetGRHandler(int type);

	/** @brief FWGraphicsHandlerの初期化
		FWGraphicsHandlerの初期化を行う．最初に必ず呼ぶ．
	 */
	/*	SetGRHandlerとGRInitを分離する意味がほとんど無いので，
		こちらの引数でタイプを指定できるようにした．
		GRInitに先立ってSetGRHandlerで選択されている場合はそちらを優先する

		tazz
	 */
	GRDeviceIf* GRInit(); // C# API用. （引数を持つGRInitのみを%ignoreしたいので）
	GRDeviceIf* GRInit(int argc, char* argv[] = NULL, int type = TypeGLUT);

public:
	/**  削除候補API  **/
	/// ウィンドウを1つだけ作成
	void	InitWindow(){ if(!NWin()) CreateWin(); }
	/// 初期状態にする
	void	Clear(){}
	/// リセットする
	void	Reset(){}

};


// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

/** @brief 力覚提示を伴う組み込み用アプリケーション
*/

class FWHapticApp : public FWAppBase {
	unsigned int physicsTimerID, hapticTimerID;

	int cnt = 0;

public:
	FWHapticApp();
	virtual ~FWHapticApp();

	// ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
	// 派生クラスで定義することのできる仮想関数

	/** @brief タイマー処理
	繰り返し実行を行う．
	デフォルトではid = 0でコールバック
	*/
	virtual void TimerFunc(int id);

	// ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
	// その他の関数

	/** @brief タイマーを作成する
	*/
	void CreateTimers();

	/** @brief タイマーを開始する
	*/
	void StartTimers();

	/** @brief 物理シーンをセットする
	*/
	void SetPHScene(PHSceneIf* phScene);

	int GetCount() { return cnt; }

};

//@}
}
#endif
