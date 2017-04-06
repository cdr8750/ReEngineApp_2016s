#include "AppClass.h"
#include "Camera.h"
#include "iostream"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("A08_Camera_Class"); // Window Name
}
void AppClass::InitVariables(void)
{
	ArcBall();

	//Generate the Cone
	m_pCone = new PrimitiveClass();
	m_pCone->GenerateCone(100.0f, 100.0f, 10, RERED);

	m_pPlane = new PrimitiveClass();
	m_pPlane->GeneratePlane(10000.0f, REBLUE);

	//Generate the Cylinder
	m_pCylinder = new PrimitiveClass();
	m_pCylinder->GenerateCylinder(100.0f, 100.0f, 10, REGREEN);

	//Calculate the first projections
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	sf::Vector2i n = sf::Vector2i(960, 540);
	sf::Mouse::setPosition(n);

}

void AppClass::Update(void)
{

	sf::Vector2i y = sf::Mouse::getPosition();
	vector2 mousePos = vector2(y.x, y.y);

	lastPressedM = sf::Keyboard::isKeyPressed(sf::Keyboard::M);
	lastPressedN = sf::Keyboard::isKeyPressed(sf::Keyboard::N);

	//Camera
	m_m4Projection = m_Camera->GetProjection(false);
	m_m4View = m_Camera->GetView(mousePos);

	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	
	//Render the grid
	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY);

	//Render the cone
	m_pCone->Render(m_m4Projection, m_m4View, IDENTITY_M4);

	//Render the cylinder
	m_pCylinder->Render(m_m4Projection, m_m4View, glm::translate(IDENTITY_M4, REAXISZ * -200.0f));

	m_pPlane->Render(m_m4Projection,m_m4View, glm::translate(IDENTITY_M4, REAXISY * -100.0f) * glm::rotate(90.0f,1.0f,0.0f,0.0f));

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	delete m_Camera;

	//Release the memory of the member fields
	SafeDelete(m_pCone);
	SafeDelete(m_pCylinder);

	//Release the memory of the inherited fields
	super::Release(); 
}