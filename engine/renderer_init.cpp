#include "pch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "primitives.h"
#include "renderer_init.h"
#include "window.h"
#include "file_stream.h"

static b8 is_initialized = false;

template<typename T> unsigned long long VECTOR_SIZE(std::vector<T> vector) 
{
	return vector.size() * sizeof(T);
}

typedef struct glprogram 
{
	GLuint handle;
	GLuint vertex, fragment;
};

typedef struct glshape 
{
	glprogram program;

	GLuint VAO, VBO, EBO;

	primitives::types type;
	u32 indice_count;
};

static std::vector<glprogram> programs;
static std::vector<glshape> shapes;

GLuint compile_shader(const char* path, GLint shader_type);
b8 create_program(GLuint v_shader, GLuint f_shader);
void bind_vertices(size_t shape, primitives::types type);
void draw_shape(glshape shape);

b8 initialize_renderer(const char* title, i32 width, i32 height) 
{
	if (is_initialized) return false;

	if (!glfwInit()) return false;

	if(!initialize_window(title, width, height)) return false;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to Load GLAD!" << std::endl;
		terminate_renderer();
		return false;
	}

	set_framebuffer_callback();

	is_initialized = true;

	return true;
}

b8 renderer_update() 
{
	draw_shape(shapes.front());

	return true;
}

GLuint compile_shader(const char* path, GLint shader_type) 
{
	std::string str_cpy = read_file(path);
	const char* file = str_cpy.c_str();

	GLuint shader = glCreateShader(shader_type);

	glShaderSource(shader, 1, &file, NULL);
	glCompileShader(shader);

	int  success;
	char log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, log);
		std::cout << "ERROR::SHADER::" 
			<< ((shader_type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT") 
			<< "::COMPILATION_FAILED\n" << log << std::endl;

		return 0;
	}

	return shader;
}

void initialize_shape()
{
	glshape shape;

	shape.type = primitives::TRIANGLE;
	shape.program.vertex = compile_shader("vertex.vert", GL_VERTEX_SHADER);
	shape.program.fragment = compile_shader("fragment.frag", GL_FRAGMENT_SHADER);

	if(!create_program(shape.program.vertex, shape.program.fragment)) return;

	shape.program = programs.back();

	shapes.push_back(shape);

	bind_vertices((shapes.size()-1), shape.type);
}

b8 create_program(GLuint v_shader, GLuint f_shader) 
{
	GLuint program_id = glCreateProgram();

	glAttachShader(program_id, v_shader);
	glAttachShader(program_id, f_shader);
	glLinkProgram(program_id);

	int  success;
	char log[512];
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(program_id, 512, NULL, log);
		std::cout << "Shader Program Cannot be Created!" << std::endl;

		glDeleteShader(v_shader);
		glDeleteShader(f_shader);

		return false;
	}

	glprogram program;

	program.handle = program_id;
	program.vertex = v_shader;
	program.fragment = f_shader;

	programs.push_back(program);

	glDeleteShader(v_shader);
	glDeleteShader(f_shader);

	return true;
}

void bind_vertices(size_t index, primitives::types type)
{
	glshape shape = shapes.at(index);

	std::vector<f32> vertices = primitives::get_vertices(type);
	std::vector<u32> indices = primitives::get_indices(type);
	u64 vertices_size = VECTOR_SIZE<f32>(vertices);
	u64 indices_size = VECTOR_SIZE<u32>(indices);
	u32 vertices_stride = (vertices_size * sizeof(f32));
	shape.indice_count = indices.size();

	std::cout << "INDICES SIZE: " << shape.indice_count << std::endl;

	glGenVertexArrays(1, &shape.VAO);
	glGenBuffers(1, &shape.VBO);
	glGenBuffers(1, &shape.EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(shape.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, shape.VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, &vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, &indices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	shapes.at(index) = shape;

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}
void draw_shape(glshape shape) 
{
	glUseProgram(shape.program.handle);
	glBindVertexArray(shape.VAO);
	glDrawElements(GL_TRIANGLES, shape.indice_count, GL_UNSIGNED_INT, 0);
}
void renderer_begin_render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.5f, 0.1f, 0.2f, 1.0f);
}
void renderer_end_render()
{
	glfwSwapBuffers((GLFWwindow*)get_window_instance());

	glfwPollEvents();
}

b8 renderer_begin_loop()
{
	return window_should_close();
}
b8 terminate_renderer()
{
	destroy_window();

	glfwTerminate();

	return true;
}
