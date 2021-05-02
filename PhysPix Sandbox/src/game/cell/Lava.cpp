#include "Lava.h"

#include "CellGrid.h"

#include "Empty.h"

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

		m_FluidDirection = -1;
	}

	Lava::~Lava()
	{
	}

	Lava* Lava::clone() const
	{
		return new Lava(*this);
	}

	void Lava::OnUpdate(float deltaTime)
	{
	}

	void Lava::OnTick()
	{
		FluidMove();
	}
}