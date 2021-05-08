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
	std::unique_ptr<cell::Cell> m_ActiveCell;
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
};