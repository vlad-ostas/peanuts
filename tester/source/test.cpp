#include <test.h>

namespace tester {

std::string get_result_string(TestResult result) {
    switch (result) {
        case TestResult::SUCCESS:
            return "SUCCESS";

        case TestResult::FATAL:
            return "FATAL";

        case TestResult::FAIL:
            return "FAIL";

        default:
            return "UNDEFINED";
    }
}

Test::Test(bool condition, TestType type, const char *test_case_name) {
    _test_info.condition = condition;
    _test_info.type = type;
    _test_info.test_case_name = test_case_name;
}


TestResult Test::result_of() const {
    switch (_test_info.type) {
        case TestType::ASSERT:
            return (_test_info.condition ? TestResult::SUCCESS : TestResult::FATAL);

        case TestType::EXPECT:
            return (_test_info.condition ? TestResult::SUCCESS : TestResult::FAIL);

        default:
            return (TestResult::NONE);
    }
}

void Test::print_result(std::ostream &os) const {
    std::string result_str = get_result_string(result_of());

    os << "Test from \'" << _test_info.test_case_name << "\' executed with result: " << result_str << std::endl;
}


Test *test(bool condition, TestType type, const char *test_case_name) {
    Test *test = new Test(condition, type, test_case_name);
    return test;
}


} // namespace tester