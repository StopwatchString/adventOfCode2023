#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main() {
	std::map<std::string, int> translations;
	translations.insert(std::make_pair("one", 1));
	translations.insert(std::make_pair("two", 2));
	translations.insert(std::make_pair("three", 3));
	translations.insert(std::make_pair("four", 4));
	translations.insert(std::make_pair("five", 5));
	translations.insert(std::make_pair("six", 6));
	translations.insert(std::make_pair("seven", 7));
	translations.insert(std::make_pair("eight", 8));
	translations.insert(std::make_pair("nine", 9));

	std::fstream input("input.txt");
	std::string line;
	int sum = 0;
	if (input.is_open()) {
		while (getline(input, line)) {
			// Map of indices to numbers found
			std::map<int, int> map;

			// Parse literal digits
			int idx = 0;
			while (idx < line.size()) {
				if (isdigit(line[idx])) {
					map.insert(std::make_pair(idx, line[idx] - '0'));
				}
				idx++;
			}

			// Parse spelled out digits
			for (auto pair : translations) {
				int pos = line.find(pair.first);
				while (pos != std::string::npos) {
					map.insert(std::make_pair(pos, pair.second));
					// pos becomes our index offset for further finds
					pos = line.find(pair.first, pos + pair.first.size());
				}
			}

			sum += map.begin()->second * 10 + map.rbegin()->second;
		}
	}
	else {
		std::cout << "Couldn't open the file." << std::endl;
		return 1;
	}

	std::cout << sum << std::endl;
	return 0;
}