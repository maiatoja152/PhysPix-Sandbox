#pragma once

#include "Cell.h"
#include "Fluid.h"

namespace cell
{
	class Water : public Cell, public Fluid
	{
	public:
		Water(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		~Water();

		void OnTick() override;
	};
}