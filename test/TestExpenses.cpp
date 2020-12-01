#include "AutoRun.h"

#include "expenses.h"

namespace TestExpenses {
	using gppUnit::equals;
	class Base : public Auto::TestCase {
		void thenVectorsMatch(const std::vector<uint32_t>& actual, const std::vector<uint32_t>& expected) {
			expect.that(actual.size(), equals(expected.size()), __FUNCTION__);

			for (size_t i{ 0 }; i < actual.size(); ++i) {
				confirm.that(actual[i], equals(expected[i]), __FUNCTION__);
			}
		}

		protected:
			void givenExpenses() {}

			void thenTwoExpensesSummingToTarget(const std::vector<uint32_t>& expenses, uint32_t target, const std::vector<uint32_t>& expected) {
				auto actual{ advent2020::expenses::findTwoExpensesSummingToTarget(expenses, target) };
				thenVectorsMatch(actual, expected);
			}
			void thenThreeEntriesSummingToTarget(const std::vector<uint32_t>& expenses, uint32_t target, const std::vector<uint32_t>& expected) {
				auto actual{ advent2020::expenses::findThreeExpensesSummingToTarget(expenses, target) };
				thenVectorsMatch(actual, expected);
			}
	};

	class FindTwoExpensesSummingToTarget : public Base {
		const std::vector<uint32_t> expenses{ 1721, 979, 366, 299, 675, 1456 };

		void test() {
			givenExpenses();
			thenTwoExpensesSummingToTarget(expenses, 2020, { 1721, 299 });
		}
	} GPPUNIT_INSTANCE;

	class FindOtherTwoExpensesSummingToTarget : public Base {
		const std::vector<uint32_t> expenses{ 1, 10, 100, 1000, 10000 };

		void test() {
			givenExpenses();
			thenTwoExpensesSummingToTarget(expenses, 1010, { 10, 1000 });
		}
	} GPPUNIT_INSTANCE;

	class ReturnEmptyVectorIfCantFindTwoExpensesSummingToTarget : public Base {
		const std::vector<uint32_t> expenses{ 1721, 979, 366, 299, 675, 1456 };

		void test() {
			givenExpenses();
			thenTwoExpensesSummingToTarget(expenses, 42, {});
		}
	} GPPUNIT_INSTANCE;

	class FindThreeExpensesSummingToTarget : public Base {
		const std::vector<uint32_t> expenses{ 1721, 979, 366, 299, 675, 1456 };

		void test() {
			givenExpenses();
			thenThreeEntriesSummingToTarget(expenses, 2020, { 979, 366, 675 });
		}
	} GPPUNIT_INSTANCE;

	class FindOtherThreeExpensesSummingToTarget : public Base {
		const std::vector<uint32_t> expenses{ 1, 10, 100, 1000, 10000 };

		void test() {
			givenExpenses();
			thenThreeEntriesSummingToTarget(expenses, 1110, { 10, 100, 1000 });
		}
	} GPPUNIT_INSTANCE;

	class ReturnEmptyVectorIfCantFindThreeExpensesSummingToTarget : public Base {
		const std::vector<uint32_t> expenses{ 1721, 979, 366, 299, 675, 1456 };

		void test() {
			givenExpenses();
			thenThreeEntriesSummingToTarget(expenses, 42, {});
		}
	} GPPUNIT_INSTANCE;
}