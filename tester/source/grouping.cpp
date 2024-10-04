#include "test.h"
#include <grouping.h>

namespace tester {

TestCase::TestCase(std::string case_name) : _case_name(case_name) {

}

void TestCase::add_test(Test&& test) {
    test.set_case(_case_name);
    _tests.push_back(test);
}

void TestCase::assert(bool condition, std::string fail_message) {
    add_test({TestType::Assert, condition, fail_message});
}

void TestCase::assert(bool condition) {
    add_test({TestType::Assert, condition});
}

void TestCase::expect(bool condition, std::string fail_message) {
    add_test({TestType::Expect, condition, fail_message});
}

void TestCase::expect(bool condition) {
    add_test({TestType::Expect, condition});
}

void TestCase::set_suite(std::string& suite_name) {
    for (auto& test : _tests) {
        test.set_suite(suite_name);
    }
}

TestResult TestCase::run() {
    TestResult case_result = TestResult::None;
    
    for (auto& test : _tests) {
        auto test_result = test.run();
        if (test_result == TestResult::Fatal) {
            return test_result;
        }

        if (test_result == TestResult::Fail) {
            case_result = test_result;
            continue;
        }

        if (test_result == TestResult::Pass && case_result == TestResult::None) {
            case_result = TestResult::Pass;
        }

    }
    
    return case_result;
}


TestSuite::TestSuite(std::string suite_name) : _suite_name(suite_name) {

}

void TestSuite::add_case(TestCase& test_case) {
    test_case.set_suite(_suite_name);
    _cases.push_back(test_case);
}

TestResult TestSuite::run() {
    TestResult suite_result = TestResult::None;
    
    for (auto& test_case : _cases) {
        auto case_result = test_case.run();

        if (suite_result == TestResult::Fatal) {
            continue;
        }

        if (case_result == TestResult::Fatal) {
            suite_result = case_result;
            continue;
        }

        if (suite_result == TestResult::Fail) { 
            continue;
        }

        if (case_result == TestResult::Fail) {
            suite_result = case_result;
            continue;
        }

        if (case_result == TestResult::Pass && suite_result == TestResult::None) {
            suite_result = TestResult::Pass;
        }
    }
    
    return suite_result;
}

} // namespace tester