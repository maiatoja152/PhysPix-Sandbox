#include "Sand.h"

namespace cell
{
	Sand::Sand(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::sand;

		m_Color = { 0.95f, 0.92f, 0.33f, 1.0f };
	}

	Sand::~Sand()
	{
	}

	void Sand::OnTick()
	{
		PowderMove(this);
	}
}