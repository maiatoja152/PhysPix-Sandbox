#pragma once

#include "GLFW/glfw3.h"

#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

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

	uint16_t m_MenuBarHeight;

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

	// Create cell selection button. Color is a glm::vec4 because that is what all cell colors are stored as so it's convenient.
	void ImGuiCellButton(uint8_t cellID, const char* label, ImVec2 size, glm::vec4 color);

	static ImVec4 GenConstrastingTextColor(glm::vec4 backgroundColor);

public:
	// \return Height of the menu bar where cells can be selected in pixels
	uint16_t GetMenuBarHeight() { return m_MenuBarHeight; }
};