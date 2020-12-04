#include "AutoRun.h"

#include "passportProcessing.h"

namespace TestPassportProcessing {
	using gppUnit::equals;
	class Base : public Auto::TestCase {
		advent2020::passportProcessing::Passports passports{};

	protected:
		const advent2020::passportProcessing::Passport passport1{ {"ecl", "gry"}, {"pid", "860033327"}, {"eyr", "2020"}, {"hcl", "#fffffd"}, {"byr", "1937"}, {"iyr", "2017"}, {"cid", "147"}, {"hgt", "183cm"} };
		const advent2020::passportProcessing::Passport passport2{ {"iyr", "2013"}, {"ecl", "amb"}, {"cid", "350"}, {"eyr", "2023"}, {"pid", "028048884"}, {"hcl", "#cfa07d"}, {"byr", "1929"} };
		const advent2020::passportProcessing::Passport passport3{ {"hcl", "#ae17e1"}, {"iyr", "2013"}, {"eyr", "2024"}, {"ecl", "brn"}, {"pid", "760753108"}, {"byr", "1931"}, {"hgt", "179cm"} };
		const advent2020::passportProcessing::Passport passport4{ {"hcl", "#cfa07d"}, {"eyr", "2025"}, {"pid", "166559648"}, {"iyr", "2011"}, {"ecl", "brn"}, {"hgt", "59in"} };

		void givenPassportProcessing() {}

		void whenBatchFileProcessed(advent2020::passportProcessing::BatchFile&& batchFile) {
			passports = advent2020::passportProcessing::passportsFromBatchFile(std::move(batchFile));
		}

		void thenPassport(const advent2020::passportProcessing::Passport& actual, const advent2020::passportProcessing::Passport& expected) {
			expect.that(actual.size(), equals(expected.size()), "Length");

			for (const auto& item: actual) {
				const auto& contents{ expected.at(item.first) };

				confirm.that(item.second, equals(contents), item.first.c_str());
			}
		}
		void thenPassports(const advent2020::passportProcessing::Passports& expected) {
			expect.that(passports.size(), equals(expected.size()), __FUNCTION__);

			for (size_t i{ 0 }; i < passports.size(); ++i) {
				const auto& actualPassport{ passports[i] };
				const auto& expectedPassport{ expected[i] };
				thenPassport(actualPassport, expectedPassport);
			}
		}
		void thenPassportContainsAllRequiredFields(const advent2020::passportProcessing::Passport& passport) {
			auto expected{ true };
			auto actual{ advent2020::passportProcessing::passportContainsAllRequiredFields(passport) };

			confirm.that(actual, equals(expected), __FUNCTION__);
		}
		void thenPassportMissingRequiredField(const advent2020::passportProcessing::Passport& passport) {
			auto expected{ false };
			auto actual{ advent2020::passportProcessing::passportContainsAllRequiredFields(passport) };

			confirm.that(actual, equals(expected), __FUNCTION__);
		}
		void thenPassportValid(size_t index) {
			auto expected{ true };
			auto actual{ advent2020::passportProcessing::passportValid(passports[index]) };

			confirm.that(actual, equals(expected), __FUNCTION__);
		}
		void thenPassportInvalid(size_t index) {
			auto expected{ false };
			auto actual{ advent2020::passportProcessing::passportValid(passports[index]) };

			confirm.that(actual, equals(expected), __FUNCTION__);
		}
	};

	class TestExtractingSinglePassportFromBatchFile : public Base {
		void test() {
			givenPassportProcessing();

			whenBatchFileProcessed({
				"ecl:gry pid:860033327 eyr:2020 hcl:#fffffd",
				"byr:1937 iyr:2017 cid:147 hgt:183cm"
				});
			thenPassports({ passport1 });
		}
	} GPPUNIT_INSTANCE;

	class TestExtractingOtherSinglePassportFromBatchFile : public Base {
		void test() {
			givenPassportProcessing();

			whenBatchFileProcessed({
				"iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884",
				"hcl:#cfa07d byr:1929",
				""}
			);
			thenPassports({ passport2 });
		}
	} GPPUNIT_INSTANCE;

	class TestExtractingMultiplePassportsFromBatchFile : public Base {
		void test() {
			givenPassportProcessing();

			whenBatchFileProcessed({
				"ecl:gry pid:860033327 eyr:2020 hcl:#fffffd",
				"byr:1937 iyr:2017 cid:147 hgt:183cm",
				"",
				"iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884",
				"hcl:#cfa07d byr:1929",
				"",
				"hcl:#ae17e1 iyr:2013",
				"eyr:2024",
				"ecl:brn pid:760753108 byr:1931",
				"hgt:179cm",
				"",
				"hcl:#cfa07d eyr:2025 pid:166559648",
				"iyr:2011 ecl:brn hgt:59in" 
				}
			);
			thenPassports({ passport1, passport2, passport3, passport4 });
		}
	} GPPUNIT_INSTANCE;

