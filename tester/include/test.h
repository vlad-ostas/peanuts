#pragma once

#include "handler.h"

#include <string>
#include <memory>

namespace tester {

enum class TestType {
    Assert,
    Expect
};

class TestCase;

class Test : public TestEntity {
public:
    Test(TestType type,
         bool condition,
         std::string fail_message,
         std::shared_ptr<TestCase> test_case);

    void set_case(TestCase& test_case);
    void set_fail_message(std::string fail_message);

    std::shared_ptr<TestCase>& get_case();

    TestResult run() override;

private:
    static TestResult _result_of(TestType type, bool condition);
    void _print_result(TestResult result) override;

private:
    bool _condition;
    std::shared_ptr<TestCase> _test_case;
    TestType _type;
    std::string _fail_message;
};

Test expect(bool condition, std::string fail_message);

} // namespace tester