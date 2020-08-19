#define GLFW_INCLUDE_GLU
#include "../headers/glfw3.h"
#include <vector>
#include <algorithm>
#include "UserInterface.h"

void initLights();

void updateUserInterface();

void display(deploymentModes typeDeployment);

void reshape(GLFWwindow *window, int width, int height);

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods);

void mouseButton(GLFWwindow* window, int button, int action, int mods);

void cursorPos(GLFWwindow* window, double x, double y);

void charInput(GLFWwindow* window, unsigned int scanChar);

void destroy();

bool initGlfw();

bool initUserInterface();

int main(void);