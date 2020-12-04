#pragma once

#include <vector>
#include <string>
#include <map>

namespace advent2020::passportProcessing {
	using BatchFile = std::vector<std::string>;
	using Passport = std::map<std::string, std::string>;
	using Passports = std::vector<Passport>;

	Passports passportsFromBatchFile(BatchFile&&);
	bool passportContainsAllRequiredFields(const Passport&);
	bool passportValid(const Passport&);
}
