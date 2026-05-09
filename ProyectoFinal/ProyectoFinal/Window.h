#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLint getDayNight() { return day_night; }
	void setDayNight(GLint value) {day_night = value; }
	GLint getMoveLampPost() { return moveLampPost; }
	GLint getMoveCar() { return moveCar; }
	void setMoveCar(GLint value) { moveCar = value; }
	GLint getRobotMove() { return robotMove; }
	void setRobotMove(GLint value) { robotMove = value; }
	GLint getCamType() { return camType; }
	GLint getLight1() { return light1; }
	void setLight1(GLint value) { light1 = value; }
	GLint getLight2() { return light2; }
	void setLight2(GLint value) { light2 = value; }
	GLint getLight3() { return light3; }
	void setLight3(GLint value) { light3 = value; }
	GLint getLight4() { return light4; }
	void setLight4(GLint value) { light4 = value; }
	void setMoveLampPost(GLint value) { moveLampPost = value; }

	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	GLint day_night = 0;
	GLint moveLampPost = 0;
	GLint moveCar = 0;
	GLint camType = 1;
	GLint robotMove = 0;
	GLint light1 = 1;
	GLint light2 = 1;
	GLint light3 = 1;
	GLint light4 = 1;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
	

};

