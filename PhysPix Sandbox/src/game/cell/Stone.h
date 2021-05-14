#pragma once

class CellGrid;

#include "Cell.h"

namespace cell
{
	class Stone : public Cell
	{
	public:
		Stone(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		~Stone();

		void OnTick() override;
	};
}