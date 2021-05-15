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

		static bool IsValidFluidDisplacement(uint8_t cellDensity, uint8_t destCellDensity, int8_t fluidDir = -1);
		static void CheckValidFluidDir(int8_t fluidDir);

	protected:
		void FluidMove(Cell* cell);
	};
}