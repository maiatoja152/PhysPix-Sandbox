#pragma once

#include "Cell.h"
#include "Fluid.h"

namespace cell
{
	class Steam : public Cell, public Fluid
	{
	public:
		Steam(CellGrid* cellGrid, int32_t posX, int32_t posY);
		~Steam();

		void OnTick() override;
	};
}
