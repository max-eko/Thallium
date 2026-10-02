#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <iterator>
#include <vector>
#include <filesystem>

#include "src/util/shader.h"
#include "src/util/texture.h"
#include "src/util/camera.h"
#include "src/model/mesh.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void updateDelta();

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Delta
float deltaTime;
float currentFrame, lastFrame;
// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


int main() 
{
    std::cout << "Project Started" << std::endl;

    // GLFW setup
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__ // This line of code is only needed for MacOS
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Creates window w/ GLFW
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Thallium Engine", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader standardShader("../src/shaders/generic.vert", "../src/shaders/generic.frag");
    Texture container("container", "../assets/container.jpg");
    Texture awesomeFace("awesomeFace", "../assets/awesomeface.png");

    float cubeVertices[] = {
        // Front face
        -0.5f, -0.5f,  0.5f,  0, 0, 1,  0.0f, 0.0f, // 0
        0.5f, -0.5f,  0.5f,  0, 0, 1,  1.0f, 0.0f, // 1
        0.5f,  0.5f,  0.5f,  0, 0, 1,  1.0f, 1.0f, // 2
        -0.5f,  0.5f,  0.5f,  0, 0, 1,  0.0f, 1.0f, // 3
        // Back face
        0.5f, -0.5f, -0.5f,  0, 0, -1,  0.0f, 0.0f, // 4
        -0.5f, -0.5f, -0.5f,  0, 0, -1,  1.0f, 0.0f, // 5
        -0.5f,  0.5f, -0.5f,  0, 0, -1,  1.0f, 1.0f, // 6
        0.5f,  0.5f, -0.5f,  0, 0, -1,  0.0f, 1.0f, // 7
        // Left face
        -0.5f, -0.5f, -0.5f,  -1, 0, 0,  0.0f, 0.0f, // 8
        -0.5f, -0.5f,  0.5f,  -1, 0, 0,  1.0f, 0.0f, // 9
        -0.5f,  0.5f,  0.5f,  -1, 0, 0,  1.0f, 1.0f, // 10
        -0.5f,  0.5f, -0.5f,  -1, 0, 0,  0.0f, 1.0f, // 11
        // Right face
        0.5f, -0.5f,  0.5f,  1, 0, 0,  0.0f, 0.0f, // 12
        0.5f, -0.5f, -0.5f,  1, 0, 0,  1.0f, 0.0f, // 13
        0.5f,  0.5f, -0.5f,  1, 0, 0,  1.0f, 1.0f, // 14
        0.5f,  0.5f,  0.5f,  1, 0, 0,  0.0f, 1.0f, // 15
        // Top face
        -0.5f,  0.5f,  0.5f,  0, 1, 0,  0.0f, 0.0f, // 16
        0.5f,  0.5f,  0.5f,  0, 1, 0,  1.0f, 0.0f, // 17
        0.5f,  0.5f, -0.5f,  0, 1, 0,  1.0f, 1.0f, // 18
        -0.5f,  0.5f, -0.5f,  0, 1, 0,  0.0f, 1.0f, // 19
        // Bottom face
        -0.5f, -0.5f, -0.5f,  0, -1, 0,  0.0f, 0.0f, // 20
        0.5f, -0.5f, -0.5f,  0, -1, 0,  1.0f, 0.0f, // 21
        0.5f, -0.5f,  0.5f,  0, -1, 0,  1.0f, 1.0f, // 22
        -0.5f, -0.5f,  0.5f,  0, -1, 0,  0.0f, 1.0f  // 23
   };
    unsigned int cubeIndices[] = {
        // Front
        0,  1,  2,
        2,  3,  0,
       // Back
        4,  5,  6,
        6,  7,  4,
       // Left
        8,  9, 10,
       10, 11,  8,
       // Right
       12, 13, 14,
       14, 15, 12,
       // Top
       16, 17, 18,
       18, 19, 16,
       // Bottom
       20, 21, 22,
       22, 23, 20
    };

    Mesh cube(std::vector<float>(std::begin(cubeVertices), std::end(cubeVertices)),
        std::vector<unsigned int>(std::begin(cubeIndices), std::end(cubeIndices)) );

    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    standardShader.use();

    standardShader.setTexture(container);
    //standardShader.setTexture(awesomeFace);

    glm::mat4 model = glm::mat4(1.0f);

    lastFrame = static_cast<float>(glfwGetTime());

    standardShader.setVec3("lightPos", glm::vec3(1.0f, 0.0f, 1.0f));
    standardShader.setVec3("lightColor", glm::vec3(1.0f));

    standardShader.setFloat("ambientStrength", 0.1f);
    standardShader.setFloat("roughness", 0.5f);
    standardShader.setInt("specularExponent", 32);

    // Render Loop
    while(!glfwWindowShouldClose(window))
    {
        updateDelta();
        // Update matrices and pass to shader
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = camera.GetProjectionMatrix(SCR_WIDTH, SCR_HEIGHT);
        standardShader.setMat4("view", view);
        standardShader.setMat4("projection", projection);
        standardShader.setMat4("model", model);
        // Pass camera position to shader
        standardShader.setVec3("viewPos", camera.Position);
        // Process input
        processInput(window);
        // Sets window color and updates depth buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Activates standard shader + textures
        standardShader.use();
        container.use();
        awesomeFace.use();
        // Draws cube
        cube.draw();
        // Updates window
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

}
void updateDelta()
{
    // Update delta time
    currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}