#pragma once

class Risc {
private:
	int registersCount;
	int* x;

public:
	Risc(int);
	~Risc();
	void Move(int, int);
	void Set(int, int);
	int Get(int);
	void Sum(int, int, int);
	void Sub(int, int, int);
	void Cpy(int, int);

};