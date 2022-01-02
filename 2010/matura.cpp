#include "matura.h"
#include <fstream>
#include <sstream>
#include <set>

using vec_vec_str = std::vector<std::vector<std::string>>;

vec_vec_str read_file(const std::string &file_name) {
	std::ifstream ifs(file_name);
	vec_vec_str input;

	if (ifs) {
		std::string line;

		while (std::getline(ifs, line)) {
			input.emplace_back();
			std::istringstream istr(line);

			for (std::string s; istr >> s;) {
				input.back().push_back(s);
			}
		}

		return input;
	}
	else {
		return {};
	}
}

void solve_a(const std::string &file_name) {
	auto input(read_file(file_name));
	std::ofstream ofs("odp_4a.txt", std::ofstream::app);

	for (const auto &x : input) {
		std::size_t first_size = 0;
		bool first = true, all_same = true;
		for (const auto &y : x) {
			if (first) {
				first_size = y.size();
				first = false;
				continue;
			}
			if (y.size() != first_size) {
				all_same = false;
				break;
			}
		}

		if (all_same) {
			for (const auto &s : x) {
				ofs << s << " ";
			}
			ofs << '\n';
		}
	}
}

void solve_b(const std::string &file_name) {
	auto input(read_file(file_name));
	std::ofstream ofs("odp_4b.txt", std::ofstream::app);

	for (const auto &x : input) {
		bool all_anagrams = true, first = true;
		std::multiset<char> chars;

		for (const auto &y : x) {
			if (first) {
				for (const auto &z : y) {
					chars.insert(z);
				}
				first = false;
				continue;
			}
			std::multiset<char> curr_chars;
			for (const auto &z : y) {
				curr_chars.insert(z);
			}

			if (curr_chars != chars) {
				all_anagrams = false;
				break;
			}
		}

		if (all_anagrams) {
			for (const auto &y : x) {
				ofs << y << " ";
			}
			ofs << '\n';
		}
	}
}
