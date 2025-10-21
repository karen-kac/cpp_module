# 42 Tokyo C++ Module Collection

## 概要

このリポジトリは、42 TokyoのC++モジュール（cpp00〜cpp09）の実装集です。  
C++98規格に準拠し、オブジェクト指向プログラミングから高度なSTLの活用まで、  
段階的にC++の概念と技術を習得できるように設計されています。

---

## 📚 モジュール一覧

### [cpp00 - C++基礎](./cpp00/)
C++プログラミングの入門モジュール
- **ex00**: Megaphone（文字列処理）
- **ex01**: My Awesome PhoneBook（クラス設計）
- **ex02**: The Job Of Your Dreams（静的メンバ）

### [cpp01 - メモリ管理とポインタ](./cpp01/)
メモリ管理とポインタ・参照の理解
- **ex00**: BraiiiiiiinnnzzzZ（クラス基本）
- **ex01**: Moar brainz!（動的配列）
- **ex02**: HI THIS IS BRAIN（ポインタと参照）
- **ex03**: Unnecessary violence（参照とポインタの使い分け）
- **ex04**: Sed is for losers（ファイル処理）
- **ex05**: Harl 2.0（関数ポインタ）
- **ex06**: Harl filter（switch文）

### [cpp02 - 演算子オーバーロードと固定小数点数](./cpp02/)
演算子オーバーロードと正統カノニカル形式
- **ex00**: My First Class（正統カノニカル形式）
- **ex01**: Towards a more useful fixed-point number class（型変換）
- **ex02**: Now we're talking（演算子オーバーロード）
- **ex03**: BSP（幾何学的計算）

### [cpp03 - 継承](./cpp03/)
オブジェクト指向の継承概念
- **ex00**: Aaaaand... OPEN!（基本クラス）
- **ex01**: Serena, my love!（単一継承）
- **ex02**: Repetitive work（継承の活用）
- **ex03**: Now it's weird!（多重継承）

### [cpp04 - ポリモーフィズム](./cpp04/)
多態性と抽象クラス
- **ex00**: Polymorphism（仮想関数）
- **ex01**: I don't want to set the world on fire（深いコピー）
- **ex02**: Abstract class（抽象クラス）
- **ex03**: Interface & recap（インターフェース）

### [cpp05 - 例外処理](./cpp05/)
例外処理と官僚シミュレーター
- **ex00**: Bureaucrat（例外処理基本）
- **ex01**: Form（書類クラス）
- **ex02**: AFormと具体的なフォーム（抽象クラス）
- **ex03**: Intern（動的オブジェクト生成）

### [cpp06 - 型変換とRTTI](./cpp06/)
型変換、シリアライゼーション、実行時型情報
- **ex00**: Convert scalar types（型変換）
- **ex01**: Serialize data!（シリアライゼーション）
- **ex02**: Identify real type（RTTI）

### [cpp07 - テンプレート](./cpp07/)
ジェネリックプログラミング
- **ex00**: A few functions（関数テンプレート）
- **ex01**: Iter（イテレーション）
- **ex02**: Array（クラステンプレート）

### [cpp08 - STLコンテナ](./cpp08/)
標準テンプレートライブラリの基本
- **ex00**: Easy find（STL検索）
- **ex01**: Span（動的配列）
- **ex02**: Mutated abomination（高度なSTL）

### [cpp09 - STLアルゴリズム](./cpp09/)
高度なアルゴリズムとパフォーマンス
- **ex00**: Bitcoin Exchange（ファイル処理）
- **ex01**: RPN Calculator（スタック）
- **ex02**: PmergeMe（Ford-Johnsonソート）

---

## 🛠 開発環境

- **コンパイラ**: C++ (g++ または clang++)
- **規格**: C++98
- **コンパイルフラグ**: `-Wall -Wextra -Werror -std=c++98`
- **OS**: macOS, Linux

---

## 📋 共通ルール

### コンパイルルール
- C++98準拠で開発
- `-Wall -Wextra -Werror` オプション必須
- メモリリークの回避

### 禁止事項
- `printf`, `malloc`, `free` の使用禁止
- `using namespace` の使用禁止
- `friend` キーワードの使用禁止（明示的に許可されていない限り）
- STLの使用はModule 08以降のみ許可

### コーディング規約
- クラス名は `UpperCamelCase`
- ヘッダファイルは `.hpp` 拡張子
- 実装ファイルは `.cpp` 拡張子
- インクルードガードの必須実装
- 正統カノニカル形式の遵守

---

## 🚀 クイックスタート

### 特定のモジュールを実行

```bash
# 例: cpp00のex00を実行
cd cpp00/ex00
make
./megaphone "Hello World"
```

### 全モジュールのビルド

```bash
# 各ディレクトリで個別にビルド
for dir in cpp*/ex*; do
    if [ -f "$dir/Makefile" ]; then
        echo "Building $dir..."
        (cd "$dir" && make)
    fi
done
```

### クリーンアップ

```bash
# 全オブジェクトファイルと実行ファイルを削除
for dir in cpp*/ex*; do
    if [ -f "$dir/Makefile" ]; then
        (cd "$dir" && make fclean)
    fi
done
```

---

## 📖 学習の進め方

### 段階的学習
1. **cpp00-01**: C++の基本概念とメモリ管理
2. **cpp02-03**: オブジェクト指向の基本（継承、演算子オーバーロード）
3. **cpp04-05**: 高度なオブジェクト指向（ポリモーフィズム、例外処理）
4. **cpp06-07**: 型システムとテンプレート
5. **cpp08-09**: STLとアルゴリズム

### 各モジュールの学習ポイント
- **理論の理解**: 各概念の背景と目的を理解
- **実装の習得**: 実際にコードを書いて動作を確認
- **デバッグ技術**: エラーの原因と解決方法を学ぶ
- **最適化**: パフォーマンスとメモリ使用量の改善

---
