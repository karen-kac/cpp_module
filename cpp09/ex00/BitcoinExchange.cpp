#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _rates(other._rates) {}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) _rates = other._rates;
	return *this;
}
BitcoinExchange::~BitcoinExchange() {}

// CSVの読み込み
void BitcoinExchange::loadDatabase(const std::string& filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");

	std::string line;
	std::getline(file, line); // 1行目ヘッダをスキップ
	while (std::getline(file, line)) {
		std::stringstream ss(line); // stringstreamを使用するのはカンマで分割するため
		std::string date, rateStr;
		if (std::getline(ss, date, ',') && std::getline(ss, rateStr)) {
			double rate = atof(rateStr.c_str());
			_rates[date] = rate;
		}
	}
}

// 入力ファイル処理
void BitcoinExchange::processInput(const std::string& filename) const {
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line); // ヘッダをスキップ
	
	// ファイルが空の場合のチェック
	if (file.eof()) {
		std::cerr << "Error: input file is empty." << std::endl;
		return;
	}
	
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string date, valueStr;

		if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr)) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		// trim
		date.erase(0, date.find_first_not_of(" \t"));
		date.erase(date.find_last_not_of(" \t") + 1);
		valueStr.erase(0, valueStr.find_first_not_of(" \t"));
		valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

		// 日付チェック
		if (!isValidDate(date)) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		// 値チェック
		double value;
		if (!isValidValue(valueStr, value))
			continue;

		// レート取得
		try {
			double rate = getRateForDate(date);
			std::cout << date << " => " << value << " = " << value * rate << std::endl;
		} catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
}

// 日付フォーマット確認
bool BitcoinExchange::isValidDate(const std::string& date) const {
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	
	// 年、月、日の各桁が数字かチェック
	for (int i = 0; i < 10; i++) {
		if (i == 4 || i == 7) continue;
		if (!std::isdigit(date[i])) return false;
	}
	
	// 年、月、日を抽出
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	
	// 月の範囲チェック
	if (month < 1 || month > 12) return false;
	
	// 日の範囲チェック（簡易版）
	if (day < 1 || day > 31) return false;
	
	// より厳密には各月の日数チェックも必要
	static const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int max_day = days_in_month[month - 1];
	
	// うるう年のチェック
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		max_day = 29;
	
	if (day > max_day) return false;
	
	return true;
}

// 値チェック
bool BitcoinExchange::isValidValue(const std::string& valueStr, double& value) const {
	std::stringstream ss(valueStr);
	ss >> value;
	if (ss.fail()) {
		std::cerr << "Error: bad input => " << valueStr << std::endl;
		return false;
	}
	if (value < 0) {
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (value > 1000) {
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
}

// 日付に対応するレートを取得
double BitcoinExchange::getRateForDate(const std::string& date) const {
	std::map<std::string, double>::const_iterator it = _rates.lower_bound(date); // lower_boundはdateより大きい最初の要素を返す
	if (it == _rates.end()) {
		--it; // 一番近い過去の日付
	} else if (it->first != date) {
		if (it == _rates.begin())
			throw std::runtime_error("Error: no earlier date in DB.");
		--it;
	}
	return it->second;
}
