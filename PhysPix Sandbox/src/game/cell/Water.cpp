#include "Water.h"

#include "CellGrid.h"

#include "Empty.h"

#include <cstdlib>

namespace cell
{
	Water::Water(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::water;

		m_Color = cell_color::water;

		m_IsFluid = true;
		m_FluidDir = -1;
		m_Density = cell_density::water;
	}

	Water::~Water()
	{
	}

	void Water::OnTick()
	{
		FluidMove(this);
	}
}