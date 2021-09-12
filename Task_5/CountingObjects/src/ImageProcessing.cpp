#include "ImageProcessing.h"
#include <thread>
#include <map>
#include <vector>
#include <mutex>
#include <iostream>
#include <string>

ImageProcessing::ImageProcessing(int _n, int _width, int _height)
	: n(_n >= 1 ? _n : 1)
	, width(_width)
	, height(_height)
{

}

ImageProcessing::~ImageProcessing() {
	destroy();
}

void ImageProcessing::destroy() {

}

int** ImageProcessing::createTable() {
	int** labels = new int* [height];
	for (int i = 0; i < height; ++i) {
		labels[i] = new int[width];
	}

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			labels[i][j] = 0;
		}
	}

	return labels;
}

int ImageProcessing::findMinLabel(std::map<int, int>& table, int key) {

	int value = table[key];

	if (table.find(value) == table.end()) {
		return value;
	}

	return findMinLabel(table, value);
}


int** ImageProcessing::start(char** image, int& result) { //bad method
	int** labels = createTable();

	int label = 1;
	std::map<int, int> eqTable;

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {

			char A = image[y][x];
			if (A == '0') {
				continue;
			}

			char B = '0';
			char C = '0';

			if (x != 0) {
				B = image[y][x - 1];
			}

			if (y != 0) {
				C = image[y - 1][x];
			}

			if (B == '0' && C == '0' && A == '1') {
				labels[y][x] = label;
				++label;
				continue;
			}

			if (A == '1' && B == '1' && C == '0') {
				labels[y][x] = labels[y][x - 1];
				continue;
			}

			if (A == '1' && B == '0' && C == '1') {
				labels[y][x] = labels[y - 1][x];
				continue;
			}

			if (A == '1' && B == '1' && C == '1') {
				labels[y][x] = labels[y][x - 1];

				if (labels[y][x - 1] != labels[y - 1][x]) {
					if (labels[y - 1][x] > labels[y][x - 1]) {
						eqTable[labels[y - 1][x]] = labels[y][x - 1];
					}
					else {
						eqTable[labels[y][x - 1]] = labels[y - 1][x];
					}
				}

				continue;
			}
		}
	}


	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			std::map<int, int>::iterator it;
			it = eqTable.find(labels[y][x]);
			if (it != eqTable.end()) {
				labels[y][x] = it->second;
			}
		}
	}

	result = label - 1 - eqTable.size();

	return labels;
}

void ImageProcessing::calculate(int** labels, char** image, int width, int height, int n, int k) {
	int offset = width * height / n;
	int label = k + 1;

	int startY = k * offset / width;
	int endY = (k + 1) * offset / width;

	if ((k + 1) * offset % width != 0) {
		++endY;
	}

	for (int y = startY; y < endY; ++y) {
		int startX = 0;
		int endX = width;

		if (y == startY) {
			startX = (k * offset) % width;
		}

		if (y == endY - 1 && k != n - 1) {
			endX = ((k + 1) * offset) % width;

			if (endX == 0) {
				endX = width;
			}
		}

		for (int x = startX; x < endX; ++x) {

			char A = image[y][x];
			if (A == '0') {
				continue;
			}

			char B = x != 0 ? image[y][x - 1] : '0';
			char C = y != 0 ? image[y - 1][x] : '0';

			if (A == '1' && B == '0' && C == '0') {
				labels[y][x] = label;
				label += n;
				continue;
			}

			if (A == '1' && B == '1' && C == '0') {

				if (labels[y][x - 1] != 0) {
					labels[y][x] = labels[y][x - 1];
				}
				else {
					labels[y][x] = label;
					label += n;
				}

				continue;
			}

			if (A == '1' && B == '0' && C == '1') {

				if (labels[y - 1][x] != 0) {
					labels[y][x] = labels[y - 1][x];
				}
				else {
					labels[y][x] = label;
					label += n;
				}
				continue;
			}

			if (A == '1' && B == '1' && C == '1') {

				if (labels[y][x - 1] != 0) {
					labels[y][x] = labels[y][x - 1];
				}
				else if (labels[y - 1][x] != 0) {
					labels[y][x] = labels[y - 1][x];
				}
				else {
					labels[y][x] = label;
					label += n;
				}

				continue;
			}

		}
	}
}


