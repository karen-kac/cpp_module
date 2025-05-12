# C++ Module 00

このリポジトリはC++プログラミングの基礎を学ぶための課題「Module 00」の実装です。C++98規格に準拠し、オブジェクト指向プログラミングの概念を学ぶ最初のステップとなります。

## 開発環境

- コンパイラ: C++ (g++ または clang++)
- コンパイルフラグ: `-Wall -Wextra -Werror -std=c++98`
- 対応規格: C++98

## プロジェクト構成

本プロジェクトは以下の3つの課題（Exercise）で構成されています：

### Exercise 00: Megaphone
標準入力から受け取ったテキストを大文字に変換して表示するシンプルなプログラム。

### Exercise 01: My Awesome PhoneBook
最大8件の連絡先情報を保持できる電話帳プログラム。連絡先の追加、検索、表示機能を提供します。

### Exercise 02: The Job Of Your Dreams
銀行口座の取引を処理し、表示するプログラム。与えられたヘッダファイルとテストファイルに対して、実装ファイルを再構築します。

## ビルドと実行方法

各課題はそれぞれのディレクトリにあり、独自のMakefileが含まれています。

### Exercise 00: Megaphone

```bash
cd ex00
make
./megaphone "shhhhh... I think the students are asleep..."
```

出力例:
```
SHHHHH... I THINK THE STUDENTS ARE ASLEEP...
```

引数なしで実行した場合:
```bash
./megaphone
```

出力:
```
* LOUD AND UNBEARABLE FEEDBACK NOISE *
```

### Exercise 01: My Awesome PhoneBook

```bash
cd ex01
make
./phonebook
```

使用可能なコマンド:
- `ADD`: 新しい連絡先を追加
- `SEARCH`: 保存された連絡先を検索・表示
- `EXIT`: プログラムを終了

### Exercise 02: The Job Of Your Dreams

```bash
cd ex02
make
./account
```

## 技術的詳細

### Exercise 00: Megaphone
- C++の基本的な入出力の扱い方
- 文字列処理（大文字変換）

### Exercise 01: My Awesome PhoneBook
- クラスとオブジェクトの定義
- カプセル化（private/publicメンバ）
- クラス間のインタラクション
- 文字列操作と表示整形

### Exercise 02: The Job Of Your Dreams
- 静的メンバ変数と静的メソッド
- クラスの継承と構成
- 日時の取り扱い
- フォーマット出力

## コーディング規約

- クラス名は `UpperCamelCase` で記述
- クラス定義のヘッダファイルは `.hpp` 拡張子を使用
- すべての出力は改行 (`\n`) で終了
- `using namespace <ns_name>` および `friend` キーワードの使用は禁止
- メモリリークを防ぐため、`new` と `delete` は適切にペアで使用

## 制限事項

- `printf()`, `malloc()`, `free()` の使用は禁止
- 標準ライブラリ（STL）は使用禁止（Module 08, 09を除く）
- C++98規格に準拠すること

## クリーンアップ

各ディレクトリで以下のコマンドを実行することで、オブジェクトファイルと実行ファイルを削除できます：

```bash
make clean    # オブジェクトファイルを削除
make fclean   # オブジェクトファイルと実行ファイルを削除
make re       # 全てを削除して再ビルド
```