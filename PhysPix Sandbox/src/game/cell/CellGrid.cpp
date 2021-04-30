#include "CellGrid.h"

#include "BatchRenderer.h"

#include "Cell.h";
#include "Empty.h"
#include "Water.h"
#include "Sand.h"
#include "Boundary.h"

#include <algorithm>
#include <random>
#include <chrono>

CellGrid::CellGrid(int32_t windowWidth, int32_t windowHeight, float cellSize)
	:m_WindowWidth(windowWidth), m_WindowHeight(windowHeight), m_CellSize(cellSize), m_CellColumns(static_cast<uint16_t>(m_WindowWidth / cellSize)), m_CellRows(static_cast<uint16_t>(windowHeight / cellSize)),
	m_Cells(InitCells()), m_TickInterval(0.03f), m_TickTimer(m_TickInterval), m_BoundaryPtr(std::make_unique<cell::Boundary>()), m_Dir(1)
{
}

CellGrid::~CellGrid()
{
	// Delete all cells
	for (std::vector<cell::Cell*> row : m_Cells)
	{
		for (cell::Cell* cell : row)
		{
			delete cell;
		}
	}
	m_Cells.clear();
}

void CellGrid::OnUpdate(float deltaTime)
{
	m_TickTimer -= deltaTime / 1000;

	if (m_TickTimer <= 0)
	{
		Tick();
		m_TickTimer += m_TickInterval;
	}

	for (uint16_t i = 0; i < m_Cells.size(); i++)
	{
		for (uint16_t j = 0; j < m_Cells[0].size(); j++)
		{
			m_Cells[i][j]->OnUpdate(deltaTime);
		}
	}
}

void CellGrid::Tick()
{
	m_Dir *= -1;

	auto cellsToTick = m_Cells;
	long long seed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::shuffle(cellsToTick.begin(), cellsToTick.end(), std::mt19937(seed));

	for (uint16_t i = 0; i < cellsToTick.size(); i++)
	{
		for (uint16_t j = 0; j < cellsToTick[0].size(); j++)
		{
			cellsToTick[i][j]->OnTick();
		}
	}
}

void CellGrid::OnRender()
{
	glm::vec2 border = { m_WindowWidth % m_CellColumns, m_WindowHeight % m_CellRows };

	BatchRenderer::BeginBatch();
	for (uint16_t i = 0; i < m_Cells.size(); i++)
	{
		for (uint16_t j = 0; j < m_Cells[0].size(); j++)
		{
			// Don't draw a quad for empty cells for performance
			if (m_Cells[i][j]->GetID() != 1)
			{
				glm::vec2 position = { i * m_CellSize + m_CellSize / 2 + border.x / 2, j * m_CellSize + m_CellSize / 2 + border.y / 2 };
				BatchRenderer::DrawQuad(position, { m_CellSize - 0, m_CellSize - 0 }, m_Cells[i][j]->GetColor());
			}
		}
	}
	BatchRenderer::EndBatch();
}

std::vector<std::vector<cell::Cell*>> CellGrid::InitCells()
{
	std::vector<std::vector<cell::Cell*>> cells(m_CellColumns, std::vector<cell::Cell*>(m_CellRows));

	for (uint16_t i = 0; i < cells.size(); i++)
	{
		for (uint16_t j = 0; j < cells[0].size(); j++)
		{
			if (i % 3 == 0 && j < cells[0].size() * 0.6f && i > cells.size() * 0.3f)
			{
				cells[i][j] = new cell::Water(this, i, j);
			}
			else if (i % 2 == 0 && j > cells[0].size() * 0.6f && i < cells.size() * 0.8f)
			{
				cells[i][j] = new cell::Sand(this, i, j);
			}
			else
			{
				cells[i][j] = new cell::Empty();
			}
		}
	}

	return cells;
}

cell::Cell* CellGrid::GetCell(uint16_t x, uint16_t y)
{
	if (x > m_CellColumns - 1 || y > m_CellRows - 1)
		return m_BoundaryPtr.get();
	else
		return m_Cells[x][y];
}

void CellGrid::ReplaceCell(uint16_t x, uint16_t y, cell::Cell* replacement)
{
	delete m_Cells[x][y];
	m_Cells[x][y] = replacement;
	replacement->UpdatePosition(x, y);
}

void CellGrid::MoveCell(uint16_t posX, uint16_t posY, uint16_t destX, uint16_t destY)
{
	delete m_Cells[destX][destY];

	m_Cells[destX][destY] = m_Cells[posX][posY];
	m_Cells[destX][destY]->UpdatePosition(destX, destY);

	m_Cells[posX][posY] = new cell::Empty();
}

void CellGrid::SwapCells(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	cell::Cell* temp = m_Cells[x2][y2];

	m_Cells[x2][y2] = m_Cells[x1][y1];
	m_Cells[x1][y1] = temp;

	m_Cells[x2][y2]->UpdatePosition(x2, y2);
	m_Cells[x1][y1]->UpdatePosition(x1, y1);
}