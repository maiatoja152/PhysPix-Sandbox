#include "Wood.h"

namespace cell
{
	Wood::Wood(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::wood;

		m_Color = cell_color::wood;

		m_BurnLifetime = 50;
	}

	Wood::~Wood()
	{
	}

	void Wood::OnTick()
	{
		BurnOnContact(this);
		if (this == nullptr)
			return;
		else if (m_CellID != cell_id::wood) // This check is necessary because BurnOnContact may delete this
			return;
		ExtinguishIfSuffocated(this);
		ExtinguishIfDoused(this);
		m_BurnsSurroudings = m_IsBurning;
	}
}