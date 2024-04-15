#pragma once
#include <string>
#include <vector>
#include <raylib.h>

class Calculator;

struct IndexPair //iterate through an element of an element within an array
{
	std::ptrdiff_t inIndex{}; //index within outIndex (for string arrays/vectors)
	std::ptrdiff_t outIndex{};
};

class TextBox //display, align and manoeuvre through text
{
	friend void debug(Calculator& session);
public:
	TextBox()
	{
		m_text.reserve(10);
	}

	TextBox(float x, float y, int width, int height, bool rightAlign = false)
		:m_x{ x }, m_y{ y }, m_width{ width }, m_height{ height }, m_rightAlign{ rightAlign }
	{
		m_text.reserve(10);
	}

	//OVERLOADS

	std::string& operator[] (const std::ptrdiff_t index) { return m_text[index]; }
	const std::string& operator[] (const std::ptrdiff_t index) const { return m_text[index]; }

	const std::string& back() const { return m_text.back(); }
	std::string& back() { return m_text.back(); }
	constexpr bool empty() const { return m_text.empty(); }
	void clear() { m_text.clear(); }
	constexpr std::ptrdiff_t ssize() const { return std::ssize(m_text); }

	void pop_back() { m_text.pop_back(); }
	void push_back(const std::string& text) { m_text.push_back(text); }
	void emplace_back(const std::string& text) { m_text.emplace_back(text); }

	//IMPLEMENTATION

	std::vector<std::string>& getText() { return m_text; }
	const bool endIndex() const { return m_endIndex; }

	void updateIndex(); //ensure that m_index catches up to final value of expression if m_endIndex is true (for calculator logic).
	void traverseArrowKey(); //if arrow keys are pressed move the " | " left/right. 
	void drawText(Font& font); //draw m_text on the screen using coordinates given and alignment.
	
	void insertIndex(const std::string& ch, const std::vector<std::string>& operList); //insert characters at the indexes of m_index (using calculator logic).
	void deleteIndex(); //remove character at m_index and modify m_index after the character is deleted
	
private:
	const bool elementIsOperator (const std::ptrdiff_t index, const std::vector<std::string>& operList) const;


	float m_x{ 0 };
	float m_y{ 0 };
	int m_width{ 0 };
	int m_height{ 0 };

	std::vector<std::string> m_text{};
	IndexPair m_index{0, 0}; //this index allows modification of m_text and holds cursor position
	bool m_endIndex{ true }; //for index to keep up with last index of m_text

	bool m_drawingState{ true }; //prevention for m_text exceeding m_width
	bool m_rightAlign{};
};
