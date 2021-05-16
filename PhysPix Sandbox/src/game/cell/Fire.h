#pragma once

#include "Cell.h"

#include <random>
#include <functional>

namespace cell
{
	class Fire : public Cell
	{
	private:
		std::_Binder<std::remove_cv<std::_Unforced>::type, std::uniform_int_distribution<int>, std::mt19937> m_rng;
		int m_rngMax;

		uint16_t m_Lifetime, m_LifetimeCounter;

	public:
		Fire(CellGrid* cellGrid, uint16_t posX, uint16_t posY);
		~Fire();

		void OnTick() override;

	private:
		void FireMove();
		void RemoveIfDoused();
	};
}
