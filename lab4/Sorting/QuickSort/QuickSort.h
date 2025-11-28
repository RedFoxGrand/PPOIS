#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>
size_t PivotSelection(vector<T>& vec, size_t left, size_t right) {
	T pivot = vec[right];
	size_t i = left - 1;

	for (size_t j = left; j < right; j++) {
		if (vec[j] < pivot) {
			i++;
			swap(vec[i], vec[j]);
		}
	}
	swap(vec[i + 1], vec[right]);

	return i + 1;
}

template <typename T>
void QuickSort(vector<T>& vec, size_t left, size_t right) {
	if (left < right) {
		size_t indexPivot = PivotSelection(vec, left, right);

		if (indexPivot > 0) QuickSort(vec, left, indexPivot - 1);
		if (indexPivot + 1 <= right) QuickSort(vec, indexPivot + 1, right);
	}
}

template <typename T>
size_t PivotSelection(T* mas, size_t left, size_t right) {
	T pivot = mas[right];
	size_t i = left - 1;

	for (size_t j = left; j < right; j++) {
		if (mas[j] < pivot) {
			i++;
			swap(mas[i], mas[j]);
		}
	}
	swap(mas[i + 1], mas[right]);

	return i + 1;
}

template <typename T>
void QuickSort(T* mas, size_t left, size_t right) {
	if (left < right) {
		size_t indexPivot = PivotSelection(mas, left, right);

		if (indexPivot > 0) QuickSort(mas, left, indexPivot - 1);
		if (indexPivot + 1 <= right) QuickSort(mas, indexPivot + 1, right);
	}
}