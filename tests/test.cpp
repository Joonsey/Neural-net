#include "test.h"
#include <iostream>
#include "cases.h"

int main()
{
    for (auto& testFunc : getTestRegistry()) {
		std::cout
			<< "running test '"
			<< testFunc.name
			<< "' in "
			<< testFunc.file
			<< std::endl;
        testFunc.function();
    }
    return 0;
}
