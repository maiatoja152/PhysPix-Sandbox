#include "CellPlacement.h"

#include "cell/Cell.h"
#include "CellGrid.h"

#include "cell/Empty.h"
#include "cell/Water.h"
#include "cell/Sand.h"
#include "cell/Poison.h"
#include "cell/Stone.h"
#include "cell/Lava.h"

#include "imgui/imgui.h"

#include <random>
#include <chrono>
#include <functional>

CellPlacement::CellPlacement(GLFWwindow* window, CellGrid* cellGrid)
	: m_Window(window), m_CellGrid(cellGrid), m_ActiveCell(std::make_unique<cell::Water>(cellGrid, 0, 0)), m_PlaceSize(10), m_InputEnabled(true), m_ClickState(ClickState::None)
{
	if (m_CellGrid != nullptr)
		m_CellGrid->SetCellPlacement(this);

	glfwSetWindowUserPointer(window, this);
	auto func = [](GLFWwindow* window, int button, int action, int mods)
	{
		static_cast<CellPlacement*>(glfwGetWindowUserPointer(window))->MouseBtnCallback(window, button, action, mods);
	};
	glfwSetMouseButtonCallback(window, func);
}

CellPlacement::~CellPlacement()
{
}

void CellPlacement::OnTick()
{
	if (m_ClickState == ClickState::Left)
	{
		double clickPosX, clickPosY;
		glfwGetCursorPos(m_Window, &clickPosX, &clickPosY);

		int32_t windowWidth, windowHeight;
		glfwGetFramebufferSize(m_Window, &windowWidth, &windowHeight);

		// Remap mouse position to make the origin bottom-left instead of top-left
		clickPosY = static_cast<double>(windowHeight + (clickPosY - 0) * (0 - windowHeight) / (windowHeight - 0));

		clickPosX /= m_CellGrid->GetCellSize();
		clickPosY /= m_CellGrid->GetCellSize();

		Place(clickPosX, clickPosY);
	}
	else if (m_ClickState == ClickState::Right)
	{
		double clickPosX, clickPosY;
		glfwGetCursorPos(m_Window, &clickPosX, &clickPosY);

		int32_t windowWidth, windowHeight;
		glfwGetFramebufferSize(m_Window, &windowWidth, &windowHeight);

		// Remap mouse position to make the origin bottom-left instead of top-left
		clickPosY = static_cast<double>(windowHeight + (clickPosY - 0) * (0 - windowHeight) / (windowHeight - 0));

		clickPosX /= m_CellGrid->GetCellSize();
		clickPosY /= m_CellGrid->GetCellSize();

		Erase(clickPosX, clickPosY);
	}
}

void CellPlacement::MouseBtnCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && m_InputEnabled)
		m_ClickState = ClickState::Left;
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && m_InputEnabled)
		m_ClickState = ClickState::Right;
	else if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) && action == GLFW_RELEASE && m_InputEnabled)
		m_ClickState = ClickState::None;
}

void CellPlacement::Place(int32_t posX, int32_t posY)
{
	long long seed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	auto rng = std::bind(std::uniform_int_distribution<int>(1, 10), std::mt19937(seed));

	if (m_PlaceSize == 1)
	{
		m_CellGrid->ReplaceCell(posX, posY, m_ActiveCell->clone());
		return;
	}

	// Generate circle with random holes
	int32_t r = m_PlaceSize;
	for (int y = -r; y <= r; y++)
	{
		for (int x = -r; x <= r; x++)
		{
			if (x * x + y * y <= r * r && rng() > 7)
			{
				m_CellGrid->ReplaceCell(posX + x, posY + y, m_ActiveCell->clone());
			}
		}
	}
}

void CellPlacement::Erase(int32_t posX, int32_t posY)
{
	if (m_PlaceSize == 1)
	{
		m_CellGrid->ReplaceCell(posX, posY, new cell::Empty());
		return;
	}

	// Generate circle
	int32_t r = m_PlaceSize;
	for (int y = -r; y <= r; y++)
	{
		for (int x = -r; x <= r; x++)
		{
			if (x * x + y * y <= r * r)
			{
				m_CellGrid->ReplaceCell(posX + x, posY + y, new cell::Empty());
			}
		}
	}
}

void CellPlacement::OnImGuiRender()
{
	ImGui::Begin("Cell Placement Menu");

	m_InputEnabled = !ImGui::IsWindowHovered();

	ImGui::SliderInt("Radius", &m_PlaceSize, 1, 30);

	if (ImGui::Button("Water"))
		m_ActiveCell = std::make_unique<cell::Water>(m_CellGrid, 0, 0);
	if (ImGui::Button("Sand"))
		m_ActiveCell = std::make_unique<cell::Sand>(m_CellGrid, 0, 0);
	if (ImGui::Button("Poison"))
		m_ActiveCell = std::make_unique<cell::Poison>(m_CellGrid, 0, 0);
	if (ImGui::Button("Stone"))
		m_ActiveCell = std::make_unique<cell::Stone>(m_CellGrid, 0, 0);
	if (ImGui::Button("Lava"))
		m_ActiveCell = std::make_unique<cell::Lava>(m_CellGrid, 0, 0);

	ImGui::NewLine();

	if (ImGui::Button("Reset"))
		m_CellGrid->Reset();

	ImGui::End();
}