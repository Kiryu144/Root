#include "application.h"

int main() {
    try {
        Application application;

        double start = glfwGetTime();
        application.init();
        AM::Logger::info("Initialized after " + std::to_string(glfwGetTime() - start) + "ms");

        application.loop();
    }catch(__AmethystException exception){
        AM::Logger::error(exception.getExceptionString());
    }

    return 0;
}




