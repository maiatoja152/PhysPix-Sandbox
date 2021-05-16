#pragma once

namespace cell
{
	class Cell;
}

#include <stdint.h>

namespace cell
{
	class Flammable
	{
	protected:
		bool m_IsBurning;
		uint16_t m_BurnLifetime;
		uint16_t m_BurnCounter;

		Flammable();
	public:
		~Flammable();

	protected:
		void SetBurningOnContact(Cell* cell);
		void ExtinguishIfSuffocated(Cell* cell);
		void ExtinguishIfDoused(Cell* cell);
		void Burn(Cell* cell);
	};
}