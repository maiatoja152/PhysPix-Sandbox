#include "Stone.h"

namespace cell
{
	Stone::Stone(CellGrid* cellGrid, int32_t posX, int32_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::stone;

		m_Color = { 0.5f, 0.5f, 0.53f, 1.0f };
	}

	Stone::~Stone()
	{
	}

	void Stone::OnTick()
	{
	}
}