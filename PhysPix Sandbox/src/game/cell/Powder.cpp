#include "Powder.h"

#include "CellGrid.h"

namespace cell
{
	void Powder::PowderMove()
	{
		int8_t dir = m_CellGrid->GetDir();
		if (m_CellGrid->GetCell(m_PosX, m_PosY -1 )->GetID() == 1 || m_CellGrid->GetCell(m_PosX, m_PosY - 1)->IsFluid())
		{
			if (m_CellGrid->GetCell(m_PosX + dir, m_PosY)->GetID() == 1)
			{
				m_CellGrid->SwapCells(m_PosX, m_PosY - 1, m_PosX + dir, m_PosY);
				m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX, m_PosY - 1);
			}
			else if (m_CellGrid->GetCell(m_PosX - dir, m_PosY)->GetID() == 1)
			{
				m_CellGrid->SwapCells(m_PosX, m_PosY - 1, m_PosX - dir, m_PosY);
				m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX, m_PosY - 1);
			}
			else
			{
				m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX, m_PosY - 1);
			}
		}
		else if (m_CellGrid->GetCell(m_PosX + dir, m_PosY - 1)->GetID() == 1 || m_CellGrid->GetCell(m_PosX + dir, m_PosY - 1)->IsFluid())
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX + dir, m_PosY - 1);
		}
		else if (m_CellGrid->GetCell(m_PosX - dir, m_PosY - 1)->GetID() == 1 || m_CellGrid->GetCell(m_PosX - dir, m_PosY - 1)->IsFluid())
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX - dir, m_PosY - 1);
		}
	}
}