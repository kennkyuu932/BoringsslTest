# BoringsslTest

[boringssl](https://boringssl.googlesource.com/boringssl)をAndroidアプリに組み込むためのテストプロジェクト

自分用メモ

現状とこれからやること

2023/07/06

WSL 2を使ってboringsslをビルドしsoファイルを生成．

Activity内で読み込みはできたと感じているため，どうやって使うのかを確認していく．

2023/07/05

boringsslのビルドとAndroid Studioの設定まで行った．

今後はboringsslのライブラリをどのようにしてjavaコードと組み合わせるのか，何ができるのかを確認していく予定．

---

実行環境

- Windows 11
- Android Studio 2022.2.1 flamingo

使用したソフトウェア

- [WSL 2](https://learn.microsoft.com/ja-jp/windows/wsl/)
- [CMake](https://cmake.org/)
- [Ninja](https://ninja-build.org/)
- [go](https://golang.org/dl/)

---

boringsslのビルド

gitを使ってboringsslをクローンする

`git clone https://boringssl.googlesource.com/boringssl`

boringsslディレクトリの中にbuildディレクトリを作成し，boringsslディレクトリにて以下のコマンドを実行．

`cmake -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-31 -DCMAKE_TOOLCHAIN_FILE={$NDK_PATH}/build/cmake/android.toolchain.cmake -GNinja -B build -DBUILD_SHARED_LIBS=ON `

一つ目のオプション`-DANDROID_ABI=arm64-v8a`はAndroidデバイスのCPUアーキテクチャによって`arm64-v8a`や，`armeabi-v7a`などになる．

`{$NDK_PATH}`にはndkのパスを代入する．

最後のオプションである`DBUILD_SHARED_LIBS=ON`をOFFまたは記述しないとき，最終的に生成されるライブラリファイルがaファイルになる．ONであるときには最終的にはsoファイルが生成される．

上記のコマンドが正常に終了した後，以下のコマンドを実行する．

`ninja -C build`

作成したbuildディレクトリ内のcrypto,decrepit,sslディレクトリ内にそれぞれ `libcrypto.so` `libdecrepit.so` `libssl.so` ファイルが生成される．

---

Android Studio

プロジェクトを作成し，app/src/main/jniLibsとなるようにjniLibsディレクトリを作成．

作成したjniLibsディレクトリにlibcrypto.so,libdecrepit.so,libssl.soを配置する．

app/build.gradleファイルにビルド設定に関する記述を追加．(build.gradle参照)

MainActivity.javaファイルにstatic{}を記述し，その中でライブラリを読み込む．

---

以下windowsのみで行った失敗

実行環境

- windows 11
- Android Studio 2022.2.1 flamingo

使用したソフトウェア

- [git](https://git-scm.com/)
- [CMake](https://cmake.org/)
- [Strawberry Perl](https://strawberryperl.com/)
- [NASM](https://www.nasm.us/)
- [Visual Studio 2022](https://visualstudio.microsoft.com/ja/)

---

boringsslのビルド

gitを使ってboringsslをクローンする

`git clone https://boringssl.googlesource.com/boringssl`

boringsslディレクトリの中にbuildディレクトリを作成し，buildディレクトリに移動して以下のコマンドを実行

`cmake -G "Visual Studio 17 2022" -A x64 ..`

正常に動作するとbuildディレクトリ内にBoringSSL.slnファイルが存在する．

BoringSSL.slnをVisualStudioで開き，VisualStudio内のBoringSSLを右クリックし，ソリューションのビルドを選択．

ビルドが成功すると，build/crypt/Debug/crypto.libとbuild/ssl/ssl.libが存在する．

上記の二つのファイルを用いてAndroidStudioでboringsslを使用する．

---

Android Studio

プロジェクトを作成し，app/src/main/jniLibsとなるようにjniLibsディレクトリを作成．

作成したjniLibsディレクトリにcrypt.lib,ssl.libを配置する．

app/build.gradleファイルにビルド設定に関する記述を追加．(build.gradle参照) 