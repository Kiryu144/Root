#include <amethyst>
#include <GLM/common.hpp>
#include <GLM/GTX/string_cast.hpp>

int main() {
    /* Initiates GLFW */
    AM::WindowHandler::init();

    /* Creates window and openGL context. Without it, the application will crash! */
    AM::WindowHandler::createWindow("Amethyst rocks!", glm::vec2(1440, 900), glm::vec4(0.5f, 0.25f, 0.25f, 1));

    AM::Camera camera(AM::Transformation(AM::Position(-2, 0, 0), AM::Quaternion(), AM::Scale(1440, 900, 900)));

    AM::Shader barrelShader("./texture_diffuse.vert", "./texture_diffuse.frag");

    AM::Transformation barrelTransformation;

    AM::WavefrontData barrelMesh;
    AM::WavefrontParser::readObj("./Barrel.obj", barrelMesh);

    AM::VBO<glm::vec3, 3> barrelVertices;
    AM::VBO<glm::vec2, 3> barrelUVs;
    AM::VBO<glm::vec3, 3> barrelNormals;

    barrelVertices.upload(barrelMesh.vertexData.get());
    barrelUVs.upload(barrelMesh.uvData.get());
    barrelNormals.upload(barrelMesh.normalData.get());

    do {
        camera.update();

        barrelShader.bind();
        barrelShader.setUniform("projection", camera.getProjection());
        barrelShader.setUniform("view", camera.getView());
        barrelShader.setUniform("transformation", barrelTransformation.getMatrix());
        barrelShader.setUniform("lightPos", glm::vec3(sin(glfwGetTime()), 0, cos(glfwGetTime())));
        barrelShader.setUniform("lightColor", glm::vec3(1, 1, 1));

        barrelVertices.bind(0);
        barrelUVs.bind(1);
        barrelNormals.bind(2);

        glDrawArrays(GL_TRIANGLES, 0, barrelMesh.vertexData.size());

    } while(AM::WindowHandler::poll()); /* Handles OS events. Returns false if closing is requested */


    return 0;
}