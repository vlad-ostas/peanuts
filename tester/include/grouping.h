#pragma once

#include <test.h>

#include <vector>

namespace tester {

class TestCase {
public:
    TestCase() = default;
    TestCase(std::string case_name);

    void add_test(Test&& test);
    void assert(bool condition, std::string fail_message);
    void assert(bool confition);
    void expect(bool condition, std::string fail_message);
    void expect(bool condition);

    void set_suite(std::string& suite_name);

    TestResult run();
    
private:
    std::vector<Test> _tests;
    std::string _case_name = "No case";
};

class TestSuite {
public:
    TestSuite() = default;
    TestSuite(std::string suite_name);
    void add_case(TestCase& test_case);
    TestResult run();

private:
    std::vector<TestCase> _cases;
    std::string _suite_name = "No suite";
};

} // namespace tester