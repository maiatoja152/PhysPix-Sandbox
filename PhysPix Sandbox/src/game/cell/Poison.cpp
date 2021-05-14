#include "Poison.h"

#include "CellGrid.h"

#include "Smoke.h"
#include "Fire.h"

#include <cstdlib>

namespace cell
{
	Poison::Poison(CellGrid* cellGrid, int32_t posX, int32_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::poison;

		m_Color = { 0.0f, 0.6f, 0.1f, 1.0f };

		m_IsFluid = true;
		m_FluidDir = -1;
		m_Density = cell_density::poison;

		m_BurnLifetime = 3;
	}

	Poison::~Poison()
	{
	}

	void Poison::OnUpdate(float deltaTime)
	{
	}

	void Poison::OnTick()
	{
		FluidMove(this);

		Spread();

		SetBurningOnContact(this);
		ExtinguishIfSuffocated(this);
		m_BurnsSurroudings = m_IsBurning;
		if (m_IsBurning)
			Burn(this);
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