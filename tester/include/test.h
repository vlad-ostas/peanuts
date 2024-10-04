#pragma once

#include <string>

namespace tester {

enum class TestType {
    Assert,
    Expect
};

enum class TestResult {
    None,
    Pass,
    Fail,
    Fatal
};


class Test {
public:
    Test(TestType type,
         bool condition,
         std::string case_name,
         std::string suite_name,
         std::string fail_message);
    Test(TestType type,
         bool condition,
         std::string fail_message);
    Test(TestType type,
         bool condition);

    void set_case(std::string case_name);
    void set_suite(std::string suite_name);
    void set_fail_message(std::string fail_message);

    TestResult run();

private:
    static TestResult _result_of(TestType type, bool condition);
    void _print_on_fail();

private:
    bool _condition;
    bool _is_run = false;
    std::string _suite_name;
    std::string _case_name;
    TestType _type;
    std::string _fail_message;
};

Test test(TestType type, bool condition, std::string fail_message);
Test test(TestType type, bool condition);

Test assert(bool condition, std::string fail_message);
Test assert(bool condition);

Test expect(bool condition, std::string fail_message);
Test expect(bool condition);

} // namespace tester