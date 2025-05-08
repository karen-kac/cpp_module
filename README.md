# 📘 C++ Module 03 - `cpp03`

このモジュールでは、C++ における「継承（Inheritance）」の基本を学びます。  
ベースクラスと派生クラスの関係、コンストラクタとデストラクタの呼び出し順、  
多重継承における設計と注意点など、オブジェクト指向設計の土台となる概念を実装します。

---

## 🔧 コンパイルルール

- `-Wall -Wextra -Werror -std=c++98` を付けてコンパイル
- `printf`, `malloc`, `free` 使用禁止
- `using namespace` や `friend` キーワードは禁止
- STL は Module 08 以降でのみ使用可
- ヘッダファイルには include guard を忘れずに

---

## 📁 各課題概要

### 🧩 ex00 - Aaaaand... OPEN!

- **目的**：基本クラス `ClapTrap` の作成
- **属性**：
  - `name`（コンストラクタ引数）
  - `hitPoints = 10`
  - `energyPoints = 10`
  - `attackDamage = 0`
- **関数**：
  - `attack(const std::string& target)`
  - `takeDamage(unsigned int amount)`
  - `beRepaired(unsigned int amount)`
- **仕様**：
  - 攻撃や修理はエネルギーを1消費
  - 残りHPやエネルギーがない場合は行動できない
  - 各関数やコンストラクタ・デストラクタは動作ログを表示

---

### 🧩 ex01 - Serena, my love!

- **目的**：`ClapTrap` を継承した `ScavTrap` の作成
- **属性の初期値**（上書き）：
  - `hitPoints = 100`
  - `energyPoints = 50`
  - `attackDamage = 20`
- **追加関数**：
  - `guardGate()`：Gate keeper モードへの移行を表示
- **注意点**：
  - コンストラクタとデストラクタの**チェーン呼び出し順序**をログで確認
  - `attack()` はオーバーライドして独自の出力を持つ

---

### 🧩 ex02 - Repetitive work

- **目的**：`FragTrap` クラスの作成（`ClapTrap` を継承）
- **属性の初期値**：
  - `hitPoints = 100`
  - `energyPoints = 100`
  - `attackDamage = 30`
- **追加関数**：
  - `highFivesGuys()`：ポジティブなハイタッチ要求を表示
- **注意点**：
  - 出力メッセージは `ScavTrap` とは別物にすること
  - クラストレースログで構築・破棄の順序を確認

---

### 🧩 ex03 - Now it’s weird!

- **目的**：多重継承の実践、`DiamondTrap` クラスの作成
- **継承**：
  - `FragTrap` と `ScavTrap` を多重継承（※ともに `ClapTrap` を継承）
- **属性**：
  - `std::string name;`（DiamondTrap自身の名前）
  - `ClapTrap::name` は `"DiamondTrapName_clap_name"` としてセット
  - `hitPoints = FragTrap` の値を継承
  - `energyPoints = ScavTrap` の値を継承
  - `attackDamage = FragTrap` の値を継承
- **関数**：
  - `attack()` → ScavTrap のものを使用
  - `whoAmI()`：自身の名前と ClapTrap 名を表示
- **注意点**：
  - `ClapTrap` は1回だけ構築されるべき（仮想継承は使用しない）
  - `-Wshadow` / `-Wno-shadow` フラグを用いた影響もチェック可
  - この課題はスキップしてもモジュールの合格には影響しない

---

## ✅ 提出時の確認事項

- クラス名・ファイル名はすべて課題通りに命名されているか？
- Makefile で `make`, `make clean`, `make fclean`, `make re` が動作するか？
- メモリリーク（`valgrind`）の確認済みか？
- 出力メッセージが全てのアクションで明確に表示されているか？


