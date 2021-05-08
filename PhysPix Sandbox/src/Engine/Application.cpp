#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "BatchRenderer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestBouncingImage.h"
#include "tests/TestBatchRendering.h"

#include "CellGrid.h"
#include "CellPlacement.h"

#include <iostream>
#include <chrono>

int main()
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
    window = glfwCreateWindow(resolutionX, resolutionY, "PhysPix Sandbox", NULL, NULL);
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

    long long seed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::srand(seed);

    // Log the current OpenGL version
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    // VSync
    glfwSwapInterval(1);

    // Blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // ImGui initialization
    IMGUI_CHECKVERSION();
    std::cout << "ImGui Version: "<< ImGui::GetVersion() << std::endl;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init();

    BatchRenderer::Init();

    test::TestClearColor testClearColor;

    CellGrid cellGrid(window, 3);
    CellPlacement cellPlacement(window, &cellGrid);

    long long lastFrameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwGetFramebufferSize(window, &resolutionX, &resolutionY);

        long long now = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        float deltaTime = (float)(now - lastFrameTime) / 1000000.0f;
        lastFrameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glViewport(0, 0, resolutionX, resolutionY));

        testClearColor.OnUpdate(deltaTime);
        testClearColor.OnRender();

        cellGrid.OnUpdate(deltaTime);
        cellGrid.OnRender();

        BatchRenderer::Flush();

        // ImGui new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        testClearColor.OnImGuiRender();
        cellPlacement.OnImGuiRender();

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