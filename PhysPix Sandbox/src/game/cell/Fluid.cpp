#include "Fluid.h"

#include "CellGrid.h"

#include <iostream>

namespace cell
{
	Fluid::Fluid()
		: m_FluidDirection(0)
	{
		m_IsFluid = true;
	}

	Fluid::~Fluid()
	{
	}

	void Fluid::FluidMove()
	{
		if (m_FluidDirection == 0)
			std::cout << "[WARNING] m_FluidDirection is 0, the fluid will not move. Make sure to initialize m_FluidDirection as 1 or -1." << std::endl;

		if (m_CellGrid->GetCell(m_PosX, m_PosY + m_FluidDirection)->GetID() == 1)
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX, m_PosY + m_FluidDirection);
			return;
		}

		int8_t dir = m_CellGrid->GetDir();
		if (m_CellGrid->GetCell(m_PosX + dir, m_PosY + m_FluidDirection)->GetID() == 1)
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX + dir, m_PosY + m_FluidDirection);
		}
		else if (m_CellGrid->GetCell(m_PosX - dir, m_PosY + m_FluidDirection)->GetID() == 1)
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX - dir, m_PosY + m_FluidDirection);
		}
		else if (m_CellGrid->GetCell(m_PosX + dir, m_PosY)->GetID() == 1)
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX + dir, m_PosY);
		}
		else if (m_CellGrid->GetCell(m_PosX - dir, m_PosY)->GetID() == 1)
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX - dir, m_PosY);
		}
	}
}