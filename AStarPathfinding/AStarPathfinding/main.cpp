#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void DrawGrid(const std::vector<std::vector<int>>& grid, ImVec2 gridStart, float cellSize)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    ImU32 wallColor = IM_COL32(0, 0, 0, 255);
    ImU32 emptyColor = IM_COL32(255, 255, 255, 255);
    ImU32 lineColor = IM_COL32(120, 120, 120, 255);

    for (int y = 0; y < grid.size(); y++)
    {
        for (int x = 0; x < grid[y].size(); x++)
        {
            float posX = gridStart.x + x * cellSize;
            float posY = gridStart.y + y * cellSize;

            ImVec2 cellMin = ImVec2(posX, posY);
            ImVec2 cellMax = ImVec2(posX + cellSize, posY + cellSize);

            if (grid[y][x] == 1)
            {
                drawList->AddRectFilled(cellMin, cellMax, wallColor);
            }
            else if (grid[y][x] == 0)
            {
                drawList->AddRectFilled(cellMin, cellMax, emptyColor);
            }
            drawList->AddRect(cellMin, cellMax, lineColor, 0.0f, 0, 1.0f);
        }
    }
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Fail to initialzie GLFW\n";
        return -1;
    }

    const char* glsl_version = "#version 130";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(
        1280,
        720,
        "A* Pathfinding Visualizer",
        nullptr,
        nullptr
    );

    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failded to initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    std::vector<std::vector<int>> grid =
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}
    };

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        ImGui::Begin("A* Control Panel");

        DrawGrid(grid, ImVec2(5,10), 40.0f);

        ImGui::Text("GUI Step 2");
        ImGui::Text("Grid data is ready.");
        
        ImGui::End();

        ImGui::Render();

        int display_w = 0;
        int display_h = 0;

        glfwGetFramebufferSize(window, &display_w, &display_h);

        glViewport(0, 0, display_w, display_h);

        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}