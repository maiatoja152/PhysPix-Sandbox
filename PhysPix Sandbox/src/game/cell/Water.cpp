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

		m_Color = { 0.1f, 0.3f, 0.8f, 1.0f };

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