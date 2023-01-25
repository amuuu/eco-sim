#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include <stdio.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


#include <string> 
#include "../GameSystems/EntityManagement/EntityManager.h"
using namespace EntityManagement;


class SimpleDumbEntity : public Entity
{
    virtual void Init() override
    {
        SetFixedUpdateActiveState(false);
    }

    virtual void Update(Tick tick) override
    {
    }

    virtual void FixedUpdate(EntityManagement::Tick fixedTick) override
    {
    }

    virtual void OnDestroy() override
    {
    }
};
















static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL2 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    // Our state
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    EntityManager entityManager{ true };

    bool showEntity = false;
    std::map<EntityId, bool> entityDisplayState{};


    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Ecosystem");

            ImGui::Checkbox("Demo Window", &show_demo_window);


            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            
            ImGui::Text("Tick: %d\nFixed Tick: %d", entityManager.GetCurrentTick(), entityManager.GetCurrentFixedTick());

            ImGui::NewLine();
            const ImVec2 buttSize = ImVec2(250, 20);
            if (ImGui::Button("Instantiate Entity", buttSize))
            {
                entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
            }

            if (ImGui::TreeNode("Entity List"))
            {
                for (const auto& entityData : *(entityManager.GetAllEntities()))
                {
                    if (ImGui::Button(std::string{ "ID: " + std::to_string(entityData.first) }.c_str()))
                    {
                        entityDisplayState[entityData.first] = !entityDisplayState[entityData.first];
                    }
                }
                
                ImGui::TreePop();
            }
            
            ImGui::End();
        }

        for (auto& entityDisplayData : entityDisplayState)
        {
            if (entityDisplayData.second == true)
            {
                const auto* entityContent = entityManager.GetEntityBasedOnID(entityDisplayData.first);
                auto name = std::string{ "Entity " + std::to_string(entityContent->Id) };
                
                ImGuiWindowFlags flags = ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoCollapse;
                ImGui::SetNextWindowSize(ImVec2(150, 60));
                ImGui::Begin(name.c_str(), &entityDisplayData.second, flags);
                
                //ImGui::Text(name.c_str());

                if (ImGui::Button("Kill"))
                {
                    entityManager.DestroyEntity(entityContent->Id);
                    entityDisplayData.second = false;
                }

                ImGui::End();
            }
        }


        
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
