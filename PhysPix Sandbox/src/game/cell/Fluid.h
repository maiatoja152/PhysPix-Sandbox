#pragma once

namespace cell
{
	class Cell;
}

#include <stdint.h>

namespace cell
{
	class Fluid
	{
	protected:
		int8_t m_FluidDir;

		Fluid();
	public:
		~Fluid();

	protected:
		void FluidMove(Cell* cell);
	};
}