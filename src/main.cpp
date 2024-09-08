#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "camera.h"
#include "shader.h"
#include "mesh.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main()
{   
    // Initialise GLFW
    if (glfwInit() != GLFW_TRUE)
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    };
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // GLFW Create Window
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(window, mouseCallback);

    glfwSetScrollCallback(window, scrollCallback);

    // Load GLAD Function Pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Camera &camera = Camera::getInstance();
    camera.framebufferCallback(WIDTH, HEIGHT);
    Shader myShader("shaders/vertex.glsl", "shaders/fragment.glsl");
    
    // Mesh cubeMesh("models/cube.obj");
    float vertices[] = {
        // positions         // normals
        -0.5f,  0.5f, -0.5f,  0,  1,  0,
        -0.5f,  0.5f,  0.5f,  0,  1,  0,
         0.5f,  0.5f, -0.5f,  0,  1,  0,
        -0.5f,  0.5f,  0.5f,  0,  1,  0,
         0.5f,  0.5f,  0.5f,  0,  1,  0,
         0.5f,  0.5f, -0.5f,  0,  1,  0,
        -0.5f, -0.5f,  0.5f,  0, -1,  0,
        -0.5f, -0.5f, -0.5f,  0, -1,  0,
         0.5f, -0.5f,  0.5f,  0, -1,  0,
        -0.5f, -0.5f, -0.5f,  0, -1,  0,
         0.5f, -0.5f, -0.5f,  0, -1,  0,
         0.5f, -0.5f,  0.5f,  0, -1,  0,
        -0.5f,  0.5f,  0.5f,  0,  0,  1,
        -0.5f, -0.5f,  0.5f,  0,  0,  1,
         0.5f,  0.5f,  0.5f,  0,  0,  1,
        -0.5f, -0.5f,  0.5f,  0,  0,  1,
         0.5f, -0.5f,  0.5f,  0,  0,  1,
         0.5f,  0.5f,  0.5f,  0,  0,  1,
        -0.5f, -0.5f, -0.5f,  0,  0, -1,
        -0.5f,  0.5f, -0.5f,  0,  0, -1,
         0.5f, -0.5f, -0.5f,  0,  0, -1,
        -0.5f,  0.5f, -0.5f,  0,  0, -1,
         0.5f,  0.5f, -0.5f,  0,  0, -1,
         0.5f, -0.5f, -0.5f,  0,  0, -1,
        -0.5f, -0.5f, -0.5f, -1,  0,  0,
        -0.5f, -0.5f,  0.5f, -1,  0,  0,
        -0.5f,  0.5f, -0.5f, -1,  0,  0,
        -0.5f, -0.5f,  0.5f, -1,  0,  0,
        -0.5f,  0.5f,  0.5f, -1,  0,  0,
        -0.5f,  0.5f, -0.5f, -1,  0,  0,
         0.5f,  0.5f, -0.5f,  1,  0,  0,
         0.5f,  0.5f,  0.5f,  1,  0,  0,
         0.5f, -0.5f, -0.5f,  1,  0,  0,
         0.5f,  0.5f,  0.5f,  1,  0,  0,
         0.5f, -0.5f,  0.5f,  1,  0,  0,
         0.5f, -0.5f, -0.5f,  1,  0,  0
    };

    unsigned int indices[] = {
        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
        12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // Draw options
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // Render Loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.use();
        
        glm::vec3 cameraPos   = camera.getPosition();
        glm::mat4 model       = glm::mat4(1.0f);
        glm::mat3 modelNormal = glm::transpose(glm::inverse(glm::mat3(model)));
        glm::mat4 view        = camera.getViewTransform();
        glm::mat4 projection  = camera.getProjectionTransform();
        glm::mat4 mvp         = projection * view * model;
        myShader.setVector3("wc_camera_position", cameraPos);
        myShader.setMatrix4("m_transform", model);
        myShader.setMatrix3("m_normal_transform", modelNormal);
        myShader.setMatrix4("mvp_transform", mvp);

        // cubeMesh.draw();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    Camera::getInstance().framebufferCallback(width, height);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) 
    {
        Camera::getInstance().dragging = false;
        return;
    }
    Camera::getInstance().mouseDragCallback(xpos, ypos);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Camera::getInstance().scrollCallback(xoffset, yoffset);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}