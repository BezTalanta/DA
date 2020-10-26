#pragma once
// Линии
template <typename X, typename Y>
struct TLine
{
	//// Ключ
	//unsigned short key;
	//// Значение
	//std::string value;

public:
	// Ключ
	X key;
	// Значение
	Y * value;

	void Clear() {
		delete value;
	}
};