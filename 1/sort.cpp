#include "class.h"
#include "struct.h"
#include <cstring>

// ���� ���������� �������
//TVector<TLine<unsigned int, std::string> > Sort(TVector<TLine<unsigned int, std::string> > & vct, unsigned int max) {
void Sort(TVector<TLine<unsigned int, std::string> > & vct, unsigned int max){
	TVector<TLine<unsigned int, std::string> > result;
	// ������ ���������� ��������� ��������� � �������
	unsigned int *sortArrCountOfElements = new unsigned int[max + 1];
	// ������ ������� ����������� ��������� ��������
	unsigned int *sortArrIndexOfEnter = new unsigned int[max + 1];
	// ��������� ��������
	memset(sortArrIndexOfEnter, 0, (max + 1) * sizeof(unsigned int));
	memset(sortArrCountOfElements, 0, (max + 1) * sizeof(unsigned int));
	// ��������� ������� ��������� ������� ��������� �����
	unsigned long long sizeOfVector = vct.Size();
	
	// ���������� ������� ������� �������
	for (unsigned long long i = 0; i < sizeOfVector; i++)
	{
		TLine<unsigned int, std::string> *tmp = new TLine<unsigned int, std::string>;
		/*tmp->key = 0;
		tmp->value = nullptr;*/
		result.PushBack(*tmp);
	}

	// �������� �� ������ ����
	if (sizeOfVector == 0) {
		//return result;
		return;
	}

	// ������� ���������� ���������
	for (unsigned long long i = 0; i < sizeOfVector; i++)
	{
		sortArrCountOfElements[vct.Get(i)->key]++;
	}

	// ���������� ������� ��������
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