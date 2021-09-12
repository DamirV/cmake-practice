#pragma once
#include <set>
#include <map>
#include <mutex>
#include <map>

class ImageProcessing
{
private:
	int n;
	const int width;
	const int height;

	int** createTable();
	void destroy();
	void startThread();
	int findMinLabel(std::map<int, int>&, int);
	void calculate(int**, char**, int, int, int, int);

public:
	ImageProcessing(int, int, int);
	~ImageProcessing();

	int** startParallel(char**, int&);
	int** start(char**, int&);
};

