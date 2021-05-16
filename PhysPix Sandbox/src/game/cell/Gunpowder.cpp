#include "Gunpowder.h"

#include "CellGrid.h"

#include "Empty.h"

#include <cstdlib>

namespace cell
{
	Gunpowder::Gunpowder(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::gunpowder;

		m_Color = cell_color::gunpowder;

		m_BurnLifetime = 2;
	}

	Gunpowder::~Gunpowder()
	{
	}

	void Gunpowder::OnTick()
	{
		PowderMove(this);

		BurnOnContact(this);
		if (this == nullptr)
			return;
		else if (m_CellID != cell_id::gunpowder)	// This check is necessary because BurnOnContact may delete this
			return;
		ExtinguishIfSuffocated(this);
		ExtinguishIfDoused(this);
		m_BurnsSurroudings = m_IsBurning;
	}
}