int** ImageProcessing::startParallel(char** image, int& result) {
	int** labels = createTable();

	std::map<int, int> eqTable;
	std::mutex m;

	std::vector<std::thread> threads;
	std::vector<std::thread> threadsForTable;
	std::vector<std::thread> finalThreads;

	std::set<int> labelsSet;

	auto fillAdjacencyTable = [&m, &eqTable, &labels](int width, int height, int n, int k)
	{
		auto fillTable = [&m, &eqTable](int max, int min) {
			if (eqTable.find(max) == eqTable.end()) {
				m.lock();
				eqTable[max] = min;
				m.unlock();
			}
			else {
				int tmpMin = eqTable[max];

				if (tmpMin > min) {
					m.lock();
					eqTable[tmpMin] = min;
					eqTable[max] = min;
					m.unlock();
				}
				else if (tmpMin < min) {
					m.lock();
					eqTable[min] = tmpMin;
					m.unlock();
				}
			}
		};

		int offset = width * height / n;

		int startY = k * offset / width;
		int endY = (k + 1) * offset / width;

		if ((k + 1) * offset % width != 0) {
			++endY;
		}

		for (int y = startY; y < endY; ++y) {
			int startX = 0;
			int endX = width;

			if (y == startY) {
				startX = (k * offset) % width;
			}

			if (y == endY - 1 && k != n - 1) {
				endX = ((k + 1) * offset) % width;

				if (endX == 0) {
					endX = width;
				}
			}

			for (int x = startX; x < endX; ++x) {

				int size = eqTable.size();
				int A = labels[y][x];
				if (A == 0) {
					continue;
				}

				int B = x != 0 ? labels[y][x - 1] : 0;
				int C = y != 0 ? labels[y - 1][x] : 0;

				if (B == 0 && C == 0 || A == B && B == C) {
					continue;
				}

				if (B != 0 && C == 0) {

					if (B != A) {
						int max = std::max(A, B);
						int min = std::min(A, B);

						fillTable(max, min);
					}
					continue;
				}

				if (B == 0 && C != 0) {
					if (C != A) {
						int max = std::max(A, C);
						int min = std::min(A, C);

						fillTable(max, min);
					}
					continue;
				}

				if (B == C) {

					int max = std::max(A, B);
					int min = std::min(A, B);

					fillTable(max, min);

					continue;

				}
				else {
					if (A == B) {
						int max = std::max(A, C);
						int min = std::min(A, C);

						fillTable(max, min);

						continue;
					}
					else if (A == C) {

						int max = std::max(A, B);
						int min = std::min(A, B);

						fillTable(max, min);

						continue;

					}
					else {
						int max = std::max(std::max(A, B), C);
						int min = std::min(std::min(A, B), C);
						int middle = A + B + C - max - min;

						fillTable(max, min);
						fillTable(middle, min);
					}
				}
			}
		}
	};

	for (int i = 0; i < n - 1; ++i) {
		threads.emplace_back(&ImageProcessing::calculate, this, labels, image, width, height, n, i);
	}
	calculate(labels, image, width, height, n, n - 1);

	for (auto& t : threads) {
		t.join();
	}


	for (int i = 0; i < n - 1; ++i) {
		threadsForTable.emplace_back(fillAdjacencyTable, width, height, n, i);
	}
	fillAdjacencyTable(width, height, n, n - 1);

	for (auto& t : threadsForTable) {
		t.join();
	}

	for (auto& t : eqTable) {
		eqTable[t.first] = findMinLabel(eqTable, t.first);
	}

	auto replaceLabels = [&labels, &eqTable, &m, &labelsSet](int width, int height, int n, int k) {
		int offset = width * height / n;
		int label = k + 1;

		int startY = k * offset / width;
		int endY = (k + 1) * offset / width;

		if ((k + 1) * offset % width != 0) {
			++endY;
		}

		for (int y = startY; y < endY; ++y) {
			int startX = 0;
			int endX = width;

			if (y == startY) {
				startX = (k * offset) % width;
			}

			if (y == endY - 1 && k != n - 1) {
				endX = ((k + 1) * offset) % width;

				if (endX == 0) {
					endX = width;
				}
			}

			for (int x = startX; x < endX; ++x) {
				int tmpLabel = labels[y][x];

				if (labels[y][x] != 0) {
					if (eqTable.find(tmpLabel) != eqTable.end()) {
						labels[y][x] = eqTable[tmpLabel];
					}
					m.lock();
					labelsSet.insert(labels[y][x]);
					m.unlock();
				}
			}
		}
	};

	for (int i = 0; i < n - 1; ++i) {
		finalThreads.emplace_back(replaceLabels, width, height, n, i);
	}
	replaceLabels(width, height, n, n - 1);

	for (auto& t : finalThreads) {
		t.join();
	}

	result = labelsSet.size();

	return labels;
}

void ImageProcessing::startThread() {

}
