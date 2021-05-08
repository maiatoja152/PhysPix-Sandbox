#include "Lava.h"

#include "CellGrid.h"

#include "Empty.h"

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

		m_FluidDirection = -1;
	}

	Lava::~Lava()
	{
	}

	void Lava::OnUpdate(float deltaTime)
	{
	}

	void Lava::OnTick()
	{
		FluidMove();

		BurnFlammables();
	}

	void Lava::BurnFlammables()
	{
		if (m_CellGrid->GetCell(m_PosX + 1, m_PosY)->IsFlammable())
			m_CellGrid->ReplaceCell(m_PosX + 1, m_PosY, new Empty());

		if (m_CellGrid->GetCell(m_PosX - 1, m_PosY)->IsFlammable())
			m_CellGrid->ReplaceCell(m_PosX - 1, m_PosY, new Empty());

		if (m_CellGrid->GetCell(m_PosX, m_PosY + 1)->IsFlammable())
			m_CellGrid->ReplaceCell(m_PosX, m_PosY + 1, new Empty());

		if (m_CellGrid->GetCell(m_PosX, m_PosY - 1)->IsFlammable())
			m_CellGrid->ReplaceCell(m_PosX, m_PosY - 1, new Empty());
	}
}