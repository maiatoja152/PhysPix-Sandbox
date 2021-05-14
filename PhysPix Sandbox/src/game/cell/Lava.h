#pragma once

#include "Cell.h"
#include "Fluid.h"

namespace cell
{
	class Lava : public Cell, public Fluid
	{
	public:
		Lava(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		~Lava();

		void OnTick() override;

	private:
		void CoolToStone();
	};
}