#include "matura.h"

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <utility>
#include <set>
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
		throw std::runtime_error("could not read the file " + file_name);
	}
}

void write_file(const std::string &file_name, const std::string &content) {
	std::ofstream ofs(file_name, std::ofstream::app);

	if (ofs) {
		ofs << content;
	}
	else {
		throw std::runtime_error("could not write the file " + file_name);
	}
}

void start(const std::vector<std::string> &args) {
	if (args.size() != 3) {
		throw std::runtime_error("wrong number of cmd args");
	}

	sol_three(args);
}

void sol_one(const std::vector<std::string> &args) {
	auto input = read_file(args[1]);
	std::ostringstream ostr;

	for (int i = 39; i < input.size(); i += 40) {
		ostr << input[i][9];
	}

	write_file(args[2], "4.1\n" + ostr.str() + "\n\n");
}

void sol_two(const std::vector<std::string> &args) {
	auto input = read_file(args[1]);
	std::pair<std::string, unsigned> greatest_word;
	bool is_first = true;

	for (const auto &x : input) {
		std::set<char> unique_chars;

		for (const auto &c : x) {
			unique_chars.insert(c);
		}

		if (is_first) {
			greatest_word.first = x;
			greatest_word.second = unique_chars.size();
			is_first = false;
		}
		else {
			if (unique_chars.size() > greatest_word.second) {
				greatest_word.first = x;
				greatest_word.second = unique_chars.size();
			}
		}
	}

	const std::string output = "4.2\n" + greatest_word.first + " " + std::to_string(greatest_word.second)
		+ "\n\n";

	write_file(args[2], output);
}

void sol_three(const std::vector<std::string> &args) {
	auto input = read_file(args[1]);
	std::ostringstream ostr;

	for (const auto &x : input) {
		bool satisfies = true;

		for (int i = 0; i != x.size() && satisfies; ++i) {
			for (int j = 0; j != x.size(); ++j) {
				if (std::abs(x[i] - x[j]) > 10) {
					satisfies = false;
					break;
				}
			}
		}

		if (satisfies) {
			ostr << x << '\n';
		}
	}

	write_file(args[2], "4.3\n" + ostr.str());
}