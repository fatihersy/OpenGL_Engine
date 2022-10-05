#include "pch.h"
#include "shader.h"

#include "file_stream.h"
#include "primitives.h"

static std::vector<glprogram> programs;

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


u32 bind_vertices(primitive_types type)
{
	GLuint VAO, VBO, EBO;

	std::vector<f32> vertices = get_vertices(type);
	std::vector<u32> indices  = get_indices(type);

	u64 vertices_size = VECTOR_SIZE<f32>(vertices);
	u64 indices_size = VECTOR_SIZE<u32>(indices);
	u64 vertices_stride = (vertices_size * sizeof(f32));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, &vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, &indices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	return VAO;
}

GLuint get_last_program_id() 
{
	return programs.back().handle;
}