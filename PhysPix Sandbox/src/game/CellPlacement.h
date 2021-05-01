#pragma once

#include "GLFW/glfw3.h"

#include <memory>

namespace cell
{
	class Cell;
}

class CellGrid;

class CellPlacement
{
private:
	std::unique_ptr<cell::Cell> m_ActiveCell;
	CellGrid* m_CellGrid;
	int32_t m_PlaceSize;

public:
	CellPlacement(CellGrid* cellGrid, GLFWwindow* window);
	~CellPlacement();

	void OnImGuiRender();

private:
	void OnClick(GLFWwindow* window, int button, int action, int mods);
	void Place(int32_t x, int32_t y);
};