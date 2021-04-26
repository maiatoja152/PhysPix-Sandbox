#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>
#include <ctime>

#include "BatchRenderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestBouncingImage.h"
#include "tests/TestBatchRendering.h"

#include "cell/CellGrid.h"

int main(void)
{
    GLFWwindow* window;

    // Initialize GLFW
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int32_t resolutionX = 1280, resolutionY = 960;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(resolutionX, resolutionY, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    std::srand(std::time(NULL));

    // Log the current OpenGL version
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    // VSync
    glfwSwapInterval(1);

    // Blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Renderer renderer;

    // ImGui initialization
    IMGUI_CHECKVERSION();
    std::cout << "ImGui Version: "<< ImGui::GetVersion() << std::endl;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init();

    BatchRenderer::Init();

    test::TestClearColor testClearColor;

    CellGrid cellGrid(resolutionX, resolutionY, 2);

    long long lastFrameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        float deltaTime = ((float)(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - lastFrameTime)) / 1000000.0f;
        lastFrameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        // Dynamic window size
        glfwGetWindowSize(window, &resolutionX, &resolutionY);

        /* Render here */
        renderer.Clear();

        testClearColor.OnUpdate(deltaTime);
        testClearColor.OnRender();

        Shader shader("res/shaders/BatchTextured.shader");
        shader.Bind();

        glm::mat4 projection = glm::ortho(0.0f, (float)resolutionX, 0.0f, (float)resolutionY, -1.0f, 1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 mvp = projection * view * model;
        shader.SetUniformMat4f("u_MVP", mvp);

        cellGrid.OnUpdate(deltaTime);
        cellGrid.OnRender();

        BatchRenderer::Flush();

        // ImGui new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        testClearColor.OnImGuiRender();

        // ImGui render
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // ImGUI shutdown
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    BatchRenderer::Shutdown();

    glfwTerminate();

    return 0;
}