#include <test.h>
#include <grouping.h>

#include <memory>
#include <iostream>

namespace tester {

Test::Test(
    TestType type,
    bool condition,
    std::string fail_message = "No message",
    std::shared_ptr<TestCase> test_case = nullptr)
        : _condition(condition),
          _test_case(test_case),
          _type(type),
          _fail_message(fail_message) {

}

void Test::set_case(TestCase& test_case) {
    _test_case = std::shared_ptr<TestCase>(&test_case);
}

void Test::set_fail_message(std::string fail_message) {
    _fail_message = fail_message;
}

std::shared_ptr<TestCase>& Test::get_case() {
    return _test_case;
}

TestResult Test::run() {
    TestResult res = _result_of(_type, _condition);
    
    _print_result(res);

    return res;
}

TestResult Test::_result_of(TestType type, bool condition) {
    auto res = TestResult::None;
    switch (type) {
        case TestType::Assert:
            res = (condition ? TestResult::Pass : TestResult::Fatal);
            break;

        case TestType::Expect:
            res = (condition ? TestResult::Pass : TestResult::Fail);
            break;

        default:
            // code should not end up here
            break;
    }
    return res;
}

void Test::_print_result(TestResult result) {
    std::string result_str;
    switch (result) {
        case TestResult::Pass:
            result_str = "PASS";
            break;
        case TestResult::Fail:
            result_str = "FAIL";
            break;
        case TestResult::Fatal:
            result_str = "FATAL";
            break;
        default:
            result_str = "NONE";
            break;
    }

    auto& test_case = get_case();
    std::string case_name = (test_case ? test_case->get_name() : "null");
    std::shared_ptr<TestSuite> suite = (test_case ? test_case->get_suite() : nullptr);
    std::string suite_name = (suite ? suite->get_name() : "null");

    std::cout << "[Suite: " << suite_name << "]"
              << "[Case: " << case_name << "]"
              << " " << (_type == TestType::Assert ? "Assert" : "Expect")
              << " " << result_str;
    if (result != TestResult::Pass) {
        std::cout << ": " << _fail_message;
    }
    std::cout << std::endl;
}

Test expect(bool condition, std::string fail_message = "No message") {
    return {TestType::Expect, condition, fail_message};
}

} // namespace tester
