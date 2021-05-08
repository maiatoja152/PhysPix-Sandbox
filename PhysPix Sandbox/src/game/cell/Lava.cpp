#include "Lava.h"

#include "CellGrid.h"

#include "Empty.h"

#include "Flammable.h"

#include <cstdlib>

namespace cell
{
	Lava::Lava(CellGrid* cellGrid, int32_t posX, int32_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::lava;

		m_Color = { 1.0f, 0.45f, 0.2f, 1.0f };

		m_IsFluid = true;
		m_FluidDirection = -1;

		m_BurnsSurroudings = true;
	}

	Lava::~Lava()
	{
	}

	void Lava::OnUpdate(float deltaTime)
	{
	}

	void Lava::OnTick()
	{
		FluidMove(m_CellGrid, m_PosX, m_PosY);
	}
}