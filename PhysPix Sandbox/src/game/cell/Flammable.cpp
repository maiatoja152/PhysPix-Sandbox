#include "Flammable.h"

#include "Cell.h"
#include "CellGrid.h"

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
		int32_t posX, posY;
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
		int32_t posX, posY;
		cell->GetPosition(&posX, &posY);

		if (cellGrid->GetCell(posX + 1, posY)->GetID() != cell_id::empty &&
			cellGrid->GetCell(posX - 1, posY)->GetID() != cell_id::empty &&
			cellGrid->GetCell(posX, posY + 1)->GetID() != cell_id::empty &&
			cellGrid->GetCell(posX, posY - 1)->GetID() != cell_id::empty)
		{
			m_IsBurning = false;
		}
	}
}