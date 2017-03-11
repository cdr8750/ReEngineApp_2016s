#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\Walleye.bto", "Walleye");

	fDuration = 1.0f;
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	float fTimer;

	//print information
	m_pMeshMngr->PrintLine("");

	//Timer
	static DWORD timerSinceBoot = GetTickCount();
	DWORD timerSinceStart = GetTickCount() - timerSinceBoot;
	fTimer = timerSinceStart / (float)1000;
	m_pMeshMngr->PrintLine(std::to_string(fTimer));

	//Array of points to cycle through
	vector3 points[] = {vector3(-4.0f, -2.0f, 5.0f),
					vector3(1.0f, -2.0f, 5.0f),
					vector3(-3.0f, -1.0f, 3.0f),
					vector3(2.0f, -1.0f, 3.0f),
					vector3(-2.0f, 0.0f, 0.0f),
					vector3(3.0f, 0.0f, 0.0f),
					vector3(-1.0f, 1.0f, -3.0f),
					vector3(4.0f, 1.0f, -3.0f),
					vector3(0.0f, 2.0f, -5.0f),
					vector3(5.0f, 2.0f, -5.0f),
					vector3(1.0f, 3.0f, -5.0f)};

	//Creates red spheres to mark points
	for (int i = 0; i < 10; i++) {
		matrix4 m4SpherePosition = glm::translate(points[i]) * glm::scale(vector3(0.1));
		m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, RERED, WIRE);
	};

	//Index for points that the models is at and will travel to
	static int currentPosition = 0;
	static int futurePosition = 1;

	//Vector 3 points for model movement
	vector3 v3Start = points[currentPosition];
	vector3 v3End = points[futurePosition];

	//Finds percentage for LERP calculation and creates LERP vector for translation
	float percentage = MapValue(fTimer, 0.0f, 3.0f, 0.0f, 1.0f);
	vector3 current = glm::lerp(v3Start, v3End, percentage);

	//Moves model using LERP vector
	matrix4 m4Mover = glm::translate(current);
	m_pMeshMngr->SetModelMatrix(m4Mover, "Walleye");

	//Changes indexes and resets timer when a point is reached
	if (current == v3End) {
		currentPosition++;
		futurePosition++;
		if (futurePosition >= 10) {
			futurePosition = 0;
		};
		if (currentPosition >= 10) {
			currentPosition = 0;
		};
		timerSinceBoot = GetTickCount();
	};
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}