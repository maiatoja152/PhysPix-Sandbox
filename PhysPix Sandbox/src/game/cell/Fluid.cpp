#include "Fluid.h"

#include "Cell.h"
#include "CellGrid.h"

#include <iostream>

namespace cell
{
	Fluid::Fluid()
	{
		m_FluidDirection = 0;
	}

	Fluid::~Fluid()
	{
	}

	void Fluid::FluidMove(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		if (m_FluidDirection == 0)
			std::cout << "[WARNING] m_FluidDirection is 0, the fluid will not move correctly. Make sure to initialize m_FluidDirection as 1 or -1." << std::endl;

		if (cellGrid->GetCell(posX, posY + m_FluidDirection)->GetID() == cell_id::empty)
		{
			cellGrid->SwapCells(posX, posY, posX, posY + m_FluidDirection);
			return;
		}

		int8_t dir = cellGrid->GetDir();
		if (cellGrid->GetCell(posX + dir, posY + m_FluidDirection)->GetID() == cell_id::empty)
		{
			cellGrid->SwapCells(posX, posY, posX + dir, posY + m_FluidDirection);
		}
		else if (cellGrid->GetCell(posX - dir, posY + m_FluidDirection)->GetID() == cell_id::empty)
		{
			cellGrid->SwapCells(posX, posY, posX - dir, posY + m_FluidDirection);
		}
		else if (cellGrid->GetCell(posX + dir, posY)->GetID() == cell_id::empty)
		{
			cellGrid->SwapCells(posX, posY, posX + dir, posY);
		}
		else if (cellGrid->GetCell(posX - dir, posY)->GetID() == cell_id::empty)
		{
			cellGrid->SwapCells(posX, posY, posX - dir, posY);
		}
	}
}