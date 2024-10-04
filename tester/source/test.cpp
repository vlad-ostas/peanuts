#include "test.h"
#include <tester.h>
#include <iostream>

namespace tester {

Test::Test(
    TestType type,
    bool condition,
    std::string case_name,
    std::string suite_name,
    std::string fail_message)
        : _condition(condition),
          _suite_name(suite_name),
          _case_name(case_name),
          _type(type),
          _fail_message(fail_message) {

}

Test::Test(
    TestType type,
    bool condition,
    std::string fail_message)
        : Test(type, condition, "No case", "No suite", fail_message) {

}

Test::Test(
    TestType type,
    bool condition)
        : Test(type, condition, "no message") {

}

void Test::set_case(std::string case_name) {
    _case_name = case_name;
}

void Test::set_suite(std::string suite_name) {
    _suite_name = suite_name;
}

void Test::set_fail_message(std::string fail_message) {
    _fail_message = fail_message;
}

TestResult Test::run() {
    TestResult res = _result_of(_type, _condition);
    _is_run = true;
    
    if (res != TestResult::Pass) {
        _print_on_fail();
    }

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

void Test::_print_on_fail() {
    std::cout << (_type == TestType::Assert ? "Assert" : "Expect") << " "
              << "fail ("
              << "Suite: " << _suite_name << ", "
              << "Case:" << _case_name << "): "
              << _fail_message << std::endl;
}


Test test(TestType type, bool condition, std::string fail_message) {
    return {type, condition, fail_message};
}

Test test(TestType type, bool condition) {
    return {type, condition};
}

Test assert(bool condition, std::string fail_message) {
    return {TestType::Assert, condition, fail_message};
}

Test assert(bool condition) {
    return {TestType::Assert, condition};
}

Test expect(bool condition, std::string fail_message) {
    return {TestType::Expect, condition, fail_message};
}

Test expect(bool condition) {
    return {TestType::Expect, condition};
}

} // namespace tester
