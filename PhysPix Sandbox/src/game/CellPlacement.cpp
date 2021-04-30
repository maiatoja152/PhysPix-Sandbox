#include "CellPlacement.h"

#include "cell/Cell.h"
#include "CellGrid.h"

CellPlacement::CellPlacement()
	: m_ActiveCell(nullptr), m_CellGrid()
{
}

CellPlacement::~CellPlacement()
{
}

void CellPlacement::Place(int32_t x, int32_t y)
{
	cell::Cell copy = *m_ActiveCell;

	m_CellGrid->ReplaceCell(x / m_CellGrid->GetCellSize(), y / m_CellGrid->GetCellSize(), &copy);
}