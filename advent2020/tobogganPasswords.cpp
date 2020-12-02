#include "tobogganPasswords.h"

#include <algorithm>

namespace {
	auto schemeFirstNumber(const std::string& p) {
		return static_cast<size_t>(std::atoi(p.c_str()));
	}
	auto schemeSecondNumber(const std::string& p) {
		return static_cast<size_t>(std::atoi(p.substr(p.find('-') + 1).c_str()));
	}
	auto targetChar(const std::string& p) {
		return p.substr(p.find(' ') + 1, p.find(':'))[0];
	}
	auto rawPassword(const std::string& p) {
		return p.substr(p.find(':') + 1);
	}
	auto countTargetInstances(const std::string& p, char target) {
		return static_cast<size_t>(std::count(std::begin(p), std::end(p), target));
	}
}

namespace advent2020::tobogganPasswords {
	bool passwordValidOldScheme(const std::string& password) {
		auto min{ schemeFirstNumber(password) };
		auto max{ schemeSecondNumber(password) };
		auto target{ targetChar(password) };
		auto raw{ rawPassword(password) };

		size_t count{ countTargetInstances(raw, target) };
		return count >= min && count <= max;
	}
	bool passwordValidNewScheme(const std::string& password) {
		auto firstPos{ schemeFirstNumber(password) };
		auto secondPos{ schemeSecondNumber(password) };
		auto target{ targetChar(password) };
		auto raw{ rawPassword(password) };

		return (raw[firstPos] == target) != (raw[secondPos] == target);
	}
}
