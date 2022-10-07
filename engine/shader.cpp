#include "pch.h"
#include "shader.h"

#include "file_stream.h"
#include "primitives.h"

static std::vector<glprogram> programs;

std::vector<f32> colorise_vertices(std::vector<f32> vertices);
f32 get_default_color(size_t i);

int create_program(const char* vertex_path, const char* fragment_path)
{
	GLuint program_id = glCreateProgram();

	GLuint v_shader = compile_shader(vertex_path, GL_VERTEX_SHADER);
	GLuint f_shader = compile_shader(fragment_path, GL_FRAGMENT_SHADER);

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

		return success;
	}

	glprogram program;

	program.handle = program_id;
	program.vertex = v_shader;
	program.fragment = f_shader;

	programs.push_back(program);

	glDeleteShader(v_shader);
	glDeleteShader(f_shader);

	return success;
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


u32 bind_vertex_data(primitive_types type)
{
	GLuint VAO, VBO, EBO;

	std::vector<f32> vertices = colorise_vertices(get_vertices(type));
	std::vector<u32> indices  = get_indices(type);

	u64 vertices_size = VECTOR_SIZE<f32>(vertices);
	u64 indices_size = VECTOR_SIZE<u32>(indices);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, &vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, &indices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	return VAO;
}

std::vector<f32> colorise_vertices(std::vector<f32> vertices)
{
	std::vector<f32> temp;

	for (size_t i = 0; i < vertices.size(); i = i + 3)
	{
		temp.push_back(vertices.at(i));
		temp.push_back(vertices.at(i + 1));
		temp.push_back(vertices.at(i + 2));
		temp.push_back(get_default_color(i));
		temp.push_back(get_default_color(i + 1));
		temp.push_back(get_default_color(i + 2));
	}

	return temp;
}

f32 get_default_color(size_t i) 
{
	std::vector<f32> default_colors
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	
	return default_colors.at(i % default_colors.size());
}


GLuint get_last_program_id() 
{
	return programs.back().handle;
}