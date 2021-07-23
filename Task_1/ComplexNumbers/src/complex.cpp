#include "Complex.h"
#include "math.h"

Complex::Complex() {
	real = 0;
	imag = 0;
}

Complex::Complex(const Complex& c) {
	real = c.real;
	imag = c.imag;
}

Complex::Complex(double _real = 0, double _imag = 0) {
	real = _real;
	imag = _imag;
}


void Complex::setImag(double _imag) {
	imag = _imag;
}

void Complex::setReal(double _real) {
	real = _real;
}

double Complex::getReal() {
	return real;
}

double Complex::getImag() {
	return imag;
}

double Complex::getModule() {
	return sqrt(pow(real, 2) + pow(imag, 2));
}

double Complex::getArgument() {
	return atan2(imag, real);
}

Complex& Complex::operator=(const Complex& c) {
	real = c.real;
	imag = c.imag;

	return *this;
}

void Complex::operator+=(const Complex& c) {
	real += c.real;
	imag += c.imag;
}

void Complex::operator-=(const Complex& c) {
	real -= c.real;
	imag -= c.imag;
}

void Complex::operator*=(const Complex& c) {
	double tmpImag = real * c.imag + imag * c.real;

	real = real * c.real - imag * c.imag;
	imag = tmpImag;
}

void Complex::operator/=(const Complex& c) {
	double tmpImag = (imag * c.real - real * c.imag) / (pow(c.real, 2) + pow(c.imag, 2));

	real = (real * c.real + imag * c.imag) / (pow(c.real, 2) + pow(c.imag, 2));
	imag = tmpImag;
}

std::string Complex::toString() {
	std::string resultStr = std::to_string(real);
	if (imag >= 0) {
		resultStr += " + " + std::to_string(imag) + "i";;
	}
	else {
		resultStr += " - " + std::to_string(-1 * imag) + "i";
	}

	return resultStr;
}

Complex operator+ (const Complex& c1, const Complex& c2) {
	return Complex(c1.real + c2.real, c1.imag + c2.imag);
}

Complex operator- (const Complex& c1, const Complex& c2) {
	return Complex(c1.real - c2.real, c1.imag - c2.imag);
}

Complex operator* (const Complex& c1, const Complex& c2) {
	return Complex(c1.real * c2.real - c1.imag * c2.imag, c1.real * c2.imag + c1.imag * c2.real);
}

Complex operator/ (const Complex& c1, const Complex& c2) {
	return Complex((c1.real * c2.real + c1.imag * c2.imag) / (pow(c2.real, 2) + pow(c2.imag, 2)),
		(c1.imag * c2.real - c1.real * c2.imag) / (pow(c2.real, 2) + pow(c2.imag, 2)));
}