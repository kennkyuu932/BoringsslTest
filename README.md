# BoringsslTest

boringssl[https://boringssl.googlesource.com/boringssl]をAndroidアプリに組み込むためのテストプロジェクト

自分用メモ

実行環境

- windows 11
- Android Studio 2022.2.1 flamingo

使用したソフトウェア

- git [https://git-scm.com/]
- CMake [https://cmake.org/]
- Strawberry Perl [https://strawberryperl.com/]
- NASM [https://www.nasm.us/]
- Visual Studio 2022 [https://visualstudio.microsoft.com/ja/]

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