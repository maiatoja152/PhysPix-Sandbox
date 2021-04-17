#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include <memory>

namespace test
{
	class TestBatchRendering : public Test
	{
	public:
		TestBatchRendering(float screenWidth, float screenHeight, uint32_t numOfQuads, float quadSize);
		~TestBatchRendering();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_ScreenWidth, m_ScreenHeight, m_QuadSize;

		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexBufferLayout> m_VertexBufferLayout;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		std::unique_ptr<Shader> m_Shader;

		std::unique_ptr<Renderer> m_Renderer;

		glm::mat4 m_ModelMatrix, m_ViewMatrix, m_ProjectionMatrix;

		float RandomFloatRange(float begin, float end);
	};
}