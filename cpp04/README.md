# C++ Module 04 - Subtype Polymorphism, Abstract Classes, and Interfaces

## 目次

- [概要](#概要)
- [ルール](#ルール)
- [課題一覧](#課題一覧)
  - [ex00: Polymorphism](#ex00-polymorphism)
  - [ex01: I don’t want to set the world on fire](#ex01-i-dont-want-to-set-the-world-on-fire)
  - [ex02: Abstract class](#ex02-abstract-class)
  - [ex03: Interface & recap](#ex03-interface--recap)
- [提出と評価](#提出と評価)

---

## 概要

C++ Module 04では、**ポリモーフィズム（多態性）**、**抽象クラス**、**インタフェース** の概念を学びます。  
継承と仮想関数の使い方を通して、動的ディスパッチの仕組みや、抽象化の手法を理解します。

---

## ルール

- コンパイルは `c++ -Wall -Wextra -Werror -std=c++98` を使用。
- C++98準拠で記述。
- STLコンテナや `<algorithm>` などは **使用禁止**（Module08以降で使用可）。
- `printf`, `malloc`, `free` も禁止。
- `using namespace`, `friend` の使用は禁止（明示的に許可されていない限り）。
- メモリリークを避けること（`new` で確保したら `delete` を忘れずに）。
- クラスは正統カノニカルフォーム（Canonical Form）で設計。
- すべてのヘッダーファイルは単独でインクルード可能にし、インクルードガードを必ず追加すること。

---

## 課題一覧

### ex00: Polymorphism

**概要**:  
- `Animal` 基底クラスを定義し、`Dog`, `Cat` を継承。
- `makeSound()` は仮想関数にし、各クラスでオーバーライド。
- `WrongAnimal`, `WrongCat` も定義し、仮想関数がない場合の挙動を確認。

**要件**:
- すべてのコンストラクタ・デストラクタでメッセージを出力。
- `main.cpp` で多態性を使った動作を確認。
- `getType()`, `makeSound()` を適切に定義。

---

### ex01: I don’t want to set the world on fire

**概要**:  
- `Brain` クラスを追加（`std::string ideas[100]`）。
- `Dog`, `Cat` に `Brain*` を持たせ、`new`/`delete` で動的に管理。
- `Animal*` 配列に `Dog`, `Cat` を交互に入れ、`delete` で正しくデストラクタが呼ばれるか確認。

**要件**:
- メモリリークチェックを行うこと。
- ディープコピーの実装（浅いコピー禁止）。

---

### ex02: Abstract class

**概要**:  
- `Animal` クラスを抽象クラスに変更（インスタンス化不可にする）。

**要件**:
- 純粋仮想関数 `makeSound()` の導入などで抽象化を行う。
- それ以外の挙動は `ex01` と同様。

---

### ex03: Interface & recap

**概要**:  
- `AMateria`, `Ice`, `Cure`, `Character`, `MateriaSource` クラスを実装。
- `AMateria` は純粋仮想関数 `clone()`, `use()` を持つ抽象クラス。
- `ICharacter`, `IMateriaSource` はインタフェースとして使用。
- キャラクターは最大4つのマテリアを装備できる。

**要件**:
- `Character` のコピー操作はディープコピーにする。
- `MateriaSource` は最大4種類のマテリアを学習し、名前から生成できるようにする。
- `unequip()` はメモリを解放しないが、メモリリークを避けるように設計。

