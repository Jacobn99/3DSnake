#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Shader.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\stb_image.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Object.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\ObjectManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\PrismObject.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\TextureManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Texture.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\GameManager.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\AppContext.h"
#include "C:\Users\jacob\source\repos\3DSnake\3DSnake\Player.h"
#include <unordered_map>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera settings
glm::vec3 cameraPos;
glm::vec3 cameraFront;
glm::vec3 cameraUp;

glm::vec3 cameraTarget;
glm::vec3 cameraDirection;
glm::vec3 up;
glm::vec3 cameraRight;

// global variables
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float lastX = 400, lastY = 300;
float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;
double minButtonDelay = 0.5;
Player player;
AppContext appContext;
//Make a hashtable containing the time last pressed
std::unordered_map<GLenum, double> buttonsPressed = std::unordered_map<GLenum, double>();

bool keyIsHeld(GLenum key) {
    if (buttonsPressed.find(key) == buttonsPressed.end()) return false;
    else {
        assert(glfwGetTime() > buttonsPressed.at(key));
        double timeDifference = glfwGetTime() - buttonsPressed.at(key);
        //printf("currentTime: %f, buttonTime: %f, timeDifference: %f\n", glfwGetTime(), buttonsPressed.at(key), timeDifference);
        return timeDifference < minButtonDelay;
    }
}

// A callback function to resize viewport with window upon resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
// Codes for processing what each input does
void processInput(GLFWwindow* window)
{
    float cameraSpeed = 2.5f * deltaTime;
    float snakeSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && player.get_head_direction() != FORWARD) {
        if (!keyIsHeld(GLFW_KEY_UP)) player.queue_turn(FORWARD, appContext);
        buttonsPressed.insert_or_assign(GLFW_KEY_E, glfwGetTime());
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && player.get_head_direction() != BACKWARD) {
        if (!keyIsHeld(GLFW_KEY_DOWN)) player.queue_turn(BACKWARD, appContext);
        buttonsPressed.insert_or_assign(GLFW_KEY_E, glfwGetTime());
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && player.get_head_direction() != LEFT) {
        if (!keyIsHeld(GLFW_KEY_LEFT)) player.queue_turn(LEFT, appContext);
        buttonsPressed.insert_or_assign(GLFW_KEY_E, glfwGetTime());
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && player.get_head_direction() != RIGHT) {
        if (!keyIsHeld(GLFW_KEY_RIGHT)) player.queue_turn(RIGHT, appContext);
        buttonsPressed.insert_or_assign(GLFW_KEY_E, glfwGetTime());
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        if (!keyIsHeld(GLFW_KEY_E)) player.queue_grow(); 
        buttonsPressed.insert_or_assign(GLFW_KEY_E, glfwGetTime());
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    //Checks to see if just now clicking onto window
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    //Constraints
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

int main()
{
    //unsigned int texture1, texture2;    
    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    3, 2, 1    // second triangle
    };
    float texCoords[] = {
    0.0f, 0.0f,  // lower-left corner  
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
    };

    int width, height, nrChannels;
    unsigned char* data;
    int sizeInTiles = 7;
    int sizeInUnits = 8;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Among Us", NULL, NULL);

    //Termiantes if can't create window
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    //Settings
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    //Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    
    TextureManager textureManager = TextureManager();
    Texture texture = textureManager.generate_texture_2D("C:\\Users\\jacob\\source\\repos\\3DSnake\\3DSnake\\Textures\\snake_tile.png", 
        GL_RGBA, GL_REPEAT, GL_LINEAR);

    //Shaders
    Shader ourShader("shader.vert", "shader.frag");
    ourShader.use();

    ObjectManager objectManager = ObjectManager();

    GameManager gameManager = GameManager(sizeInUnits, sizeInTiles);
    Texture snakeTexture = textureManager.generate_texture_2D(
        "C:\\Users\\jacob\\source\\repos\\3DSnake\\3DSnake\\Textures\\snake_scale.png",
        GL_RGBA, GL_REPEAT, GL_LINEAR);

    gameManager.set_snake_texture(snakeTexture);
	appContext = AppContext(&gameManager, &textureManager, &ourShader, &objectManager);
    objectManager.generate_default_vertices(appContext);

    //Object creation
	PrismObject prism = PrismObject(36, ourShader, appContext);
	generate_prism(prism, appContext, -(sizeInUnits/2), (sizeInUnits / 2), 
        -0.5f, 0.5f, -(sizeInUnits / 2), (sizeInUnits / 2), gameManager.sizeInTiles);
    prism.set_position(gameManager.boardCenter - glm::vec3(0.0f, 1.01f, 0.0f));
    prism.set_texture(snakeTexture);
    //Don't have to change initial offset if changing to opposite direction

    Direction oldDirection = LEFT;
    Direction newDirection = RIGHT;
    
    PrismObject prism2 = PrismObject(36, ourShader, appContext);
    generate_prism(prism2, appContext, -0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 1.0f);
    prism2.set_position(gameManager.board_to_vec3(glm::vec2(4.0f, 4.0f)));
    prism2.set_texture(texture);
    prism2.set_scale(prism2.get_scale() + glm::vec3(0.0f, 0.0f, 1.0f));

    //Player creation
    player = Player(appContext);

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);

    //Camera fields
    glm::vec3 startLoc = glm::vec3(0.0f, 10.0f, 0.0f);
    //MUST INITIALIZE CAMERA FIELDS RELATIVE TO cameraStart BECAUSE THE VALUES SHOULD CHANGE WITH CHANGES IN CAMERA POSITION
    //This calibrates them to relative to where the camera is currently located at
	cameraPos = glm::vec3(startLoc.x, startLoc.y, startLoc.z + 3.0f);
    cameraFront = glm::vec3(0, 0, -1.0f);
    cameraUp = glm::vec3(0, 1.0f, 0);

    cameraTarget = startLoc;
    cameraDirection = glm::normalize(cameraPos - cameraTarget);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
	pitch = -60.0f; // Set pitch to look down
    
    //Ensures viewport resizes with window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    while (!glfwWindowShouldClose(window))
    {
        // Pregame logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);

        //Input
        processInput(window);
        player.move_body(deltaTime, appContext);

        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;

        // create transformations
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes 
        // it's often best practice to set it outside the main loop only once.
        ourShader.setMat4("projection", projection);

        //Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        objectManager.draw_prism(prism);
        objectManager.draw_prism(prism2);
        player.draw_body(appContext);

        glBindVertexArray(0);

        // Check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	prism.delete_object(false);
    glfwTerminate();
    return 0;
}

/* What I need to accomplish for textures:
    - Toggle texture mode easily
    - Apply textures (ideally with one function)
    - Toggle texture mode easily*/