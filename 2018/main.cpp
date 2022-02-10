#include "matura.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

int main(int argc, char **argv) {
	try {
		start(std::vector<std::string>(argv, argv + argc));
	}
	catch (const std::runtime_error &err) {
		std::cerr << err.what() << '\n';
		std::exit(EXIT_FAILURE);
	}

	return 0;
}