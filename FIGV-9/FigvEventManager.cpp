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

#include "FigvEventManager.h"
#include "imgui.h"
#include "FigvScene.h"

FigvEventManager* FigvEventManager::instance = NULL;

FigvEventManager::FigvEventManager() = default;

FigvEventManager* FigvEventManager::getInstance() {

    if (!instance) { instance = new FigvEventManager(); }
    return instance;
}

CameraMode* FigvEventManager::getCameraMovementip() {
    return &cameraMovement;
}

void FigvEventManager::processMouseClics(GLFWwindow* window, int button, int action, int mods) {
    getInstance()->mouseClics(window, button, action, mods);
}

void FigvEventManager::mouseClics(GLFWwindow* window, int button, int action, int mods) {

    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(button, action);

    if (!io.WantCaptureMouse) {
        if ((button == GLFW_MOUSE_BUTTON_1) && (action == GLFW_PRESS)) {
            glfwGetCursorPos(window, &lastX, &lastY);
            dragging = true;
        } else if ((button == GLFW_MOUSE_BUTTON_1) && (action == GLFW_RELEASE)) {
            dragging = false;
        }
    }
}

void FigvEventManager::processMouseScroll(double yDisplacement) {
    getInstance()->mouseScroll(yDisplacement);
}

void FigvEventManager::mouseScroll(double yDisplacement) {
    switch (cameraMovement) {
        case DOLLY:
            FigvScene::dollyCamera(float(yDisplacement));
            break;

        case ZOOM:
            FigvScene::zoomCamera(float(yDisplacement)); 
            break;

        default:
            break;
    }
}

void FigvEventManager::processCursorPosition(double xPos, double yPos) {
    getInstance()->cursorPosition(xPos, yPos);
}

void FigvEventManager::cursorPosition(double xPos, double yPos) {
    if (dragging) {
        double xOffset = lastX - xPos;
        double yOffset = lastY - yPos;

        lastX = xPos;
        lastY = yPos;

        switch (cameraMovement) {
            case ORBIT:
                FigvScene::orbitCamera(float(-xOffset), float(-yOffset));
                break;

            case PAN:
                FigvScene::panCamera(float(xOffset), float(yOffset));
                break;

            case TRACK:
                FigvScene::trackCamera(float(xOffset), float(yOffset)); 
                break;

            default:
                break;
        }
    }
}

#include <stdio.h>
