#pragma once

#include <vector>
#include <fstream>

namespace parsing {
	template<class T>
	auto getVector(const char* filename) {
		std::ifstream inputFile{ filename };

		std::vector<T> ret{};
		T value;

		if (inputFile) {
			while (inputFile >> value) {
				ret.push_back(value);
			}
		}

		return ret;
	}
}
