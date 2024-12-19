//
// FIGV (Fundamentos de Informática Gráfica y Visualización)
// Master en Desarrollo de Software, Universidad de Granada.
//
// Juan Carlos Torres Cantero
// ETSIIT, Depto. Lenguajes y Sistemas Informáticos, Universidad de Granada, jctorres@ugr.es
//
// Francisco de Asís Conde Rodríguez
// EPS, Depto. Informática, Universidad de Jaén, fconde@ujaen.es
//

#define GL_SILENCE_DEPRECATION

#include "FigvUserInterface.h"
#include "FigvAuxiliaryFunctions.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "FigvRenderer.h"
#include "FigvScene.h"
#include "FigvCamera.h"
#include "FigvEventManager.h"

FigvUserInterface::FigvUserInterface(GLFWwindow* associatedWindow) {
    
    FigvLog("FigvUserInterface", __LINE__, "Initializing the user interface");
    
    this->associatedWindow = associatedWindow;
    this->glsl_version = "#version 400";
    this->darkMode = false;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO&ioo = ImGui::GetIO();
    ioo.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ioo.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ioo.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ioo.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ioo.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    ImGui_ImplGlfw_InitForOpenGL(associatedWindow, false);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

FigvUserInterface::~FigvUserInterface() {

    FigvLog("FigvUserInterface", __LINE__, "Destroying the user interface");

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void FigvUserInterface::preRenderActions() {

    if (darkMode) { ImGui::StyleColorsDark(); }
    else { ImGui::StyleColorsLight(); }

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(associatedWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
}

void FigvUserInterface::afterRenderActions() {

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = associatedWindow; // glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void FigvUserInterface::prepareInterfaceObjects() {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    preparePalettes();
}

void FigvUserInterface::preparePalettes() {
    
    const char* shaderList[] = { "Normals", "Cartoon" };
    const char* modelList[] = { "Spot", "Bob", "Blub", "Spot HD", "Blub HD" };
    CameraMode* cameraMovement = FigvEventManager::getInstance()->getCameraMovementip();

    ImGui::Begin("FIGV properties");
    
    ImGui::SeparatorText("Interface properties");
    ImGui::Checkbox("Dark mode", &this->darkMode);
    
    ImGui::SeparatorText("Rendering properties");
    ImGui::ColorEdit3("Background", FigvRenderer::getInstance()->getBackgroundColor3fp());
    // FIGV 21
    ImGui::Checkbox("Use texture", FigvRenderer::getInstance()->getUseTexturebp());
    ImGui::RadioButton("Fill", FigvRenderer::getInstance()->getRenderingModeip(), GL_FILL); ImGui::SameLine();
    ImGui::RadioButton("Line", FigvRenderer::getInstance()->getRenderingModeip(), GL_LINE); ImGui::SameLine();
    ImGui::RadioButton("Point", FigvRenderer::getInstance()->getRenderingModeip(), GL_POINT); ImGui::SameLine();
    ImGui::LabelText("", "Mode");
    if (ImGui::TreeNode("Point mode properties"))
    {
        ImGui::SliderFloat("Point size", FigvRenderer::getInstance()->getPointSizefp(), 1.0f, 20.0f);
        ImGui::TreePop();
        ImGui::Spacing();
    }
    
    ImGui::SeparatorText("Camera propierties");

    // Checkbox para "Orbit"
    bool orbitSelected = (*cameraMovement == ORBIT);
    if (ImGui::Checkbox("Orbit", &orbitSelected)) {
        if (orbitSelected) *cameraMovement = ORBIT;
    }ImGui::SameLine();

    // Checkbox para "Pan"
    bool panSelected = (*cameraMovement == PAN);
    if (ImGui::Checkbox("Pan", &panSelected)) {
        if (panSelected) *cameraMovement = PAN;
    }ImGui::SameLine();

    // Checkbox para "Dolly"
    bool dollySelected = (*cameraMovement == DOLLY);
    if (ImGui::Checkbox("Dolly", &dollySelected)) {
        if (dollySelected) *cameraMovement = DOLLY;
    }ImGui::SameLine();

    // Checkbox para "Track"
    bool trackSelected = (*cameraMovement == TRACK);
    if (ImGui::Checkbox("Track", &trackSelected)) {
        if (trackSelected) *cameraMovement = TRACK;
    }ImGui::SameLine();

     // Checkbox para "Zoom"
    bool zoomSelected = (*cameraMovement == ZOOM);
    if (ImGui::Checkbox("Zoom", &zoomSelected)) {
        if (zoomSelected) *cameraMovement = ZOOM;
    }ImGui::SameLine();
    

    
    ImGui::Separator();
    
    ImGui::Combo("Use shader", FigvRenderer::getInstance()->getShaderActiveip(), shaderList, IM_ARRAYSIZE(shaderList));

    if (ImGui::TreeNode("Normal shader properties"))
    {
        ImGui::Checkbox("Scaled normal", FigvRenderer::getInstance()->getScaledNormalbp());
        ImGui::TreePop();
        ImGui::Spacing();
    }

    if (ImGui::TreeNode("Cartoon shader properties"))
    {
        ImGui::Checkbox("Solid color", FigvRenderer::getInstance()->getCartoonSolidColorbp());
        ImGui::InputInt("Levels", FigvRenderer::getInstance()->getCartoonLevelsip(), 1, 1);
        ImGui::InputFloat("Multiplier", FigvRenderer::getInstance()->getCartoonMultiplierfp(), 0.1f, 1.0f, "%.1f");
        ImGui::InputFloat("Threshold", FigvRenderer::getInstance()->getCartoonThresholdfp(), 0.1f, 1.0f, "%.1f");
        ImGui::TreePop();
        ImGui::Spacing();
    }

    ImGui::SeparatorText("Models properties");
    // ImGui::Combo("Model", FigvScene::getInstance()->getModelSelectedip(), modelList, IM_ARRAYSIZE(modelList));
    
    ImGui::SeparatorText("Light source properties");
    ImGui::RadioButton("Scene lights", FigvScene::getInstance()->getUseModelingLightip(), 0); ImGui::SameLine();
    ImGui::RadioButton("Modeling light", FigvScene::getInstance()->getUseModelingLightip(), 1);
    ImGui::ColorEdit3("Ia", FigvScene::getInstance()->getIa3fp());
    ImGui::DragFloat3("Light position",
                      FigvScene::getInstance()->getLightSource()->getPosition3fp(),
                      0.1f, -100.0f, 100.0f);
    ImGui::ColorEdit3("Id", FigvScene::getInstance()->getLightSource()->getId3fp());
    ImGui::ColorEdit3("Is", FigvScene::getInstance()->getLightSource()->getIs3fp());

    ImGui::End();

// Si se descomenta la siguiente línea, se construye una segunda paleta en la
// que se muestran todos los widgets que se pueden usar con ImGui. El código
// que construye esos widgets se encuentra en el archivo: imgui_demo.cpp
    
// ImGui::ShowDemoWindow();
}
