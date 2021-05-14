#include "Oil.h"

#include "CellGrid.h"

#include "Empty.h"

#include <cstdlib>

namespace cell
{
	Oil::Oil(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::oil;

		m_Color = { 0.05f, 0.05f, 0.05f, 1.0f };

		m_IsFluid = true;
		m_FluidDir = -1;
		m_Density = cell_density::oil;

		m_BurnLifetime = 10;
	}

	Oil::~Oil()
	{
	}

	void Oil::OnTick()
	{
		FluidMove(this);

		SetBurningOnContact(this);
		ExtinguishIfSuffocated(this);
		m_BurnsSurroudings = m_IsBurning;
		if (m_IsBurning)
			Burn(this);
	}
}