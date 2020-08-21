#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Shader.h"
#include "src/3rdparty/imgui/imgui.h";
#include "src/3rdparty/imgui/imgui_impl_glfw.h"
#include "src/3rdparty/imgui/imgui_impl_opengl3.h"

static void MenuList(GLuint VAO, GLuint VBO, GLFWwindow* window, float *editor_space_color);
static void showEditorPreferencesMenu(bool* p_open);
static void showAboutMenu(bool* p_open);

