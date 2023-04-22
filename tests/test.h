#pragma once
#include <vector>
#include <functional>
#include <string>

using TestFunc = std::function<void()>;

typedef struct {
	TestFunc function;
	std::string name;
	std::string file;
} test_case;

std::vector<test_case>& getTestRegistry()
{
    static std::vector<test_case> testRegistry;
    return testRegistry;
}

// Define a macro to register test functions
#define TEST_CASE(name) \
    void name(); \
    static bool name##Registered = []() { \
        getTestRegistry().push_back({name, #name, __FILE__}); \
        return true; \
    }(); \
    void name()

/* Define a test function using the TEST_CASE macro
TEST_CASE(myTestFunction)
{
	std::cout << "running test case" << std::endl;
    static_assert(1 == 1, "one equals one");
}
*/
