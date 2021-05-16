#pragma once

#include "Cell.h"
#include "Powder.h"
#include "Flammable.h"

namespace cell
{
	class Gunpowder : public Cell, public Powder, public Flammable
	{
	public:
		Gunpowder(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		~Gunpowder();

		void OnTick() override;
	};
}