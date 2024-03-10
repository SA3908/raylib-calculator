#include "TextBox.h"

const bool TextBox::elementIsOperator(const std::ptrdiff_t index, const std::vector<std::string>& operList) const
{
	for (std::ptrdiff_t opIndex{ 0 }; opIndex < std::ssize(operList); ++opIndex)
	{
		if (m_text[index] == operList[opIndex] || m_text[index] == "(" || m_text[index] == ")")
			return true;
	}
	return false;
}
