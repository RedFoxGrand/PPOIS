#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>
void SortingNetwork(vector<T>& vec) {
	if (vec.size() <= 1) return;

	for (size_t phase = 0; phase < vec.size(); phase++) {
		size_t start = (phase % 2 == 0) ? 0 : 1;
		for (size_t i = start; i < vec.size() - 1; i += 2) {
			if (vec[i + 1] < vec[i]) swap(vec[i], vec[i + 1]);
		}
	}
}

template <typename T>
void SortingNetwork(T* mas, size_t size) {
	if (size <= 1) return;

	for (size_t phase = 0; phase < size; phase++) {
		size_t start = (phase % 2 == 0) ? 0 : 1;
		for (size_t i = start; i < size - 1; i += 2) {
			if (mas[i + 1] < mas[i]) swap(mas[i], mas[i + 1]);
		}
	}
}