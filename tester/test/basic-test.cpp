#include "test.h"
#include <tester.h>

int main() {
    using namespace tester;

    Test test_true = expect(true, "test_true - this message should not appear");
    Test test_false = expect(false, "test_false message");
    Test test_false_ctr = Test(TestType::Assert, false, "test_false_ctr message", nullptr);
    // add overloaded
    Test test_setmessage = expect(false, "this message should not appear");
    test_setmessage.set_fail_message("test_setmessage message");


    test_true.run();
    test_false.run();
    test_false_ctr.run();
    test_setmessage.run();
}