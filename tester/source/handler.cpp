#include <handler.h>

namespace tester {

void TestHandler::add_entity(TestEntity* entity) {
    _entities.emplace_back(entity);
}

int TestHandler::run_all_testing() {
    bool is_all_passed = true;
    for(auto& entity : _entities) {
        is_all_passed = is_all_passed && (entity->run() == TestResult::Pass);
    }
    return (is_all_passed ? 0 : 1);
}

TestEntity::TestEntity(TestHandler& handler) 
        : _handler(handler) {
    _handler.add_entity(this);
}

TestEntity::TestEntity() : TestEntity(default_handler) {
    
}

int test_all() {
    return default_handler.run_all_testing();
}

TestHandler default_handler;

} // namespace tester