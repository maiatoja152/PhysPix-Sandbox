#pragma once

#include "Cell.h"
#include "Fluid.h"

namespace cell
{
	class Lava : public Cell, public Fluid
	{
	public:
		Lava(CellGrid* cellGrid, int32_t posX, int32_t posY);
		~Lava();

		void OnTick() override;

	private:
		void CoolToStone();
	};
}