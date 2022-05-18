#include "matura.h"

#include <stdexcept>

#include <fstream>
#include <sstream>

#include <utility>

#include <algorithm>

using record = std::pair<int, std::string>;

std::vector<record> read_file(const std::string &file_name) {
	std::ifstream ifs(file_name);

	if (ifs) {
		std::vector<record> input;

		for (std::string line; std::getline(ifs, line);) {
			std::istringstream istr(line);
			int val = 0;
			std::string str;

			istr >> val >> str;

			input.emplace_back(val, str);
		}

		return input;
	}
	else {
		throw std::runtime_error("could not open the file " + file_name);
	}
}

void write_file(const std::string &file_name, const std::string &contents) {
	std::ofstream ofs(file_name, std::ofstream::app);

	if (ofs) {
		ofs << contents;
	}
	else {
		throw std::runtime_error("could not open the file " + file_name);
	}
}

void start(const std::vector<std::string> &args) {
	if (args.size() != 3) {
		throw std::runtime_error("wrong number of cmd line args");
	}

	solve_three(args);
}

// 1

bool is_prime(int n) {
	if (n < 2) {
		return false;
	}

	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	
	return true;
}

// liczba jest parzysta i >4
std::pair<int, int> goldbach(int val) {
	for (int i = 3; i < val; ++i) {
		if (is_prime(i) && i % 2 == 1) {
			if (is_prime(val - i) && (val - i) % 2 == 1) {
				return std::pair<int, int>(i, val - i);
			}
		}
	}

	return std::pair<int, int>(0, 0);
}

// 2

std::pair<char, int> longest_str(const std::string &word) {
	char max_char = word[0], current_char = word[0];
	int max_count = 1, current_count = 1;

	for (int i = 1; i != word.size(); ++i) {
		if (word[i] == current_char) {
			++current_count;
		}
		else {
			if (current_count > max_count) {
				max_char = current_char;
				max_count = current_count;
			}

			current_char = word[i];
			current_count = 1;
		}
	}

	if (current_count > max_count) {
		max_count = current_count;
		max_char = current_char;
	}

	return std::make_pair(max_char, max_count);
}

// 3

bool less(const record &lhs, const record &rhs) {
	if (lhs.first < rhs.first) {
		return true;
	}
	else if (lhs.first == rhs.first && lhs.second < rhs.second) {
		return true;
	}
	else {
		return false;
	}
}

void solve_one(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));
	std::ostringstream ostr;

	for (const auto &x : input) {
		if (x.first % 2 == 0) {
			if (x.first == 4) {
				ostr << x.first << " nie da sie przedstawic\n";
			}
			else {
				auto result(goldbach(x.first));

				ostr << x.first << " " << result.first << " " << result.second << '\n';
			}
		}
	}

	write_file(args[2], "4.1\n" + ostr.str() + "\n\n");
}

void solve_two(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));
	std::ostringstream ostr;

	for (const auto &x : input) {
		auto result(longest_str(x.second));

		ostr << std::string(result.second, result.first) << " " << result.second << '\n';
	}

	write_file(args[2], "4.2\n" + ostr.str() + "\n\n");
}

void solve_three(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	std::vector<record> sifted;

	for (const auto &x : input) {
		if (x.first == x.second.size()) {
			sifted.push_back(x);
		}
	}

	std::sort(sifted.begin(), sifted.end(), less);

	auto result(sifted.front());

	write_file(args[2], "4.3\n" + std::to_string(result.first) + " " + result.second + "\n\n");
}