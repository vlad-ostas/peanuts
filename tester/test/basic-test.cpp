#include <tester.h>

int main() {
    using namespace tester;

    Test assert_true(TestType::Assert, true, "assert_true test fail");
    Test assert_false(TestType::Assert, false, "assert_false test fail");
    Test expect_true(TestType::Expect, true, "expect_true test fail");
    Test expect_false(TestType::Expect, false, "expect_false test fail");

    assert_true.run();
    assert_false.run();
    expect_true.run();
    expect_false.run();
}