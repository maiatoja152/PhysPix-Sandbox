#include "TestBatchRendering.h"

#include "Renderer.h"

#include "imgui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"

#include <cstdlib>

namespace test
{
	TestBatchRendering::TestBatchRendering(float screenWidth, float screenHeight, uint32_t numOfQuads, float quadSize, std::string* texturePaths, uint8_t count)
		: m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight), m_QuadSize(quadSize),
		m_ModelMatrix(glm::mat4(1.0f)), m_ViewMatrix(glm::mat4(1.0f)), m_ProjectionMatrix(glm::ortho(0.0f, (float)m_ScreenWidth, 0.0f, (float)m_ScreenHeight, -1.0f, 1.0f))
	{
		// Make sure the number of textures passed is less than or equal to the max number of textures available to the fragment shader
		int maxTexUnits;
		GLCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTexUnits));
		ASSERT(count <= maxTexUnits - 1);

		std::vector<float> batchedVerts;
		std::vector<uint32_t> indices;

		for (uint32_t i = 0; i < numOfQuads; i++)
		{
			// The range of the offsets is set so that the quads can be up to half way off the screen
			float offsetX = RandomFloatRange(0.0f, m_ScreenWidth);
			float offsetY = RandomFloatRange(0.0f, m_ScreenHeight);

			// Vertex color RGBA values
			float r = RandomFloatRange(0.1f, 1.0f),
				  g = RandomFloatRange(0.1f, 1.0f),
				  b = RandomFloatRange(0.1f, 1.0f),
				  a = 1;

			uint8_t textureIndex = std::rand() % count;

			float scale = RandomFloatRange(0.5f, 1.5f);

			float quadVerts[] = {
				(-m_QuadSize / 2 + offsetX) * scale, (-m_QuadSize / 2 + offsetY) * scale, r, g, b, a, 0.0f, 0.0f, static_cast<float>(textureIndex), // 0
				 (m_QuadSize / 2 + offsetX) * scale, (-m_QuadSize / 2 + offsetY) * scale, r, g, b, a, 1.0f, 0.0f, static_cast<float>(textureIndex), // 1
				 (m_QuadSize / 2 + offsetX) * scale,  (m_QuadSize / 2 + offsetY) * scale, r, g, b, a, 1.0f, 1.0f, static_cast<float>(textureIndex), // 2
				(-m_QuadSize / 2 + offsetX) * scale,  (m_QuadSize / 2 + offsetY) * scale, r, g, b, a, 0.0f, 1.0f, static_cast<float>(textureIndex)  // 3
			};

			// Add to the batched verts
			batchedVerts.insert(batchedVerts.end(), &quadVerts[0], &quadVerts[sizeof(quadVerts) / sizeof(float)]);

			// The total number of verts currently in the vector of batched verts. Useful for generating indices.
			uint32_t n = i * 4;
			uint32_t quadIndices[] = { n, n + 1, n + 2, n + 2, n + 3, n };

			// Add to the indices
			indices.insert(indices.end(), &quadIndices[0], &quadIndices[sizeof(quadIndices) / sizeof(float)]);
		}

		// Vertex array
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>((const void*)&batchedVerts[0], 9 * 4 * numOfQuads * sizeof(float), GL_STATIC_DRAW);

		m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
		m_VertexBufferLayout->Push<float>(2); // Position
		m_VertexBufferLayout->Push<float>(4); // Vertex color
		m_VertexBufferLayout->Push<float>(2); // Texture coordinates
		m_VertexBufferLayout->Push<float>(1); // Texture index
		m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

		// Index buffer
		m_IndexBuffer = std::make_unique<IndexBuffer>((const unsigned int*)&indices[0], indices.size(), GL_STATIC_DRAW);

		// Shader
		m_Shader = std::make_unique<Shader>("res/shaders/BatchTextured.shader");
		m_Shader->Bind();

		// Texture
		std::vector<int> samplers;

		for (uint8_t i = 0; i < count; i++)
		{
			m_Textures.push_back(Texture(texturePaths[i]));
			m_Textures[i].Bind(i);
			
			samplers.push_back(i);
		}

		m_Shader->SetUniform1iv("u_Textures", samplers.size(), &samplers[0]);

		m_Renderer = std::make_unique<Renderer>();
	}

	TestBatchRendering::~TestBatchRendering()
	{
	}

	float TestBatchRendering::RandomFloatRange(float begin, float end)
	{
		return begin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (end - begin)));
	}

	void TestBatchRendering::OnUpdate(float deltaTime)
	{
	}

	void TestBatchRendering::OnRender()
	{
		glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
	}

	void TestBatchRendering::OnImGuiRender()
	{
	}
}