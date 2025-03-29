#pragma once

#include <string>
#include <iostream>

namespace tester {

constexpr int MAX_NAME_LENGTH = 32;
constexpr auto DEFAULT_CASE_NAME = "none";


enum class TestType {
    ASSERT,
    EXPECT
};

enum class TestResult {
    NONE,
    SUCCESS,
    FAIL,
    FATAL
};

std::string get_result_string(TestResult result);

struct TestInfo {

    TestType type;
    bool condition;
    std::string test_case_name;
};

class Test {
public:
    Test(bool condition, TestType type, const char *test_case_name = DEFAULT_CASE_NAME);
    ~Test() = default;

    Test(const Test &) = delete;
    Test(Test &&) = delete;
    Test &operator=(const Test &) = delete;
    Test &operator=(Test &&) = delete;

    [[nodiscard]] const TestInfo &info() const { return _test_info; }

    TestResult result_of() const ;
    void print_result(std::ostream& os = std::cout) const;

private:
    TestInfo _test_info;
};

Test* test(bool condition, TestType type, const char *test_case_name = DEFAULT_CASE_NAME);

inline Test* assert(const bool condition, const char *test_case_name = DEFAULT_CASE_NAME) {
    return test(condition, TestType::ASSERT, test_case_name);
}

inline Test* expect(const bool condition, const char *test_case_name = DEFAULT_CASE_NAME) {
    return test(condition, TestType::EXPECT, test_case_name);
}

} // namespace tester