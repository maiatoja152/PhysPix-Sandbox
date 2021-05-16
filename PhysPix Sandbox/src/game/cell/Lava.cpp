#include "Lava.h"

#include "CellGrid.h"

#include "Flammable.h"

#include "Empty.h"
#include "Stone.h"
#include "Steam.h"

#include <cstdlib>

namespace cell
{
	Lava::Lava(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::lava;

		m_Color = cell_color::lava;

		m_IsFluid = true;
		m_FluidDir = -1;
		m_Density = cell_density::lava;

		m_BurnsSurroudings = true;
	}

	Lava::~Lava()
	{
	}

	void Lava::OnTick()
	{
		CoolToStone();

		FluidMove(this);
	}

	void Lava::CoolToStone()
	{
		if (m_CellGrid->GetCell(m_PosX + 1, m_PosY)->GetID() == cell_id::water)
		{
			m_CellGrid->ReplaceCell(m_PosX + 1, m_PosY, new cell::Steam(m_CellGrid, m_PosX + 1, m_PosY));
			m_CellGrid->ReplaceCell(m_PosX, m_PosY, new Stone(m_CellGrid, m_PosX + 1, m_PosY));
			return;
		}

		if (m_CellGrid->GetCell(m_PosX - 1, m_PosY)->GetID() == cell_id::water)
		{
			m_CellGrid->ReplaceCell(m_PosX - 1, m_PosY, new cell::Steam(m_CellGrid, m_PosX - 1, m_PosY));
			m_CellGrid->ReplaceCell(m_PosX, m_PosY, new Stone(m_CellGrid, m_PosX - 1, m_PosY));
			return;
		}

		if (m_CellGrid->GetCell(m_PosX, m_PosY + 1)->GetID() == cell_id::water)
		{
			m_CellGrid->ReplaceCell(m_PosX, m_PosY + 1, new cell::Steam(m_CellGrid, m_PosX, m_PosY + 1));
			m_CellGrid->ReplaceCell(m_PosX, m_PosY, new Stone(m_CellGrid, m_PosX, m_PosY + 1));
			return;
		}

		if (m_CellGrid->GetCell(m_PosX, m_PosY - 1)->GetID() == cell_id::water)
		{
			m_CellGrid->ReplaceCell(m_PosX, m_PosY - 1, new cell::Steam(m_CellGrid, m_PosX, m_PosY - 1));
			m_CellGrid->ReplaceCell(m_PosX, m_PosY, new Stone(m_CellGrid, m_PosX, m_PosY - 1));
			return;
		}
	}
}