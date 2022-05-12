#include "matura.h"

#include <fstream>
#include <sstream>
#include <utility>

using encrypt_unit = std::pair<std::string, int>;

std::vector<std::string> read_file_one(const std::string &file_name) {
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

std::vector<encrypt_unit> read_file_two(const std::string &file_name) {
	std::ifstream ifs(file_name);

	if (ifs) {
		std::vector<encrypt_unit> input;

		for (std::string line; std::getline(ifs, line);) {
			std::istringstream istr(line);

			std::string word;
			int k = 0;

			istr >> word >> k;

			input.emplace_back(word, k);
		}

		return input;
	}
	else {
		throw std::runtime_error("could not open the given file " + file_name);
	}
}

std::vector<std::pair<std::string, std::string>> read_file_three(const std::string &file_name) {
	std::ifstream ifs(file_name);

	if (ifs) {
		std::vector<std::pair<std::string, std::string>> input;

		for (std::string line; std::getline(ifs, line);) {
			std::istringstream istr(line);

			std::string first, second;

			istr >> first >> second;

			input.emplace_back(first, second);
		}

		return input;
	}
	else {
		throw std::runtime_error("could not open the given file " + file_name);
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
		throw std::runtime_error("wrong number of cmd args");
	}

	solve_three(args);
}

// 1

char shift_letter(char ch, int k) {
	for (int i = 0; i != k; ++i) {
		if (ch == 'Z') {
			ch = 'A';
		}
		else {
			++ch;
		}
	}

	return ch;
}

std::string encrypt(const std::string &word, int k) {
	std::string cpy(word);

	for (auto &x : cpy) {
		x = shift_letter(x, k);
	}

	return cpy;
}

// 2

char shift_back(char ch, int k) {
	for (int i = 0; i != k; ++i) {
		if (ch == 'A') {
			ch = 'Z';
		}
		else {
			--ch;
		}
	}

	return ch;
}

std::string decrypt(const std::string &word, int k) {
	std::string cpy(word);

	for (auto &x : cpy) {
		x = shift_back(x, k);
	}

	return cpy;
}

// 3

int number_of_shifts(char ch1, char ch2) {
	unsigned ctr = 0;

	while (ch1 != ch2) {
		if (ch1 == 'Z') {
			ch1 = 'A';
		}
		else {
			++ch1;
		}

		++ctr;
	}

	return ctr;
}

bool is_properly_encrypted(const std::string &original, const std::string &ciphertext) {
	int k = number_of_shifts(original.front(), ciphertext.front());

	for (decltype(original.size()) i = 1; i != original.size(); ++i) {
		if (number_of_shifts(original[i], ciphertext[i]) != k) {
			return false;
		}
	}

	return true;
}
 
void solve_one(const std::vector<std::string> &args) {
	auto input(read_file_one(args[1]));
	constexpr int shift_value = 107;

	std::ostringstream ostr;

	for (const auto &x : input) {
		ostr << encrypt(x, shift_value) << '\n';
	}

	write_file(args[2], ostr.str());
}

void solve_two(const std::vector<std::string> &args) {
	auto input(read_file_two(args[1]));

	std::ostringstream ostr;

	for (const auto &x : input) {
		ostr << decrypt(x.first, x.second) << '\n';
	}

	write_file(args[2], ostr.str());
}

void solve_three(const std::vector<std::string> &args) {
	auto input(read_file_three(args[1]));

	std::ostringstream ostr;

	for (const auto &x : input) {
		if (!is_properly_encrypted(x.first, x.second)) {
			ostr << x.first << '\n';
		}
	}

	write_file(args[2], ostr.str());
}