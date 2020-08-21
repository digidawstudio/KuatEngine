// KuatEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define GLEW_STATIC
#include "KuatEngineF.h" 

//static void MenuList(GLuint VAO, GLuint VBO, GLFWwindow *window);
//static void showPropertiesMenu(ImVec4 clear_color);

const GLint WIDTH = 1280, HEIGHT = 720;
static bool isShowEditorPrefs = false;
static bool showAbout = false;
ImVec4 editor_space_color = ImVec4(0.314f, 0.314f, 0.314f, 1.00f);

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void ShowMainMenuBar(GLuint VAO, GLuint VBO, GLFWwindow *window, float *editor_space_color) {
    if (isShowEditorPrefs)    showEditorPreferencesMenu(&isShowEditorPrefs);
    if (showAbout)            showAboutMenu(&showAbout);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            MenuList(VAO, VBO, window, editor_space_color);
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
            if (ImGui::MenuItem("Magic Game Idea Generator", "alt+G")){}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

static void MenuList(GLuint VAO, GLuint VBO, GLFWwindow *window, float *editor_space_color)
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


int main()
{

    GLFWwindow* window;
    
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return -1;

    const char* glsl_version = "#version 130";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Kuat Engine", NULL, NULL);
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    //initalize imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO(); (void)io;

    //Set ImGui dark theme
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, screenWidth, screenHeight);

    Shader myShader("src/Shaders/core.vertex", "src/Shaders/core.frag");

    //setup vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        //position              //colors
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f,
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //position attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //color attrib
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    bool show_demo_window = false;


    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ShowMainMenuBar(VAO, VBO, window, (float*)&editor_space_color);

        /*showPropertiesMenu(clear_color);*/
       
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Properties");                          // Create a window called "Hello, world!" and append into it.

            /*ImGui::Text("This is some useful text.");   */            // Display some text (you can use a format strings too)

            //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        
        glClearColor(editor_space_color.x, editor_space_color.y, editor_space_color.z, editor_space_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        myShader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    std::cout << "Hello World!\n";

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

//For showing Editor Preferences Menu
static void showEditorPreferencesMenu(bool* p_open) {
    ImGui::SetNextWindowSize(ImVec2(300, 600), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Editor Preferences", p_open, {ImGuiWindowFlags_NoCollapse})) {
        ImGui::Text("Editor Layout Color");
        ImGui::ColorEdit4("Pick a color", (float*) &editor_space_color);
        ImGui::Button("Save", ImVec2(100, 0));
        ImGui::SameLine();
        if (ImGui::Button("Close"))
            isShowEditorPrefs = false;
    }
    ImGui::End();
}

//For showing About
static void showAboutMenu(bool* p_open) {
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("About KuatEngine", p_open, { ImGuiWindowFlags_NoCollapse })) {
        ImGui::Text("KuatEngine is a Open Source C++ Game Engine made by Game Developer for Game Developer");
        if (ImGui::Button("Close"))
            showAbout = false;
    }
    ImGui::End();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
