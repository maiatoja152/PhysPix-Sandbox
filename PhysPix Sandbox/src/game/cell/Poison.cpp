#include "Poison.h"

#include "CellGrid.h"

#include "Smoke.h"
#include "Fire.h"

#include <cstdlib>

namespace cell
{
	Poison::Poison(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::poison;

		m_Color = cell_color::poison;

		m_IsFluid = true;
		m_FluidDir = -1;
		m_Density = cell_density::poison;

		m_BurnLifetime = 5;
	}

	Poison::~Poison()
	{
	}

	void Poison::OnTick()
	{
		FluidMove(this);

		Spread();

		BurnOnContact(this);
		if (this == nullptr)	// This check is necessary because BurnOnContact may delete this
			return;
		ExtinguishIfSuffocated(this);
		ExtinguishIfDoused(this);
		m_BurnsSurroudings = m_IsBurning;
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