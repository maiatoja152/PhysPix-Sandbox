#include "Hydrogen.h"

namespace cell
{
	Hydrogen::Hydrogen(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::hydrogen;

		m_Color = cell_color::hydrogen;

		m_IsFluid = true;
		m_FluidDir = 1;
		m_Density = cell_density::hydrogen;

		m_BurnLifetime = 2;
	}

	Hydrogen::~Hydrogen()
	{
	}

	void Hydrogen::OnTick()
	{
		FluidMove(this);

		BurnOnContact(this);
		if (this == nullptr)
			return;
		else if (m_CellID != cell_id::hydrogen)	// This check is necessary because BurnOnContact may delete this
			return;
		ExtinguishIfSuffocated(this);
		ExtinguishIfDoused(this);
		m_BurnsSurroudings = m_IsBurning;
	}
}