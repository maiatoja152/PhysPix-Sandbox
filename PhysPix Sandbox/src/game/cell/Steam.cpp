#include "Steam.h"

namespace cell
{
	Steam::Steam(CellGrid* cellGrid, int32_t posX, int32_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::steam;

		m_Color = { 0.7f, 0.7f, 0.7f, 1.0f };

		m_IsFluid = true;
		m_FluidDir = 1;
		m_Density = cell_density::steam;
	}

	Steam::~Steam()
	{
	}

	void Steam::OnUpdate(float deltaTime)
	{
	}

	void Steam::OnTick()
	{
		FluidMove(this);
	}
}