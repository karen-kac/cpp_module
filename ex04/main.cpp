#include <iostream>
#include <fstream>
#include <string>

std::string replaceAll(const std::string& str, const std::string& from, const std::string& to)
{
	std::string result = str;
	size_t pos = 0;
	
	while ((pos = result.find(from, pos)) != std::string::npos)
	{
		result = result.substr(0, pos) + to + result.substr(pos + from.length());
		pos += to.length();
	}
	return result;
}

int main(int argc, char* argv[])
{
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		return 1;
	}
	
	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];
	
	if (s1.empty()) {
		std::cerr << "Error: s1 cannot be empty" << std::endl;
		return 1;
	}

	std::ifstream inFile(filename.c_str());
	if (!inFile.is_open()) {
		std::cerr << "Error: Could not open input file " << filename << std::endl;
		return 1;
	}

	std::string outFilename = filename + ".replace";
	std::ofstream outFile(outFilename.c_str());
	if (!outFile.is_open()) {
		std::cerr << "Error: Could not create output file " << outFilename << std::endl;
		inFile.close();
		return 1;
	}

	std::string line;
	while (std::getline(inFile, line)) {
		outFile << replaceAll(line, s1, s2);
		if (!inFile.eof()) {
			outFile << std::endl;
		}
	}
	inFile.close();
	outFile.close();
	
	std::cout << "Replacement completed. Output saved to " << outFilename << std::endl;
	
	return 0;
}

// test
// echo "Hello World! This is a test file." > hello.txt
// ./replace hello.txt "World" "Universe"