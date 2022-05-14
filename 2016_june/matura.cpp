#include "matura.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <algorithm>
#include <cmath>

std::vector<std::string> read_file(const std::string &file_name) {
	std::ifstream ifs(file_name);

	if (ifs) {
		std::vector<std::string> input;

		for (std::string line; std::getline(ifs, line);) {
			input.push_back(line);
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

	solve_five(args);
}

// 4
long long oct_to_dec(const std::string &octal) {
	long long result = 0;
	int exp = 0;

	for (int i = octal.size() - 1; i >= 0; --i) {
		int val = std::stoi(std::string(1, octal[i]));
		result += val * std::pow(8, exp);
		++exp;
	}

	return result;
}

// 4 ver. 2
std::string add_decimals(std::vector<std::string> vec) {
	if (!vec.empty()) {
		std::size_t max_size = vec.front().size();
		std::string sum;
		int next_temp = 0;

		for (int i = 1; i != vec.size(); ++i) {
			if (vec[i].size() > max_size) {
				max_size = vec[i].size();
			}
		}

		for (auto &x : vec) {
			while (x.size() != max_size) {
				x.insert(x.begin(), '0');
			}
		}

		for (int i = max_size - 1; i >= 0; --i) {
			int temp = next_temp;
			for (const auto &x : vec) {
				temp += std::stoi(std::string(1, x[i]));
			}

			int res = temp % 10;
			next_temp = temp / 10;

			std::string str(std::to_string(res));
			sum.insert(sum.begin(), str.front());
		}

		return sum;
	}
	else {
		return "";
	}
}

std::string oct_to_dec_str(const std::string &octal) {
	std::vector<std::string> parts;
	int exp = 0;

	for (int i = octal.size() - 1; i >= 0; --i) {
		int val = std::stoi(std::string(1, octal[i])) * std::pow(8, exp);
		parts.push_back(std::to_string(val));
		++exp;
	}

	return add_decimals(parts);
}

// 5

long long convert_to_dec(const std::string &num, int base) {
	long long sum = 0;
	int exp = 0;

	for (int i = num.size() - 1; i >= 0; --i) {
		sum += std::stoi(std::string(1, num[i])) * std::pow(base, exp);
		++exp;
	}

	return sum;
}

void solve_one(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	unsigned satisfied_ctr = 0;

	for (const auto &x : input) {
		if (x.back() == '8') {
			++satisfied_ctr;
		}
	}

	write_file(args[2], "Liczba liczb zapisanych w systemie osemkowym: " + std::to_string(satisfied_ctr));
}

void solve_two(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	unsigned satisfied_ctr = 0;

	for (const auto &x : input) {
		if (x.back() == '4' && std::find(x.begin(), x.end(), '0') == x.end()) {
			++satisfied_ctr;
		}
	}

	write_file(args[2], "Ilosc takich liczb: " + std::to_string(satisfied_ctr));
}

void solve_three(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	unsigned satisfied_ctr = 0;

	for (const auto &x : input) {
		if (x.back() == '2' && x[x.size() - 2] == '0') {
			++satisfied_ctr;
		}
	}

	write_file(args[2], "Takich liczb jest: " + std::to_string(satisfied_ctr));
}

// given the problem even though we might not be able to convert
// some numbers to decimal because they are to large to fit into an int
// but we can use long long and it will fit because of the specification
void solve_four(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));
	long long sum = 0;

	for (const auto &x : input) {
		if (x.back() == '8') {
			sum += oct_to_dec(std::string(x.begin(), x.end() - 1));
		}
	}

	write_file(args[2], "Suma wszystkich liczb w systemie osemkowym jest: " + std::to_string(sum));
}

// version that would allow to sum numbers that would not fit in the primitive data types
void solve_four_ver2(const std::vector<std::string> &args) {
	std::cout << oct_to_dec_str("104") << '\n';
}

void solve_five(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	std::string max_str(input.front()), min_str(input.front());
	long long max = convert_to_dec(input.front().substr(0, input.front().size() - 1), std::stoi(std::string(1, input.front().back()))),
		min = max;

	for (int i = 1; i != input.size(); ++i) {
		long long val = convert_to_dec(input[i].substr(0, input[i].size() - 1), std::stoi(std::string(1, input[i].back())));

		if (val > max) {
			max = val;
			max_str = input[i];
		}
		if (val < min) {
			min = val;
			min_str = input[i];
		}
	}

	write_file(args[2], "Najmniejsza\nkod: " + min_str + "\twartosc w dziesietnym: " + std::to_string(min)
		+ "\n\nNajwieksza\nkod: " + max_str + "\twartosc w dziesietnym: " + std::to_string(max) + "\n\n");
}