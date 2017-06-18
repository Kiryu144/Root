#include "application.h"

int main() {
    try {
        Application application;

        double start = glfwGetTime();
        application.init();
        AM::Logger::info("Initialized after " + std::to_string(glfwGetTime() - start) + "ms", 2);

        application.loop();
    }catch(__AmethystException exception){
        AM::Logger::error(exception.getExceptionError(), 2);
    }

    return 0;
}




