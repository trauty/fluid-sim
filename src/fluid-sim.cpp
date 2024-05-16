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
		1920, 1080,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

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

	gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

	GLfloat vertices[] = {
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		0.0f,
		0.7071f,
		0.7071f,
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.7071f,
		-0.7071f,
		0.0f,
		0.0f,
		-1.0f,
		0.0f,
		-0.7071f,
		-0.7071f,
		0.0f,
		-1.0f,
		0.0f,
		0.0f,
		-0.7071f,
		0.7071f,
		0.0f,
	};

	GLuint indices[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 1};

	SDL_GL_SetSwapInterval(1);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();
	#pragma region colors
	ImVec4 *colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.48f, 0.16f, 0.16f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.98f, 0.26f, 0.26f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.78f, 0.09f, 0.09f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.88f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.98f, 0.26f, 0.26f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.98f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.98f, 0.26f, 0.26f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.75f, 0.10f, 0.10f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.75f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.98f, 0.26f, 0.26f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.98f, 0.26f, 0.26f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.58f, 0.18f, 0.18f, 0.86f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.68f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.07f, 0.07f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.42f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.98f, 0.26f, 0.26f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	#pragma endregion colors

	ImGui_ImplSDL2_InitForOpenGL(window, ctx);
	ImGui_ImplOpenGL3_Init("#version 430");

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertex_shader_string = getFileContent("shaders/main.vert");
	const char *vertex_shader_source = vertex_shader_string.c_str();
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragment_shader_string = getFileContent("shaders/main.frag");
	const char *fragment_shader_source = fragment_shader_string.c_str();
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	return true;
}

void FluidSim::execute()
{
	uint32_t w, h;
	SDL_GetWindowSize(window, (int *)&w, (int *)&h);

	std::vector<Particle> particles;
	std::vector<glm::mat4> model_matrices;

	for (float_t y = boundary_eps; y < h - boundary_eps * 2.0f; y += smoothing_radius)
	{
		for (float_t x = w / 8.0f; x <= w / 2.0f; x += smoothing_radius)
		{
			if (particles.size() < num_particles)
			{
				Particle new_particle;

				new_particle.pos = glm::vec2(x + std::rand() % 10, y);

				glm::mat4 model_mat = glm::mat4(1.0f);
				model_mat = glm::translate(model_mat, glm::vec3(new_particle.pos, 0.0f));
				model_mat = glm::scale(model_mat, glm::vec3(particle_scale, particle_scale, 1.0f));

				model_matrices.push_back(model_mat);

				particles.push_back(new_particle);
			}
			else
			{
				break;
			}
		}
	}

	GLuint model_matrices_buf_id;
	glGenBuffers(1, &model_matrices_buf_id);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, model_matrices_buf_id);
	glBufferData(
		GL_SHADER_STORAGE_BUFFER, sizeof(glm::mat4) * model_matrices.size(),
		(const void *)model_matrices.data(),
		GL_DYNAMIC_COPY);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	glm::mat4 view_mat = glm::mat4(1.0f);
	view_mat = glm::translate(view_mat, glm::vec3(0.0f, 0.0f, -1.0f));

	glm::mat4 ortho_mat = glm::ortho(0.0f, (float)w, 0.0f, (float)h);

	delta_time = 0;
	uint64_t now = SDL_GetPerformanceCounter();
	uint64_t last = 0;

	bool exit = 0;
	while (!exit)
	{
		last = now;
		now = SDL_GetPerformanceCounter();

		delta_time = (float)(now - last) / (float)SDL_GetPerformanceFrequency();
		delta_time *= 1.0f;

		compute_density_pressure(particles);
		compute_forces(particles);
		integrate(particles, w, h);

		for (uint32_t i = 0; i < particles.size(); i++)
		{
			model_matrices[i] = glm::mat4(1.0f);
			model_matrices[i] = glm::translate(model_matrices[i], glm::vec3(particles[i].pos, 0.0f));
			model_matrices[i] = glm::scale(model_matrices[i], glm::vec3(particle_scale, particle_scale, 1.0f));
		}

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
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
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					glViewport(0, 0, event.window.data1, event.window.data2);
					ortho_mat = glm::ortho(0.0f, (float)event.window.data1, 0.0f, (float)event.window.data2);
					w = event.window.data1;
					h = event.window.data2;
				}
				break;

			default:
				break;
			}
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		
		ImGui::Begin("fbs-fluid-sim");
		ImGui::Text("Einstellungen");
		ImGui::DragInt("Partikelanzahl", (int32_t*)&num_particles);
		ImGui::SliderFloat2("Gravitationskraft", glm::value_ptr(gravity), -10.0f, 10.0f);
		ImGui::DragFloat("Ruhedichte", &rest_dens);
		ImGui::DragFloat("Gaskonstante", &gas_const);
		ImGui::DragFloat("Radius", &smoothing_radius);
		ImGui::DragFloat("Partikelmasse", &mass);
		ImGui::DragFloat("Viskosität", &visc);
		ImGui::DragFloat("Berechnungsintervall", &time_step, 0.0001f, 0.0f, 0.0f, "%.5f");
		
		if (ImGui::Button("Simulation zurücksetzen"))
		{
			update(particles, model_matrices, w, h);
		}

		ImGui::End();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, model_matrices_buf_id);

		glUseProgram(shader_program);

		glUniformMatrix4fv(
			glGetUniformLocation(shader_program, "view"),
			1, GL_FALSE,
			glm::value_ptr(view_mat));
		glUniformMatrix4fv(
			glGetUniformLocation(shader_program, "ortho"),
			1, GL_FALSE,
			glm::value_ptr(ortho_mat));

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, model_matrices_buf_id);
		GLvoid *buff_ptr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
		std::memcpy(buff_ptr, (void *)model_matrices.data(), sizeof(glm::mat4) * model_matrices.size());
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

		glBindVertexArray(vao);
		glDrawElementsInstanced(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_INT, 0, num_particles);
		glBindVertexArray(0);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		SDL_GL_SwapWindow(window);
		std::string fps_num = std::to_string((uint16_t)(1.0f / delta_time));
		std::string fps_out = "fluid-sim - " + fps_num + " FPS";
		SDL_SetWindowTitle(window, fps_out.c_str());
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(ctx);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void FluidSim::update(std::vector<Particle> &particles, std::vector<glm::mat4> &model_matrices, uint32_t w, uint32_t h)
{
	uint32_t i = 0;
	for (float_t y = boundary_eps; y < h - boundary_eps * 2.0f; y += smoothing_radius)
	{
		for (float_t x = w / 8.0f; x <= w / 2.0f; x += smoothing_radius)
		{
			if (i < particles.size())
			{
				glm::vec2 new_pos(x + std::rand() % 10, y);
				glm::mat4 model_mat = glm::mat4(1.0f);
				model_mat = glm::translate(model_mat, glm::vec3(new_pos, 0.0f));
				model_mat = glm::scale(model_mat, glm::vec3(particle_scale, particle_scale, 1.0f));

				model_matrices[i] = model_mat;

				particles[i].pos = new_pos;
				particles[i].vel = glm::vec2(0.0f);

				i++;
			}
			else
			{
				break;
			}
		}
	}
}

