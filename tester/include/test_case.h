#pragma once

#include "test.h"

#include <vector>

namespace tester {

class TestCase {
public:
    TestCase(std::string name);
    ~TestCase();

    TestCase(const TestCase &) = delete;
    TestCase(TestCase &&) = delete;
    TestCase & operator=(const TestCase&) = delete;
    TestCase & operator=(TestCase&&) = delete;

    void test(bool condition, TestType type);

    void assert(const bool condition) {
        test(condition, TestType::ASSERT);
    }
    void expect(const bool condition) {
        test(condition, TestType::EXPECT);
    }

    TestResult result_of() const;
    void print_result(std::ostream& os = std::cout) const;

private:
    static constexpr auto DEFAULT_CASE_NAME = "unnamed";

    std::vector<Test*> _tests;
    std::string _name;
};

} // namespace tester