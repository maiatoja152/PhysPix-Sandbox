#pragma once

#include "Cell.h"
#include "Fluid.h"
#include "Flammable.h"

namespace cell
{
	class Hydrogen : public Cell, public Fluid, public Flammable
	{
	public:
		Hydrogen(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		~Hydrogen();

		void OnTick() override;
	};
}
