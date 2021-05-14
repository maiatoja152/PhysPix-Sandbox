#pragma once

#include "Cell.h"
#include "Fluid.h"

namespace cell
{
	class Steam : public Cell, public Fluid
	{
	public:
		Steam(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		~Steam();

		void OnTick() override;
	};
}
