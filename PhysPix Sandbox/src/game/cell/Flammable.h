#pragma once

class CellGrid;

#include <stdint.h>

namespace cell
{
	class Flammable
	{
	protected:
		bool m_IsBurning;
		uint32_t m_BurnLifetime;
		uint32_t m_BurnCounter;

		Flammable();
	public:
		~Flammable();

	protected:
		void SetBurningOnContact(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		virtual void Burn() = 0;
	};
}