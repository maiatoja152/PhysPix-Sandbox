#include "Fire.h"

#include "CellGrid.h"

#include "Fluid.h"

#include "Smoke.h"

#include <chrono>
#include <utility>
#include <vector>

namespace cell
{
	Fire::Fire(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
		: m_rng(std::bind(std::uniform_int_distribution<int>(NULL), std::mt19937(static_cast<unsigned int>(NULL)))), m_rngMax(1000), m_Lifetime(NULL), m_LifetimeCounter(0)
	{
		m_CellGrid = cellGrid;

		m_PosX = posX;
		m_PosY = posY;

		m_CellID = cell_id::fire;

		m_Color = { 0.8f, 0.1f, 0.1f, 1.0f };

		m_IsFluid = true;
		m_Density = cell_density::fire;

		m_BurnsSurroudings = true;

		long long seed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		m_rng = std::bind(std::uniform_int_distribution<int>(0, m_rngMax), std::mt19937(static_cast<unsigned int>(seed)));

		m_Lifetime = std::bind(std::uniform_int_distribution<int>(10, 50), std::mt19937(static_cast<unsigned int>(seed)))();
	}

	Fire::~Fire()
	{
	}

	void Fire::OnTick()
	{
		if (++m_LifetimeCounter >= m_Lifetime)
		{
			if (m_rng() % 13 == 0)
				m_CellGrid->ReplaceCell(m_PosX, m_PosY, new Smoke(m_CellGrid, m_PosX, m_PosY));
			else
				RemoveCell();

			return;
		}

		FireMove();
	}

	void Fire::FireMove()
	{
		int8_t dir = m_CellGrid->GetDir();

		int randomNum = m_rng();
		float biases[] = { 0.6f, 0.8f, 0.8f, 1.0f, 1.0f };

		// Check down
		Cell* currCell = m_CellGrid->GetCell(m_PosX, m_PosY + 1);
		if ((currCell->GetID() == cell_id::empty || Fluid::IsValidFluidDisplacement(m_Density, currCell->GetDensity(), 1)) &&
			(randomNum * biases[0] <= m_rngMax))
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX, m_PosY + 1);
			return;
		}
		// Check upper left and right
		currCell = m_CellGrid->GetCell(m_PosX + dir, m_PosY + 1);
		if ((currCell->GetID() == cell_id::empty || Fluid::IsValidFluidDisplacement(m_Density, currCell->GetDensity(), 1)) &&
			(randomNum * biases[1] <= m_rngMax))
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX + dir, m_PosY + 1);
			return;
		}
		currCell = m_CellGrid->GetCell(m_PosX - dir, m_PosY + 1);
		if ((currCell->GetID() == cell_id::empty || Fluid::IsValidFluidDisplacement(m_Density, currCell->GetDensity(), 1)) &&
			(randomNum * biases[2] <= m_rngMax))
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX - dir, m_PosY + 1);
			return;
		}
		// Check left and right
		currCell = m_CellGrid->GetCell(m_PosX + dir, m_PosY);
		if ((currCell->GetID() == cell_id::empty || Fluid::IsValidFluidDisplacement(m_Density, currCell->GetDensity(), 1)) &&
			(randomNum * biases[3] <= m_rngMax))
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX + dir, m_PosY);
			return;
		}
		currCell = m_CellGrid->GetCell(m_PosX - dir, m_PosY);
		if ((currCell->GetID() == cell_id::empty || Fluid::IsValidFluidDisplacement(m_Density, currCell->GetDensity(), 1)) &&
			(randomNum * biases[4] <= m_rngMax))
		{
			m_CellGrid->SwapCells(m_PosX, m_PosY, m_PosX - dir, m_PosY);
			return;
		}
	}
}