	class TestPassportValidity : public Base {
		void test() {
			givenPassportProcessing();

			thenPassportContainsAllRequiredFields(passport1);
			thenPassportContainsAllRequiredFields(passport3);
		}
	} GPPUNIT_INSTANCE;

	class TestPassportInvalidity : public Base {
		void test() {
			givenPassportProcessing();

			thenPassportMissingRequiredField(passport2);
			thenPassportMissingRequiredField(passport4);
		}
	} GPPUNIT_INSTANCE;

	class TestPassportRequiresAllKeyFields : public Base {
		void test() {
			givenPassportProcessing();

			thenPassportContainsAllRequiredFields({ {"ecl", "gry"}, {"pid", "860033327"}, {"eyr", "2020"}, {"hcl", "#fffffd"}, {"byr", "1937"}, {"iyr", "2017"}, {"cid", "147"}, {"hgt", "183cm"} });
			thenPassportContainsAllRequiredFields({ {"ecl", "gry"}, {"pid", "860033327"}, {"eyr", "2020"}, {"hcl", "#fffffd"}, {"byr", "1937"}, {"iyr", "2017"}, {"hgt", "183cm"} });

			thenPassportMissingRequiredField({ {"ecl", "gry"}, {"pid", "860033327"}, {"eyr", "2020"}, {"hcl", "#fffffd"}, {"byr", "1937"}, {"iyr", "2017"}, {"cid", "147"} });
			thenPassportMissingRequiredField({ {"ecl", "gry"}, {"pid", "860033327"}, {"eyr", "2020"}, {"hcl", "#fffffd"}, {"byr", "1937"}, {"cid", "147"}, {"hgt", "183cm"} });
			thenPassportMissingRequiredField({ {"ecl", "gry"}, {"pid", "860033327"}, {"eyr", "2020"}, {"hcl", "#fffffd"}, {"iyr", "2017"}, {"cid", "147"}, {"hgt", "183cm"} });
			thenPassportMissingRequiredField({ {"ecl", "gry"}, {"pid", "860033327"}, {"eyr", "2020"}, {"byr", "1937"}, {"iyr", "2017"}, {"cid", "147"}, {"hgt", "183cm"} });
			thenPassportMissingRequiredField({ {"ecl", "gry"}, {"pid", "860033327"}, {"hcl", "#fffffd"}, {"byr", "1937"}, {"iyr", "2017"}, {"cid", "147"}, {"hgt", "183cm"} });
			thenPassportMissingRequiredField({ {"ecl", "gry"}, {"eyr", "2020"}, {"hcl", "#fffffd"}, {"byr", "1937"}, {"iyr", "2017"}, {"cid", "147"}, {"hgt", "183cm"} });
			thenPassportMissingRequiredField({ {"pid", "860033327"}, {"eyr", "2020"}, {"hcl", "#fffffd"}, {"byr", "1937"}, {"iyr", "2017"}, {"cid", "147"}, {"hgt", "183cm"} });
		}
	} GPPUNIT_INSTANCE;

	class TestPassportValidationCatchesInvalidPasswords : public Base {
		void test() {
			givenPassportProcessing();

			whenBatchFileProcessed({
				"eyr:1972 cid:100",
				"hcl:#18171d ecl:amb hgt:170 pid:186cm iyr:2018 byr:1926",
				"",
				"iyr:2019",
				"hcl:#602927 eyr:1967 hgt:170cm",
				"ecl:grn pid:012533040 byr:1946",
				"",
				"hcl:dab227 iyr:2012",
				"ecl:brn hgt:182cm pid:021572410 eyr:2020 byr:1992 cid:277",
				"",
				"hgt:59cm ecl:zzz",
				"eyr:2038 hcl:74454a iyr:2023",
				"pid:3556412378 byr:2007"
				}
			);
			thenPassportInvalid(0);
			thenPassportInvalid(1);
			thenPassportInvalid(2);
			thenPassportInvalid(3);
		}
	} GPPUNIT_INSTANCE;

	class TestPassportValidationPermitsValidPasswords : public Base {
		void test() {
			givenPassportProcessing();

			whenBatchFileProcessed({
				"pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1980",
				"hcl:#623a2f",
				"",
				"eyr:2029 ecl:blu cid:129 byr:1989",
				"iyr:2014 pid:896056539 hcl:#a97842 hgt:165cm",
				"",
				"hcl:#888785",
				"hgt:164cm byr:2001 iyr:2015 cid:88",
				"pid:545766238 ecl:hzl",
				"eyr:2022",
				"",
				"iyr:2010 hgt:158cm hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719"
				}
			);
			thenPassportValid(0);
			thenPassportValid(1);
			thenPassportValid(2);
			thenPassportValid(3);
		}
	} GPPUNIT_INSTANCE;

