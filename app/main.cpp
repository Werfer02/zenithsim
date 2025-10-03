#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

void DrawRadarIcon(ImDrawList* draw_list, ImVec2 center, float radius, ImU32 color) {
    // Filled base circle
    draw_list->AddCircleFilled(center, radius, color, 32);

    // Crosshair lines
    draw_list->AddLine(ImVec2(center.x - radius, center.y), ImVec2(center.x + radius, center.y), IM_COL32(255, 255, 255, 255), 1.0f);
    draw_list->AddLine(ImVec2(center.x, center.y - radius), ImVec2(center.x, center.y + radius), IM_COL32(255, 255, 255, 255), 1.0f);

    // Extra ring (optional)
    draw_list->AddCircle(center, radius * 0.66f, IM_COL32(255, 255, 255, 128), 32, 1.0f);
}


void glfw_error_callback(int error, const char* description){
    std::cerr << "GLFW error " << error << ": " << description << std::endl;
}

int main(){
    
    std::cout << "Hello, World!\n";

    glfwInit();
    glfwSetErrorCallback(glfw_error_callback);
    
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "zenithsim gui", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Begin("Custom Shape Demo");

        ImVec2 window_pos = ImGui::GetWindowPos();      // Top-left corner of the window (screen space)
        ImVec2 window_size = ImGui::GetWindowSize();    // Width and height of the window

        ImVec2 center = ImVec2(
            window_pos.x + window_size.x * 0.5f,
            window_pos.y + window_size.y * 0.5f
        );
        ImDrawList* draw = ImGui::GetWindowDrawList();

        DrawRadarIcon(draw, center, 80.0f, IM_COL32(0, 200, 100, 200));

        ImGui::End();
        
        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

}   