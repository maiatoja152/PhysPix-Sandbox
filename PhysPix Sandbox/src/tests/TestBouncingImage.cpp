#include "TestBouncingImage.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

namespace test
{
    TestBouncingImage::TestBouncingImage(uint32_t screenWidth, uint32_t screenHeight, std::string texturePath, uint32_t startPosX /*= 0*/, uint32_t startPosY /*= 0*/)
        : m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight), m_ImageSize(screenWidth/6), m_TranslationSpeed(6.0f), m_PositionX(startPosX), m_PositionY(startPosY), m_DirX(1), m_DirY(1),
        m_ModelMatrix(glm::mat4(1.0f)), m_ViewMatrix(glm::mat4(1.0f)), m_ProjectionMatrix(glm::ortho(0.0f, (float)m_ScreenWidth, 0.0f, (float)m_ScreenHeight, -1.0f, 1.0f))
	{
        float vertPositions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, // 0
             0.5f, -0.5f, 1.0f, 0.0f, // 1
             0.5f,  0.5f, 1.0f, 1.0f, // 2
            -0.5f,  0.5f, 0.0f, 1.0f  // 3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        // Vertex array
        m_VertexArray = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(vertPositions, 4 * 4 * sizeof(float));

        m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
        m_VertexBufferLayout->Push<float>(2);
        m_VertexBufferLayout->Push<float>(2);
        m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

        // Index buffer
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        // Shader
        m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        m_Shader->Bind();

        // Texture
        m_Texture = std::make_unique<Texture>(texturePath);
        m_Texture->Bind();
        // Set which texture the shader will sample (the int is the texture slot)
        m_Shader->SetUniform1i("u_Texture", 0);

        m_Renderer = std::make_unique<Renderer>();
	}

    TestBouncingImage::~TestBouncingImage()
    {
    }

	void TestBouncingImage::OnUpdate(float deltaTime)
	{
        m_PositionX += m_TranslationSpeed * m_DirX * deltaTime;
        m_PositionY += m_TranslationSpeed * m_DirY * deltaTime;

        if (m_PositionX > m_ScreenWidth - m_ImageSize / 2)
        {
            m_PositionX = m_ScreenWidth - m_ImageSize / 2;
            m_DirX = -1;
        }
        else if (m_PositionX < m_ImageSize / 2)
        {
            m_PositionX = m_ImageSize / 2;
            m_DirX = 1;
        }

        if (m_PositionY > m_ScreenHeight - m_ImageSize / 2)
        {
            m_PositionY = m_ScreenHeight - m_ImageSize / 2;
            m_DirY = -1;
        }
        else if (m_PositionY < m_ImageSize / 2)
        {
            m_PositionY = m_ImageSize / 2;
            m_DirY = 1;
        }
	}

    void TestBouncingImage::OnRender()
    {
        m_ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_PositionX, m_PositionY, 0));
        m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(m_ImageSize, m_ImageSize, 1));
        glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;

        m_Shader->SetUniformMat4f("u_MVP", mvp);

        m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }

    void TestBouncingImage::OnImGuiRender()
    {
        ImGui::Begin("TestBouncingImage");
        ImGui::SliderFloat("Translation speed", &m_TranslationSpeed, 0.0f, 20.0f);
        ImGui::SliderFloat("Image size", &m_ImageSize, 0.0f, m_ScreenWidth/2);
        ImGui::End();
    }
}