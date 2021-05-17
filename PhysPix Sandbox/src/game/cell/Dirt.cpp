#include "Dirt.h"

namespace cell
{
	Dirt::Dirt(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::dirt;

		m_Color = cell_color::dirt;
	}

	Dirt::~Dirt()
	{
	}

	void Dirt::OnTick()
	{
		PowderMove(this);
	}
}