#pragma once

class CellGrid;

#include "Cell.h"
#include "Flammable.h"

namespace cell
{
	class Wood : public Cell, public Flammable
	{
	public:
		Wood(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		~Wood();

		void OnTick() override;
	};
}