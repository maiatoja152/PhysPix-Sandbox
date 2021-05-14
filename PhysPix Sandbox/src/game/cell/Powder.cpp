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
		uint16_t posX, posY;
		cell->GetPosition(&posX, &posY);

		// Check down cell
		Cell* currCell = cellGrid->GetCell(posX, posY - 1);
		if (currCell->GetID() == cell_id::empty || currCell->IsFluid())
		{
			cellGrid->DisplaceFluid(posX, posY, posX, posY - 1);
			return;
		}

		// Check bottom left and right cells as well as the left and right cells on the same y-level
		int8_t dir = cellGrid->GetDir();
		currCell = cellGrid->GetCell(posX + dir, posY - 1);
		if ((currCell->GetID() == cell_id::empty || currCell->IsFluid()) && (cellGrid->GetCell(posX + dir, posY)->GetID() == cell_id::empty || cellGrid->GetCell(posX + dir, posY)->IsFluid()))
		{
			cellGrid->DisplaceFluid(posX, posY, posX + dir, posY - 1);
			return;
		}
		currCell = cellGrid->GetCell(posX - dir, posY - 1);
		if ((currCell->GetID() == cell_id::empty || currCell->IsFluid()) && (cellGrid->GetCell(posX + dir, posY)->GetID() == cell_id::empty || cellGrid->GetCell(posX + dir, posY)->IsFluid()))
		{
			cellGrid->DisplaceFluid(posX, posY, posX - dir, posY - 1);
			return;
		}
	}
}