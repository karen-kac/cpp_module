# C++ Module 05 - 官僚シミュレーター

このモジュールでは、**例外処理**、**抽象クラス**、**オブジェクト指向設計**に焦点を当て、  
C++98 標準に基づいて、官僚制度を模したクラス群を実装します。

## 📦 課題構成

- [ex00 - Bureaucrat（官僚クラス）](#ex00---bureaucrat官僚クラス)
- [ex01 - Form（書類クラス）](#ex01---form書類クラス)
- [ex02 - AFormと具体的なフォーム](#ex02---aformと具体的なフォーム)
- [ex03 - Intern（インターン）](#ex03---internインターン)
- [ビルド方法](#ビルド方法)
- [使い方](#使い方)
- [制約ルール](#制約ルール)

---

## ex00 - Bureaucrat（官僚クラス）

`Bureaucrat` クラスを実装します：

- 名前（定数文字列）と等級（グレード）を持つ
- グレードは 1（最高）〜150（最低）の範囲
- `incrementGrade()` / `decrementGrade()` で昇格・降格可能（例外処理付き）
- `GradeTooHighException` / `GradeTooLowException` を実装
- `<<` 演算子をオーバーロードして表示形式を整える

---

## ex01 - Form（書類クラス）

`Form` クラスを実装します：

- 名前、署名状態、署名に必要なグレード、実行に必要なグレードを持つ
- `beSigned()` 関数で、適切な官僚によって署名される
- 条件を満たさなければ例外を投げる
- `Bureaucrat::signForm()` を追加し、署名成功/失敗を出力

---

## ex02 - AFormと具体的なフォーム

`Form` を抽象クラス `AForm` にリファクタリングし、以下の具象クラスを実装します：

- `ShrubberyCreationForm`：ターゲット名に応じたファイルにASCIIアートの木を出力
- `RobotomyRequestForm`：50%の確率でロボトミーに成功/失敗のメッセージを出力
- `PresidentialPardonForm`：Zaphod Beeblebrox による恩赦のメッセージを出力

各フォームは `execute()` 関数を実装し、実行には以下が必要です：

- 書類が署名済みであること
- 官僚の実行グレードが条件を満たすこと

`Bureaucrat` クラスには `executeForm()` を追加し、実行ログを出力します。

---

## ex03 - Intern（インターン）

`Intern` クラスを実装します：

- 名前・グレードなどの属性は一切なし
- `makeForm(formName, target)` 関数で動的に `AForm*` を生成
- 対応するフォームが存在しない場合は明確にエラーメッセージを出力
- `if / else` を多用したコードは禁止。関数ポインタ配列などでスマートに実装すること

対応するフォーム名：
- `"shrubbery creation"`
- `"robotomy request"`
- `"presidential pardon"`

---

## 🛠 ビルド方法

```bash
cd ex0X/
make        # コンパイル
make fclean # クリーンアップ
./main      # 実行
