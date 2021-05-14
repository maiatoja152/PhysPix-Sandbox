#pragma once

#include "Cell.h"
#include "Fluid.h"
#include "Flammable.h"

namespace cell
{
	class Oil : public Cell, public Fluid, public Flammable
	{
	public:
		Oil(CellGrid* cellGrid, int32_t posX, int32_t posY);
		~Oil();

		void OnTick() override;
	};
}