#pragma once

#include "Cell.h"

namespace cell
{
	class Water : public Cell
	{
	public:
		Water(int32_t posX, int32_t posY);
		~Water();

		void OnUpdate(float deltaTime) override;
		void OnTick() override;
	};
}