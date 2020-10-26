#include "class.h"
#include "struct.h"
#include <cstring>

// Сама сортировка вектора
//TVector<TLine<unsigned int, std::string> > Sort(TVector<TLine<unsigned int, std::string> > & vct, unsigned int max) {
void Sort(TVector<TLine<unsigned int, std::string> > & vct, unsigned int max){
	TVector<TLine<unsigned int, std::string> > result;
	// Массив количества найденных элементов в векторе
	unsigned int *sortArrCountOfElements = new unsigned int[max + 1];
	// Массив индекса правильного вхождения элемента
	unsigned int *sortArrIndexOfEnter = new unsigned int[max + 1];
	// Обнуление массивов
	memset(sortArrIndexOfEnter, 0, (max + 1) * sizeof(unsigned int));
	memset(sortArrCountOfElements, 0, (max + 1) * sizeof(unsigned int));
	// Получение размера исходного вектора введенных строк
	unsigned long long sizeOfVector = vct.Size();
	
	// Заполнение массива пустыми линиями
	for (unsigned long long i = 0; i < sizeOfVector; i++)
	{
		TLine<unsigned int, std::string> *tmp = new TLine<unsigned int, std::string>;
		/*tmp->key = 0;
		tmp->value = nullptr;*/
		result.PushBack(*tmp);
	}

	// Проверка на пустой ввод
	if (sizeOfVector == 0) {
		//return result;
		return;
	}

	// Подсчет количества элементов
	for (unsigned long long i = 0; i < sizeOfVector; i++)
	{
		sortArrCountOfElements[vct.Get(i)->key]++;
	}

	// Заполнение массива индексов
	unsigned long long curIndex = -1;
	for (unsigned long long i = 0; i <= max; i++)
	{
		unsigned int tmp = sortArrCountOfElements[i];
		if (tmp != 0) {
			curIndex += tmp;
			sortArrIndexOfEnter[i] = curIndex;
		}
	}

	for (unsigned long long i = sizeOfVector; i > 0; i--)
	{
		TLine<unsigned int, std::string> * tmp = new TLine<unsigned int, std::string>;
		tmp = vct.Get(i - 1);
		unsigned int tmpIndex = sortArrIndexOfEnter[tmp->key];
		result.Set(*tmp, tmpIndex);
		if (tmpIndex != 0) {
			sortArrIndexOfEnter[tmp->key]--;
		}
	}
	delete[] sortArrIndexOfEnter;
	delete[] sortArrCountOfElements;
	result.PrintAll();
	return;
}