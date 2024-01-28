#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"

// ... (other includes)

int main() {
    // ... (initialize your application)

    // Setup ImGui context
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Initialize ImGui backend for OpenGL
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // ... (your main loop)

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
