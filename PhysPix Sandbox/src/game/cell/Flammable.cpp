#include "Flammable.h"

#include "Cell.h"
#include "CellGrid.h"

#include "Fire.h"

namespace cell
{
	Flammable::Flammable()
		: m_IsBurning(false), m_BurnLifetime(0), m_BurnCounter(0)
	{
	}

	Flammable::~Flammable()
	{
	}

	void Flammable::SetBurningOnContact(Cell* cell)
	{
		auto cellGrid = cell->GetCellGrid();
		uint16_t posX, posY;
		cell->GetPosition(&posX, &posY);

		if (cellGrid->GetCell(posX + 1, posY)->BurnsSurroudings() ||
			cellGrid->GetCell(posX - 1, posY)->BurnsSurroudings() ||
			cellGrid->GetCell(posX, posY + 1)->BurnsSurroudings() ||
			cellGrid->GetCell(posX, posY - 1)->BurnsSurroudings() ||
			cellGrid->GetCell(posX + 1, posY + 1)->BurnsSurroudings() ||
			cellGrid->GetCell(posX + 1, posY - 1)->BurnsSurroudings() ||
			cellGrid->GetCell(posX - 1, posY - 1)->BurnsSurroudings() ||
			cellGrid->GetCell(posX - 1, posY + 1)->BurnsSurroudings())
		{
			m_IsBurning = true;
		}
	}

	void Flammable::ExtinguishIfSuffocated(Cell* cell)
	{
		auto cellGrid = cell->GetCellGrid();
		uint16_t posX, posY;
		cell->GetPosition(&posX, &posY);

		if (cellGrid->GetCell(posX + 1, posY)->GetID() != cell_id::empty &&
			cellGrid->GetCell(posX - 1, posY)->GetID() != cell_id::empty &&
			cellGrid->GetCell(posX, posY + 1)->GetID() != cell_id::empty &&
			cellGrid->GetCell(posX, posY - 1)->GetID() != cell_id::empty)
		{
			m_IsBurning = false;
		}
	}

	void Flammable::Burn(Cell* cell)
	{
		CellGrid* cellGrid = cell->GetCellGrid();
		uint16_t posX, posY;
		cell->GetPosition(&posX, &posY);

		int8_t dir = cellGrid->GetDir();
		// Check down
		if (cellGrid->GetCell(posX, posY + 1)->GetID() == cell_id::empty)
		{
			cellGrid->ReplaceCell(posX, posY + 1, new Fire(cellGrid, posX, posY + 1));
		}
		// Check upper left and right
		else if (cellGrid->GetCell(posX + dir, posY + 1)->GetID() == cell_id::empty)
		{
			cellGrid->ReplaceCell(posX + dir, posY + 1, new Fire(cellGrid, posX + dir, posY + 1));
		}
		else if (cellGrid->GetCell(posX - dir, posY + 1)->GetID() == cell_id::empty)
		{
			cellGrid->ReplaceCell(posX - dir, posY + 1, new Fire(cellGrid, posX - dir, posY + 1));
		}
		// Check left and right
		else if (cellGrid->GetCell(posX + dir, posY)->GetID() == cell_id::empty)
		{
			cellGrid->ReplaceCell(posX + dir, posY, new Fire(cellGrid, posX + dir, posY));
		}
		else if (cellGrid->GetCell(posX - dir, posY)->GetID() == cell_id::empty)
		{
			cellGrid->ReplaceCell(posX - dir, posY, new Fire(cellGrid, posX - dir, posY));
		}

		if (++m_BurnCounter >= m_BurnLifetime)
		{
			cellGrid->ReplaceCell(posX, posY, new Fire(cellGrid, posX, posX));
		}
	}
}