
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>

const int NUM_SEGMENTS = 100;


struct Circle
{
    std::vector<float> vertices;
};

std::vector<Circle> circleVertices;

void generateCircle(float cx, float cy, float r) {
    Circle newCircleVertices;

    newCircleVertices.vertices.push_back(cx); // Center of circle
    newCircleVertices.vertices.push_back(cy);
    for (int i = 0; i <= NUM_SEGMENTS; i++) {
        float angle = (2.0f * M_PI * i) / NUM_SEGMENTS;
        newCircleVertices.vertices.push_back(cx + r * cos(angle));
        newCircleVertices.vertices.push_back(cy + r * sin(angle));
    }
    circleVertices.push_back(newCircleVertices);
}

GLuint VBO, VAO;
void setupCircle() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}

void drawCircle() {
    glColor3f(0.0f, 1.0f, 0.0f); // Set color to green

    for (const Circle& circle : circleVertices) {
        glBegin(GL_TRIANGLE_FAN);
        for (size_t i = 0; i < circle.vertices.size(); i += 2) {
            glVertex2f(circle.vertices[i], circle.vertices[i + 1]);
        }
        glEnd();
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_N && action == GLFW_PRESS) {
        float randX = (rand() % 200 - 100) / 100.0f; // Random position in normalized space
        float randY = (rand() % 200 - 100) / 100.0f;
        generateCircle(randX, randY, 0.1f); // Generate circle at random position
    } else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Green Circles", NULL, NULL);
    if (!window) return -1;

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glewInit();

    setupCircle();
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        if (!circleVertices.empty()) drawCircle(); // Draw circles

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

