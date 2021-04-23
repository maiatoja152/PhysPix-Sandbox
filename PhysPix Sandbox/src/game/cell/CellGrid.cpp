#include "CellGrid.h"

#include "Cell.h";

#include "Empty.h"

CellGrid::CellGrid(int32_t windowWidth, int32_t windowHeight, float cellSize)
	:m_WindowWidth(windowWidth), m_WindowHeight(windowHeight), m_CellSize(cellSize), m_CellColumns(m_WindowWidth / cellSize), m_CellRows(windowHeight / cellSize),
	m_Cells(InitCells()), m_TickInterval(0.5f), m_TickTimer(m_TickInterval)
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

	for (std::vector<cell::Cell*> row : m_Cells)
	{
		for (cell::Cell* cell : row)
		{
			cell->OnUpdate(deltaTime);
		}
	}
}

void CellGrid::Tick()
{
	for (std::vector<cell::Cell*> row : m_Cells)
	{
		for (cell::Cell* cell : row)
		{
			cell->OnTick();
		}
	}
}

std::vector<std::vector<cell::Cell*>> CellGrid::InitCells()
{
	std::vector<std::vector<cell::Cell*>> cells(m_CellColumns, std::vector<cell::Cell*>(m_CellRows));

	for (uint16_t i = 0; i < cells.size(); i++)
	{
		for (uint16_t j = 0; j < cells[0].size(); j++)
		{
			cells[i][j] = new cell::Empty();
		}
	}

	return cells;
}

cell::Cell* CellGrid::GetCell(uint16_t x, uint16_t y)
{
	return m_Cells[x][y];
}

void CellGrid::ReplaceCell(uint16_t x, uint16_t y, cell::Cell* replacement)
{
	delete m_Cells[x][y];
	m_Cells[x][y] = replacement;
}