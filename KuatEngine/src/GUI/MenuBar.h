#pragma once
#ifndef MENU_BAR
#define MENU_BAR
#include "kepch.h"
#include "json/json.h"

class MenuBar
{
public:
	static void ShowMainMenuBar(GLuint VAO, GLuint VBO, GLFWwindow* window);
	static void MenuList(GLuint VAO, GLuint VBO, GLFWwindow* window);
	static void showEditorPreferencesMenu(bool* p_open);
	static void showAboutMenu(bool* p_open);
};
#endif // !MENU_BAR