	class TestPassportValidationChecksByr : public Base {
		void test() {
			givenPassportProcessing();

			whenBatchFileProcessed({
				"pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1919",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:2002",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:2003",
				"hcl:#623a2f"
				}
			);
			thenPassportValid(0);
			thenPassportInvalid(1);
			thenPassportValid(2);
			thenPassportInvalid(3);
		}
	} GPPUNIT_INSTANCE;

	class TestPassportValidationChecksIyr : public Base {
		void test() {
			givenPassportProcessing();

			whenBatchFileProcessed({
				"pid:087499704 hgt:74in ecl:grn iyr:2010 eyr:2030 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:74in ecl:grn iyr:2009 eyr:2030 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:74in ecl:grn iyr:2020 eyr:2030 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:74in ecl:grn iyr:2021 eyr:2030 byr:1920",
				"hcl:#623a2f",
				}
			);
			thenPassportValid(0);
			thenPassportInvalid(1);
			thenPassportValid(2);
			thenPassportInvalid(3);
		}
	} GPPUNIT_INSTANCE;

	class TestPassportValidationChecksEyr : public Base {
		void test() {
			givenPassportProcessing();

			whenBatchFileProcessed({
				"pid:087499704 hgt:74in ecl:grn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:74in ecl:grn iyr:2010 eyr:2019 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:74in ecl:grn iyr:2010 eyr:2030 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:74in ecl:grn iyr:2010 eyr:2031 byr:1920",
				"hcl:#623a2f",
				}
			);
			thenPassportValid(0);
			thenPassportInvalid(1);
			thenPassportValid(2);
			thenPassportInvalid(3);
		}
	} GPPUNIT_INSTANCE;

	class TestPassportValidationChecksHgtCm : public Base {
		void test() {
			givenPassportProcessing();

			whenBatchFileProcessed({
				"pid:087499704 hgt:150cm ecl:grn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:149cm ecl:grn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:193cm ecl:grn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:194cm ecl:grn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				}
			);
			thenPassportValid(0);
			thenPassportInvalid(1);
			thenPassportValid(2);
			thenPassportInvalid(3);
		}
	} GPPUNIT_INSTANCE;

	class TestPassportValidationChecksHgtIn : public Base {
		void test() {
			givenPassportProcessing();

			whenBatchFileProcessed({
				"pid:087499704 hgt:59in ecl:grn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:58in ecl:grn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:76in ecl:grn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:77in ecl:grn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				}
			);
			thenPassportValid(0);
			thenPassportInvalid(1);
			thenPassportValid(2);
			thenPassportInvalid(3);
		}
	} GPPUNIT_INSTANCE;

	class TestPassportValidationChecksHcl : public Base {
		void test() {
			givenPassportProcessing();

			whenBatchFileProcessed({
				"pid:087499704 hgt:59in ecl:grn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:59in ecl:grn iyr:2010 eyr:2020 byr:1920",
				"hcl:#123abz",
				"",
				"pid:087499704 hgt:59in ecl:grn iyr:2010 eyr:2020 byr:1920",
				"hcl:#123abc",
				"",
				"pid:087499704 hgt:59in ecl:grn iyr:2010 eyr:2020 byr:1920",
				"hcl:123abc",
				}
			);
			thenPassportValid(0);
			thenPassportInvalid(1);
			thenPassportValid(2);
			thenPassportInvalid(3);
		}
	} GPPUNIT_INSTANCE;

	class TestPassportValidationChecksEcl : public Base {
		void test() {
			givenPassportProcessing();

			whenBatchFileProcessed({
				"pid:087499704 hgt:59in ecl:brn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:59in ecl:wat iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:59in ecl:amb iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:087499704 hgt:59in ecl:foo iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				}
			);
			thenPassportValid(0);
			thenPassportInvalid(1);
			thenPassportValid(2);
			thenPassportInvalid(3);
		}
	} GPPUNIT_INSTANCE;

	class TestPassportValidationChecksPid : public Base {
		void test() {
			givenPassportProcessing();

			whenBatchFileProcessed({
				"pid:087499704 hgt:59in ecl:brn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:0123456789 hgt:59in ecl:brn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:000000001 hgt:59in ecl:brn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				"",
				"pid:01234567 hgt:59in ecl:brn iyr:2010 eyr:2020 byr:1920",
				"hcl:#623a2f",
				}
			);
			thenPassportValid(0);
			thenPassportInvalid(1);
			thenPassportValid(2);
			thenPassportInvalid(3);
		}
	} GPPUNIT_INSTANCE;
}
