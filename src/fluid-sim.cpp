#include "fluid-sim.h"

bool FluidSim::init() 
{
    std::cout << "fluid-sim" << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		std::cout << "Error while initializing SDL2: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow(
		"fluid-sim", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		1024, 576, 
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	if (window == nullptr) 
	{
		std::cout << "Error while initializing window: " << SDL_GetError() << std::endl;
		return false;
	}
	
	ctx = SDL_GL_CreateContext(window);
	

	if (ctx == nullptr) 
	{
		std::cout << "Error while initializing OpenGL context: " << SDL_GetError() << std::endl;
		return false;
	}

	gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);

	GLfloat vertices[] = {
    	0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	}; 

	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	GLuint vertex_shader = glCreateShader(GL_VERTEX_ARRAY);
	std::string vertex_shader_string = getFileContent("shaders/main.vert");
	const char* vertex_shader_source = vertex_shader_string.c_str();
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragment_shader_string = getFileContent("shaders/main.frag");
	const char* fragment_shader_source = fragment_shader_string.c_str();
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glGenVertexArrays(1, &vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);

	GLuint ebo;
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    return true;
}

void FluidSim::execute() 
{
    bool exit = 0;
	while (!exit) 
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type)
			{
				case SDL_QUIT:
					exit = true;
					break;

				case SDL_KEYUP:
					if (event.key.keysym.sym == SDLK_ESCAPE) 
					{
						exit = true;
					}	
					break;

				case SDL_WINDOWEVENT:
					if(event.window.event == SDL_WINDOWEVENT_RESIZED)
					{
						std::cout << event.window.data1 << " : " << event.window.data2 << std::endl;
						glViewport(0, 0, event.window.data1, event.window.data2);
					}
					break;

				default:
					break;
			}
		}

		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		SDL_GL_SwapWindow(window);
	}

    SDL_GL_DeleteContext(ctx);
	SDL_DestroyWindow(window);
	SDL_Quit();
}