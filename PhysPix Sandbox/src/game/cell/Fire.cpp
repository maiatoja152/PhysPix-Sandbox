#include "Fire.h"

#include "CellGrid.h"

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
		std::vector<std::pair<int32_t, int32_t>> validMovePositions;
		validMovePositions.reserve(5);
		int8_t dir = m_CellGrid->GetDir();

		// Check down
		if (m_CellGrid->GetCell(m_PosX, m_PosY + 1)->GetID() == cell_id::empty)
		{
			validMovePositions.push_back({ m_PosX, m_PosY + 1 });
		}
		// Check upper left and right
		if (m_CellGrid->GetCell(m_PosX + dir, m_PosY + 1)->GetID() == cell_id::empty)
		{
			validMovePositions.push_back({ m_PosX + dir, m_PosY + 1 });
		}
		if (m_CellGrid->GetCell(m_PosX - dir, m_PosY + 1)->GetID() == cell_id::empty)
		{
			validMovePositions.push_back({ m_PosX - dir, m_PosY + 1 });
		}
		// Check left and right
		if (m_CellGrid->GetCell(m_PosX + dir, m_PosY)->GetID() == cell_id::empty)
		{
			validMovePositions.push_back({ m_PosX + dir, m_PosY });
		}
		if (m_CellGrid->GetCell(m_PosX - dir, m_PosY)->GetID() == cell_id::empty)
		{
			validMovePositions.push_back({ m_PosX - dir, m_PosY });
		}

		// Exit immediately if there are no valid moves
		if (validMovePositions.size() == 0)
			return;

		float biases[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
		int randomNum = m_rng();
		for (uint8_t i = 0; i < validMovePositions.size(); i++)
		{
			if (randomNum * biases[i] <= (m_rngMax / validMovePositions.size()) * (i + 1))
			{
				m_CellGrid->SwapCells(m_PosX, m_PosY, validMovePositions[i].first, validMovePositions[i].second);
				return;
			}
		}
	}
}