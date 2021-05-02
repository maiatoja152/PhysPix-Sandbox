#include "Poison.h"

#include "CellGrid.h"

#include "Empty.h"

#include <cstdlib>

namespace cell
{
	Poison::Poison(CellGrid* cellGrid, int32_t posX, int32_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::poison;

		m_Color = { 0.1f, 0.75f, 0.2f, 1.0f };

		m_FluidDirection = -1;
	}

	Poison::~Poison()
	{
	}

	Poison* Poison::clone() const
	{
		return new Poison(*this);
	}

	void Poison::OnUpdate(float deltaTime)
	{
	}

	void Poison::OnTick()
	{
		FluidMove();

		Spread();
	}

	void Poison::Spread()
	{
		if (m_CellGrid->GetCell(m_PosX + 1, m_PosY)->GetID() == cell_id::water)
			m_CellGrid->ReplaceCell(m_PosX + 1, m_PosY, new Poison(m_CellGrid, m_PosX + 1, m_PosY));

		if (m_CellGrid->GetCell(m_PosX - 1, m_PosY)->GetID() == cell_id::water)
			m_CellGrid->ReplaceCell(m_PosX - 1, m_PosY, new Poison(m_CellGrid, m_PosX - 1, m_PosY));

		if (m_CellGrid->GetCell(m_PosX, m_PosY + 1)->GetID() == cell_id::water)
			m_CellGrid->ReplaceCell(m_PosX, m_PosY + 1, new Poison(m_CellGrid, m_PosX, m_PosY + 1));

		if (m_CellGrid->GetCell(m_PosX, m_PosY - 1)->GetID() == cell_id::water)
			m_CellGrid->ReplaceCell(m_PosX, m_PosY - 1, new Poison(m_CellGrid, m_PosX, m_PosY - 1));
	}
}