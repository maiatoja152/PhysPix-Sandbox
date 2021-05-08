#pragma once

#include "Fluid.h"

namespace cell
{
	class Lava : public Fluid
	{
	public:
		Lava(CellGrid* cellGrid, int32_t posX, int32_t posY);
		~Lava();

		void OnUpdate(float deltaTime) override;
		void OnTick() override;

	private:
		void BurnFlammables();
	};
}