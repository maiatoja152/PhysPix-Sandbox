#include "Stone.h"

namespace cell
{
	Stone::Stone(CellGrid* cellGrid, int32_t posX, int32_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::stone;

		m_Color = { 0.6f, 0.6f, 0.65f, 1.0f };
	}

	Stone::~Stone()
	{
	}

	Stone* Stone::clone() const
	{
		return new Stone(*this);
	}
}