#pragma once

namespace cell
{
	class Cell;
}

#include <vector>

class CellGrid
{
private:
	int32_t m_WindowWidth, m_WindowHeight;
	float m_CellSize;
	uint16_t m_CellColumns, m_CellRows;
	std::vector<std::vector<cell::Cell*>> m_Cells;
	float m_TickInterval, m_TickTimer;

public:
	CellGrid(int32_t windowWidth, int32_t windowHeight, float cellSize);
	~CellGrid();

	void OnUpdate(float deltaTime);

private:
	void Tick();

	std::vector<std::vector<cell::Cell*>> InitCells();

public:
	cell::Cell* GetCell(uint16_t x, uint16_t y);
	void ReplaceCell(uint16_t x, uint16_t y, cell::Cell* replacement);
};

