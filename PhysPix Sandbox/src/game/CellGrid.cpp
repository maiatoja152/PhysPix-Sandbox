#include "CellGrid.h"

#include "BatchRenderer.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "cell/Cell.h"
#include "cell/Empty.h"
#include "cell/Water.h"
#include "cell/Sand.h"
#include "cell/Poison.h"
#include "cell/Boundary.h"

#include "CellPlacement.h"

#include <random>
#include <chrono>
#include <numeric>

CellGrid::CellGrid(GLFWwindow* window, float cellSize, CellPlacement* cellPlacement /*= nullptr*/)
	: m_Window(window), m_WindowWidth(0), m_WindowHeight(0), m_CellSize(cellSize), m_CellColumns(0), m_CellRows(0),
	m_Cells(NULL), m_TickInterval(0.02f), m_TickTimer(m_TickInterval), m_BoundaryPtr(std::make_unique<cell::Boundary>()), m_Dir(1), m_CellPlacement(cellPlacement)
{
	glfwGetFramebufferSize(window, &m_WindowWidth, &m_WindowHeight);
	m_CellColumns = static_cast<uint16_t>(m_WindowWidth / cellSize);
	m_CellRows = static_cast<uint16_t>(m_WindowHeight / cellSize);

	InitCells();
}

CellGrid::~CellGrid()
{
	// Delete all cells
	for (auto row : m_Cells)
	{
		for (auto cell : row)
		{
			delete cell;
		}
	}
	m_Cells.clear();
}

void CellGrid::OnUpdate(float deltaTime)
{
	m_TickTimer -= deltaTime / 1000;

	if (m_TickTimer <= 0)
	{
		Tick();
		m_TickTimer += m_TickInterval;
	}

	for (uint16_t i = 0; i < m_Cells.size(); i++)
	{
		for (uint16_t j = 0; j < m_Cells[0].size(); j++)
		{
			if (m_Cells[i][j]->GetID() != cell_id::empty)
				m_Cells[i][j]->OnUpdate(deltaTime);
		}
	}
}

void CellGrid::Tick()
{
	if (!glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED))
	{
		glfwGetFramebufferSize(m_Window, &m_WindowWidth, &m_WindowHeight);
		ResizeGrid(static_cast<uint16_t>(m_WindowWidth / m_CellSize), static_cast<uint16_t>(m_WindowHeight / m_CellSize));
	}

	m_Dir *= -1;

	if (m_CellPlacement != nullptr)
		m_CellPlacement->OnTick();

	// Random indices
	std::vector<uint16_t> indices(m_CellColumns);
	std::iota(indices.begin(), indices.end(), 0);
	long long seed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::shuffle(indices.begin(), indices.end(), std::mt19937(static_cast<unsigned int>(seed)));

	for (uint16_t i = 0; i < m_Cells.size(); i++)
	{
		for (uint16_t j = 0; j < m_Cells[0].size(); j++)
		{
			if (m_Cells[indices[i]][j]->GetID() != cell_id::empty && !m_Cells[indices[i]][j]->IsTicked())
			{
				m_Cells[indices[i]][j]->SetTickState(true);
				m_Cells[indices[i]][j]->OnTick();
			}
		}
	}

	// Untick all cells
	for (auto& row : m_Cells)
		for (auto& cell : row)
			cell->SetTickState(false);
}

void CellGrid::OnRender()
{
	Shader shader("res/shaders/BatchTextured.shader");
	shader.Bind();

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_WindowWidth), 0.0f, static_cast<float>(m_WindowHeight), -1.0f, 1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 mvp = projection * view * model;
	shader.SetUniformMat4f("u_MVP", mvp);

	glm::vec2 border = { m_WindowWidth % m_CellColumns, m_WindowHeight % m_CellRows };

	BatchRenderer::BeginBatch();
	for (uint16_t i = 0; i < m_Cells.size(); i++)
	{
		for (uint16_t j = 0; j < m_Cells[0].size(); j++)
		{
			// Don't draw a quad for empty cells for performance
			if (m_Cells[i][j]->GetID() != cell_id::empty)
			{
				glm::vec2 position = { static_cast<float>(i * m_CellSize + m_CellSize / 2 + border.x / 2), static_cast<float>(j * m_CellSize + m_CellSize / 2 + border.y / 2) };
				BatchRenderer::DrawQuad(position, { m_CellSize, m_CellSize }, m_Cells[i][j]->GetColor());
			}
		}
	}
	BatchRenderer::EndBatch();
}

