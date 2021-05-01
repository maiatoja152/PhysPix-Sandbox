#include "Sand.h"

namespace cell
{
	Sand::Sand(CellGrid* cellGrid, int32_t posX, int32_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = 3;

		m_Color = { 0.95f, 0.92f, 0.33f, 1.0f };
	}

	Sand::~Sand()
	{
	}

	Sand* Sand::clone() const
	{
		return new Sand(*this);
	}

	void Sand::OnUpdate(float deltaTime)
	{
	}

	void Sand::OnTick()
	{
		PowderMove();
	}
}