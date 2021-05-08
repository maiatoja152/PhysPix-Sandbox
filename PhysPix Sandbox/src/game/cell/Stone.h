#pragma once

class CellGrid;

#include "Cell.h"

namespace cell
{
	class Stone : public Cell
	{
	public:
		Stone(CellGrid* cellGrid, int32_t posX, int32_t posY);
		~Stone();
	};
}