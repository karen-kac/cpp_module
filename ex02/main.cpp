/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:46:09 by myokono           #+#    #+#             */
/*   Updated: 2025/03/21 17:46:11 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main() {
	// 文字列変数を作成
	std::string stringVAR = "HI THIS IS BRAIN";
	
	// 文字列へのポインタを作成
	std::string* stringPTR = &stringVAR;
	
	// 文字列への参照を作成
	std::string& stringREF = stringVAR;
	
	// メモリアドレスの出力
	std::cout << "メモリアドレス:" << std::endl;
	std::cout << "stringVAR のアドレス: " << &stringVAR << std::endl;
	std::cout << "stringPTR が指すアドレス: " << stringPTR << std::endl;
	std::cout << "stringREF のアドレス: " << &stringREF << std::endl;
	
	// 値の出力
	std::cout << "\n値:" << std::endl;
	std::cout << "stringVAR の値: " << stringVAR << std::endl;
	std::cout << "stringPTR が指す値: " << *stringPTR << std::endl;
	std::cout << "stringREF の値: " << stringREF << std::endl;
	
	// 変数の値を変更して、ポインタと参照の動作を確認
	std::cout << "\n変数の値を変更:" << std::endl;
	stringVAR = "BRAIN HAS BEEN MODIFIED";
	std::cout << "stringVAR の新しい値: " << stringVAR << std::endl;
	std::cout << "stringPTR が指す新しい値: " << *stringPTR << std::endl;
	std::cout << "stringREF の新しい値: " << stringREF << std::endl;
	
	// ポインタを通じて値を変更
	std::cout << "\nポインタを通じて値を変更:" << std::endl;
	*stringPTR = "POINTER MODIFIED THE BRAIN";
	std::cout << "stringVAR の新しい値: " << stringVAR << std::endl;
	std::cout << "stringPTR が指す新しい値: " << *stringPTR << std::endl;
	std::cout << "stringREF の新しい値: " << stringREF << std::endl;
	
	// 参照を通じて値を変更
	std::cout << "\n参照を通じて値を変更:" << std::endl;
	stringREF = "REFERENCE MODIFIED THE BRAIN";
	std::cout << "stringVAR の新しい値: " << stringVAR << std::endl;
	std::cout << "stringPTR が指す新しい値: " << *stringPTR << std::endl;
	std::cout << "stringREF の新しい値: " << stringREF << std::endl;
	
	return 0;
}