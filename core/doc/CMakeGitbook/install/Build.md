## ビルド

ライブラリのビルドについては特に説明することはありません。

**Windows の場合**

ディレクトリ *build* へ移動して "Springhead.sln" を Visual Studio で実行し、
プロジェクト Springhead をビルドしてください。
[ビルドの準備](/install/Preparation.md) でインストール先を指定していなければ、
ライブラリファイルは "C:/Springhead/generated/lib/&lt;*arch*&gt;" に生成されます。
&lt;*arch*&gt; はマシンのアーキテクチャに従い、
"win64" または "win32" のいずれかです。

**unix の場合**

ディレクトリ *build* へ移動して make コマンドを実行してください。
[ビルドの準備](/install/Preparation.md) でインストール先を指定していなければ、
ライブラリファイルは "C:/Springhead/generated/lib" に生成されます。

