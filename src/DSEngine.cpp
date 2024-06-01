#include "DSEngine.hpp"
#include "stdio.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define DEBUG

DSEngine::DSEngine() : showDebug(false) { // Will try to initialize GLFW and imgui.
	init();
	std::cout << "Constructed DSEngine" << std::endl;
};

DSEngine::~DSEngine(){
	cleanup();
	std::cout << "Exiting Program" << std::endl;
};

void DSEngine::error_callback(int error, const char* description){
	fprintf(stdout, "Error: %s\n", description);
};

void DSEngine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	// std::cout << "Key callback" << std::endl;
	if(action == GLFW_PRESS){
		// std::cout << "Press Detected" << std::endl;
		DSEngine* engine = static_cast<DSEngine*>(glfwGetWindowUserPointer(window));
		if(engine){
			// std::cout << "Engine cast to ptr" << std::endl;
			if (key == GLFW_KEY_ESCAPE){
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
			if(key == GLFW_KEY_BACKSLASH){
				engine->toggleDebug();
			}
		} else {
			// std::cout << "Failed to cast engine" << std::endl;
		}
	}
};

//Initialize ImGui and GLFW
uint8_t DSEngine::init(){
	std::cout << "Initializing DSEngine" << std::endl;

	glfwSetErrorCallback(DSEngine::error_callback);

	if(!glfwInit()){
		std::cerr << "Failed to init glfw" << std::endl;
		return EXIT_FAILURE;
	}

// Versioning logic for ImGui and opengl build things.
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#elif defined(__WIN32__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 450";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#ifdef DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); //Debug messages.
#endif
#endif

	//Create the glfw window held in DSEngine.	
	window = glfwCreateWindow(800, 640, "DSRender", NULL, NULL);
	if(!window){
		std::cerr << "Failed to init glfwWindow" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	
	//Create window then do things.
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSwapInterval(0); // This is v-sync. Caps framerate of window to refreshrate.
	glfwSetKeyCallback(window, DSEngine::key_callback);
	
	// Setup ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// OpenGL Integration and Initialization.
	if(!gladLoadGL(glfwGetProcAddress)){
		std::cerr << "Failed to init OpenGL" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugOutput, nullptr);

	const GLubyte* renderer = glGetString(GL_RENDERER); // Get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // Version as a string

	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "OpenGL version supported: " << version << std::endl;

	std::cout << "Initialized GLFW Window" << std::endl;

	float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };

	//Setup OpenGL structs.
	//Vertex Buffer
	glGenBuffers(1, &VBO); //Generates one vertex buffer
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Binds a buffer to a specific purpose/target.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	std::cout << "Initialized vertex_buffer/array" << std::endl;

	shaders.push_back(Shader("../shaders/test.vert", "../shaders/test.frag"));
	std::cout << "Test shaders compiled and linked successfully" << std::endl;;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0); //0 Is index of VAO
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3 * sizeof(float))); //1 Is index of VBO
	glEnableVertexAttribArray(1);
	
	// std::cout << "Shaders compiled: " << shaders.size() << std::endl;
	std::cout << "Initialized OpenGL" << std::endl;	
	return EXIT_SUCCESS;
}

uint8_t DSEngine::cleanup(){
	// ImGui Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
	
	//Free the window.
	glfwDestroyWindow(window);

	glfwTerminate();
	std::cout << "GLFW Terminated Succesfully" << std::endl;
	return EXIT_SUCCESS;
}

uint8_t DSEngine::run(){
	std::cout << "Begin Run" << std::endl;
	ImGuiIO& io = ImGui::GetIO();
	double upTime = 0;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImVec2 debug_pos = ImVec2(0.0f, 0.0f);

	bool first = true;
	while(!glfwWindowShouldClose(window)){  
		if(first){
			std::cout << "Begin mainloop" << std::endl;
			first = false;
		}
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::SetNextWindowPos(debug_pos, ImGuiCond_Always);

		//ImGui example frame.
		static float f = 0.0f;
        static int counter = 0;		

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button")) { // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		}                           
                
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		shaders[0].use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		if(showDebug){ //Only draw imgui window if displaying debug.
			ImGui::Render(); // Render current ImGui frame to window. 
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		upTime = glfwGetTime();
	}

	std::cout << "Ending loop" << std::endl;

	return EXIT_SUCCESS;
}