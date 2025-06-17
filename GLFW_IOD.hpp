#pragma once

#include "IOD.hpp"
#include <GLFW/glfw3.h>

void IOD_GLFW_SETUP(GLFWwindow* window);
void IOD_GLFW_BIND_KEY_CALLBACK(GLFWkeyfun cb);
void IOD_GLFW_BIND_MOUSE_BUTTON_CALLBACK(GLFWmousebuttonfun cb);
void IOD_GLFW_BIND_MOUSE_MOVE_CALLBACK(GLFWcursorposfun cb);