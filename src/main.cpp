#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
struct Coordinate
{
	float x;
	float y;
	Coordinate(float x, float y)
	{
		this->x = x;
		this->y = y;
	};
};
vector<float> get_triangle_vertices(float scale = 1.0f, Coordinate offset = {0.0f, 0.0f})
{
	vector<float> vertices = {
		-0.5f + offset.x,
		-0.5f + offset.y,
		0.0f,
		0.5f + offset.x,
		-0.5f + offset.y,
		0.0f,
		0.0f + offset.x,
		0.5f + offset.y,
		0.0f,

	};
	return vertices;
};
vector<int> get_triangle_indices(){
	return {
		0,1,2
	};
}
vector<float> get_square_vertices(){
	return {
		-.5f,-.9f,.0f,
		+.5f,-.9f,.0f,
		+.5f,+.9f,.0f,
		-.5f,+.9f,.0f,
	};
}
vector<int> get_square_indices(){
	return {
		0,1,2,
		2,3,0
	};
};
unsigned int create_shader_program()
{
	const char *vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec3 aPos;\n"
									 "void main()\n"
									 "{\n"
									 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
									 "}\0";
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	const char *fragment_shader_source = R"(
	#version 330 core
	out vec4 FragColor;
	void main(){
		FragColor = vec4(1.0f,0.5f,0.4f,1.0f);
	}
)";
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::Fragment::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::Program::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	auto window = glfwCreateWindow(800, 600, "First try", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Could not initialize window\n";
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	auto vertices = 	get_square_vertices();
	auto indices = 		get_square_indices();
	size_t vertices_size = vertices.size() * sizeof(float);


	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	std::cout << "Size " << vertices_size << endl;
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(float), indices.data(), GL_STATIC_DRAW);

	unsigned int shaderProgram = create_shader_program();
	glFrontFace(GL_CCW);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
	}

	
	glfwTerminate();

	return 0;
}
