/* Created by David Klostermann on 31.05.2017. */
#include "application.h"


Application::Application() : cam(AM::Transformation(AM::Position(), AM::Quaternion(), AM::Scale(1440, 900, 900))), debugCam(&cam) {

}

void Application::draw() {
    blockWorld->draw(cam);
}

void Application::init() {
    AM::WindowHandler::init();
    AM::WindowHandler::createWindow("Root", glm::vec2(1440, 900), glm::vec4(0, 50, 0, 255));
    AM::InputController::lockMousePosition(glm::vec2(1440/2.0f, 900/2.0f));

    m_loadingFinished = false;
    glfwMakeContextCurrent(nullptr);
    std::thread loadingThread(&Application::load, std::ref(*this));
    while(!m_loadingFinished){
        AM::WindowHandler::poll(false);
    }
    loadingThread.join();
    glfwMakeContextCurrent(AM::WindowHandler::getGlfwWindow());

    blockWorld = new BlockWorld();
}

void Application::load(){
    glfwMakeContextCurrent(AM::WindowHandler::getGlfwWindow());
    ResourceManager::shaders.add("chunk", new AM::Shader("./shaders/color_shader.vert", "./shaders/color_shader.frag"));
    glfwMakeContextCurrent(nullptr);
    m_loadingFinished = true;
}

void Application::loop() {
    for(int x = -5; x <= 5; x++){
        for(int y = -5; y <= 5; y++){
            blockWorld->generateChunk(glm::vec2(x, y));
        }
    }

    while(m_keepRunning){
        m_keepRunning = AM::WindowHandler::poll();
        debugCam.updateMovement();
        cam.update();
        AM::Time::update();
        draw();
        AM::InputController::process();
    }
}
