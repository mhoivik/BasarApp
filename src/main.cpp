#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "font.h"

void SetupImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Modify ImGui style
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.ChildRounding = 0.0f;
    style.GrabRounding = 0.0f;

    io.Fonts->AddFontFromMemoryTTF(JetBrainsFont,sizeof(JetBrainsFont), 16.0f);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

bool ButtonCenteredOnLine(const char* label, float alignment = 0.5f)
{
    ImGuiStyle& style = ImGui::GetStyle();

    float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;
    float off = (avail - size) * alignment;
    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

    return ImGui::Button(label);
}

int main(void)
{
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Utøy Bedehus Basar App", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cerr << "init of glew failed!" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    SetupImGui(window);

    int range = 1000;
	float color[4] = { 0.914f, 0.769f, 0.416f, 1.0f };
	float seccolor[192]; // 12 * 4 * sizeof(float) = 192

    for (int i = 0; i < sizeof(seccolor) / sizeof(seccolor[0]); i++) {
        if ((i % 4) == 0) {
            seccolor[i] = 1.0f;
        }
        else {
            seccolor[i] = 0.0f;
        }
    }

    int numberOfColors = 1;

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        // ImGui::ShowStyleEditor();

        ImGui::Begin("SetupGUI", nullptr, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

        ImGui::InputInt(" ", &range, NULL, NULL);
        ImGui::SliderInt("Antall Farger: ", &numberOfColors, 1, 12);
        ImGui::ColorEdit4("Color", color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
        float fps = ImGui::GetIO().Framerate;
        ImGui::Text("FPS: %.1f", fps);

        ImGui::End();

        ImGui::Render();
        glViewport(0, 0, (int)viewport->Size.x, (int)viewport->Size.y);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
