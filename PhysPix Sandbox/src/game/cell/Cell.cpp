#include "Cell.h"

#include "CellGrid.h"

#include "Empty.h"

namespace cell
{
	Cell::Cell()
		: m_PosX(0), m_PosY(0), m_CellID(cell_id::default_id), m_CellGrid(nullptr), m_Color(1.0f, 0.0f, 1.0f, 1.0f), m_IsFluid(false)
	{
	}

	Cell::~Cell()
	{
	}

	void Cell::RemoveCell()
	{
		m_CellGrid->ReplaceCell(m_PosX, m_PosY, new Empty());
	}

	void Cell::UpdatePosition(uint16_t posX, uint16_t posY)
	{
		m_PosX = posX;
		m_PosY = posY;
	}
}