#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include "ImageProcessing.h"
#include <thread>
#include <map>


char** generateImage(int width, int height) {
	char** image = new char* [height];

	for (int i = 0; i < height; ++i) {
		image[i] = new char[width];
	}

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			image[i][j] = rand() % 2 + 48;
		}
	}

	return image;
}

void printImage(char** image, int width, int height) {
	std::string result = "";
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			result += image[i][j];
		}
		result += '\n';
	}

	std::cout << result << std::endl;
}


void printLabels(int** labels, int width, int height) {
	std::string result = "";
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			result += std::to_string(labels[i][j]) + " ";
		}
		result += '\n';
	}

	std::cout << result << std::endl;
}

void main() {
	
	int height = 1024;
	int width = 1024;
	int n = 8;
	char** image = generateImage(width, height);
	printImage(image, width, height);
	std::cout << std::endl;
	
	ImageProcessing im(n, width, height);
	int result;
	
	clock_t start = clock();
	int** labels = im.start(image, result);
	clock_t end = clock();
	printLabels(labels, width, height);

	std::cout << "Time: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << std::endl;
	std::cout << std::endl;
	std::cout <<"Result: " << result << std::endl;

	for (int i = 0; i < height; ++i) {
		delete[] image[i];
	}
	delete[] image;

	for (int i = 0; i < height; ++i) {
		delete[] labels[i];
	}

	delete[] labels;
	return;
}

