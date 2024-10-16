#pragma once

#include <vector>

namespace tester {

enum class TestResult {
    None,
    Pass,
    Fail,
    Fatal
};

class TestEntity;

class TestHandler {
public:
    TestHandler() = default;

    void add_entity(TestEntity* entity);

    int run_all_testing();

private:
    std::vector<TestEntity*> _entities;
};

extern TestHandler default_handler;


class TestEntity {
public:
    TestEntity(TestHandler& handler);

    TestEntity();
    
    virtual ~TestEntity() = default;

    virtual TestResult run() = 0;

protected:
    virtual void _print_result(TestResult) = 0;

protected:
    TestHandler& _handler = default_handler;
};

int test_all();

} // namespace tester


