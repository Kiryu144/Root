/* Created by David Klostermann on 31.05.2017. */
#include "application.h"


Application::Application() : cam(AM::Transformation(AM::Position(), AM::Quaternion(), AM::Scale(1440, 900, 900))), debugCam(&cam) {

}

void Application::draw() {
    blockWorld->draw(cam);
}

void Application::init() {
    AM::WindowHandler::init("Root", glm::vec2(1440, 900), glm::vec4(0, 50/255.0f, 0, 255), 4);
    AM::InputController::lockMousePosition(glm::vec2(1440/2.0f, 900/2.0f));

    m_loadingFinished = false;
    AM::WindowHandler::getWindow()->makeContextNull();
    std::thread loadingThread(&Application::load, std::ref(*this));
    while(!m_loadingFinished){
        AM::WindowHandler::update(false);
    }
    loadingThread.join();
    AM::WindowHandler::getWindow()->makeContextCurrent();

    blockWorld = new BlockWorld();
}

void Application::load(){
    AM::WindowHandler::getWindow()->makeContextCurrent();
    ResourceManager::shaders.add("chunk", new AM::Shader("./shaders/color_shader.vert", "./shaders/color_shader.frag"));
    AM::WindowHandler::getWindow()->makeContextNull();
    m_loadingFinished = true;
}

void Application::loop() {
    while(m_keepRunning){
        m_keepRunning = AM::WindowHandler::update(true);
        debugCam.updateMovement();
        cam.update();
        AM::Time::update();

        if(AM::InputController::isClicked(GLFW_KEY_R)){
            for(int x = -20; x <= 20; x++){
                for(int y = -20; y <= 20; y++){
                    blockWorld->deleteChunk(glm::vec2(x, y));
                    blockWorld->generateChunk(glm::vec2(x, y));
                }
            }
        }

        draw();

        if(glfwGetTime() - lastTime >= 1){
            lastTime = glfwGetTime();
            this->oncePerSecond();
        }

        AM::InputController::process();
    }
}

void Application::oncePerSecond() {
    AM::WindowHandler::getWindow()->setTitle("Root [FPS: " + std::to_string(std::round(AM::FPS::getFPS()))+ "]");
}

