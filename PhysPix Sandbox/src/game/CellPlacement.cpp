#include "CellPlacement.h"

#include "cell/Cell.h"
#include "CellGrid.h"

#include "cell/Empty.h"
#include "cell/Water.h"
#include "cell/Sand.h"
#include "cell/Poison.h"

#include "imgui/imgui.h"

CellPlacement::CellPlacement(CellGrid* cellGrid, GLFWwindow* window)
	: m_ActiveCell(std::make_unique<cell::Water>(cellGrid, 0, 0)), m_CellGrid(cellGrid), m_PlaceSize(5)
{
	glfwSetWindowUserPointer(window, this);

	auto func = [](GLFWwindow* window, int button, int action, int mods)
	{
		static_cast<CellPlacement*>(glfwGetWindowUserPointer(window))->OnClick(window, button, action, mods);
	};

	glfwSetMouseButtonCallback(window, func);
}

CellPlacement::~CellPlacement()
{
}

void CellPlacement::OnClick(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double mousePosX, mousePosY;
		glfwGetCursorPos(window, &mousePosX, &mousePosY);

		int32_t windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		// Remap mouse position to make the origin bottom-left instead of top-left
		mousePosY = static_cast<double>(windowHeight + (mousePosY - 0) * (0 - windowHeight) / (windowHeight - 0));

		Place(mousePosX, mousePosY);
	}
}

void CellPlacement::Place(int32_t x, int32_t y)
{
	m_CellGrid->ReplaceCell(x / m_CellGrid->GetCellSize(), y / m_CellGrid->GetCellSize(), m_ActiveCell->clone());

	for (uint16_t i = 1; i < m_PlaceSize; i++)
	{
		// Up right down left
		m_CellGrid->ReplaceCell(x / m_CellGrid->GetCellSize() + i, y / m_CellGrid->GetCellSize(), m_ActiveCell->clone());
		m_CellGrid->ReplaceCell(x / m_CellGrid->GetCellSize(), y / m_CellGrid->GetCellSize() + i, m_ActiveCell->clone());
		m_CellGrid->ReplaceCell(x / m_CellGrid->GetCellSize(), y / m_CellGrid->GetCellSize() - i, m_ActiveCell->clone());
		m_CellGrid->ReplaceCell(x / m_CellGrid->GetCellSize() - i, y / m_CellGrid->GetCellSize(), m_ActiveCell->clone());

		// Diagonals
		m_CellGrid->ReplaceCell(x / m_CellGrid->GetCellSize() + i, y / m_CellGrid->GetCellSize() + i, m_ActiveCell->clone());
		m_CellGrid->ReplaceCell(x / m_CellGrid->GetCellSize() + i, y / m_CellGrid->GetCellSize() - i, m_ActiveCell->clone());
		m_CellGrid->ReplaceCell(x / m_CellGrid->GetCellSize() - i, y / m_CellGrid->GetCellSize() - i, m_ActiveCell->clone());
		m_CellGrid->ReplaceCell(x / m_CellGrid->GetCellSize() - i, y / m_CellGrid->GetCellSize() + i, m_ActiveCell->clone());
	}
}

void CellPlacement::OnImGuiRender()
{
	ImGui::Begin("Cell Placement Menu");

	ImGui::SliderInt("Size", &m_PlaceSize, 1, 15);

	if (ImGui::Button("Empty"))
		m_ActiveCell = std::make_unique<cell::Empty>();
	if (ImGui::Button("Water"))
		m_ActiveCell = std::make_unique<cell::Water>(m_CellGrid, 0, 0);
	if (ImGui::Button("Sand"))
		m_ActiveCell = std::make_unique<cell::Sand>(m_CellGrid, 0, 0);
	if (ImGui::Button("Poison"))
		m_ActiveCell = std::make_unique<cell::Poison>(m_CellGrid, 0, 0);

	ImGui::End();
}