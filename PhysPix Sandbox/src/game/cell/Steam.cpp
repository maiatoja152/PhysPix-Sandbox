#include "Steam.h"

namespace cell
{
	Steam::Steam(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::steam;

		m_Color = { 0.8f, 0.8f, 0.8f, 1.0f };

		m_IsFluid = true;
		m_FluidDir = 1;
		m_Density = cell_density::steam;
	}

	Steam::~Steam()
	{
	}

	void Steam::OnTick()
	{
		FluidMove(this);
	}
}