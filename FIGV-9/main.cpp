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

#include "FigvWindowSystem.h"
#include "FigvAuxiliaryFunctions.h"
#include "FigvUserInterface.h"
#include "FigvRenderer.h"
#include "FigvEventManager.h"
#include "FigvScene.h"

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    FigvEventManager::processMouseScroll(yOffset);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    FigvEventManager::processMouseClics(window, button, action, mods);
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
    FigvEventManager::processCursorPosition(xPos, yPos);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    FigvScene::setFrameSize(width, height);
}

int main(int argc, const char * argv[]) {

    FigvLog("main", __LINE__, "Starting application");

    const unsigned int WINDOW_WIDTH = 1600;
    const unsigned int WINDOW_HEIGHT = 900;
    const char* windowName = "FIGV";

    FigvWindowSystem* windowSystem = new FigvWindowSystem(WINDOW_WIDTH, WINDOW_HEIGHT, windowName);
    auto* userInterface = new FigvUserInterface(windowSystem->getAppWindow());
    
    glfwSetScrollCallback(windowSystem->getAppWindow(), scrollCallback);
    glfwSetMouseButtonCallback(windowSystem->getAppWindow(), mouseButtonCallback);
    glfwSetCursorPosCallback(windowSystem->getAppWindow(), cursorPosCallback);
    glfwSetFramebufferSizeCallback(windowSystem->getAppWindow(), framebufferSizeCallback);
    
    while (!windowSystem->getWindowShouldClose()) {

        glfwPollEvents();

        userInterface->prepareInterfaceObjects();
        userInterface->preRenderActions();

        FigvRenderer::renderScene();

        userInterface->afterRenderActions();
        windowSystem->swapBuffers();
    }

    delete(FigvRenderer::getInstance());
    delete(userInterface);
    delete(windowSystem);

    FigvLog("main", __LINE__, "Ending application");

    return 0;
}

