#pragma once

class CellGrid;

#include <stdint.h>

namespace cell
{
	class Fluid
	{
	protected:
		int8_t m_FluidDirection;

		Fluid();
	public:
		~Fluid();

	protected:
		void FluidMove(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
	};
}