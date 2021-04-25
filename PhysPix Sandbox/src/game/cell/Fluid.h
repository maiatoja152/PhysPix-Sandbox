#pragma once

#include "Cell.h"

namespace cell
{
	class Fluid : public Cell
	{
	protected:
		int8_t m_FluidDirection;

	public:
		Fluid();
		~Fluid();

	protected:
		void FluidMove();
	};
}