#pragma once

namespace Constants
{
	 const std::string div{ "\xc3\xb7"};
	 const std::string mul{ "\xc3\x97" };
	 const std::string sqrt{ "\xe2\x88\x9a" };

	 const std::string square{ "\xc2\xb2" };

	 const std::string fraction{ "\xc2\xbd" };
	 const std::string backspace{ "\xe2\x8c\xab" };

	 namespace Precedence
	 {
		 constexpr int equal{ -1 };
		 constexpr int lower{ 0 };
		 constexpr int higher{ 1 };
	 }
}