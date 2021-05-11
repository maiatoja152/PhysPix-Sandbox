#pragma once

namespace cell
{
	class Cell;
}

#include <stdint.h>

namespace cell
{
	class Powder
	{
	protected:
		Powder();

		void PowderMove(Cell* cell);

	public:
		~Powder();
	};
}