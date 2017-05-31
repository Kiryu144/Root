#include <amethyst>
#include <GLM/common.hpp>
#include <GLM/GTX/string_cast.hpp>

int main() {
    try {
        /* Initiates GLFW */
        AM::WindowHandler::init();

        /* Creates window and openGL context. Without it, the application will crash! */
        AM::WindowHandler::createWindow("Amethyst rocks!", glm::vec2(1440, 900), glm::vec4(0, 0, 0, 255));
        AM::InputController::lockMousePosition(glm::vec2(1440/2.0f, 900/2.0f));

        AM::Camera camera(AM::Transformation(AM::Position(-2, 0, 0), AM::Quaternion(0, 20, 0), AM::Scale(1440, 900, 900)));
        AM::Debugcamera debugcamera(&camera);

        AM::Shader barrelShader("./texture_diffuse.vert", "./texture_diffuse.frag");
        AM::Texture barrelTexture("./Texture.png");

        AM::Transformation barrelTransformation(AM::Position(glm::vec3(0, 0, 0)), AM::Quaternion(), AM::Scale(glm::vec3(20, 20, 20)));

        AM::WavefrontData barrelMesh;
        AM::WavefrontParser::readObj("./nudemuch.obj", barrelMesh);

        AM::VBO<glm::vec3, 3> barrelVertices;
        AM::VBO<glm::vec2, 3> barrelUVs;
        AM::VBO<glm::vec3, 3> barrelNormals;

        barrelVertices.upload(barrelMesh.vertexData.get());
        barrelUVs.upload(barrelMesh.uvData.get());
        barrelNormals.upload(barrelMesh.normalData.get());

        do {
            AM::DeltaTime::update();
            camera.update();
            debugcamera.updateMovement();

            barrelShader.bind();
            barrelShader.setUniform("projection", camera.getProjection());
            barrelShader.setUniform("view", camera.getView());
            barrelShader.setUniform("transformation", barrelTransformation.getMatrix());
            barrelShader.setUniform("pointLight", camera.getTransformation().getPosition().get());

            barrelVertices.bind(0);
            barrelUVs.bind(1);
            barrelNormals.bind(2);

            glDrawArrays(GL_TRIANGLES, 0, barrelMesh.vertexData.size());

            AM::InputController::process();
        } while (AM::WindowHandler::poll()); /* Handles OS events. Returns false if closing is requested */

    }catch(__AmethystException exception){
        AM::Logger::error(exception.getExceptionError(), 2);
    }

    return 0;
}



