void CellGrid::InitCells()
{
	m_Cells = std::vector<std::vector<cell::Cell*>>(m_CellColumns, std::vector<cell::Cell*>(m_CellRows));

	for (uint16_t i = 0; i < m_Cells.size(); i++)
	{
		for (uint16_t j = 0; j < m_Cells[0].size(); j++)
		{
			m_Cells[i][j] = new cell::Empty();
		}
	}
}

void CellGrid::Reset()
{
	for (uint16_t i = 0; i < m_Cells.size(); i++)
	{
		for (uint16_t j = 0; j < m_Cells[0].size(); j++)
		{
			// Only replace non-empty cells
			if (m_Cells[i][j]->GetID() != 1)
				ReplaceCell(i, j, new cell::Empty());
		}
	}
}

void CellGrid::ResizeGrid(uint16_t columns, uint16_t rows)
{
	if (columns > m_CellColumns)
	{
		m_Cells.reserve(columns);

		uint16_t rowsToAdd = columns - m_CellColumns;
		for (uint16_t i = 0; i < rowsToAdd; i++)
		{
			std::vector<cell::Cell*> emptyRow(m_CellRows);
			for (auto& cell : emptyRow)
				cell = new cell::Empty();

			m_Cells.push_back(emptyRow);
		}
	}
	else if (columns < m_CellColumns)
	{
		uint16_t rowsToRemove = m_CellColumns - columns;
		for (uint16_t i = 0; i < rowsToRemove; i++)
		{
			for (auto& cell : m_Cells.back())
				delete cell;

			m_Cells.pop_back();
		}
	}

	if (rows > m_CellRows)
	{
		for (auto& row : m_Cells)
		{
			row.reserve(rows);

			uint16_t cellsToAdd = rows - m_CellRows;
			for (uint16_t i = 0; i < cellsToAdd; i++)
			{
				row.push_back(new cell::Empty);
			}
		}
	}
	else if (rows < m_CellRows)
	{
		for (auto& row : m_Cells)
		{
			uint16_t cellsToRemove = m_CellRows - rows;
			for (uint16_t i = 0; i < cellsToRemove; i++)
			{
				delete row.back();
				row.pop_back();
			}
		}
	}

	m_CellColumns = columns;
	m_CellRows = rows;
}

cell::Cell* CellGrid::GetCell(uint16_t x, uint16_t y)
{
	if (x > m_CellColumns - 1 || y > m_CellRows - 1)
		return m_BoundaryPtr.get();
	else
		return m_Cells[x][y];
}

void CellGrid::ReplaceCell(uint16_t x, uint16_t y, cell::Cell* replacement)
{
	if (x < m_CellColumns && y < m_CellRows)
	{
		delete m_Cells[x][y];
		m_Cells[x][y] = replacement;
		replacement->UpdatePosition(x, y);
	}
	else
		delete replacement;
}

void CellGrid::MoveCell(uint16_t posX, uint16_t posY, uint16_t destX, uint16_t destY)
{
	delete m_Cells[destX][destY];

	m_Cells[destX][destY] = m_Cells[posX][posY];
	m_Cells[destX][destY]->UpdatePosition(destX, destY);

	m_Cells[posX][posY] = new cell::Empty();
}

void CellGrid::SwapCells(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	cell::Cell* temp = m_Cells[x2][y2];

	m_Cells[x2][y2] = m_Cells[x1][y1];
	m_Cells[x1][y1] = temp;

	m_Cells[x2][y2]->UpdatePosition(x2, y2);
	m_Cells[x1][y1]->UpdatePosition(x1, y1);
}

void CellGrid::DisplaceFluid(uint16_t posX, uint16_t posY, int32_t destX, int32_t destY)
{
	// Check left and right
	if (GetCell(destX + m_Dir, destY)->GetID() == cell_id::empty)
	{
		SwapCells(destX, destY, destX + m_Dir, destY);
		SwapCells(posX, posY, destX, destY);
	}
	else if (GetCell(destX - m_Dir, destY)->GetID() == cell_id::empty)
	{
		SwapCells(destX, destY, destX - m_Dir, destY);
		SwapCells(posX, posY, destX, destY);
	}
	// Check upper left and right
	else if (GetCell(destX + m_Dir, destY + 1)->GetID() == cell_id::empty)
	{
		SwapCells(destX, destY, destX + m_Dir, destY + 1);
		SwapCells(posX, posY, destX, destY);
	}
	else if (GetCell(destX - m_Dir, destY + 1)->GetID() == cell_id::empty)
	{
		SwapCells(destX, destY, destX - m_Dir, destY + 1);
		SwapCells(posX, posY, destX, destY);
	}
	else
	{
		SwapCells(posX, posY, destX, destY);
	}
}