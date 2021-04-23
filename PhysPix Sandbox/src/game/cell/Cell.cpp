#include "Cell.h"

#include "CellGrid.h"

#include "Empty.h"

namespace cell
{
	Cell::Cell()
		: m_PosX(0), m_PosY(0), m_CellGrid(nullptr)
	{
		m_CellGrid = nullptr;
	}

	Cell::~Cell()
	{
	}

	void Cell::RemoveCell()
	{
		m_CellGrid->ReplaceCell(m_PosX, m_PosY, new Empty());
	}

	void Cell::MoveCell(uint16_t x, uint16_t y)
	{
		RemoveCell();
		m_CellGrid->ReplaceCell(x, y, this);

		m_PosX = x;
		m_PosY = y;
	}
}