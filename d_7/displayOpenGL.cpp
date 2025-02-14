
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>


/*
THIS DOES WORK NOW AND I DONT KNOW WHY YET

I LIKED X11 BETTER
*/


#include <fstream>
#include <sstream>
#include <string>

std::string readShaderFile(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}



GLuint compileShader(const std::string& source, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    const char* shaderCode = source.c_str();
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader Compilation Error:\n" << infoLog << std::endl;
    }

    return shader;
}

GLuint createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = R"(
    #version 330 core 
    layout (location = 0) in vec2 aPos;
    void main() 
    {
    gl_Position = vec4(aPos, 0.0, 1.0);
    }
    )";
    std::string fragmentCode = R"(
                                #version 330 core 
    out vec4 FragColor; 
    void main() 
    {
    FragColor = vec4(0.0, 1.0, 0.0, 1.0); // Green
    }
    )";

    GLuint vertexShader = compileShader(vertexCode, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentCode, GL_FRAGMENT_SHADER);

    // Create program and link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader Linking Error:\n" << infoLog << std::endl;
    }

    // Clean up shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}




int NUM_SEGMENTS = 100;

struct Circle
{
    std::vector<float> vertices;
};

std::vector<Circle> circleVertices;

GLuint VBO, VAO;
void setupCircle() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

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

    std::vector<float> allVertices(circleVertices.size()*newCircleVertices.vertices.size());

    for (Circle& circle : circleVertices)
    {
        for (float vx : circle.vertices)
        {
            allVertices.push_back(vx);
        }
    }

    std::cout << allVertices.size() << std::endl;

    glBindVertexArray(VAO);
            
            
    glBufferData(GL_ARRAY_BUFFER,allVertices.size() * sizeof(float), allVertices.data(), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER,newCircleVertices.vertices.size() * sizeof(float), newCircleVertices.vertices.data(), GL_STATIC_DRAW);


    glBindVertexArray(0); // Unbind
}


void drawCircle() {
    
    glBindVertexArray(VAO);

    size_t offset = 0;

    for (Circle& circle : circleVertices) {

        glDrawArrays(GL_TRIANGLE_FAN, 0, circle.vertices.size() / 2);
        offset+=circle.vertices.size() / 2;
    }
    
    glBindVertexArray(0);

    glFlush();
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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        int width, height;

        glfwGetCursorPos(window, &xpos, &ypos);
        glfwGetWindowSize(window, &width, &height);

        // Convert to OpenGL NDC coordinates
        float ndcX = (xpos / width) * 2.0f - 1.0f;
        float ndcY = 1.0f - (ypos / height) * 2.0f;

        std::cout << "Mouse clicked at: (" << xpos << ", " << ypos << ") "
                  << "-> OpenGL coords: (" << ndcX << ", " << ndcY << ")" << std::endl;
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
    GLuint shaderProgram = createShaderProgram("vertexShader.glsl", "fragmentShader.glsl");
    glUseProgram(shaderProgram);

    setupCircle();
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background



    glfwSetMouseButtonCallback(window, mouse_button_callback);


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        if (!circleVertices.empty()) drawCircle(); // Draw circles


        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cout << "OpenGL Error: " << err << std::endl;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glDeleteBuffers(1, &VBO);  // Delete the vertex buffer
    glDeleteVertexArrays(1, &VAO);  // Delete the vertex array
    glDeleteProgram(shaderProgram);
    glfwTerminate();


    return 0;
}

