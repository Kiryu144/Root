#include <amethyst>
#include <GLM/common.hpp>

int main() {
    /* Initiates GLFW */
    AM::WindowHandler::init();

    /* Creates window and openGL context. Without it, the application will crash! */
    AM::WindowHandler::createWindow("Amethyst rocks!", glm::vec2(1440, 900), glm::vec4(0.5f, 0.25f, 0.25f, 1));


    do {


    } while(AM::WindowHandler::poll()); /* Handles OS events. Returns false if closing is requested */


    return 0;
}