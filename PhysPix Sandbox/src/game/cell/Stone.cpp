#include "Stone.h"

namespace cell
{
	Stone::Stone(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::stone;

		m_Color = cell_color::stone;
	}

	Stone::~Stone()
	{
	}

	void Stone::OnTick()
	{
	}
}