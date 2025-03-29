#include <test_case.h>

namespace tester {

TestCase::TestCase(std::string name)
        : _name(std::move(name)) {}

TestCase::~TestCase() {
    for (const auto * test : _tests) {
        delete test;
    }
}

void TestCase::test(const bool condition, const TestType type) {
    Test* test = new Test(condition, type, _name.c_str());
    _tests.push_back(test);
}

TestResult TestCase::result_of() const {
    auto result = TestResult::SUCCESS;
    for (const auto * test : _tests) {
        const auto test_result = test->result_of();
        if (test_result == TestResult::FATAL) {
            result = TestResult::FATAL;
            break;
        }
        if (test_result == TestResult::FAIL) {
            result = TestResult::FAIL;
        }
    }
    return result;
}

void TestCase::print_result(std::ostream &os) const {
    os << "Entering test case: " << _name << "\n";
    os << "--------------------------------------" << std::endl;
    for (const auto * test : _tests) {
        os << "    ";
        test->print_result(os);
    }
}

} // namespace tester