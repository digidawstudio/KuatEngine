#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Shader.h"
#include "src/3rdparty/imgui/imgui.h";
#include "src/3rdparty/imgui/imgui_impl_glfw.h"
#include "src/3rdparty/imgui/imgui_impl_opengl3.h"


const GLint WIDTH = 1280, HEIGHT = 720;
static ImVec4 editor_space_color = ImVec4(0.314f, 0.314f, 0.314f, 1.00f);
static bool isShowEditorPrefs = false;
static bool showAbout = false;