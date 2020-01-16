## ビルドの準備

ダウンロードが済んだら "C:/Springhead/core/src" に移動してください。

配布されたファイル "CMakeLists.txt.Lib.dist" を "CMakeLists.txt" という名前で
コピーします。

```
> chdir C:/Springhead/core/src
> copy CMakeLists.txt.Lib.dist CMakeLists.txt
```

配布されたビルド条件で構わないのであれば、これで準備は終了です。
[ビルド](/install/Build.md) へ進んでください。

独自にインストールしたパッケージ boost, glew, glut, glui を使用する場合
およびライブラリファイルとヘッダファイルのインストール先を指定する場合には、
配布されたファイル "CMakeConf.txt.dist" を "CMakeConf.txt" という名前でコピーして
必要な編集をします。
編集の方法は "CMakeConf.txt" に記述されています。

```CMake
> copy CMakeConf.txt.dist CMakeConf.txt
> edit CMakeConf.txt
　　:
set(CMAKE_PREFIX_PATH "C:/somewhere/appropreate")
#　　　　　　　　(use absolute path)
#　　　　　　　　(multiple paths must be separated by 'space', 'newline' or 'semicolon')
　　:
set(SPRINGHEAD_INCLUDE_PREFIX       "C:/somewhere/appropreate")
set(SPRINGHEAD_LIBRARY_DIR_DEBUG    "C:/somewhere/appropreate")
set(SPRINGHEAD_LIBRARY_DIR_RELEASE  "C:/somewhere/appropreate")
```

> 変数 variable に値 value を設定するには set(variable "value") とします。
途中に空白やセミコロンを含まない文字列ならば引用符は省略できます。
また、${variable} とすると他の変数の値を、
$ENV{variable} とすると環境変数の値を参照できます。
文字 '#' 以降はコメントです。

コンパイル及びリンクのオプションはファイル "CMakeOpts.txt.dist" に設定されています。
これらのオプションを変更するときは、配布されたファイル "CMakeOpts.txt.dist" を
"CMakeOpts.txt" という名前でコピーして必要な編集をします。

```
> copy CMakeOpts.txt.dist CMakeOpts.txt
> edit CMakeOpts.txt
　　:
```

以上で準備作業は終了です。
