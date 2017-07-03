/* Created by David Klostermann on 31.05.2017. */
#include "application.h"


Application::Application() {

}

void Application::draw() {
    world->update();
}

void Application::init() {
    AM::WindowHandler::init("Root", glm::vec2(1440, 900), glm::vec4(1/255.0f, 1/255.0f, 1/255.0f, 255), 1);
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
    AM::Logger::info("A single block size: " + std::to_string(int(sizeof(Block))) + "B", 2);

    world = new World();
    world->setViewDistance(16);
    world->generateChunk(glm::vec2(0, 0));
    debugCam = new AM::Debugcamera(&world->getPlayer().getCamera());
    debugCam->setSpeed(10);
}

void Application::load(){
    AM::WindowHandler::getWindow()->makeContextCurrent();

    ResourceManager::shaders.add("chunk", new AM::Shader("./shaders/chunk.vert", "./shaders/chunk.frag"));
    ResourceManager::shaders.add("billboard texture", new AM::Shader("./shaders/bill_texture.vert", "./shaders/bill_texture.frag"));
    ResourceManager::shaders.add("sky", new AM::Shader("./shaders/sky.vert", "./shaders/sky.frag"));

    ResourceManager::textures.add("sky", new AM::Texture("sky.png"));

    AM::WavefrontData wavefrontData;
    AM::WavefrontParser::readObj("./sphere.obj", wavefrontData);
    AM::VBO<glm::vec3, 3>* sphere_vertices = new AM::VBO<glm::vec3, 3>();
    sphere_vertices->upload(wavefrontData.vertexData.get());
    //sphere_vertices->upload(standardmesh::model_cube);
    ResourceManager::vbo3D.add("sphere_vertices", sphere_vertices);

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

