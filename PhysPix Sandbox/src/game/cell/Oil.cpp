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

		m_Color = cell_color::oil;

		m_IsFluid = true;
		m_FluidDir = -1;
		m_Density = cell_density::oil;

		m_BurnLifetime = 18;
	}

	Oil::~Oil()
	{
	}

	void Oil::OnTick()
	{
		FluidMove(this);

		BurnOnContact(this);
		if (this == nullptr)
			return;
		else if (m_CellID != cell_id::oil)	// This check is necessary because BurnOnContact may delete this
			return;
		ExtinguishIfSuffocated(this);
		ExtinguishIfDoused(this);
		m_BurnsSurroudings = m_IsBurning;
	}
}