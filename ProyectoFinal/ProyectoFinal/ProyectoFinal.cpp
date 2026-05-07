/*
Práctica 7: Iluminación 1 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;

Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;
Model Sonic_Head;
Model Sonic_Body;
Model SonicRightArm;
Model SonicRightElbow;
Model SonicRightHand;
Model SonicRightThumb;
Model SonicRightIndex;
Model SonicRightMiddle;
Model SonicRightRing;
Model SonicRightPinky;
Model SonicRightKnee;
Model SonicRightLeg;
Model SonicLeftArm;
Model SonicLeftElbow;
Model SonicLeftHand;
Model SonicLeftThumb;
Model SonicLeftIndex;
Model SonicLeftMiddle;
Model SonicLeftRing;
Model SonicLeftPinky;
Model SonicLeftKnee;
Model SonicLeftLeg;
Model LampPostUpper, LampPostLower;


Skybox skybox_day;
Skybox skybox_night;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
// animación de la lámpara (Sonic)
GLfloat postSpin = 0.0f;
GLfloat postScaleX = 0.0f;
GLfloat postScaleY = 0.0f;
GLfloat postScaleZ = 0.0f;
GLfloat spinTimer = 0.0f;
GLfloat spinLightX = 0.0f;
GLfloat spinLightY = 0.0f;
// temporizador de luz direccional
GLfloat dirTimer = 0.0f;
GLfloat moveDirectionalX = 0.0f;
GLfloat moveDirectionalY = 0.0f;

// movimiento de la cámara con Sonic
glm::vec3 posicionSonic = glm::vec3(30.0f, 3.0f, 15.0f);
GLfloat xChange = 0.0f;
GLfloat sonicVista = 0.0f;
glm::vec3 sonicFrente;
glm::vec3 sonicDerecha;
GLfloat sonicSpeed = 0.0f; // mil pesos a que el profe no entiende la referencia
GLfloat camaraAtras = 10.0f;
GLfloat camaraArriba = 4.0f;
glm::vec3 posicionCamara;
GLfloat anguloSonic;

// detección de llaves
bool* keys;

// articulaciones de Sonic
GLfloat leftShoulderArt = 0.0f;
GLfloat leftArmArt = 0.0f;
GLfloat rightShoulderArt = 0.0f;
GLfloat rightArmArt = 0.0f;
static double limitFPS = 1.0 / 60.0;

// Banderas de cámara
GLint cam1 = 0;
GLint cam2 = 0;
GLint cam3 = 0;
GLint camDebug = 0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};
	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


void CrearDado()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,

		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,

		// right
		4, 5, 6,
		6, 7, 4,

	};	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.26f,  0.34f,		0.0f,	0.0f,	1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.49f,	0.34f,		0.0f,	0.0f,	1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.49f,	0.66f,		0.0f,	0.0f,	1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.26f,	0.66f,		0.0f,	0.0f,	1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	1.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	1.0f,	1.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.0f,	1.0f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		1.0f,	0.0f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		1.0f,	1.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,	1.0f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,  0.0f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	1.0f,	0.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f,	1.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	1.0f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	1.0f,	0.0f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	1.0f,	1.0f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.0f,	1.0f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f,	0.0f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	1.0f,	1.0f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.0f,	1.0f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(dado);

}




int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();
	CreateObjects();
	CrearDado();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");

	// MODELO: SONIC
	Sonic_Head = Model();
	Sonic_Head.LoadModel("Models/rewrite-sonic/source/SonicHead.obj");
	Sonic_Body = Model();
	Sonic_Body.LoadModel("Models/rewrite-sonic/source/SonicBody.obj");
	SonicRightArm = Model();
	SonicRightArm.LoadModel("Models/rewrite-sonic/source/SonicRightArm.obj");
	SonicRightElbow = Model();
	SonicRightElbow.LoadModel("Models/rewrite-sonic/source/SonicRightElbow.obj");
	SonicRightHand = Model();
	SonicRightHand.LoadModel("Models/rewrite-sonic/source/SonicRightHand.obj");
	SonicRightThumb = Model();
	SonicRightThumb.LoadModel("Models/rewrite-sonic/source/SonicRightThumb.obj");
	SonicRightIndex = Model();
	SonicRightIndex.LoadModel("Models/rewrite-sonic/source/SonicRightIndex.obj");
	SonicRightMiddle = Model();
	SonicRightMiddle.LoadModel("Models/rewrite-sonic/source/SonicRightMiddle.obj");
	SonicRightRing = Model();
	SonicRightRing.LoadModel("Models/rewrite-sonic/source/SonicRightRing.obj");
	SonicRightPinky = Model();
	SonicRightPinky.LoadModel("Models/rewrite-sonic/source/SonicRightPinky.obj");
	SonicRightKnee = Model();
	SonicRightKnee.LoadModel("Models/rewrite-sonic/source/SonicRightKnee.obj");
	SonicRightLeg = Model();
	SonicRightLeg.LoadModel("Models/rewrite-sonic/source/SonicRightLeg.obj");
	SonicLeftArm = Model();
	SonicLeftArm.LoadModel("Models/rewrite-sonic/source/SonicLeftArm.obj");
	SonicLeftElbow = Model();
	SonicLeftElbow.LoadModel("Models/rewrite-sonic/source/SonicLeftElbow.obj");
	SonicLeftHand = Model();
	SonicLeftHand.LoadModel("Models/rewrite-sonic/source/SonicLeftHand.obj");
	SonicLeftThumb = Model();
	SonicLeftThumb.LoadModel("Models/rewrite-sonic/source/SonicLeftThumb.obj");
	SonicLeftIndex = Model();
	SonicLeftIndex.LoadModel("Models/rewrite-sonic/source/SonicLeftIndex.obj");
	SonicLeftMiddle = Model();
	SonicLeftMiddle.LoadModel("Models/rewrite-sonic/source/SonicLeftMiddle.obj");
	SonicLeftRing = Model();
	SonicLeftRing.LoadModel("Models/rewrite-sonic/source/SonicLeftRing.obj");
	SonicLeftPinky = Model();
	SonicLeftPinky.LoadModel("Models/rewrite-sonic/source/SonicLeftPinky.obj");
	SonicLeftKnee = Model();
	SonicLeftKnee.LoadModel("Models/rewrite-sonic/source/SonicLeftKnee.obj");
	SonicLeftLeg = Model();
	SonicLeftLeg.LoadModel("Models/rewrite-sonic/source/SonicLeftLeg.obj");

	// MODELOS: Elementos 
	LampPostLower = Model();
	LampPostLower.LoadModel("Models/LampPostBody.obj");
	LampPostUpper = Model();
	LampPostUpper.LoadModel("Models/LampPostPole.obj");


	std::vector<std::string> skyboxFacesDay, skyboxFacesNight;
	
	skyboxFacesDay.push_back("Textures/Skybox/DayTime_Skybox_right_converted.tga");
	skyboxFacesDay.push_back("Textures/Skybox/DayTime_Skybox_left_converted.tga");
	skyboxFacesDay.push_back("Textures/Skybox/DayTime_Skybox_bottom_converted.tga");
	skyboxFacesDay.push_back("Textures/Skybox/DayTime_Skybox_top_converted.tga");
	skyboxFacesDay.push_back("Textures/Skybox/DayTime_Skybox_back_converted.tga");
	skyboxFacesDay.push_back("Textures/Skybox/DayTime_Skybox_front_converted.tga");
	
	/*
	skyboxFacesDay.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFacesDay.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFacesDay.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFacesDay.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFacesDay.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFacesDay.push_back("Textures/Skybox/cupertin-lake_ft.tga");
	*/
	

	
	skyboxFacesNight.push_back("Textures/Skybox/NightTime_Skybox_left_converted.tga");
	skyboxFacesNight.push_back("Textures/Skybox/NightTime_Skybox_right_converted.tga");
	skyboxFacesNight.push_back("Textures/Skybox/NightTime_Skybox_bottom_converted.tga");
	skyboxFacesNight.push_back("Textures/Skybox/NightTime_Skybox_top_converted.tga");
	skyboxFacesNight.push_back("Textures/Skybox/NightTime_Skybox_back_converted.tga");
	skyboxFacesNight.push_back("Textures/Skybox/NightTime_Skybox_front_converted.tga");
	/*
	skyboxFacesNight.push_back("Textures/Skybox/cupertin-lake-night_rt.tga");
	skyboxFacesNight.push_back("Textures/Skybox/cupertin-lake-night_lf.tga");
	skyboxFacesNight.push_back("Textures/Skybox/cupertin-lake-night_dn.tga");
	skyboxFacesNight.push_back("Textures/Skybox/cupertin-lake-night_up.tga");
	skyboxFacesNight.push_back("Textures/Skybox/cupertin-lake-night_bk.tga");
	skyboxFacesNight.push_back("Textures/Skybox/cupertin-lake-night_ft.tga");
	*/
	skybox_day = Skybox(skyboxFacesDay);
	skybox_night = Skybox(skyboxFacesNight);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 0.75f,
		0.1f, 1.5f,
		0.0f, -1.0f, 0.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		-6.0f, 1.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	// luz de la lampara
	pointLights[1] = PointLight(0.75f, 0.8f, 1.0f,
		5.0f, 0.1f,
		20.5f, 8.0f, 7.0f,
		1.0f, 0.3f, 0.02f
	);
	pointLightCount++;

	
	unsigned int spotLightCount = 0;
	/*
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;
	*/
	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		// Se activa una sola cámara.
		// También se introduce una guardia para el tipo de cámara, para poder cambiar la posición una sola vez.
		// Cámara 1: Moverse en el plano XZ en tercera persona
		// TODO: Implementar movimiento del personaje.
		if (mainWindow.getCamType() == 1) {
			if (cam1 == 0) {
				cam1 = 1;
			}
			xChange = mainWindow.getXChange();
			sonicVista += xChange * 0.5f;
			sonicFrente = glm::vec3(cos(sonicVista * toRadians), 0.0f, sin(sonicVista * toRadians));
			sonicFrente = glm::normalize(sonicFrente);

			sonicDerecha = glm::normalize(glm::cross(sonicFrente, glm::vec3(0.0f, 1.0f, 0.0f)));

			sonicSpeed = 0.5f * deltaTime;

			keys = mainWindow.getsKeys();
			if (keys[GLFW_KEY_W]) posicionSonic += sonicFrente * sonicSpeed;
			if (keys[GLFW_KEY_S]) posicionSonic -= sonicFrente * sonicSpeed;
			if (keys[GLFW_KEY_A]) posicionSonic -= sonicDerecha * sonicSpeed;
			if (keys[GLFW_KEY_D]) posicionSonic += sonicDerecha * sonicSpeed;

			posicionCamara = posicionSonic - sonicFrente * camaraAtras + glm::vec3(0.0f, camaraArriba, 0.0f);
			camera.setCameraPosition(posicionCamara);
			camera.setFront(glm::normalize(posicionSonic - posicionCamara));

			anguloSonic = atan2(sonicFrente.x, sonicFrente.z);
			cam2 = 0;
			cam3 = 0;
			camDebug = 0;
			/* funcionaba como debug.
			printf("FRONT ACTUAL: ");
			printf("%f %f %f", camera.getFront().x, camera.getFront().y, camera.getFront().z);
			printf("\n");
			*/
		}
		// Cámara que mira desde arriba.
		else if (mainWindow.getCamType() == 2) {
			if (cam2 == 0) {
				camera.setCameraPosition(glm::vec3(0.0f, 70.0f, 0.0f));
				camera.setFront(glm::vec3(0.0f, -1.0f, 0.00001f));
				camera.setRight(glm::vec3(0.0f, 0.0f, 1.0f));
				camera.setUp(glm::vec3(1.0f, 0.0f, 0.0f));
				cam2 = 1;
			}
			camera.keyControlViewAbove(mainWindow.getsKeys(), deltaTime);
			cam1 = 0;
			cam3 = 0;
			camDebug = 0;
		}
		else if (mainWindow.getCamType() == 3) {
			// Muestra de elemento de escenario con SET.
		}
		else if (mainWindow.getCamType() == 4) {
			// Muestra de elemento de escenario con SET.
		}
		else if (mainWindow.getCamType() == 5) {
			// Muestra de elemento de escenario con SET.
		}
		// Podemos implementar más sin problemas.

		// Cámara de debug, las demás cámaras son fáciles pues solo es un set. 
		else if (mainWindow.getCamType() == 0) {
			if (camDebug == 0) {
				camDebug = 1;
			}
			camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
			camera.keyControl(mainWindow.getsKeys(), deltaTime);
			cam1 = 0;
			cam2 = 0;
			cam3 = 0;
		}
		

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (mainWindow.getDayNight() == 0) {
			skybox_day.DrawSkybox(camera.calculateViewMatrix(), projection);
			mainLight.changeLight(1.0f, 0.875f, 0.8f);
		}else 
		{
			skybox_night.DrawSkybox(camera.calculateViewMatrix(), projection);
			mainLight.changeLight(0.800f, 0.5f, 0.965f);
		}

		
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());
		//spotLights[1].SetPos(poscoche + glm::vec(x, y, cofre));

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//Instancia del coche 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex(), 0.5f, -3.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Kitt_M.RenderModel();

		//Llanta delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(7.0f, -0.5f, 8.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		color = glm::vec3(0.5f, 0.5f, 0.5f);//llanta con color gris
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.5f, -0.5f, 8.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(7.0f, -0.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.5f, -0.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 6.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, 5.0f, 6.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		meshList[4]->RenderMesh();

		// SONIC
		model = glm::mat4(1.0);
		model = glm::translate(model, posicionSonic);
		model = glm::rotate(model, anguloSonic, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Sonic_Body.RenderModel();

		// SONIC: CABEZA
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Sonic_Head.RenderModel();
		model = modelaux;

		// SONIC: CODO IZQUIERDO Y ARTICULACIÓN
		model = glm::translate(model, glm::vec3(0.35f, 0.2f, 0.0f));
		model = glm::rotate(model, -40.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, leftShoulderArt * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));


		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SonicLeftElbow.RenderModel();

		// SONIC: BRAZO IZQUIERDO Y ARTICULACION
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::rotate(model, leftArmArt * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SonicLeftArm.RenderModel();

		// SONIC: MANO IZQUIERDA
		model = glm::translate(model, glm::vec3(1.3f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SonicLeftHand.RenderModel();

		// SONIC: RODILLA IZQUIERDA
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.32f, -0.3f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SonicLeftKnee.RenderModel();

		// SONIC: PIERNA IZQUIERDA
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SonicLeftLeg.RenderModel();
		

		// SONIC: CODO DERECHO Y ARTICULACIÓN
		model = modelaux;

		model = glm::translate(model, glm::vec3(-0.5f, 0.1f, 0.0f));
		model = glm::rotate(model, 40.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, rightShoulderArt * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));


		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SonicRightElbow.RenderModel();

		// SONIC: BRAZO DERECHO Y ARTICULACION
		model = glm::translate(model, glm::vec3(-0.75f, 0.0f, 0.0f));
		model = glm::rotate(model, rightArmArt * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SonicRightArm.RenderModel();

		// SONIC: MANO DERECHA
		model = glm::translate(model, glm::vec3(-0.7f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SonicRightHand.RenderModel();

		// SONIC: RODILLA DERECHA
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.32f, -0.3f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SonicLeftKnee.RenderModel();

		// SONIC: PIERNA DERECHA
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SonicLeftLeg.RenderModel();


		// programación del faro
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.5f, -0.75f, 7.0f));
		model = glm::scale(model, glm::vec3(0.5f + postScaleX, 0.5f + postScaleY, 0.5f + postScaleZ));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LampPostLower.RenderModel();
		//model = modelaux;

		//lámpara del paro
		model = glm::translate(model, glm::vec3(-0.3f, 7.3f, 0.6f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, postSpin * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LampPostUpper.RenderModel();
		model = modelaux;

		//Agave ¿qué sucede si lo renderizan antes del coche y el helicóptero?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);

		if (mainWindow.getMoveLampPost() == 1) {
			
			spinTimer += 1.0f;

			if (spinTimer < 360) {
				postScaleX += 0.0002f;
				postScaleY -= 0.0004f;
				postScaleZ += 0.0002f;
			}

			if (spinTimer > 360 && spinTimer < 1440) {
				if (postScaleX > 0) {
					postScaleX -= 0.002f;
				}
				if (postScaleY < 0) {
					postScaleY += 0.004f;
				}
				if (postScaleZ > 0) {
					postScaleZ -= 0.002f;
				}

				if (spinTimer > 396 && spinTimer < 480) {
					postScaleX -= 0.003f;
					postScaleY += 0.006f;
					postScaleZ -= 0.003f;
				}

				if (spinTimer > 480 && spinTimer < 600) {
					postScaleX += 0.003f;
					postScaleY -= 0.006f;
					postScaleZ += 0.003f;
				}

				postSpin += 2.0f;
				spinLightX = 1.75f * -sin(1 * postSpin * toRadians);
				spinLightY = 1.75f * cos(1 * postSpin * toRadians) - 1.75f;
				pointLights[1].updatePosition(glm::vec3(20.5f + spinLightX, 8.0f + spinLightY, 7.0f));
				
				
			}
			

			/*
			// Bloque para hacer debugging
			spinTimer += 0.0f;
			postSpin += 0.0f;
			spinLightX = 1.75f * -sin(1 * spinTimer * toRadians);
			spinLightY = 1.75f * cos(1 * spinTimer * toRadians) - 1.75f;
			pointLights[1].updatePosition(glm::vec3(20.5f + spinLightX, 8.0f + spinLightY, 7.0f));
			*/
			
			if (spinTimer == 1440) {
				mainWindow.setMoveLampPost(0);
				spinTimer = 0;
				pointLights[1].updatePosition(glm::vec3(20.5f, 8.0f, 7.0f));
				postSpin = 0;
				postScaleX = postScaleY = postScaleZ = 0;
			}
			
		}

		// cambia la luz cada 2 minutos
		mainLight.setDirection(glm::vec3(moveDirectionalX,moveDirectionalY,0.0f));
		if (dirTimer == 36000 && mainWindow.getDayNight() == 0) {
			skybox_night.DrawSkybox(camera.calculateViewMatrix(), projection);
			mainLight.changeLight(1.0f, 0.875f, 0.8f);
			mainWindow.setDayNight(1);
			dirTimer = 0;
		}
		else if (dirTimer == 360 && mainWindow.getDayNight() == 1) {
			skybox_night.DrawSkybox(camera.calculateViewMatrix(), projection);
			mainLight.changeLight(0.800f, 0.5f, 0.965f);
			mainWindow.setDayNight(0);
			dirTimer = 0;
		}

		// define hacia dónde se mueve la luz dependiendo de si es de noche o de día
		if (mainWindow.getDayNight() == 0) {
			dirTimer += 1.0f;
		}
		else {
			dirTimer -= 1.0f;
		}
		moveDirectionalX = cos(0.0001f*dirTimer);
		moveDirectionalY = -sin(0.0001f* dirTimer);


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
