#include "passportProcessing.h"

#include <regex>

namespace {
	const std::map<std::string, std::regex> validationChecks{
		{"byr", std::regex{"^19[2-9][0-9]|200[0-2]$"}},
		{"iyr", std::regex{"^20(1[0-9]|20)$"}},
		{"eyr", std::regex{"^20(2[0-9]|30)$"}},
		{"hgt", std::regex{"^1([5-8][0-9]|9[0-3])cm|(59|6[0-9]|7[0-6])in$"}},
		{"hcl", std::regex{"^#[0-9a-f]{6}$"}},
		{"ecl", std::regex{"^amb|blu|brn|gry|grn|hzl|oth$"}},
		{"pid", std::regex{"^[0-9]{9}$"}}
	};
}

namespace advent2020::passportProcessing {
	Passports passportsFromBatchFile(BatchFile&& batchFile) {
		Passports ret{};
		Passport passport{};

		batchFile.push_back("");

		for (auto& line : batchFile) {
			if (line != "") {
				line += ' ';
				std::string pair{};
				size_t pos{ 0 };
				while ((pos = line.find(' ')) != std::string::npos) {
					pair = line.substr(0, pos);
					line.erase(0, pos + 1);

					auto first{ pair.substr(0, pair.find(':')) };
					auto second{ pair.substr(pair.find(':') + 1) };

					passport[first] = second;
				}
			}
			else if (passport.size()) {
				ret.push_back(passport);
				passport.clear();
			}
		}

		return ret;
	}

	bool passportContainsAllRequiredFields(const Passport& passport) {
		for (const auto& check: validationChecks) {
			if (passport.find(check.first) == std::end(passport)) {
				return false;
			}
		}
		return true;
	}

	bool passportValid(const Passport& passport) {
		for (const auto& check : validationChecks) {
			auto value{ passport.find(check.first) };
			if (value == std::end(passport)) {
				return false;
			}
			if (!std::regex_match(value->second, check.second)) {
				return false;
			}
		}
		return true;
	}
}