void FluidSim::compute_density_pressure(std::vector<Particle> &particles)
{
	for (Particle &pi : particles)
	{
		pi.density = 0.0f;
		for (Particle &pj : particles)
		{
			glm::vec2 p_vec = pj.pos - pi.pos;
			float_t r2 = glm::length(p_vec);

			if (r2 < smoothing_radius_q)
			{
				pi.density += mass * poly6 * std::pow(smoothing_radius_q - r2, 3.0f);
			}
		}
		pi.pressure = gas_const * (pi.density - rest_dens);
	}
}

void FluidSim::compute_forces(std::vector<Particle> &particles)
{
	for (Particle &pi : particles)
	{
		glm::vec2 f_press(0.0f, 0.0f);
		glm::vec2 f_visc(0.0f, 0.0f);

		for (Particle &pj : particles)
		{
			if (&pi == &pj)
			{
				continue;
			}

			glm::vec2 p_vec = pj.pos - pi.pos;

			float_t r = glm::length(p_vec);

			if (r < smoothing_radius)
			{
				f_press += -glm::normalize(p_vec) *
						   mass * (pi.pressure + pj.pressure) / (2.0f * pj.density) *
						   spiky_grad * std::pow(smoothing_radius - r, 3.0f);

				f_visc += visc * mass * (pj.vel - pi.vel) / pj.density * visc_lap * (smoothing_radius - r);
			}
		}

		glm::vec2 f_grav = gravity * mass / pi.density;
		pi.force = f_press + f_visc + f_grav;
	}
}

void FluidSim::integrate(std::vector<Particle> &particles, uint32_t w, uint32_t h)
{
	for (Particle &p : particles)
	{
		p.vel += time_step * p.force / p.density;
		p.pos += time_step * p.vel;

		if (p.pos.x - boundary_eps < 0.0f)
		{
			p.vel.x *= boundary_damping;
			p.pos.x = boundary_eps;
		}
		if (p.pos.x + boundary_eps > w)
		{
			p.vel.x *= boundary_damping;
			p.pos.x = w - boundary_eps;
		}
		if (p.pos.y - boundary_eps < 0.0f)
		{
			p.vel.y *= boundary_damping;
			p.pos.y = boundary_eps;
		}
		if (p.pos.y + boundary_eps > h)
		{
			p.vel.y *= boundary_damping;
			p.pos.y = h - boundary_eps;
		}
	}
}