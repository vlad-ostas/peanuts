#pragma once

#include "handler.h"

#include <vector>
#include <string>
#include <memory>

namespace tester {

class Test;
class TestSuite;

class TestCase : public TestEntity {
public:
    TestCase() = default;
    TestCase(std::string case_name);

    void add_test(Test&& test);
    void assert(bool condition, std::string fail_message);
    void expect(bool condition, std::string fail_message);

    void set_suite(TestSuite& suite);

    std::string get_name();
    std::shared_ptr<TestSuite>& get_suite();

    TestResult run() override;
    
private:
    void _print_result(TestResult result) override;

private:
    std::vector<Test> _tests;
    std::string _case_name = "null";
    std::shared_ptr<TestSuite> _suite;
};

class TestSuite : public TestEntity {
public:
    TestSuite() = default;
    TestSuite(std::string suite_name);

    void add_case(TestCase& test_case);
    
    std::string get_name();
    
    TestResult run() override;

private:
    void _print_result(TestResult result) override;

private:
    std::vector<TestCase> _cases;
    std::string _suite_name = "null";
};

} // namespace tester