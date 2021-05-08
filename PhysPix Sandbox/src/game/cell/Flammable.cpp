#include "Flammable.h"

#include "Cell.h"
#include "CellGrid.h"

namespace cell
{
	Flammable::Flammable()
	{
	}

	Flammable::~Flammable()
	{
	}

	void Flammable::BurnOnContact(CellGrid* cellGrid, uint16_t posX, uint16_t posY)
	{
		if (cellGrid->GetCell(posX + 1, posY)->BurnsSurroudings())
			Burn();

		if (cellGrid->GetCell(posX - 1, posY)->BurnsSurroudings())
			Burn();

		if (cellGrid->GetCell(posX, posY + 1)->BurnsSurroudings())
			Burn();

		if (cellGrid->GetCell(posX, posY - 1)->BurnsSurroudings())
			Burn();
	}
}