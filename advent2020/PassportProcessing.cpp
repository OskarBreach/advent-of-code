#include "passportProcessing.h"

#include <regex>

namespace {
	bool passportContains(const advent2020::passportProcessing::Passport& passport, const std::string& key) {
		return passport.find(key) != std::end(passport);
	}
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
		return passportContains(passport, "byr")
			&& passportContains(passport, "iyr")
			&& passportContains(passport, "eyr")
			&& passportContains(passport, "hgt")
			&& passportContains(passport, "hcl")
			&& passportContains(passport, "ecl")
			&& passportContains(passport, "pid");
	}

	bool passportValid(const Passport& passport) {
		if (!std::regex_match(passport.at("byr"), std::regex{ "^19[2-9][0-9]|200[0-2]$" })) {
			return false;
		}
		if (!std::regex_match(passport.at("iyr"), std::regex{ "^20(1[0-9]|20)$" })) {
			return false;
		}
		if (!std::regex_match(passport.at("eyr"), std::regex{ "^20(2[0-9]|30)$" })) {
			return false;
		}
		if (!std::regex_match(passport.at("hgt"), std::regex{ "^1([5-8][0-9]|9[0-3])cm|(59|6[0-9]|7[0-6])in$" })) {
			return false;
		}
		if (!std::regex_match(passport.at("hcl"), std::regex{ "^#[0-9a-f]{6}$" })) {
			return false;
		}
		if (!std::regex_match(passport.at("ecl"), std::regex{ "^amb|blu|brn|gry|grn|hzl|oth$" })) {
			return false;
		}
		if (!std::regex_match(passport.at("pid"), std::regex{ "^[0-9]{9}$" })) {
			return false;
		}

		return true;
	}
}
