Creatureモジュールは，物理シミュレータを用いてバーチャルクリーチャ（自律動作するキャラクタ）を作成する機能を提供します．Springheadの物理シミュレーション機能は，人間・動物・キャラクタ・ロボット等の身体動作をシミュレーションすることにおいても利用価値があります．剛体・関節系で身体モデルを作成し，関節に組み込まれた制御機能や関節系のIK機能を用いて身体動作を生成することができます．物理シミュレータ内の情報（物体の運動・形状・接触力等）を利用してバーチャルな感覚（センサ）情報の生成もできます．感覚・制御のループを回すことで自律動作するキャラクタやロボットが実現できます．こうしたバーチャルなキャラクタ・ロボット等を総称して，バーチャルクリーチャ（Creature : 生き物）と呼びます．
## Creatureモジュールの構成
下図にCreatureモジュールのシーンツリー構造を示します。
```c++
CRSdk
+-- CRCreature
|   +-- CRBody
|   |   +-- CRBone
|   +-- CREngine (CRSensor, CRController)
```
*CRSdk*はCreatureの機能を使用する根本となるオブジェクトです。
```c++
CRSdkIf* crSdk = CRSdkIf::CreateSdk();
```
*CRCreature*は，バーチャルクリーチャ*1*体分の機能を統括するオブジェクトです．身体、感覚器、制御器を有しています．CRCreatureDescには特に設定すべき項目はありません。
```c++
CRCreatureIf* crCreature = crSdk->CreateCreature(
  CDCreatureIf::GetIfInfoStatic(), CRCreatureDesc());
```
CRCreatureを作成したら、物理シミュレーションのシーンと関連づけるために、PHSceneを子オブジェクトとしてセットしてください。
```c++
// PHSceneIf* phScene;   // should be taken from somewhere
crCreature->AddChildObject(phScene);
```
シミュレーション実行時は、1ステップに1回、CRCreatureのStepを呼んでください。これを呼ぶとCreatureが持つ各EngineのStepが実行されます。
```c++
// Every time after simulation step
crCreature.Step();
```

### 身体
*CRBody*は，バーチャルクリーチャの身体モデルを統括します．身体モデルは身体構成部品の集合体です．
```c++
CDBodyIf* crBody = crCreature->CreateBody(
  CRBodyIf::GetIfInfoStatic(), CRBodyDesc());
```
*CRBone*は，身体構成部品ひとつひとつに対応するオブジェクトです．剛体と関節、IKのためのアクチュエータ（場合によってはエンドエフェクタ）をセットにしたものです。
```c++
CRBoneIf* crBone = crBody->CreateObject(
  CDBoneIf::GetIfInfoStatic(), CRBoneDesc());
```
CRBoneに関連づけるべきオブジェクトはすべて子オブジェクトとしてください。
```c++
// このBoneに対応する剛体
// PHSolidIf* phSolid; 
crBone->AddChildObject(phSolid);

// このBoneを親Boneに接続する関節。Root Boneの場合は存在しないので追加不要。
// PHJointIf* phJoint;
crBone->AddChildObject(phJoint);

// IKのエンドエフェクタ（手先など）である場合は対応するPHIKEndEffector
// PHIKEndEffectorIf* phIKEEff;
crBone->AddChildObject(phIKEEff);

// phJointに対応するIKアクチュエータ
// PHIKActuatorIf* phIKAct;
crBone->AddChildObject(phIKAct);
```

### 感覚器
感覚器(CRSensor)はCREngineの一種です。*CREngine*は，バーチャルクリーチャのステップ処理の実行主体です．*CRCreature*の*Step*関数が1回呼ばれるたびに，*CRCreature*が保持する全ての*CREngine*の*Step*関数が順に実行されます．CRSensorには視覚（CRVisualSensor）、触覚（CRTouchSensor）があります。\paragraph{視覚}視野内にある剛体を1Stepごとにリストアップする機能です。
```c++
// 設定
CRVisualSensorDesc descVisualSensor;
/// 視野の大きさ： 水平角度，垂直角度
descVisualSensor.range = Vec2d(Rad(90), Rad(60));
// 中心視野の大きさ： 水平角度，垂直角度
descVisualSensor.centerRange = Vec2d(Rad(10), Rad(10));
// 視覚センサを対象剛体に貼り付ける位置・姿勢
descVisualSensor.pose = Posed();
// この距離を越えたものは視野外        
descVisualSensor.limitDistance = 60;	

// 作成
CRVisualSensorIf* crVisualSensor = crCreature->CreateEngine(
  CRVisualSensorIf::GetIfInfoStatic(), descVisualSensor);
```
視覚情報を読み出すには NVisibles() と GetVisible(int n) を用います。視覚情報を利用する前には必ずUpdateを実行してください。Updateを実行すると視覚情報が最新のStepに基づく情報に更新されます。
```c++
crVisualSensor->Update();
for (int i=0; i<crVisualSensor->NVisibles(); ++i) {
	CRVisualInfo info = crVisualSensor->GetVisible(i);
	// 可視剛体一個分の視覚情報
	info.posWorld;    // 可視剛体のワールド座標
	info.posLocal;    // 頭を基準とした可視剛体のローカル座標
	info.velWorld;    // 速度
	info.velLocal;    // ローカル座標での速度
	info.angle;       // 視野中心から剛体までの視角（たぶん）
	info.solid;       // 可視剛体
	info.solidSensor; // 視覚センサ剛体（頭とか目とか）
	info.sensorPose;  // 視覚センサ剛体の位置・姿勢（たぶん）
	info.bMyBody;     // 自分の身体を構成する剛体であればtrue
	info.bCenter;     // 中心視野に入っていればtrue
}
```

### 制御器
*CRController*は*CREngine*の一種で，バーチャルクリーチャの身体制御を担当します．実際の制御機能は*CRController*を継承した各クラスが担当します．到達運動制御、眼球運動制御などがあります。
