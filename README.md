# C++ Module 02 - Fixed-point Arithmetic & Orthodox Canonical Form

## 概要

このモジュールでは、以下の3つの主要なC++の概念を学びます：

- **Ad-hoc polymorphism（演算子オーバーロード）**
- **Orthodox Canonical Form（正統カノニカル形式）**
- **固定小数点数の扱い**

このモジュールを通じて、C++特有の演算子オーバーロードの使い方、クラス設計における正統な形式、浮動小数点に代わる数値表現方法である「固定小数点数」の扱いを習得します。

---

## ルール

- C++98 準拠で開発すること
- `-Wall -Wextra -Werror` オプションを用いてコンパイル
- STLの使用は禁止（Module 08以降のみ許可）
- `printf`, `malloc`, `free` などのC関数は禁止
- `using namespace` や `friend` の使用も禁止

---

## 正統カノニカル形式（Orthodox Canonical Form）

すべてのクラスは以下の4つの関数を必ず実装すること：

1. デフォルトコンストラクタ
2. コピーコンストラクタ
3. コピー代入演算子（`operator=`）
4. デストラクタ

---

## 各課題の概要

### ex00 - My First Class in Orthodox Canonical Form

- 固定小数点数（固定ビット数：8）の基本クラス `Fixed` を実装
- `getRawBits()` / `setRawBits()` を用いた内部値の取得・設定
- 正統カノニカル形式を満たすこと

### ex01 - Towards a more useful fixed-point number class

- int・float からのコンストラクタ追加
- `toFloat()`, `toInt()` による変換機能
- `<<` 演算子のオーバーロードによる出力対応

### ex02 - Now we’re talking

- 演算子のオーバーロード（比較、算術、インクリメント/デクリメント）
- `min()` / `max()` の静的関数実装（const / 非const 両方）

### ex03 - BSP（Binary Space Partitioning）

- `Fixed` を活用した `Point` クラスを実装
- `bsp()` 関数で点が三角形内に存在するかを判定
- 三角形の辺上または頂点上は「外側」として扱う

