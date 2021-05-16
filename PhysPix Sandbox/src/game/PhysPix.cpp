#include "PhysPix.h"

#include "GLCore.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "BatchRenderer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "CellGrid.h"
#include "CellPlacement.h"

#include <stdint.h>
#include <iostream>
#include <chrono>
#include <memory>

namespace physpix
{
	static GLFWwindow* glfwWindow;
	static int32_t windowWidth = 1280, windowHeight = 960;
    static constexpr int32_t minWindowWidth = 700, minWindowHeight = 780;

    static constexpr float cellSize = 4.0f;
    static std::unique_ptr<CellGrid> cellGrid;
    static std::unique_ptr<CellPlacement> cellPlacement;

    static constexpr float clearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

	bool Init()
	{
        if (!glfwInit())
            return false;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        /* Create a windowed mode window and its OpenGL context */
        glfwWindow = glfwCreateWindow(windowWidth, windowHeight, "PhysPix Sandbox", NULL, NULL);
        if (!glfwWindow)
        {
            glfwTerminate();
            return false;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(glfwWindow);

        // VSync
        glfwSwapInterval(1);

        glfwSetWindowSizeLimits(glfwWindow, minWindowWidth, minWindowHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);

        // Initialize GLEW
        if (glewInit() != GLEW_OK)
        {
            glfwTerminate();
            return false;
        }

        // Log the current OpenGL version
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

        // ImGui initialization
        IMGUI_CHECKVERSION();
        std::cout << "ImGui Version: " << ImGui::GetVersion() << std::endl;

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init();

        BatchRenderer::Init();

        cellGrid = std::make_unique<CellGrid>(glfwWindow, cellSize);
        cellPlacement = std::make_unique<CellPlacement>(glfwWindow, cellGrid.get());

        GLCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));

        return true;
	}

    void Run()
    {
        long long lastFrameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(glfwWindow))
        {
            glfwGetFramebufferSize(glfwWindow, &windowWidth, &windowHeight);
            GLCall(glViewport(0, 0, windowWidth, windowHeight));

            long long now = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            float deltaTime = (float)(now - lastFrameTime) / 1000000.0f;
            lastFrameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

            cellGrid->OnUpdate(deltaTime);

            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            cellGrid->OnRender();

            BatchRenderer::Flush();

            // ImGui new frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            cellPlacement->OnImGuiRender();

            // ImGui render
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(glfwWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    void Shutdown()
    {
        // ImGUI shutdown
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        BatchRenderer::Shutdown();

        glfwTerminate();
    }
}