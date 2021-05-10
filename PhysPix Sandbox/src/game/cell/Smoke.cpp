#include "Smoke.h"

namespace cell
{
	Smoke::Smoke(CellGrid* cellGrid, int32_t posX, int32_t posY)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::smoke;

		m_Color = { 0.2f, 0.2f, 0.2f, 1.0f };

		m_IsFluid = true;
		m_FluidDir = 1;
		m_Density = cell_density::smoke;
	}

	Smoke::~Smoke()
	{
	}

	void Smoke::OnUpdate(float deltaTime)
	{
	}

	void Smoke::OnTick()
	{
		FluidMove(this);
	}
}