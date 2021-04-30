#pragma once

#include "Fluid.h"

namespace cell
{
	class Poison : public Fluid
	{
	public:
		Poison(CellGrid* cellGrid, int32_t posX, int32_t posY);
		~Poison();

		void OnUpdate(float deltaTime) override;
		void OnTick() override;

		void Spread();
	};
}