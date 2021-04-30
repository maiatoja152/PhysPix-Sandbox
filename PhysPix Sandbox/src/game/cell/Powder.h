#pragma once

#include "Cell.h"

namespace cell
{
	class Powder : public Cell
	{
	protected:
		void PowderMove();
		void DisplaceFluid(int32_t destX, int32_t destY);
	};
}
