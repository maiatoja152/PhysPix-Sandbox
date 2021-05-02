#pragma once

class CellGrid;

#include "glm/gtc/matrix_transform.hpp"

#include <stdint.h>

namespace cell
{
	class Cell
	{
	protected:
		CellGrid* m_CellGrid;
		int32_t m_PosX, m_PosY;
		uint8_t m_CellID;

		glm::vec4 m_Color;

		bool m_IsFluid;

	public:
		Cell();
		~Cell();

		virtual Cell* clone() const = 0;

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnTick() {}

		void RemoveCell();

		void UpdatePosition(uint16_t posX, uint16_t posY);

		inline glm::vec4 GetColor() { return m_Color; }
		inline uint8_t GetID() { return m_CellID; }
		inline bool IsFluid() { return m_IsFluid; }
	};
}

namespace cell_id
{
	static constexpr uint8_t default_id = 0;
	static constexpr uint8_t empty = 1;
	static constexpr uint8_t water = 2;
	static constexpr uint8_t poison = 3;
	static constexpr uint8_t lava = 4;
	static constexpr uint8_t sand = 5;
	static constexpr uint8_t stone = 6;
	static constexpr uint8_t boundary = 255;
}