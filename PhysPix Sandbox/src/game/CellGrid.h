#pragma once

#include "GLFW/glfw3.h"

namespace cell
{
	class Cell;
	class Boundary;
}

class CellPlacement;

class Shader;

#include <vector>
#include <memory>
#include <stdint.h>

class CellGrid
{
private:
	GLFWwindow* m_Window;
	int32_t m_WindowWidth, m_WindowHeight;
	float m_CellSize;
	uint16_t m_CellColumns, m_CellRows;
	std::vector<std::vector<cell::Cell*>> m_Cells;
	float m_TickInterval, m_TickTimer;

	std::unique_ptr<cell::Boundary> m_BoundaryPtr;

	int8_t m_Dir;

	CellPlacement* m_CellPlacement;

	std::unique_ptr<Shader> m_Shader;

public:
	CellGrid(GLFWwindow* window, float cellSize, CellPlacement* cellPlacement = nullptr);
	~CellGrid();

	void OnUpdate(float deltaTime);
	void OnRender();

	void Reset();

private:
	void Tick();

	void InitCells();

	void ResizeGrid(uint16_t columns, uint16_t rows);

public:
	cell::Cell* GetCell(uint16_t x, uint16_t y);
	void ReplaceCell(uint16_t x, uint16_t y, cell::Cell* replacement);
	void MoveCell(uint16_t posX, uint16_t posY, uint16_t destX, uint16_t destY);
	void SwapCells(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
	void DisplaceFluid(uint16_t posX, uint16_t posY, int32_t destX, int32_t destY, int8_t fluidDir = -1);

	inline float GetCellSize() { return m_CellSize; }
	inline int8_t GetDir() { return m_Dir; }

	inline void SetCellPlacement(CellPlacement* cellPlacement) { m_CellPlacement = cellPlacement; }
};

