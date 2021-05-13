#include "Lava.h"

#include "CellGrid.h"

#include "Flammable.h"

#include "Empty.h"
#include "Stone.h"

#include <cstdlib>

namespace cell
{
	Lava::Lava(CellGrid* cellGrid, int32_t posX, int32_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::lava;

		m_Color = { 1.0f, 0.45f, 0.2f, 1.0f };

		m_IsFluid = true;
		m_FluidDir = -1;
		m_Density = cell_density::lava;

		m_BurnsSurroudings = true;
	}

	Lava::~Lava()
	{
	}

	void Lava::OnUpdate(float deltaTime)
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
			m_CellGrid->GetCell(m_PosX + 1, m_PosY)->RemoveCell();
			m_CellGrid->ReplaceCell(m_PosX, m_PosY, new Stone(m_CellGrid, m_PosX + 1, m_PosY));
			return;
		}

		if (m_CellGrid->GetCell(m_PosX - 1, m_PosY)->GetID() == cell_id::water)
		{
			m_CellGrid->GetCell(m_PosX - 1, m_PosY)->RemoveCell();
			m_CellGrid->ReplaceCell(m_PosX, m_PosY, new Stone(m_CellGrid, m_PosX - 1, m_PosY));
			return;
		}

		if (m_CellGrid->GetCell(m_PosX, m_PosY + 1)->GetID() == cell_id::water)
		{
			m_CellGrid->GetCell(m_PosX, m_PosY + 1)->RemoveCell();
			m_CellGrid->ReplaceCell(m_PosX, m_PosY, new Stone(m_CellGrid, m_PosX, m_PosY + 1));
			return;
		}

		if (m_CellGrid->GetCell(m_PosX, m_PosY - 1)->GetID() == cell_id::water)
		{
			m_CellGrid->GetCell(m_PosX, m_PosY - 1)->RemoveCell();
			m_CellGrid->ReplaceCell(m_PosX, m_PosY, new Stone(m_CellGrid, m_PosX, m_PosY - 1));
			return;
		}
	}
}