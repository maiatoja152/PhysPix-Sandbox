#include "CellPlacement.h"

#include "cell/Cell.h"
#include "CellGrid.h"

#include "cell/Empty.h"
#include "cell/Water.h"
#include "cell/Sand.h"
#include "cell/Poison.h"
#include "cell/Stone.h"
#include "cell/Lava.h"
#include "cell/Smoke.h"
#include "cell/Steam.h"

#include "imgui/imgui.h"

#include <random>
#include <chrono>
#include <functional>

#include <stdexcept>
#include <string>
#include <iostream>

CellPlacement::CellPlacement(GLFWwindow* window, CellGrid* cellGrid)
	: m_Window(window), m_CellGrid(cellGrid), m_ActiveCell(cell_id::water), m_PlaceSize(10), m_InputEnabled(true), m_ClickState(ClickState::None)
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

		Place(static_cast<int32_t>(clickPosX), static_cast<int32_t>(clickPosY));
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

		Erase(static_cast<int32_t>(clickPosX), static_cast<int32_t>(clickPosY));
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
	auto rng = std::bind(std::uniform_int_distribution<int>(1, 10), std::mt19937(static_cast<unsigned int>(seed)));

	if (m_PlaceSize == 1)
	{
		m_CellGrid->ReplaceCell(posX, posY, GetNewCellByID(m_ActiveCell));
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
				m_CellGrid->ReplaceCell(posX + x, posY + y, GetNewCellByID(m_ActiveCell));
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

cell::Cell* CellPlacement::GetNewCellByID(uint8_t id)
{
	switch (id)
	{
	case cell_id::water:
		return new cell::Water(m_CellGrid, 0, 0);
		break;
	case cell_id::sand:
		return new cell::Sand(m_CellGrid, 0, 0);
		break;
	case cell_id::poison:
		return new cell::Poison(m_CellGrid, 0, 0);
		break;
	case cell_id::stone:
		return new cell::Stone(m_CellGrid, 0, 0);
		break;
	case cell_id::lava:
		return new cell::Lava(m_CellGrid, 0, 0);
		break;
	case cell_id::smoke:
		return new cell::Smoke(m_CellGrid, 0, 0);
		break;
	case cell_id::steam:
		return new cell::Steam(m_CellGrid, 0, 0);
		break;
	default:
		std::string message = std::string("Default case triggered due to invalid cell ID: ") + std::to_string(id);
		std::cout << "[ERROR] " << message << std::endl;
		throw std::invalid_argument(message.c_str());
	}
}

void CellPlacement::OnImGuiRender()
{
	ImGui::Begin("Cell Placement Menu");

	m_InputEnabled = !ImGui::IsWindowHovered();

	ImGui::SliderInt("Radius", &m_PlaceSize, 1, 30);

	if (ImGui::Button("Water"))
		m_ActiveCell = cell_id::water;
	if (ImGui::Button("Sand"))
		m_ActiveCell = cell_id::sand;
	if (ImGui::Button("Poison"))
		m_ActiveCell = cell_id::poison;
	if (ImGui::Button("Stone"))
		m_ActiveCell = cell_id::stone;
	if (ImGui::Button("Lava"))
		m_ActiveCell = cell_id::lava;
	if (ImGui::Button("Smoke"))
		m_ActiveCell = cell_id::smoke;
	if (ImGui::Button("Steam"))
		m_ActiveCell = cell_id::steam;

	ImGui::NewLine();

	if (ImGui::Button("Reset"))
		m_CellGrid->Reset();

	ImGui::End();
}