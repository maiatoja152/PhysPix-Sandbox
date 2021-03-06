#include "Cell.h"

#include "CellGrid.h"

#include "Empty.h"

namespace cell
{
	Cell::Cell()
		: m_CellGrid(nullptr), m_IsTicked(false), m_PosX(0), m_PosY(0), m_CellID(cell_id::default_id), m_Color(cell_color::default_color),
		m_IsFluid(false), m_Density(cell_density::default_density), m_BurnsSurroudings(false)
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