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
		bool m_IsTicked;
		int32_t m_PosX, m_PosY;
		uint8_t m_CellID;

		glm::vec4 m_Color;

		bool m_IsFluid;
		uint8_t m_Density;

		bool m_BurnsSurroudings;

	public:
		Cell();
		~Cell();

		virtual void OnTick() = 0;

		void RemoveCell();

		void UpdatePosition(uint16_t posX, uint16_t posY);

		inline CellGrid* GetCellGrid() { return m_CellGrid; }
		void SetTickState(bool state) { m_IsTicked = state; }
		inline bool IsTicked() { return m_IsTicked; }
		inline void GetPosition(int32_t* x, int32_t* y) { *x = m_PosX; *y = m_PosY; }
		inline uint8_t GetID() { return m_CellID; }
		inline glm::vec4 GetColor() { return m_Color; }

		inline bool IsFluid() { return m_IsFluid; }
		inline uint8_t GetDensity() { return m_Density; }
		inline bool BurnsSurroudings() { return m_BurnsSurroudings; }
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
	static constexpr uint8_t smoke = 7;
	static constexpr uint8_t fire = 8;
	static constexpr uint8_t steam = 9;
	static constexpr uint8_t oil = 10;
	static constexpr uint8_t boundary = 255;
}

namespace cell_density
{
	static constexpr uint8_t default_density = 255;
	static constexpr uint8_t fire = 0;
	static constexpr uint8_t steam = 125;
	static constexpr uint8_t smoke = 126;
	static constexpr uint8_t water = 127;
	static constexpr uint8_t poison = 127;
	static constexpr uint8_t oil = 128;
	static constexpr uint8_t lava = 129;
}