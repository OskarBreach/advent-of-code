#include "AutoRun.h"

#include "tobogganPasswords.h"

namespace TestTobogganPasswords {
	using gppUnit::equals;
	class Base : public Auto::TestCase {
	protected:
		void givenTobogganPasswords() {}

		void thenPasswordAcceptedByOldScheme(const std::string& password) {
			auto expected{ true };
			auto actual{ advent2020::tobogganPasswords::passwordValidOldScheme(password) };

			confirm.that(actual, equals(expected), __FUNCTION__);
		}
		void thenPasswordRejectedByOldScheme(const std::string& password) {
			auto expected{ false };
			auto actual{ advent2020::tobogganPasswords::passwordValidOldScheme(password) };

			confirm.that(actual, equals(expected), __FUNCTION__);
		}
		void thenPasswordAcceptedByNewScheme(const std::string& password) {
			auto expected{ true };
			auto actual{ advent2020::tobogganPasswords::passwordValidNewScheme(password) };

			confirm.that(actual, equals(expected), __FUNCTION__);
		}
		void thenPasswordRejectedByNewScheme(const std::string& password) {
			auto expected{ false };
			auto actual{ advent2020::tobogganPasswords::passwordValidNewScheme(password) };

			confirm.that(actual, equals(expected), __FUNCTION__);
		}
	};

	class ValidPasswordAcceptedByOldScheme : public Base {
		void test() {
			givenTobogganPasswords();

			thenPasswordAcceptedByOldScheme("1-3 a: abcde");
		}
	} GPPUNIT_INSTANCE;

	class InvalidPasswordRejectedByOldScheme : public Base {
		void test() {
			givenTobogganPasswords();

			thenPasswordRejectedByOldScheme("1-3 b: cdefg");
		}
	} GPPUNIT_INSTANCE;

	class OtherValidPasswordAcceptedByOldScheme : public Base {
		void test() {
			givenTobogganPasswords();

			thenPasswordAcceptedByOldScheme("2-9 c: ccccccccc");
		}
	} GPPUNIT_INSTANCE;

	class InvalidPasswordWithMultiDigitMaxRejectedByOldScheme : public Base {
		void test() {
			givenTobogganPasswords();

			thenPasswordRejectedByOldScheme("1-10 d: ddddddddddd");
		}
	} GPPUNIT_INSTANCE;

	class ValidPasswordWithMultiDigitMaxAcceptedByOldScheme : public Base {
		void test() {
			givenTobogganPasswords();

			thenPasswordAcceptedByOldScheme("1-10 d: dddddddddd");
		}
	} GPPUNIT_INSTANCE;

	class InvalidPasswordWithMultiDigitMinRejectedByOldScheme : public Base {
		void test() {
			givenTobogganPasswords();

			thenPasswordRejectedByOldScheme("10-10 d: ddddddddd");
		}
	} GPPUNIT_INSTANCE;

	class ValidPasswordAcceptedByNewScheme : public Base {
		void test() {
			givenTobogganPasswords();

			thenPasswordAcceptedByNewScheme("1-3 a: abcde");
		}
	} GPPUNIT_INSTANCE;

	class InvalidPasswordRejectedByNewScheme : public Base {
		void test() {
			givenTobogganPasswords();

			thenPasswordRejectedByNewScheme("1-3 b: cdefg");
		}
	} GPPUNIT_INSTANCE;

	class OtherInvalidPasswordRejectedByNewScheme : public Base {
		void test() {
			givenTobogganPasswords();

			thenPasswordRejectedByNewScheme("2-9 c: ccccccccc");
		}
	} GPPUNIT_INSTANCE;

	class OtherValidPasswordAcceptedByNewScheme : public Base {
		void test() {
			givenTobogganPasswords();

			thenPasswordAcceptedByNewScheme("1-3 c: abcde");
		}
	} GPPUNIT_INSTANCE;
}
