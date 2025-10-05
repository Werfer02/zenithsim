#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

#include "uinode.hpp"
#include "node.hpp"

void glfwerrorcallback(int error, const char* description){
    std::cerr << "GLFW error " << error << ": " << description << std::endl;
}

int main(){
    
    std::cout << "Hello, World!\n";

    glfwInit();
    glfwSetErrorCallback(glfwerrorcallback);
    
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "zenithsim gui", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    std::vector<uinode> uinodes;

    float shapewidth = 0, shaperadius = 0;

    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Begin("Custom Shape");{

            ImGui::SliderFloat("width", &shapewidth, -1.0f, 500.0f);
            ImGui::SliderFloat("connection radius", &shaperadius, -1.0f, 200.0f);

            ImVec2 window_pos = ImGui::GetWindowPos();
            ImVec2 window_size = ImGui::GetWindowSize();

            ImVec2 center = ImVec2(
                window_pos.x + window_size.x * 0.5f,
                window_pos.y + window_size.y * 0.5f
            );

            ImDrawList* draw = ImGui::GetWindowDrawList();
            
            auto node1 = zs::node::create(zs::eval::TRUE);
            auto node2 = zs::node::create(zs::eval::TRUE);
            auto node3 = zs::node::create(zs::eval::TRUE);
            uinode n(zs::node::create(zs::eval::TRUE, {node1, node2, node3}));
            n.draw(draw, center, shapewidth, ImColor(0.9f,0.9f,0.0f), shaperadius);

            draw->AddLine({100, 100}, {400, 400}, ImColor(0.0f,0.9f,0.9f), 20.0f);

        }ImGui::End();
        
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