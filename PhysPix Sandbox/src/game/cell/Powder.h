#pragma once

class CellGrid;

#include <stdint.h>

namespace cell
{
	class Powder
	{
	protected:
		void PowderMove(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		void DisplaceFluid(CellGrid* cellGrid, uint16_t posX, uint16_t posY, int32_t destX, int32_t destY);
	};
}
