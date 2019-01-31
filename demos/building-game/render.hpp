#pragma once

// ImGui - standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
// (GL3W is a helper library to access OpenGL functions since there is no standard header to access modern OpenGL functions easily. Alternatives are GLEW, Glad, etc.)

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "imgui/GL/gl3w.h"    // This example is using gl3w to access OpenGL functions. You may use another OpenGL loader/header such as: glew, glext, glad, glLoadGen, etc.
#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions

GLFWwindow* setupWindowSystem();