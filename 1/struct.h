#pragma once
// �����
template <typename X, typename Y>
struct TLine
{
	//// ����
	//unsigned short key;
	//// ��������
	//std::string value;

public:
	// ����
	X key;
	// ��������
	Y * value;

	void Clear() {
		delete value;
	}
};