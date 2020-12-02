#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>

namespace parsing {
	template<class T>
	auto getValue(const std::string& line) {
		T ret;
		std::istringstream ss{ line };
		ss >> ret;
		return ret;
	}
	template<>
	auto getValue<std::string>(const std::string& line) {
		return line;
	}

	template<class T>
	auto getVector(const std::string& filename) {
		std::ifstream inputFile{ filename };

		std::vector<T> ret{};
		T value;

		if (inputFile) {
			std::string line;
			while (std::getline(inputFile, line)) {
				ret.push_back(getValue<T>(line));
			}
		}

		return ret;
	}
}
