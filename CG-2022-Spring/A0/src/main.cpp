#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "camera.h"
#include "shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// camera
Camera camera(glm::vec3(1.0f, 1.0f, 3.0f));

namespace Model{
	bool cameraRotating(false);
	bool objRotating(false);
	float rotation;
	glm::mat4 projection(glm::mat4(1.0f));
	glm::mat4 view(glm::mat4(1.0f));
	glm::mat4 transform(glm::mat4(1.0f));
	glm::vec3 coords(0.0f, 0.0f, 0.0f);
}

GLFWwindow* create_window(){
		// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	GLFWwindow *window =
		glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	return window;
}

void config_opengl(){
	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(1);
	}
}

float zero() { return 0.0; }

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
        Model::objRotating ^= 1;
    else if(key == GLFW_KEY_T && action == GLFW_PRESS)
    	Model::cameraRotating ^= 1;
}

int main(int argc, char *argv[]) {

	srand(time(0));
	GLFWwindow *window = create_window();
	config_opengl();
	// build and compile our shader program
	Shader ourShader("../src/vertex.shader", "../src/fragment.shader");

	int num_vertices;
	if(argc != 2){
		puts("Usage: ./app [num-vertices]");
		exit(1);
	}
	else{
		try{
			num_vertices = std::stoi(argv[1]);
			if(num_vertices < 3) throw(-1);
		}
		catch(...){
			puts("Argument passed must be an integer in the range 3 - 2^31-1");
			exit(1);
		}
	}

	double ang_inc = glm::radians((float)360/num_vertices);
	double ang_accum = 0;

	float color_top[3] = { (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX };
	float color_bottom[3] = { (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX };
	
	float vertices[72*num_vertices];
	for(int t=0; t<2*num_vertices; t++){
		for(int v=0; v<3; v++){
			int id = t*18 + 6*v;
			int x = id, y = id+1, z = id+2;
			if(v == 0){
				vertices[x] = vertices[y] = zero();
			}
			else if(v == 1){
				vertices[x] = cos(ang_accum);
				vertices[y] = sin(ang_accum);
			}
			else if(v == 2){
				vertices[x] = cos(ang_accum + ang_inc);
				vertices[y] = sin(ang_accum + ang_inc);
			}
			vertices[z] = (t >= num_vertices) ? 0.5f : zero();
			vertices[id+3] = (t >= num_vertices) ? color_top[0] : color_bottom[0];
			vertices[id+4] = (t >= num_vertices) ? color_top[1] : color_bottom[1];
			vertices[id+5] = (t >= num_vertices) ? color_top[2] : color_bottom[2];
		}
		ang_accum += ang_inc;
	}

	const int OFFSET = 2*num_vertices*18;
	for(int t=0; t<num_vertices; t++){
		float rand_color[3] = { (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX };
		for(int v=0; v<3; v++){
			int id = 2*t*18 + 6*v + OFFSET;
			int x = id, y = id+1, z = id+2;
			if(v == 0){
				vertices[x] = cos(ang_accum);
				vertices[y] = sin(ang_accum);
				vertices[z] = 0.5f;
			}
			else if(v == 1){
				vertices[x] = cos(ang_accum);
				vertices[y] = sin(ang_accum);
				vertices[z] = zero();
			}
			else if(v == 2){
				vertices[x] = cos(ang_accum + ang_inc);
				vertices[y] = sin(ang_accum + ang_inc);
				vertices[z] = zero();
			}
			for(int i=0; i<3; i++) vertices[id + 3 + i] = rand_color[i];
		}

		for(int v=0; v<3; v++){
			int id = 2*t*18 + 18 + 6*v + OFFSET;
			int x = id, y = id+1, z = id+2;
			if(v == 0){
				vertices[x] = cos(ang_accum + ang_inc);
				vertices[y] = sin(ang_accum + ang_inc);
				vertices[z] = zero();
			}
			else if(v == 1){
				vertices[x] = cos(ang_accum);
				vertices[y] = sin(ang_accum);
				vertices[z] = 0.5f;
			}
			else if(v == 2){
				vertices[x] = cos(ang_accum + ang_inc);
				vertices[y] = sin(ang_accum + ang_inc);
				vertices[z] = 0.5f;
			}
			for(int i=0; i<3; i++) vertices[id + 3 + i] = rand_color[i];
		}
		ang_accum += ang_inc;
	}

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s),
	// and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
						  (void *)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered
	// VBO as the vertex attribute's bound vertex buffer object so afterwards we
	// can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally
	// modify this VAO, but this rarely happens. Modifying other VAOs requires a
	// call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
	// VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, key_callback);
	// render loop
	while (!glfwWindowShouldClose(window)) {
		// print stuff for better understanding
		/*
		printf("\n");
		printf("Camera Position: %0.3f %0.3f %0.3f\n", camera.Position.x,
			   camera.Position.y, camera.Position.z);
		*/

		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Model::transform = glm::mat4(1.0f);  // identity matrix

		Model::transform = glm::translate(Model::transform, Model::coords);

		// make transformations
		// rotation
		if(Model::objRotating)
			Model::rotation += 1;
		
		Model::transform = glm::rotate(Model::transform, glm::radians(Model::rotation), glm::vec3(0.0f, 0.0f, 1.0f));


		ourShader.use();
		ourShader.setMat4("transform", Model::transform);
		
		if(Model::cameraRotating){
			camera.LookAt(Model::coords);
			glm::mat4 ctrans = glm::mat4(1.0f);  // id
			camera.Position = camera.Position - Model::coords + glm::vec3(0.0f, Model::coords.y, 0.0f);
			static float ang = 0.0f;
			ang = 1;
			ctrans = glm::rotate(ctrans, glm::radians(ang), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::vec4 res = glm::vec4(camera.Position, 1.0f);
			res = ctrans * res;
			camera.Position = glm::vec3(res);
			camera.Position = camera.Position + Model::coords - glm::vec3(0.0f, Model::coords.y, 0.0f);
			camera.LookAt(Model::coords);
		}

		// view matrix
		Model::view = camera.GetViewMatrix();
		ourShader.setMat4("view", Model::view);

		// projection matrix
		Model::projection = glm::perspective(
			glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
			0.1f, 100.0f);
		ourShader.setMat4("projection", Model::projection);

		glBindVertexArray(VAO);  // seeing as we only have a single VAO there's
		// no need to bind it every time, but we'll do
		// so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 12*num_vertices);
		// glBindVertexArray(0); // no need to unbind it every time

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse
		// moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
void processInput(GLFWwindow *window) {

	glm::vec3 nfront = camera.Position - camera.Direction;
	glm::normalize(nfront);
	glm::vec3 nright = glm::normalize(glm::cross(nfront, camera.WorldUp));
	glm::vec3 nup = glm::normalize(glm::cross(nright, nfront));

	float scale_fac = 0.125;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, 0.05, Model::coords);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, 0.05, Model::coords);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, 0.05, Model::coords);
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, 0.05, Model::coords);
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(UPWARD, 0.05, Model::coords);
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWNWARD, 0.05, Model::coords);
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		Model::coords += nup * scale_fac;
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		Model::coords -= nup * scale_fac;
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		Model::coords += nright * scale_fac;
	else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		Model::coords -= nright * scale_fac;
	else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		Model::coords += nfront * scale_fac;
	else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		Model::coords -= nfront * scale_fac;
	else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS){
		
	}
	else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS){
		camera.Position = glm::vec3(1.0f, 2.0f, 5.0f);
		camera.LookAt(Model::coords);
	}
	else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS){
		camera.Position = glm::vec3(3.0f, 5.0f, 1.0f);
		camera.LookAt(Model::coords);
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width
	// and height will be significantly larger than specified on retina
	// displays.
	glViewport(0, 0, width, height);
}
