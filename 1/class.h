#pragma once
#include <iostream>
#include <string>
// TLine<unsigned short, std::string> - T
// Вектор
template <typename T>
class TVector {

	// Массив линий
	T *lines;
	// Размер массива
	unsigned long long size;
	// Макс размер
	unsigned long long capacity;

public:
	TVector() {
		lines = NULL;
		size = 0;
		capacity = 0;
	}

	~TVector() {		
		delete[] lines;
	}

	// Clear void
	void Clean() {
		for (int i = 0; i < size; i++)
		{
			lines[i].Clear();
		}
	}

	// Метод добавления новой линии в массив
	void PushBack(T &t) {
		if (size < capacity) {
			lines[size++] = t;
			return;
		}

		unsigned long long newCap = capacity * 2 + 1;
		T *tmpLines = new T[newCap];
		for (int i = 0; i < size; i++)
		{
			tmpLines[i] = lines[i];
		}
		tmpLines[size] = t;
		//Clean();
		delete[] lines;
		lines = tmpLines;
		size++;
		capacity = newCap;
	}

	// Получение линии из массива по индексу
	T * Get(unsigned long long index) {
		return &lines[index];
	}

	// Установка линии в массив по индексу
	void Set(T &a, unsigned long long index) {
		lines[index] = a;
	}

	// Вывод вектора на экран
	void PrintAll() {
		for (unsigned long long i = 0; i < size; ++i)
		{
			std::cout << lines[i].key << '\t' << *lines[i].value << std::endl;
		}
	}

	// Получение размера вектора
	unsigned long long Size() {
		return size;
	}

	unsigned long long Cap() {
		return capacity;
	}
};