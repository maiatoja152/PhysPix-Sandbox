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

	void Powder::PowderMove(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		int8_t dir = cellGrid->GetDir();
		if (cellGrid->GetCell(posX, posY - 1)->GetID() == cell_id::empty || cellGrid->GetCell(posX, posY - 1)->IsFluid())
		{
			DisplaceFluid(cellGrid, posX, posY, posX, posY - 1);
		}
		else if (cellGrid->GetCell(posX + dir, posY - 1)->GetID() == cell_id::empty || cellGrid->GetCell(posX + dir, posY - 1)->IsFluid())
		{
			DisplaceFluid(cellGrid, posX, posY, posX + dir, posY - 1);
		}
		else if (cellGrid->GetCell(posX - dir, posY - 1)->GetID() == cell_id::empty || cellGrid->GetCell(posX - dir, posY - 1)->IsFluid())
		{
			DisplaceFluid(cellGrid, posX, posY, posX - dir, posY - 1);
		}
	}

	void Powder::DisplaceFluid(CellGrid* cellGrid, uint16_t posX, uint16_t posY, int32_t destX, int32_t destY)
	{
		int8_t dir = cellGrid->GetDir();
		// Check left and right
		if (cellGrid->GetCell(destX + dir, destY)->GetID() == cell_id::empty)
		{
			cellGrid->SwapCells(destX, destY, destX + dir, destY);
			cellGrid->SwapCells(posX, posY, destX, destY);
		}
		else if (cellGrid->GetCell(destX - dir, destY)->GetID() == cell_id::empty)
		{
			cellGrid->SwapCells(destX, destY, destX - dir, destY);
			cellGrid->SwapCells(posX, posY, destX, destY);
		}
		// Check upper left and right
		else if (cellGrid->GetCell(destX + dir, destY + 1)->GetID() == cell_id::empty)
		{
			cellGrid->SwapCells(destX, destY, destX + dir, destY + 1);
			cellGrid->SwapCells(posX, posY, destX, destY);
		}
		else if (cellGrid->GetCell(destX - dir, destY + 1)->GetID() == cell_id::empty)
		{
			cellGrid->SwapCells(destX, destY, destX - dir, destY + 1);
			cellGrid->SwapCells(posX, posY, destX, destY);
		}
		else
		{
			cellGrid->SwapCells(posX, posY, destX, destY);
		}
	}
}