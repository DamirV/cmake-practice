#include "risc.h"

Risc::Risc(int _registersCount = 32) {

	if (_registersCount > 0) {
		registersCount = _registersCount;
		x = new int[registersCount];

		for (int i = 0; i < registersCount; ++i) {
			x[i] = 0;
		}
	}
	else {
		registersCount = 0;
	}
}



Risc::~Risc() {
	if (registersCount != 0) {
		delete[] x;
	}
}

void Risc::Move(int indexTo, int indexFrom) {
	x[indexTo] = x[indexFrom];
	x[indexFrom] = 0;
}

void Risc::Set(int indexTo, int num) {
	x[indexTo] = num;
}

int Risc::Get(int index) {
	return x[index];
}

void Risc::Sum(int indexTo, int index1, int index2) {
	x[indexTo] = x[index1] + x[index2];
}

void Risc::Sub(int indexTo, int index1, int index2) {
	x[indexTo] = x[index1] - x[index2];
}

void Risc::Cpy(int indexTo, int indexFrom) {
	x[indexTo] = x[indexFrom];
}

