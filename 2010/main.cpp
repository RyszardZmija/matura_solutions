#include <iostream>
#include <utility>
#include <cstddef>
#include <algorithm>
#include <string>
#include <cmath>
#include <iterator>

// using dynamic array because problem specification explicitly
// requested it
std::pair<char *, std::size_t> encrypt(std::size_t d, const char *tekst) {
	std::size_t s = 1;
	while (d > s * s) {
		++s;
	}
	char *szyfr = new char[s * s];
	char *new_tekst = new char[s * s];

	for (int i = 0; i != d; ++i) {
		new_tekst[i] = tekst[i];
	}
	for (int i = d; i != s * s; ++i) {
		new_tekst[i] = '_';
	}

	int i = 0, j = 0;
	while (i * s + j < s * s) {
		szyfr[j * s + i] = new_tekst[i * s + j];
		++j;

		if (j == s) {
			++i;
			j = 0;
		}
	}

	delete[] new_tekst;
	return std::make_pair(szyfr, s * s);
}

std::string decrypt(const char *beg, const char *end) {
	std::size_t sz = end - beg;
	std::string text(sz, ' ');
	int s = static_cast<int>(std::sqrt(sz));

	int i = 0, j = 0;
	while (i < s) {
		text[j * s + i] = beg[i * s + j];
		++j;

		if (j == s) {
			++i;
			j = 0;
		}
	}
	
	return text;
}

void print_arr(std::ostream &os, char *beg, char *end) {
	while (beg != end) {
		os << *beg;
		++beg;
	}
}

int main() {
	const char ca1[] = "Programming in C++ is (very) enjoyable.";
	char ca2[sizeof(ca1) / sizeof(*ca1) - 1];

	std::copy(std::begin(ca1), std::end(ca1) - 1, ca2);

	auto ret = encrypt(sizeof(ca2) / sizeof(*ca2), ca2);

	print_arr(std::cout, ret.first, ret.first + ret.second);

	std::cout << "\n\n";

	std::cout << decrypt(ret.first, ret.first + ret.second) << '\n';

	delete[] ret.first;

	return 0;
}