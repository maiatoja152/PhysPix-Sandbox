#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

namespace test
{
	class TestBouncingImage : public Test
	{
	public:
		TestBouncingImage(int screenWidth, int screenHeight, float imageSize, int startPosX = 0, int startPosY = 0);
		~TestBouncingImage();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		int m_ScreenHeight, m_ScreenWidth;
		float m_TranslationSpeed, m_PositionX, m_PositionY;
		int m_DirX, m_DirY;

		VertexBuffer* m_VertexBuffer;
		VertexBufferLayout* m_VertexBufferLayout;
		VertexArray* m_VertexArray;
		IndexBuffer* m_IndexBuffer;

		Shader* m_Shader;
		Texture* m_Texture;

		Renderer* m_Renderer;

		glm::mat4 m_ModelMatrix, m_ViewMatrix, m_ProjectionMatrix;
	};
}