/*
Práctica 7: Iluminación 1 
Pr�ctica 7: Iluminaci�n 1 
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
//para iluminaci�n
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
Model SonicRightKnee;
Model SonicRightLeg;
Model SonicLeftArm;
Model SonicLeftElbow;
Model SonicLeftHand;
Model SonicLeftKnee;
Model SonicLeftLeg;

Model LampPostUpper, LampPostLower;
Model Balloon_Gift;
Model Balloon_Gift_Propeller1;
Model Balloon_Gift_Propeller2;
Model White_Rabbit;
Model White_RabbitClock;
Model White_RabbitRight;
Model White_RabbitHead;
Model SteamPunkBooth;
Model SteamPunkClock;
Model SteamPunkHammer;
Model SteamPunkChair;
Model SteamPunkCars;
Model SteamPunkRobot;
// Brazo derecho e izquierdo est�n al rev�s xddddd
Model SteamPunkRobotRightArm;
Model SteamPunkRobotRightForeArm;
Model SteamPunkRobotLeftArm;
Model SteamPunkRobotLeftForeArm;
Model SteamPunkRobotCannon;
Model SteamPunkRobotLeftLeg;
Model SteamPunkRobotRightLeg;
Model AstroGun;


Model ChaosEmeraldG;
Model ChaosEmeraldR;
Model ChaosEmeraldM;
Model ChaosEmeraldB;
Model ChaosEmeraldGrey;
Model ChaosEmeraldY;
Model ChaosEmeraldC;
Model Spring;
Model ChaoKey;
Model GoalRing;

Model Fountain;
Model Tree1, Tree2, Tree3;
Model Bench;

Model Emil_Body;
Model Emil_Head;
Model Emil_Coat0;
Model Emil_Coat1;
Model Emil_Weapon;
Model Emil_Left_Leg0;
Model Emil_Left_Leg1;
Model Emil_Right_Leg0;
Model Emil_Right_Leg1;
Model Emil_Left_Arm0;
Model Emil_Left_Arm1;
Model Emil_Right_Arm0;
Model Emil_Right_Arm1;
Model Emil_Left_Hand;
Model Emil_Right_Hand;
Model Emil_Left_Foot;
Model Emil_Right_Foot;



Model CheshireCat_Body;
Model CheshireCat_Tail;
Model CheshireCat_Head;
Model CheshireCat_Right_Arm;
Model CheshireCat_Right_Leg;
Model CheshireCat_Left_Arm;
Model CheshireCat_Left_Leg;

Model StreetLight1;
Model StreetLight2;

Skybox skybox_day;
Skybox skybox_night;

//materiales
Material Material_brillante;
Material Material_opaco;
Material MaterialMuyBrillante;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
// animación de la lámpara (Sonic)
// animaci�n de la l�mpara (Sonic)
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

// movimiento de la c�mara con Sonic
glm::vec3 posicionSonic = glm::vec3(70.0f, 3.0f, -65.0f);
GLfloat xChange = 0.0f;
GLfloat sonicVista = 0.0f;
glm::vec3 sonicFrente;
glm::vec3 sonicDerecha;
GLfloat sonicSpeed = 0.0f; // mil pesos a que el profe no entiende la referencia
GLfloat camaraAtras = 30.0f;
GLfloat camaraArriba = 5.0f;
glm::vec3 posicionCamara;
GLfloat anguloSonic;
GLfloat walkCycle;
GLfloat dondeReset = 0.0f;
GLfloat diferenciaCycle = 0.0f;

// detección de llaves
// detecci�n de llaves
bool* keys;

// articulaciones de Sonic
GLfloat leftShoulderArt = 0.0f;
GLfloat leftArmArt = 0.0f;
GLfloat leftLegMove = 0.0f;
GLfloat leftKneeBend = 0.0f;
GLfloat rightShoulderArt = 0.0f;
GLfloat rightArmArt = 0.0f;
GLfloat rightLegMove = 0.0f;
GLfloat rightKneeBend = 0.0f;
GLfloat chestMove = 0.0f;
GLfloat headBob = 0.0f;
static double limitFPS = 1.0 / 60.0;

// WHITE RABBIT: Movimiento
GLfloat whiteRabbitHeadBob = 0.0f;

// BALLOON GIFT: Movimiento
GLfloat lemniscateTimer = 0.0f;
const GLfloat a = 3.0f;
GLfloat lemniscate_X = 0.0f, lemniscate_Y = 0.0f;
GLfloat helixSpin = 0.0f;

// Steampunk Clock
GLfloat SteamPunkClockFloat = 0.0f;

// Chaos Emeralds
GLfloat chaosEmeraldsComplex;

// Movimiento Carro Steampunk
GLfloat carroX = 0.0f;
GLfloat carroY = 0.0f;
GLfloat carroZ = -15.0f;
GLfloat carroScaleX = 0.0f;
GLfloat carroScaleY = 0.0f;
GLfloat carroScaleZ = 0.0f;
GLfloat carroRotate = -90.0f;
GLfloat steamPunkTimer = 0.0f;

// articulaciones de Emil
GLfloat emilShoulderRight = 70.0f;
GLfloat emilShoulderLeft = -70.0f;

// articulaciones de Cheshire Cat
GLfloat cheshireShoulderRight = 70.0f;
GLfloat cheshireShoulderLeft = -70.0f;

// articulaciones y tiempos de robot
GLfloat robotRightShoulderArt = 0.0f;
GLfloat robotRightArmArt = 0.0f;
GLfloat robotLeftShoulderArt = 0.0f;
GLfloat robotLeftArmArt = 0.0f;
GLfloat robotLeftCannonArt = 0.0f;
GLfloat robotTimer = 0.0f;
GLfloat robotForward = 0.0f;
GLfloat robotLeftLegArt = 0.0f;
GLfloat robotRightLegArt = 0.0f;
GLfloat robotSpin = 0.0f;


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
//funci�n de calculo de normales por promedio de v�rtices 
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
	pisoTexture = Texture("Textures/tiledFloor.tga");
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
	SonicLeftKnee = Model();
	SonicLeftKnee.LoadModel("Models/rewrite-sonic/source/SonicLeftKnee.obj");
	SonicLeftLeg = Model();
	SonicLeftLeg.LoadModel("Models/rewrite-sonic/source/SonicLeftLeg.obj");

	// Emil
	Emil_Body = Model();
	Emil_Body.LoadModel("Models/emil/body.obj");
	Emil_Head = Model();
	Emil_Head.LoadModel("Models/emil/head.obj");
	Emil_Coat0 = Model();
	Emil_Coat0.LoadModel("Models/emil/coat_0.obj");
	Emil_Coat1 = Model();
	Emil_Coat1.LoadModel("Models/emil/coat_1.obj");
	Emil_Weapon = Model();
	Emil_Weapon.LoadModel("Models/emil/weapon.obj");
	Emil_Left_Leg0 = Model();
	Emil_Left_Leg0.LoadModel("Models/emil/left_leg_0.obj");
	Emil_Left_Leg1 = Model();
	Emil_Left_Leg1.LoadModel("Models/emil/left_leg_1.obj");
	Emil_Right_Leg0 = Model();
	Emil_Right_Leg0.LoadModel("Models/emil/right_leg_0.obj");
	Emil_Right_Leg1 = Model();
	Emil_Right_Leg1.LoadModel("Models/emil/right_leg_1.obj");
	Emil_Left_Arm0 = Model();
	Emil_Left_Arm0.LoadModel("Models/emil/left_arm_0.obj");
	Emil_Left_Arm1 = Model();
	Emil_Left_Arm1.LoadModel("Models/emil/left_arm_1.obj");
	Emil_Right_Arm0 = Model();
	Emil_Right_Arm0.LoadModel("Models/emil/right_arm_0.obj");
	Emil_Right_Arm1 = Model();
	Emil_Right_Arm1.LoadModel("Models/emil/right_arm_1.obj");
	Emil_Left_Hand = Model();
	Emil_Left_Hand.LoadModel("Models/emil/left_hand.obj");
	Emil_Right_Hand = Model();
	Emil_Right_Hand.LoadModel("Models/emil/right_hand.obj");
	Emil_Left_Foot = Model();
	Emil_Left_Foot.LoadModel("Models/emil/left_foot.obj");
	Emil_Right_Foot = Model();
	Emil_Right_Foot.LoadModel("Models/emil/right_foot.obj");

	// Cheshire Cat
	CheshireCat_Body = Model();
	CheshireCat_Body.LoadModel("Models/cheshire-cat/body.obj");
	CheshireCat_Tail = Model();
	CheshireCat_Tail.LoadModel("Models/cheshire-cat/tail.obj");
	CheshireCat_Head = Model();
	CheshireCat_Head.LoadModel("Models/cheshire-cat/head.obj");
	CheshireCat_Right_Arm = Model();
	CheshireCat_Right_Arm.LoadModel("Models/cheshire-cat/right_arm.obj");
	CheshireCat_Right_Leg = Model();
	CheshireCat_Right_Leg.LoadModel("Models/cheshire-cat/right_leg.obj");
	CheshireCat_Left_Arm = Model();
	CheshireCat_Left_Arm.LoadModel("Models/cheshire-cat/left_arm.obj");
	CheshireCat_Left_Leg = Model();
	CheshireCat_Left_Leg.LoadModel("Models/cheshire-cat/left_leg.obj");

	

	// MODELOS: Elementos 
	LampPostLower = Model();
	LampPostLower.LoadModel("Models/LampPostBody.obj");
	LampPostUpper = Model();
	LampPostUpper.LoadModel("Models/LampPostPole.obj");
	Balloon_Gift = Model();
	Balloon_Gift.LoadModel("Models/peachy-balloon-gift/BalloonGift.obj");
	Balloon_Gift_Propeller1 = Model();
	Balloon_Gift_Propeller1.LoadModel("Models/peachy-balloon-gift/Helix1.obj");
	Balloon_Gift_Propeller2 = Model();
	Balloon_Gift_Propeller2.LoadModel("Models/peachy-balloon-gift/Helix2.obj");
	SteamPunkBooth = Model();
	SteamPunkBooth.LoadModel("Models/SteamPunkBooth.obj");
	SteamPunkClock = Model();
	SteamPunkClock.LoadModel("Models/SteamPunkClock.obj");
	SteamPunkHammer = Model();
	SteamPunkHammer.LoadModel("Models/SteamPunkHammer.obj");
	SteamPunkChair = Model();
	SteamPunkChair.LoadModel("Models/SteamPunkChair.obj");
	SteamPunkCars = Model();
	SteamPunkCars.LoadModel("Models/SteamPunkCar.obj");
	SteamPunkRobot = Model();
	SteamPunkRobot.LoadModel("Models/SteamPunkRobot.obj");
	SteamPunkRobotRightArm = Model(); 
	SteamPunkRobotRightArm.LoadModel("Models/SteamPunkRobotLeftArm.obj");
	SteamPunkRobotRightForeArm = Model();
	SteamPunkRobotRightForeArm.LoadModel("Models/SteamPunkRobotLeftForeArm.obj");
	SteamPunkRobotLeftArm = Model();
	SteamPunkRobotLeftArm.LoadModel("Models/SteamPunkRobotRightArm.obj");
	SteamPunkRobotLeftForeArm = Model();
	SteamPunkRobotLeftForeArm.LoadModel("Models/SteamPunkRobotRightForeArm.obj");
	SteamPunkRobotCannon = Model();
	SteamPunkRobotCannon.LoadModel("Models/SteamPunkRobotRightCannon.obj");
	SteamPunkRobotLeftLeg = Model();
	SteamPunkRobotLeftLeg.LoadModel("Models/SteamPunkRobotLeftLeg.obj");
	SteamPunkRobotRightLeg = Model();
	SteamPunkRobotRightLeg.LoadModel("Models/SteamPunkRobotRightLeg.obj");

	ChaosEmeraldG = Model();
	ChaosEmeraldG.LoadModel("Models/source/GreenChaosEmerald.obj");
	ChaosEmeraldY = Model();
	ChaosEmeraldY.LoadModel("Models/source/YellowChaosEmerald.obj");
	ChaosEmeraldGrey = Model();
	ChaosEmeraldGrey.LoadModel("Models/source/GreyChaosEmerald.obj");
	ChaosEmeraldR = Model();
	ChaosEmeraldR.LoadModel("Models/source/RedChaosEmerald.obj");
	ChaosEmeraldB = Model();
	ChaosEmeraldB.LoadModel("Models/source/BlueChaosEmerald.obj");
	ChaosEmeraldM = Model();
	ChaosEmeraldM.LoadModel("Models/source/MagentaChaosEmerald.obj");
	ChaosEmeraldC = Model();
	ChaosEmeraldC.LoadModel("Models/source/CyanChaosEmerald.obj");
	ChaoKey = Model();
	ChaoKey.LoadModel("Models/ChaoKey.obj");
	Spring = Model();
	Spring.LoadModel("Models/source/Spring/Spring.obj");
	GoalRing = Model();
	GoalRing.LoadModel("Models/source/Goal Ring/Goal Ring.obj");

	Tree1 = Model();
	Tree1.LoadModel("Models/Tree1.obj");
	Tree2 = Model();
	Tree2.LoadModel("Models/Tree2.obj");
	Tree3 = Model();
	Tree3.LoadModel("Models/Tree3.obj");
	Fountain = Model();
	Fountain.LoadModel("Models/Fountain.obj");
	Bench = Model();
	Bench.LoadModel("Models/Bench.obj");

	AstroGun = Model();
	AstroGun.LoadModel("Models/astrogun.obj");

	StreetLight1 = Model();
	StreetLight1.LoadModel("Models/StreetLight1.obj");
	

	// NPCs
	White_Rabbit = Model();
	White_Rabbit.LoadModel("Models/play-station-2-kingdom-hearts-white-rabbit/source/WhiteRabbitBody.obj");
	White_RabbitHead = Model();
	White_RabbitHead.LoadModel("Models/play-station-2-kingdom-hearts-white-rabbit/source/WhiteRabbitHead.obj");
	White_RabbitClock = Model();
	White_RabbitClock.LoadModel("Models/play-station-2-kingdom-hearts-white-rabbit/source/WhiteRabbitClockArm.obj");
	White_RabbitRight = Model();
	White_RabbitRight.LoadModel("Models/play-station-2-kingdom-hearts-white-rabbit/source/WhiteRabbitRightArm.obj");
	


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
	MaterialMuyBrillante = Material(6.0f, 256);


	//luz direccional, sólo 1 y siempre debe de existir
	//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 0.75f,
		0.1f, 1.5f,
		0.0f, -1.0f, 0.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	//Declaraci�n de primer luz puntual
	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f,
		3.0f, 3.0f,
		25.0f, 7.0f, -60.0f,
		0.1f, 0.4f, 0.004f
	);
	pointLightCount++;

	// luz de la lampara
	pointLights[1] = PointLight(0.75f, 0.8f, 1.0f,
		5.0f, 0.1f,
		90.0f, 8.0f, -70.0f,
		1.0f, 0.3f, 0.02f
	);
	pointLightCount++;

	// luz del anillo
	pointLights[2] = PointLight(1.0f, 1.0f, 0.0f,
		5.0f, 1.0f,
		80.0f, 3.0f, 80.0f,
		1.5f, 0.2f, 0.002f
	);
	pointLightCount++;

	// luz de las chaos Emeralds
	

	
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
		// Se activa una sola c�mara.
		// Tambi�n se introduce una guardia para el tipo de c�mara, para poder cambiar la posici�n una sola vez.
		// C�mara 1: Moverse en el plano XZ en tercera persona
		// TODO: Implementar movimiento del personaje.
		if (mainWindow.getCamType() == 1) {
			if (cam1 == 0) {
				camera.setUp(glm::vec3(0.0f, 1.0f, 0.0f));
				cam1 = 1;
			}
			xChange = mainWindow.getXChange();
			sonicVista += xChange * 0.5f;
			sonicFrente = glm::vec3(cos(sonicVista * toRadians), 0.0f, sin(sonicVista * toRadians));
			sonicFrente = glm::normalize(sonicFrente);

			sonicDerecha = glm::normalize(glm::cross(sonicFrente, glm::vec3(0.0f, 1.0f, 0.0f)));

			sonicSpeed = 0.5f * deltaTime;

			keys = mainWindow.getsKeys();
			if (keys[GLFW_KEY_W] || keys[GLFW_KEY_S] || keys[GLFW_KEY_A] || keys[GLFW_KEY_D]) {
				if (keys[GLFW_KEY_W]) posicionSonic += sonicFrente * sonicSpeed;
				if (keys[GLFW_KEY_S]) posicionSonic -= sonicFrente * sonicSpeed;
				if (keys[GLFW_KEY_A]) posicionSonic -= sonicDerecha * sonicSpeed;
				if (keys[GLFW_KEY_D]) posicionSonic += sonicDerecha * sonicSpeed;
				walkCycle += 0.05f;
				leftShoulderArt = sin(walkCycle) * 30.0f;
				leftArmArt = sin(walkCycle) * 60.0f;
				rightShoulderArt = -sin(walkCycle) * 30.0f;
				rightArmArt = -sin(walkCycle) * 60.0f;
				leftLegMove = sin(walkCycle) * 30.0f;
				leftKneeBend = sin(walkCycle) * 60.0f;
				rightLegMove = -sin(walkCycle) * 30.0f;
				rightKneeBend = -sin(walkCycle) * 60.0f;
				chestMove = sin(walkCycle) * 15.0f;
				headBob = -sin(walkCycle) * 17.5f;
			}
			else {
				dondeReset = round(walkCycle / (float)M_PI) * (float)M_PI;
				diferenciaCycle = dondeReset - walkCycle;

				if (fabs(diferenciaCycle) > 0.02f) {
					walkCycle += (diferenciaCycle > 0 ? 1.0f : -1.0f) * 0.01f;
					leftShoulderArt = sin(walkCycle) * 30.0f;
					leftArmArt = sin(walkCycle) * 60.0f;
					rightShoulderArt = -sin(walkCycle) * 30.0f;
					rightArmArt = -sin(walkCycle) * 60.0f;
					leftLegMove = sin(walkCycle) * 30.0f;
					leftKneeBend = sin(walkCycle) * 60.0f;
					rightLegMove = -sin(walkCycle) * 30.0f;
					rightKneeBend = -sin(walkCycle) * 60.0f;
					chestMove = sin(walkCycle) * 15.0f;
					headBob = -sin(walkCycle) * 17.5f;
				}
				else {
					walkCycle = dondeReset;
					leftShoulderArt = leftArmArt = rightShoulderArt = rightArmArt = 0.0f;
					leftLegMove = leftKneeBend = rightLegMove = rightKneeBend = 0.0f;
				}
			}
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
		// C�mara que mira desde arriba.
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
		// Podemos implementar m�s sin problemas.

		// Cámara de debug, las demás cámaras son fáciles pues solo es un set. 
		// C�mara de debug, las dem�s c�maras son f�ciles pues solo es un set. 
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
		}
		else
		{
			skybox_night.DrawSkybox(camera.calculateViewMatrix(), projection);
			mainLight.changeLight(0.500f, 0.3f, 0.765f);
		}


		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//información en el shader de intensidad especular y brillo
		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		// luz ligada a la c�mara de tipo flash
		//sirve para que en tiempo de ejecuci�n (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());
		//spotLights[1].SetPos(poscoche + glm::vec(x, y, cofre));

		//información al shader de fuentes de iluminación
		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		if (mainWindow.getDayNight() == 1) {
			shaderList[0].SetPointLights(pointLights, pointLightCount);
		}
		else {
			shaderList[0].SetPointLights(pointLights, 0);
		}


		shaderList[0].SetSpotLights(spotLights, spotLightCount);



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(15.0f, 1.0f, 15.0f));
		color = glm::vec3(0.5f, 0.5f, 0.5f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();



		// SONIC
		model = glm::mat4(1.0);
		model = glm::translate(model, posicionSonic);
		model = glm::rotate(model, anguloSonic, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, chestMove * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaterialMuyBrillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Sonic_Body.RenderModel();

		// SONIC: CABEZA
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
		model = glm::rotate(model, headBob * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaterialMuyBrillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Sonic_Head.RenderModel();
		model = modelaux;

		// SONIC: CODO IZQUIERDO Y ARTICULACIÓN
		// SONIC: CODO IZQUIERDO Y ARTICULACI�N
		model = glm::translate(model, glm::vec3(0.35f, 0.2f, 0.0f));
		model = glm::rotate(model, -50.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, leftShoulderArt * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));


		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaterialMuyBrillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		SonicLeftElbow.RenderModel();

		// SONIC: BRAZO IZQUIERDO Y ARTICULACION
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::rotate(model, leftArmArt * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaterialMuyBrillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		SonicLeftArm.RenderModel();

		// SONIC: MANO IZQUIERDA
		model = glm::translate(model, glm::vec3(1.3f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaterialMuyBrillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		SonicLeftHand.RenderModel();

		// SONIC: RODILLA IZQUIERDA
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.32f, -0.3f, 0.0f));
		model = glm::rotate(model, leftLegMove * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaterialMuyBrillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		SonicLeftKnee.RenderModel();

		// SONIC: PIERNA IZQUIERDA
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, 0.0f));
		model = glm::rotate(model, leftKneeBend * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaterialMuyBrillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		SonicLeftLeg.RenderModel();

		model = modelaux;

		// SONIC: CODO DERECHA Y ARTICULACIÓN
		model = glm::rotate(model, -180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.35f, 0.2f, 0.0f));
		model = glm::rotate(model, 105.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, rightShoulderArt * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));


		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaterialMuyBrillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		SonicLeftElbow.RenderModel();

		// SONIC: BRAZO DERECHA Y ARTICULACION
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::rotate(model, rightArmArt * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaterialMuyBrillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		SonicLeftArm.RenderModel();

		// SONIC: MANO DERECHA
		model = glm::translate(model, glm::vec3(1.3f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaterialMuyBrillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		SonicLeftHand.RenderModel();

		// SONIC: RODILLA DERECHA
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.32f, -0.3f, 0.0f));
		model = glm::rotate(model, rightLegMove * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaterialMuyBrillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		SonicLeftKnee.RenderModel();

		// SONIC: PIERNA DERECHA
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, 0.0f));
		model = glm::rotate(model, rightKneeBend * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaterialMuyBrillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		SonicLeftLeg.RenderModel();

		// EMIL
		//body
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, 7.0f, 90.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Body.RenderModel();
		//head
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.29f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Head.RenderModel();
		//coat 0
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.32f - 0.1f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Coat0.RenderModel();
		//coat 1
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Coat1.RenderModel();
		//left_arm
		//arm 0
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.1f, 0.15f, 0.0f));
		model = glm::rotate(model, emilShoulderLeft * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Left_Arm0.RenderModel();
		//arm 1
		model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Left_Arm1.RenderModel();
		//hand
		model = glm::translate(model, glm::vec3(0.23f, 0.0f, -0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Left_Hand.RenderModel();
		//right_arm
		//arm 0
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.1f, 0.15f, 0.0f));
		model = glm::rotate(model, emilShoulderRight * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Right_Arm0.RenderModel();
		//arm 1
		model = glm::translate(model, glm::vec3(-0.25f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Right_Arm1.RenderModel();
		//hand
		model = glm::translate(model, glm::vec3(-0.23f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Right_Hand.RenderModel();
		//weapon
		model = glm::translate(model, glm::vec3(-0.1f, -0.02f, 0.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Weapon.RenderModel();
		//left_leg
		//leg 0
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.08f, -0.21f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Left_Leg0.RenderModel();
		//leg 1
		model = glm::translate(model, glm::vec3(0.01f, -0.34f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Left_Leg1.RenderModel();
		//foot
		model = glm::translate(model, glm::vec3(-0.01f, -0.33f, -0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Left_Foot.RenderModel();
		//right_leg
		//leg 0
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.08f, -0.21f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Right_Leg0.RenderModel();
		//leg 1
		model = glm::translate(model, glm::vec3(-0.01f, -0.34f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Right_Leg1.RenderModel();
		//foot
		model = glm::translate(model, glm::vec3(0.01f, -0.33f, -0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Emil_Right_Foot.RenderModel();

		// Chaos Emeralds
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 7.0f + 2 * sin(chaosEmeraldsComplex) - 5 * sin((2 * chaosEmeraldsComplex) / 3), -60.0f + +2 * cos(chaosEmeraldsComplex) + 5 * cos((2 * chaosEmeraldsComplex) / 3)));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ChaosEmeraldG.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 7.0f + 2 * sin(chaosEmeraldsComplex - 1.0f) - 5 * sin((2 * chaosEmeraldsComplex - 1.0f) / 3), -60.0f + 2 * cos(chaosEmeraldsComplex - 1.0f) + 5 * cos((2 * chaosEmeraldsComplex - 1.0f) / 3)));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ChaosEmeraldB.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 7.0f + 2 * sin(chaosEmeraldsComplex - 2.0f) - 5 * sin((2 * chaosEmeraldsComplex - 2.0f) / 3), -60.0f + 2 * cos(chaosEmeraldsComplex - 2.0f) + 5 * cos((2 * chaosEmeraldsComplex - 2.0f) / 3)));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ChaosEmeraldR.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 7.0f + 2 * sin(chaosEmeraldsComplex - 3.0f) - 5 * sin((2 * chaosEmeraldsComplex - 3.0f) / 3), -60.0f + 2 * cos(chaosEmeraldsComplex - 3.0f) + 5 * cos((2 * chaosEmeraldsComplex - 3.0f) / 3)));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ChaosEmeraldC.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 7.0f + 2 * sin(chaosEmeraldsComplex - 4.0f) - 5 * sin((2 * chaosEmeraldsComplex - 4.0f) / 3), -60.0f + 2 * cos(chaosEmeraldsComplex - 4.0f) + 5 * cos((2 * chaosEmeraldsComplex - 4.0f) / 3)));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ChaosEmeraldY.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 7.0f + 2 * sin(chaosEmeraldsComplex - 5.0f) - 5 * sin((2 * chaosEmeraldsComplex - 5.0f) / 3), -60.0f + 2 * cos(chaosEmeraldsComplex - 5.0f) + 5 * cos((2 * chaosEmeraldsComplex - 5.0f) / 3)));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ChaosEmeraldGrey.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 7.0f + 2 * sin(chaosEmeraldsComplex - 6.0f) - 5 * sin((2 * chaosEmeraldsComplex - 6.0f) / 3), -60.0f + 2 * cos(chaosEmeraldsComplex - 6.0f) + 5 * cos((2 * chaosEmeraldsComplex - 6.0f) / 3)));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ChaosEmeraldM.RenderModel();


		// programaci�n del faro
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(90.0f, -0.75f, -70.0f));
		model = glm::scale(model, glm::vec3(0.5f + postScaleX, 0.5f + postScaleY, 0.5f + postScaleZ));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LampPostLower.RenderModel();
		//model = modelaux;

		//l�mpara del paro
		model = glm::translate(model, glm::vec3(-0.3f, 7.3f, 0.6f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, postSpin * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LampPostUpper.RenderModel();

		// anillo de meta
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, sin(SteamPunkClockFloat) * -2.0f, 80.0f));
		model = glm::rotate(model, SteamPunkClockFloat * 50.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f,0.5f,0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		GoalRing.RenderModel();
		//model = modelaux;


		// Resorte de Sonic
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, -1.0f, -50.0f));
		model = glm::scale(model, glm::vec3(0.0125f, 0.0125f, 0.0125f));
		model = glm::rotate(model, postSpin * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Spring.RenderModel();
		model = modelaux;

		// Balloon Gift
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(90.5f + lemniscate_X, 15.0f + lemniscate_Y, -90.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Balloon_Gift.RenderModel();

		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 7.5f));
		model = glm::rotate(model, helixSpin * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Balloon_Gift_Propeller1.RenderModel();

		model = modelaux;

		model = glm::translate(model, glm::vec3(-0.5f, 0.1f, 7.5f));
		model = glm::rotate(model, -helixSpin * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Balloon_Gift_Propeller2.RenderModel();

		model = modelaux;

		model = glm::translate(model, glm::vec3(1.0f, 0.0f, -7.5f));
		model = glm::rotate(model, -helixSpin * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Balloon_Gift_Propeller1.RenderModel();

		model = modelaux;

		model = glm::translate(model, glm::vec3(-0.5f, 0.1f, -7.5f));
		model = glm::rotate(model, helixSpin * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Balloon_Gift_Propeller2.RenderModel();


		// White Rabbit
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(130.5f, 1.0f, -85.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		White_Rabbit.RenderModel();

		model = glm::translate(model, glm::vec3(0.0f, 29.0f, 0.0f));
		model = glm::rotate(model, sin(whiteRabbitHeadBob * 0.05f) * toRadians * 20, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		White_RabbitHead.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-8.7f, 15.0f, -5.0f));
		model = glm::rotate(model, 60.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 20.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		White_RabbitRight.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(8.7f, 16.0f, -5.0f));
		model = glm::rotate(model, -60.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, -sin(whiteRabbitHeadBob * 0.05f) * toRadians * 30, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -60.0f * toRadians, glm::vec3(1.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		White_RabbitClock.RenderModel();

		// Martillo Steampunk
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, 120.0f));
		model = glm::rotate(model, -85.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SteamPunkHammer.RenderModel();

		// Cabina Steampunk
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 13.0f, -80.0f));
		model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SteamPunkBooth.RenderModel();

		// Reloj Steampunk
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 9.0f + sin(SteamPunkClockFloat * 3.0f), 30.0f));
		model = glm::rotate(model, SteamPunkClockFloat * 100.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SteamPunkClock.RenderModel();

		// Silla Steampunk
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 3.5f, 45.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SteamPunkChair.RenderModel();

		// Carro Steampunk
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + carroX, 3.5f, 0.0f + carroZ));
		model = glm::rotate(model, (carroRotate)*toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f + carroScaleX, 2.0f + carroScaleY, 2.0f + carroScaleZ));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SteamPunkCars.RenderModel();

		// Astrogun
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f, 3.5f, 35.0f));
		model = glm::rotate(model, (carroRotate)*toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AstroGun.RenderModel();

		// Robot Steampunk
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f + robotForward, 11.5f, 70.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, robotSpin * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SteamPunkRobot.RenderModel();
		modelaux = model;

		model = glm::translate(model, glm::vec3(1.67f, 0.5f, 0.0f));
		//model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, robotLeftShoulderArt * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SteamPunkRobotLeftArm.RenderModel();

		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::rotate(model, robotLeftArmArt * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SteamPunkRobotLeftForeArm.RenderModel();

		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::rotate(model, robotLeftCannonArt * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SteamPunkRobotCannon.RenderModel();

		model = modelaux;

		model = glm::translate(model, glm::vec3(-1.67f, 0.5f, 0.0f));
		model = glm::rotate(model, 45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 45.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, robotRightShoulderArt * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SteamPunkRobotRightArm.RenderModel();

		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 22.5f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, robotRightArmArt * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SteamPunkRobotRightForeArm.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.0f, -1.7f, 0.0f));
		model = glm::rotate(model, robotRightLegArt * toRadians, glm::vec3(1.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SteamPunkRobotRightLeg.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(1.0f, -1.7f, 0.0f));
		model = glm::rotate(model, robotLeftLegArt * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SteamPunkRobotLeftLeg.RenderModel();



		// Fuente
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 5.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fountain.RenderModel();

		// �rboles
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, 2.0f, 45.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tree1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, 2.0f, 37.5f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tree2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, 2.0f, 52.5f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tree3.RenderModel();

		// Bancas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, -0.5f, 70.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bench.RenderModel();

		model = glm::translate(model, glm::vec3(0.0f, -0.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bench.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(130.0f, -2.0f, -55.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bench.RenderModel();

		model = glm::translate(model, glm::vec3(2.0f, -0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bench.RenderModel();

		// Arbustos

		// Luces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -2.0f, 55.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		StreetLight1.RenderModel();



		//Cheshire Cat
		//body
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-60.0f, 2.5f, 15.0f));
		model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f,6.0f,6.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CheshireCat_Body.RenderModel();
		//head
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f,0.325f,0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CheshireCat_Head.RenderModel();
		//tail
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f,-0.225f,-0.225f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CheshireCat_Tail.RenderModel();
		//left_arm
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.2f,0.24f,-0.05f));
		model = glm::rotate(model, cheshireShoulderLeft * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CheshireCat_Left_Arm.RenderModel();
		//right_arm
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.2f,0.24f,-0.05f));
		model = glm::rotate(model, cheshireShoulderRight * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CheshireCat_Right_Arm.RenderModel();
		//left_leg
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.15f,-0.28f,-0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CheshireCat_Left_Leg.RenderModel();
		//right_leg
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.15f,-0.28f,-0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CheshireCat_Right_Leg.RenderModel();

		if (mainWindow.getMoveLampPost() == 1) {

			spinTimer += 3.0f;

			if (spinTimer < 360) {
				postScaleX += 0.0006f;
				postScaleY -= 0.0012f;
				postScaleZ += 0.0006f;
			}

			if (spinTimer > 360 && spinTimer < 1440) {
				if (postScaleX > 0) {
					postScaleX -= 0.006f;
				}
				if (postScaleY < 0) {
					postScaleY += 0.012f;
				}
				if (postScaleZ > 0) {
					postScaleZ -= 0.006f;
				}

				if (spinTimer > 396 && spinTimer < 480) {
					postScaleX -= 0.009f;
					postScaleY += 0.018f;
					postScaleZ -= 0.009f;
				}

				if (spinTimer > 480 && spinTimer < 600) {
					postScaleX += 0.009f;
					postScaleY -= 0.018f;
					postScaleZ += 0.009f;
				}

				postSpin += 6.0f;
				spinLightX = 1.75f * -sin(1 * postSpin * toRadians);
				spinLightY = 1.75f * cos(1 * postSpin * toRadians) - 1.75f;
				pointLights[1].updatePosition(glm::vec3(90.0f + spinLightX, 8.0f + spinLightY, -70.0f));


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
				pointLights[1].updatePosition(glm::vec3(90.0f, 8.0f, -70.0f));
				postSpin = 0;
				postScaleX = postScaleY = postScaleZ = 0;
			}

		}

		if (mainWindow.getMoveCar() == 1) {
			steamPunkTimer += 2.0f;
			carroScaleZ = carroScaleX = sin(steamPunkTimer * 0.04f)*0.4;
			carroScaleY = -sin(steamPunkTimer * 0.04f)*0.4;
			carroRotate = steamPunkTimer * 0.57f - 90.0f;
			carroX = -sin(steamPunkTimer * 0.01f) * 15.0f;
			carroY = sin(steamPunkTimer * 0.1f);
			carroZ = -cos(steamPunkTimer * 0.01f) * 15.0f;
			if (steamPunkTimer == 628.0f) {
				mainWindow.setMoveCar(0);
				steamPunkTimer = 0.0f;
				carroScaleZ = carroScaleX = carroScaleY = carroX = carroY = 0.0f;
				carroZ = -15.0f;
				carroRotate = -90.0f;
			}
		}

		if (mainWindow.getRobotMove() == 1) {
			robotTimer += 1.5f;
			if (robotTimer >= 0.0f && robotTimer <= 30.0f) {
				robotLeftShoulderArt -= 4.5f;
			}

			if (robotTimer >= 30.0f && robotTimer <= 780.0f) {
				robotRightShoulderArt = sin((robotTimer - 60.0f) *0.03f) * 50.0f;
				robotForward -= 0.1f;
				robotLeftLegArt = sin((robotTimer - 30.0f) *0.03) * 50.0f;
				robotRightLegArt = -sin((robotTimer - 30.0f) *0.03) * 50.0f;
			}

			if (robotTimer >= 780.0f && robotTimer <= 810.0f) {
				robotLeftShoulderArt += 4.5f;
				robotSpin += 9.0f;
			}

			if (robotTimer >= 810.0f && robotTimer <= 1560.0f) {
				robotRightShoulderArt = sin(robotTimer * 0.03f) * 50.0f;
				robotForward += 0.1f;
				robotLeftLegArt = sin((robotTimer - 60.0f) * 0.03) * 50.0f;
				robotRightLegArt = -sin((robotTimer - 60.0f) * 0.03) * 50.0f;
			}

			if (robotTimer >= 1560.0f && robotTimer <= 1590.0f) {
				robotSpin += 9.0f;
			}

			if (robotTimer >= 1590.0f) {
				robotTimer = 0;
				robotRightShoulderArt = robotForward = robotLeftLegArt = robotRightLegArt = 0.0f;
				robotSpin = leftShoulderArt = 0.0f;
				mainWindow.setRobotMove(0);
			}
		}

		// cambia la luz cada cierto tiempo
		mainLight.setDirection(glm::vec3(moveDirectionalX, moveDirectionalY, 0.0f));
		if (dirTimer >= 31000 && mainWindow.getDayNight() == 0) {
			mainWindow.setDayNight(1);
			dirTimer = 0.0f;
		}
		else if (dirTimer >= 31000 && mainWindow.getDayNight() == 1) {
			mainWindow.setDayNight(0);
			dirTimer = 0.0f;
		}

		// define la dirección de la luz
		dirTimer += 1.5f;
		moveDirectionalX = cos(0.0001f * dirTimer);
		moveDirectionalY = -abs(sin(0.0001f * dirTimer));
		// define la dirección de la luz
		dirTimer += 1.5f;
		moveDirectionalX = cos(0.0001f * dirTimer);
		moveDirectionalY = -abs(sin(0.0001f * dirTimer));
		// define hacia d�nde se mueve la luz dependiendo de si es de noche o de d�a
		if (mainWindow.getDayNight() == 0) {
			dirTimer += 1.0f;
		}
		else {
			dirTimer -= 1.0f;
		}
		moveDirectionalX = cos(0.0001f*dirTimer);
		moveDirectionalY = -sin(0.0001f* dirTimer);

		// contadores
		// White Rabbit
		whiteRabbitHeadBob += 0.5f;

		// Chaos Emeralds
		chaosEmeraldsComplex += 0.05f;

		// Reloj Steampunk
		SteamPunkClockFloat += 0.01f;

		// Balloon Gift
		lemniscateTimer += 0.009f;
		lemniscate_X = ((a*sqrt(2)*cos(lemniscateTimer))/1+pow(sin(lemniscateTimer), 2));
		lemniscate_Y = ((a * sqrt(2) * cos(lemniscateTimer)*sin(lemniscateTimer)) / 1 + pow(sin(lemniscateTimer), 2));
		helixSpin += 4.0f;


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
