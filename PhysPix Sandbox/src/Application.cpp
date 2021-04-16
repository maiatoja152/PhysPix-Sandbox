#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"

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

#include <chrono>

#include "tests/TestClearColor.h"
#include "tests/TestBouncingImage.h"

int main(void)
{
    GLFWwindow* window;

    // Initialize GLFW
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int resolutionX = 1280, resolutionY = 960;

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

    // Log the current OpenGL version
    std::cout << glGetString(GL_VERSION) << std::endl;

    // VSync
    glfwSwapInterval(0);

    // Blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Renderer renderer;

    // ImGui initialization
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init();

    long long lastFrameTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    test::TestClearColor testClearColor;
    test::TestBouncingImage testBouncingImage(resolutionX, resolutionY, 100, 100, 340);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Dynamic window size
        glfwGetWindowSize(window, &resolutionX, &resolutionY);

        /* Render here */
        renderer.Clear();

        // Calculate deltaTime
        long long currentFrameTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        int deltaTime = currentFrameTime - lastFrameTime;

        testClearColor.OnUpdate(deltaTime);
        testClearColor.OnRender();

        testBouncingImage.OnUpdate(deltaTime);
        testBouncingImage.OnRender();

        // ImGui new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        testClearColor.OnImGuiRender();

        testBouncingImage.OnImGuiRender();

        // ImGui render
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        lastFrameTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    // ImGUI shutdown
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}