#include "Powder.h"

#include "CellGrid.h"

namespace cell
{
	void Powder::PowderMove()
	{
		if (m_CellGrid->GetCell(m_PosX, m_PosY -1 )->GetID() == 1 || m_CellGrid->GetCell(m_PosX, m_PosY - 1)->IsFluid())
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX, m_PosY - 1);
		}
		else if (m_CellGrid->GetCell(m_PosX + 1, m_PosY - 1)->GetID() == 1 || m_CellGrid->GetCell(m_PosX + 1, m_PosY - 1)->IsFluid())
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX + 1, m_PosY - 1);
		}
		else if (m_CellGrid->GetCell(m_PosX - 1, m_PosY - 1)->GetID() == 1 || m_CellGrid->GetCell(m_PosX - 1, m_PosY - 1)->IsFluid())
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX - 1, m_PosY - 1);
		}
	}
}