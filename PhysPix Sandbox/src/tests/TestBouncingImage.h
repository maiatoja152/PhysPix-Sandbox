#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include <memory>

namespace test
{
	class TestBouncingImage : public Test
	{
	public:
		TestBouncingImage(uint32_t screenWidth, uint32_t screenHeight, std::string texturePath, uint32_t startPosX = 0, uint32_t startPosY = 0);
		~TestBouncingImage();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		uint32_t m_ScreenHeight, m_ScreenWidth;
		float m_ImageSize, m_TranslationSpeed, m_PositionX, m_PositionY;
		int8_t m_DirX, m_DirY;

		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexBufferLayout> m_VertexBufferLayout;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		std::unique_ptr <Renderer> m_Renderer;

		glm::mat4 m_ModelMatrix, m_ViewMatrix, m_ProjectionMatrix;
	};
}