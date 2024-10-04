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

class TestCase;

class Test {
public:
    Test(TestType type,
         bool condition,
         TestCase* test_case,
         std::string fail_message);
    Test(TestType type,
         bool condition,
         std::string fail_message);
    Test(TestType type,
         bool condition);

    void set_case(TestCase* test_case);
    void set_fail_message(std::string fail_message);

    TestCase* get_case();

    TestResult run();

private:
    static TestResult _result_of(TestType type, bool condition);
    void _print_result(TestResult result);

private:
    bool _condition;
    TestCase* _test_case;
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