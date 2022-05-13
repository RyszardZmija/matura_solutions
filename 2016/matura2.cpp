#include "matura.h"

#include <fstream>
#include <sstream>
#include <utility>
#include <cmath>

// the x y coordinates must be integers
using point = std::pair<int, int>;

std::vector<point> read_file(const std::string &file_name) {
	std::ifstream ifs(file_name);

	if (ifs) {
		std::vector<point> input;

		for (std::string line; std::getline(ifs, line);) {
			std::istringstream istr(line);

			int x = 0, y = 0;

			istr >> x >> y;

			input.emplace_back(x, y);
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
		throw std::runtime_error("could not open the given file " + file_name);
	}
}

void start(const std::vector<std::string> &args) {
	if (args.size() != 3) {
		throw std::runtime_error("wrong number of cmd line args");
	}

	solve_two(args);
}

// 1
char circle_position(point p) {
	int val = std::pow(p.first - 200, 2) + std::pow(p.second - 200, 2);

	if (val == std::pow(200, 2)) {
		return 'e';
	}
	else if (val < std::pow(200, 2)) {
		return 'i';
	}
	else {
		return 'n';
	}
}

// 2

unsigned belonging_to_circle(std::vector<point> points) {
	unsigned satisfied_ctr = 0;

	for (const auto &x : points) {
		int val = std::pow(x.first - 200, 2) + std::pow(x.second - 200, 2);

		if (val <= std::pow(200, 2)) {
			++satisfied_ctr;
		}
	}

	return satisfied_ctr;
}

double approximate_pi(std::vector<point> points, int precision) {
	double numerator = belonging_to_circle(points) * std::pow(400.0, 2);
	double denominator = points.size() * std::pow(200.0, 2);
	double result = numerator / denominator;
	result = std::round(result * std::pow(10, precision));

	return result / std::pow(10, precision);
}

void solve_one(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	std::ostringstream ostr;
	unsigned satisfied_ctr = 0;

	for (const auto &x : input) {
		auto result = circle_position(x);

		if (result == 'e') {
			ostr << x.first << " " << x.second << '\n';
		}
		else if (result == 'i') {
			++satisfied_ctr;
		}
	}

	write_file(args[2], "4.1\nilosc nalezacych do wnetrza: " + std::to_string(satisfied_ctr) + "\npunkty lezace na brzegu:\n"
		+ ostr.str() + "\n\n");
}

void solve_two(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	std::ostringstream ostr;

	ostr << "przyblizenie dla pierwszych 1000 punktow: " <<
		approximate_pi(std::vector<point>(input.begin(), input.begin() + 1000), 4) << '\n';
	ostr << "przyblizenie dla pierwszych 5000 punktow: " <<
		approximate_pi(std::vector<point>(input.begin(), input.begin() + 5000), 4) << '\n';
	ostr << "przyblizenie dla wszystkich punktow: " << approximate_pi(input, 4) << '\n';

	write_file(args[2], "4.2\n" + ostr.str() + "\n\n");
}

void solve_three(const std::vector<std::string> &args) {

}