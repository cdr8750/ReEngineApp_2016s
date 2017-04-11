#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion
#pragma region FEEL FREE TO USE THIS CLOCK
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 
#pragma endregion
#pragma region YOUR CODE GOES HERE
	m_m4Steve = glm::mat4(1.0f); // same as m_m4Steve = IDENTITY_M4; setting the identity to steve

	static bool state = true;
	static double start = 0.0;
	float fTimer = MapValue((dTotalTime - start), 0.0, 5.0, 0.0, 1.0);
	float xv;
	float angle = glm::lerp(0.0f, 359.9f, fTimer);

	if (state) {
		xv = glm::lerp(0.0f, 4.0f, fTimer);
	}
	else {
		xv = 4.0f - glm::lerp(0.0f, 4.0f, fTimer);
	}
	glm::mat4 transMat = glm::mat4(glm::translate(0.0f,xv,0.0f));
	glm::mat4 rotMat = glm::mat4(glm::rotate(IDENTITY_M4, angle, vector3(0.0,0.0,1.0)));

	if (fTimer >= 1.0) {
		start = dTotalTime;
		state = !state;
	}

	m_m4Steve = rotMat * transMat;
#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds:");
	m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}
