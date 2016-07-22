#define GLEW_STATIC
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#define LOG(a) std::cout << a << std::endl;

GLFWwindow* window;

int InitializeWindow()
{
	if (!glfwInit())
	{
		LOG("GLFW Initialization Failed");
		return 1;
	}

	window = glfwCreateWindow(800, 600, "TEAM KUNING GAME", NULL, NULL);
	if (!window)
	{
		LOG("Window creation failed");
		glfwTerminate();
		return 2;
	}

	glfwMakeContextCurrent(window);
	return 0;
}

float TriangleVertexArray[9] =	{	0.f		,1.f	,0.f,
											-1.f	,-1.f	,0.f,			
											1.f		,-1.f	,0.f
								};

//RENDER CURRENTLY DOES NOT EXIT UNTIL PROGRAM TERMINATION
int Render()
{
	std::cout << "Begin initializing window" << std::endl;
	if (InitializeWindow())//InitalizeWindow returns non-zero on error
	{
		return -1;
	}

	if (GLEW_OK != glewInit())
	{
		LOG("GLEW initialization failed");
		return -1;
	}

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleVertexArray), TriangleVertexArray, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}