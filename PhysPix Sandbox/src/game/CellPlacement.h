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
	GLFWwindow* m_Window;
	CellGrid* m_CellGrid;
	uint8_t m_ActiveCell;
	int32_t m_PlaceSize;

	bool m_InputEnabled;

	enum class ClickState { None, Left, Right};
	ClickState m_ClickState;

public:
	CellPlacement(GLFWwindow* window, CellGrid* cellGrid);
	~CellPlacement();

	void OnTick();

	void OnImGuiRender();

private:
	void MouseBtnCallback(GLFWwindow* window, int button, int action, int mods);
	void Place(int32_t posX, int32_t posY);
	void Erase(int32_t posX, int32_t posY);

	cell::Cell* GetNewCellByID(uint8_t id);
};