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
		Fire(CellGrid* cellGrid, int32_t posX, int32_t posY);
		~Fire();

		void OnUpdate(float deltaTime) override;
		void OnTick() override;

	private:
		void FireMove();
	};
}
