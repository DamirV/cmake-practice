#include <iostream>
#include "Complex.h"
#include <vector>

void printComplex(Complex&);

void printComplexPolynomial(Complex& z, std::vector<Complex>& arr) {
	int n = arr.size();
	std::string result = "";

	for (int i = 0; i < n; ++i) {
		result += "(" + arr[i].toString() + ")" + "(" + z.toString() + ")" + "^" + std::to_string(n - i - 1);

		if (i != n - 1) {
			result += " + ";
		}
	}

	std::cout << result << std::endl;
}

Complex calcPolynomial(Complex& z, std::vector<Complex>& arr) {
	//printComplexPolynomial(z, arr);
	int n = arr.size();
	Complex res(0, 0);
	Complex tmp;

	for (int i = 0; i < n; ++i) {
		tmp = Complex(1, 0);
		for (int j = i + 1; j < n; ++j) {
			tmp *= z;
		}

		tmp *= arr[i];
		res += tmp;
	}

	return res;
}

void printComplex(Complex& c) {
	std::cout << c.toString() << std::endl;
}

std::vector<Complex> createComplexVector() {
	std::vector<Complex> arr;
	arr.push_back(Complex(1, 1));
	arr.push_back(Complex(-2, 2));
	arr.push_back(Complex(3, -3));
	arr.push_back(Complex(-4, -4));

	return arr;
}

int main() {
	std::vector<Complex> arr(createComplexVector());
	Complex z(-5, 2);

	Complex result(calcPolynomial(z, arr));

	printComplex(result);
	std::cout << "-----------------------------" << std::endl;

	return 0;
}
