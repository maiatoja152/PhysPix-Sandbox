#include "Sand.h"

namespace cell
{
	Sand::Sand(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::sand;

		m_Color = cell_color::sand;
	}

	Sand::~Sand()
	{
	}

	void Sand::OnTick()
	{
		PowderMove(this);
	}
}