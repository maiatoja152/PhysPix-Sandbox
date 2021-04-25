#include "Water.h"

#include "CellGrid.h"

#include "Empty.h"

#include <cstdlib>

namespace cell
{
	Water::Water(CellGrid* cellGrid, int32_t posX, int32_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = 2;

		m_Color = { 0.1f, 0.3f, 0.8f, 1.0f };

		m_FluidDirection = -1;
	}

	Water::~Water()
	{
	}

	void Water::OnUpdate(float deltaTime)
	{
	}

	void Water::OnTick()
	{
		FluidMove();
	}
}