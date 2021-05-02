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

	bool m_InputEnabled;

	enum class ClickState { None, Left, Right};
	ClickState m_ClickState;
	GLFWwindow* m_Window;

public:
	CellPlacement(CellGrid* cellGrid, GLFWwindow* window);
	~CellPlacement();

	void OnTick();

	void OnImGuiRender();

private:
	void MouseBtnCallback(GLFWwindow* window, int button, int action, int mods);
	void Place(int32_t posX, int32_t posY);
	void Erase(int32_t posX, int32_t posY);
};