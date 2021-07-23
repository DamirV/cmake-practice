#ifndef COMPLEX_H
#define COMPLEX_H

#include <string>
#define PI 3.14159265


class Complex
{
private:
	double real, imag;

public:
	Complex();
	Complex(double, double);
	Complex(const Complex&);

	void setReal(double);
	void setImag(double);

	double getReal();
	double getImag();
	double getModule();
	double getArgument();

	Complex& operator=(const Complex&);
	void operator+=(const Complex&);
	void operator-=(const Complex&);
	void operator*=(const Complex&);
	void operator/=(const Complex&);

	std::string toString();

	friend Complex operator+(const Complex&, const Complex&);
	friend Complex operator-(const Complex&, const Complex&);
	friend Complex operator*(const Complex&, const Complex&);
	friend Complex operator/(const Complex&, const Complex&);

};

#endif // COMPLEX_H
