#pragma once

#include "Cell.h"
#include "Fluid.h"

namespace cell
{
	class Smoke : public Cell, public Fluid
	{
	public:
		Smoke(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		~Smoke();

		void OnTick() override;
	};
}
