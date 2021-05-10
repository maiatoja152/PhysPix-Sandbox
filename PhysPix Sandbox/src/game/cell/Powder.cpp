#include "Powder.h"

#include "Cell.h"

#include "CellGrid.h"

namespace cell
{
	Powder::Powder()
	{
	}

	Powder::~Powder()
	{
	}

	void Powder::PowderMove(Cell* cell)
	{
		auto cellGrid = cell->GetCellGrid();
		int32_t posX, posY;
		cell->GetPosition(&posX, &posY);

		int8_t dir = cellGrid->GetDir();
		if (cellGrid->GetCell(posX, posY - 1)->GetID() == cell_id::empty || cellGrid->GetCell(posX, posY - 1)->IsFluid())
		{
			cellGrid->DisplaceFluid(posX, posY, posX, posY - 1);
		}
		else if (cellGrid->GetCell(posX + dir, posY - 1)->GetID() == cell_id::empty || cellGrid->GetCell(posX + dir, posY - 1)->IsFluid())
		{
			cellGrid->DisplaceFluid(posX, posY, posX + dir, posY - 1);
		}
		else if (cellGrid->GetCell(posX - dir, posY - 1)->GetID() == cell_id::empty || cellGrid->GetCell(posX - dir, posY - 1)->IsFluid())
		{
			cellGrid->DisplaceFluid(posX, posY, posX - dir, posY - 1);
		}
	}
}