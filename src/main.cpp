#include <iostream>
#include <thread>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "font.h"

bool started = false;
int range = 1000;
GLFWwindow* windowView = nullptr;
typedef struct {
    float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
} Colors;

void SwitchColor(float r, float g, float b, float alfa, int arrayIndex, Colors colors[12]) {
    colors[arrayIndex].color[0] = r;
    colors[arrayIndex].color[1] = g;
    colors[arrayIndex].color[2] = b;
    colors[arrayIndex].color[3] = alfa;
}


void BasarView(GLFWwindow* windowView) {
    
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(windowView);
    glfwPollEvents();
    if (!started)
        glfwDestroyWindow(windowView);
}

void SettingsMenu(Colors colors[12],int& range, int& numberOfColors) {
    ImGui::Begin("SetupGUI", nullptr, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    ImGui::InputInt(" ", &range, NULL, NULL);
    ImGui::SliderInt("Antall Farger: ", &numberOfColors, 1, 12);

    for (int i = 0; i < numberOfColors; ++i) {
        ImGui::ColorEdit4(("Color " + std::to_string(i+1)).c_str(), colors[i].color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
    }

    if (ImGui::Button("START")) {
        started = true;
        
        windowView = glfwCreateWindow(1200, 600, "Viewport", nullptr, nullptr);
        if (!windowView) {
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(windowView);
    }

    float fps = ImGui::GetIO().Framerate;
    ImGui::Text("FPS: %.1f", fps);


    ImGui::End();
}

void RunTime(GLFWwindow* window) {
    ImGui::Begin("Running" ,nullptr, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    if (ImGui::Button("Stop")) {
        glfwDestroyWindow(windowView);
        windowView = nullptr;
        started = false;
    }
    ImGui::End();
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


int main(void) {
    Colors colors[12];
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(640, 480, "Utøy Bedehus Basar App", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "init of glew failed!" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    (void)io;

    ImGui::StyleColorsDark();
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


    // 8 farger: hvit, svart, lilla, gul, rød, blå, grønn, brun.
    SwitchColor(1.0f, 1.0f, 1.0f, 1.0f, 0, colors); // hvit/blank
    SwitchColor(0.0f, 0.0f, 0.0f, 0.0f, 1, colors); // svart(Her har vi et problem...)
    SwitchColor(1.0f, 0.0f, 1.0f, 1.0f, 2, colors); // lilla
    SwitchColor(1.0f, 1.0f, 0.0f, 1.0f, 3, colors); // gul
    SwitchColor(1.0f, 0.0f, 0.0f, 1.0f, 4, colors); // rød
    SwitchColor(0.0f, 0.0f, 1.0f, 1.0f, 5, colors); // blå
    SwitchColor(0.0f, 1.0f, 0.0f, 1.0f, 6, colors); // grønn
    SwitchColor(0.7f, 0.5f, 0.0f, 1.0f, 7, colors); // brun
    int numberOfColors = 1;


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        // ImGui::ShowStyleEditor();

        if (!started) {
            glfwMakeContextCurrent(window);
            SettingsMenu(colors, range,numberOfColors); 
        }
        else {
            glfwMakeContextCurrent(windowView);
            // BasarView(windowView);
            glfwMakeContextCurrent(window);
            RunTime(windowView); 
        }
        ImGui::Render();
        glViewport(0, 0, (int)viewport->Size.x, (int)viewport->Size.y);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    started = false;
    ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
