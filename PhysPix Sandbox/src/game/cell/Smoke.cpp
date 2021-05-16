#include "Smoke.h"

namespace cell
{
	Smoke::Smoke(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::smoke;

		m_Color = cell_color::smoke;

		m_IsFluid = true;
		m_FluidDir = 1;
		m_Density = cell_density::smoke;
	}

	Smoke::~Smoke()
	{
	}

	void Smoke::OnTick()
	{
		FluidMove(this);
	}
}