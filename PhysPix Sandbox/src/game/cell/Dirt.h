#pragma once

#include "Cell.h"
#include "Powder.h"

namespace cell
{
	class Dirt : public Cell, public Powder
	{
	public:
		Dirt(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		~Dirt();

		void OnTick() override;
	};
}