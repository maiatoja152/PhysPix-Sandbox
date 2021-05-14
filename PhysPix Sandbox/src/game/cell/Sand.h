#pragma once

#include "Cell.h"
#include "Powder.h"

namespace cell
{
	class Sand : public Cell, public Powder
	{
	public:
		Sand(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		~Sand();

		void OnTick() override;
	};
}