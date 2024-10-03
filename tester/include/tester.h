#include <vector>
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

    void set_case(std::string case_name);
    void set_suite(std::string suite_name);

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

class TestCase {
public:
    TestCase() = default;
    TestCase(std::string case_name);
    void add_test(Test& test);
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

// class TestHandler {
//
// };

} // namespace tester