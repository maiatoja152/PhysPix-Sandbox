#include "CellPlacement.h"

#include "cell/Cell.h"
#include "CellGrid.h"

#include "cell/Empty.h"
#include "cell/Water.h"
#include "cell/Sand.h"
#include "cell/Poison.h"
#include "cell/Stone.h"

#include "imgui/imgui.h"

#include <random>
#include <chrono>
#include <functional>
#include <math.h>

CellPlacement::CellPlacement(CellGrid* cellGrid, GLFWwindow* window)
	: m_ActiveCell(std::make_unique<cell::Water>(cellGrid, 0, 0)), m_CellGrid(cellGrid), m_PlaceSize(5), m_InputEnabled(true)
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
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && m_InputEnabled)
	{
		double mousePosX, mousePosY;
		glfwGetCursorPos(window, &mousePosX, &mousePosY);

		int32_t windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		// Remap mouse position to make the origin bottom-left instead of top-left
		mousePosY = static_cast<double>(windowHeight + (mousePosY - 0) * (0 - windowHeight) / (windowHeight - 0));

		mousePosX /= m_CellGrid->GetCellSize();
		mousePosY /= m_CellGrid->GetCellSize();
		Place(mousePosX, mousePosY);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && m_InputEnabled)
	{
		double mousePosX, mousePosY;
		glfwGetCursorPos(window, &mousePosX, &mousePosY);

		int32_t windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		// Remap mouse position to make the origin bottom-left instead of top-left
		mousePosY = static_cast<double>(windowHeight + (mousePosY - 0) * (0 - windowHeight) / (windowHeight - 0));

		mousePosX /= m_CellGrid->GetCellSize();
		mousePosY /= m_CellGrid->GetCellSize();
		Erase(mousePosX, mousePosY);
	}
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

	ImGui::NewLine();

	if (ImGui::Button("Reset"))
		m_CellGrid->Reset();

	ImGui::End();
}