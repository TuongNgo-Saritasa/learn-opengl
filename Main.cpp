#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() 
{
	// Initialize GLFW
	glfwInit();
	// Tell GLFW what version of OpenGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Create a GLFWwindow object of 800 by 800 pixels, naming it "LearnOpenGL"
	GLFWwindow* myWindow = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);
	if (myWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		// Terminate GLFW
		glfwTerminate();
		return -1;
	}
	// Make the context of our window the main context on the current thread
	glfwMakeContextCurrent(myWindow);
	// Initialize GLAD
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, 800, 800);



	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Delete the now useless vertex and fragment shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Upper triangle
		5, 4, 1 // Lower right triangle
	};

	// Create reference containers for the Vertex Array Object and the Vertex Buffer Object
	GLuint VBO, VAO, EBO;
	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	//Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	/* Using EBO
		//Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		//Introduce the indices into the EBO
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	*/
		// Linking Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Unbind the VBO/VAO/EBO to prevent accidentally modifying them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(myWindow);

	while (!glfwWindowShouldClose(myWindow))
	{
		//Specify the background's color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// Clean the back buffer and assign new color to it.
		glClear(GL_COLOR_BUFFER_BIT);

		//Tell OpenGL to use shader propgram we want to use.
		glUseProgram(shaderProgram);

		// Bind the VAO for OpenGL knows how to use it.
		glBindVertexArray(VAO);

		//// Draw the trialge using the GL_TRIANGLES primitive.
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		//Swap the back buffer to the front buffer.
		glfwSwapBuffers(myWindow);

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		processInput(myWindow);

		//Take care of all GLFW events.
		glfwPollEvents();
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwDestroyWindow(myWindow);
	glfwTerminate();

	return 0;
}

