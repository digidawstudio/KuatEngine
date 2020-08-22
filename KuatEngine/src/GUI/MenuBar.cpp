#include "MenuBar.h"

//Json::CharReaderBuilder reader;
//Json::Value root;
//
//bool parseSuccess = reader.parse("../Preferences/default_settings.json", root, false);

void MenuBar::ShowMainMenuBar(GLuint VAO, GLuint VBO, GLFWwindow* window) {
	if (isShowEditorPrefs)    MenuBar::showEditorPreferencesMenu(&isShowEditorPrefs);
	if (showAbout)            MenuBar::showAboutMenu(&showAbout);

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			MenuList(VAO, VBO, window);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Others")) {
			ImGui::MenuItem("About KuatEngine", NULL, &showAbout);
			if (ImGui::MenuItem("KuatEngine API Documentation", "F1", false, false)) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Magic Game Idea Generator", "alt+G")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void MenuBar::MenuList(GLuint VAO, GLuint VBO, GLFWwindow* window)
{

	//ImGui::MenuItem("(demo menu)", NULL, false, false);
	if (ImGui::MenuItem("New")) {}
	if (ImGui::MenuItem("Open", "Ctrl+O")) {}
	if (ImGui::BeginMenu("Open Recent"))
	{
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem("Save", "Ctrl+S")) {}
	if (ImGui::MenuItem("Save As..")) {}

	ImGui::Separator();

	// Here we demonstrate appending again to the "Options" menu (which we already created above)
	// Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
	// In a real code-base using it would make senses to use this feature from very different code locations.
	if (ImGui::BeginMenu("Preferences")) // <-- Append!
	{
		ImGui::MenuItem("Editor", "ctrl+alt+e", &isShowEditorPrefs);
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem("Quit", "Alt+F4")) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();
		exit(0);
	}
}

//For showing About
void MenuBar::showAboutMenu(bool* p_open) {
	ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("About KuatEngine", p_open, { ImGuiWindowFlags_NoCollapse })) {
		ImGui::Text("KuatEngine is a Open Source C++ Game Engine made by Game Developer for Game Developer");
		if (ImGui::Button("Close"))
			showAbout = !p_open;
	}
	ImGui::End();
}

//For showing Editor Preferences Menu
void MenuBar::showEditorPreferencesMenu(bool* p_open) {
	ImGui::SetNextWindowSize(ImVec2(300, 600), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Editor Preferences", p_open, { ImGuiWindowFlags_NoCollapse })) {
		ImGui::Text("Editor Layout Color");
		ImGui::ColorEdit4("Pick a color", (float*)&editor_space_color);
		if (ImGui::Button("Save", ImVec2(100, 0))) {
			/*if (parseSuccess) {
				cout << "Config list: " << root.asString() << endl;
			}
			else {
				cout << "file not found";
			}*/
		}
		ImGui::SameLine();
		if (ImGui::Button("Close"))
			isShowEditorPrefs = !p_open;
	}
	ImGui::End();
}