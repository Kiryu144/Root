/* Created by David Klostermann on 31.05.2017. */
#include "application.h"


Application::Application() {

}

void Application::draw() {
    world->update();
}

void Application::init() {
    AM::WindowHandler::init("Root", glm::vec2(1440, 900), glm::vec4(0, 50/255.0f, 0, 255), 1);
    glfwSetWindowPos(AM::WindowHandler::getGlfwWindow(), 50, 50);
    AM::InputController::lockMousePosition(glm::vec2(1440/2.0f, 900/2.0f));

    m_loadingFinished = false;
    AM::WindowHandler::getWindow()->makeContextNull();
    std::thread loadingThread(&Application::load, std::ref(*this));
    while(!m_loadingFinished){
        AM::WindowHandler::update(false);
    }
    loadingThread.join();
    AM::WindowHandler::getWindow()->makeContextCurrent();

    world = new World();
    world->setViewDistance(16);
    world->generateChunk(glm::vec2(0, 0));
    debugCam = new AM::Debugcamera(&world->getPlayer().getCamera());
    debugCam->setSpeed(10);
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
        debugCam->updateMovement();
        AM::Time::update();

        this->draw();

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

