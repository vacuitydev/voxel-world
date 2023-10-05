#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <tuple>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "graphics/shader.h"
#include "graphics/model.h"
#include "graphics/geometry.h"
#include "utils/generators.h"
#include "utils/read_image.h"
using namespace std;
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
};
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
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
	std::tuple<vector<VertexData>, vector<int>> quad = get_quad_vertices_indices(glm::vec3{0, +0.2, 0}, glm::normalize(glm::vec3{0, -0.5, -1}), 0.5f, 0);
	auto vertices = std::get<0>(quad);
	auto indices = std::get<1>(quad);

	Model square_model = Model(vertices, indices);
	quad = get_quad_vertices_indices(glm::vec3{-0.5f, -0.5f, 0}, glm::normalize(glm::vec3{0, 0, 1}), 0.5f, 0);
	Model model2 = Model(std::get<0>(quad), std::get<1>(quad));
	quad = get_quad_vertices_indices(glm::vec3{0}, glm::vec3{.0f,.0f,1.f}, 0.5f, 0);
	Model model3 = Model(std::get<0>(quad), std::get<1>(quad));
	Shader shader = Shader::shaderFromFiles("shaders/default.vert", "./shaders/default.frag");
	Geometry g1= Geometry(&square_model,&shader);
	Geometry g2= Geometry(&model2, 		&shader);
	Geometry g3= Geometry(&model3, 		&shader);

	glFrontFace(GL_CCW);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	ImageData imageData = read_image_from_file("/images/popcat.jpg");
	if (imageData.data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageData.width, imageData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	unsigned int transformLoc = glGetUniformLocation(shader.Id, "transform");
	// std::cout<<"Transforming "<<trans<<std::endl;
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		
		glBindTexture(GL_TEXTURE_2D, texture);
		g1.Draw();
		g2.Draw();
		g3.Draw();
		GLenum error;
		while ((error = glGetError()) != GL_NO_ERROR)
		{
			std::cerr << "OpenGL Error: " << error << std::endl;
		}
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}
