#pragma once

class CellGrid;

#include <stdint.h>

namespace cell
{
	class Flammable
	{
	public:
		Flammable();
		~Flammable();

	protected:
		void BurnOnContact(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		virtual void Burn() = 0;
	};
}