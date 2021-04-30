#include "Powder.h"

#include "CellGrid.h"

namespace cell
{
	void Powder::PowderMove()
	{
		int8_t dir = m_CellGrid->GetDir();
		if (m_CellGrid->GetCell(m_PosX, m_PosY -1 )->GetID() == 1 || m_CellGrid->GetCell(m_PosX, m_PosY - 1)->IsFluid())
		{
			DisplaceFluid(m_PosX, m_PosY - 1);
		}
		else if (m_CellGrid->GetCell(m_PosX + dir, m_PosY - 1)->GetID() == 1 || m_CellGrid->GetCell(m_PosX + dir, m_PosY - 1)->IsFluid())
		{
			DisplaceFluid(m_PosX + dir, m_PosY - 1);
		}
		else if (m_CellGrid->GetCell(m_PosX - dir, m_PosY - 1)->GetID() == 1 || m_CellGrid->GetCell(m_PosX - dir, m_PosY - 1)->IsFluid())
		{
			DisplaceFluid(m_PosX - dir, m_PosY - 1);
		}
	}

	void Powder::DisplaceFluid(int32_t destX, int32_t destY)
	{
		int8_t dir = m_CellGrid->GetDir();
		// Check left and right
		if (m_CellGrid->GetCell(destX + dir, destY)->GetID() == 1)
		{
			m_CellGrid->SwapCells(destX, destY, destX + dir, destY);
			m_CellGrid->SwapCells(m_PosX, m_PosY, destX, destY);
		}
		else if (m_CellGrid->GetCell(destX - dir, destY)->GetID() == 1)
		{
			m_CellGrid->SwapCells(destX, destY, destX - dir, destY);
			m_CellGrid->SwapCells(m_PosX, m_PosY, destX, destY);
		}
		// Check upper left and right
		else if (m_CellGrid->GetCell(destX + dir, destY + 1)->GetID() == 1)
		{
			m_CellGrid->SwapCells(destX, destY, destX + dir, destY + 1);
			m_CellGrid->SwapCells(m_PosX, m_PosY, destX, destY);
		}
		else if (m_CellGrid->GetCell(destX - dir, destY + 1)->GetID() == 1)
		{
			m_CellGrid->SwapCells(destX, destY, destX - dir, destY + 1);
			m_CellGrid->SwapCells(m_PosX, m_PosY, destX, destY);
		}
		else
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, destX, destY);
		}
	}
}