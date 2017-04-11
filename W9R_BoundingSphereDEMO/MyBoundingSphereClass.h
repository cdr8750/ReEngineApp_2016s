#pragma once
#include "RE\ReEng.h"

class MyBoundingSphereClass
{
public:
<<<<<<< HEAD
	float m_fRadius = 0.0f;
	vector3 m_v3Center = vector3(0.0f);

	MeshManagerSingleton* pMeshMngr = nullptr;
	MyBoundingSphereClass(std::vector<vector3> vertexList);

	void RenderSphere();

=======
	float m_fRadius = 0.0f; //radius of the sphere
	vector3 m_v3CenterLocal = vector3(0.0f); //center of the sphere in local space
	vector3 m_v3CenterGlobal = vector3(0.0f); //center of the sphere in global space
	matrix4 m_m4ToWorld = IDENTITY_M4; //matrix that takes you from local to global space
	MeshManagerSingleton* m_pMeshMngr = nullptr; //for drawing the sphere
	/*
	Constructor, needs a vertex list
	*/
	MyBoundingSphereClass(std::vector<vector3> vertexList);
	/*
	Renders the sphere based on the radius and the center in global space
	*/
	void RenderSphere();
	/*
	Sets the transform from the local to world matrix
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);
>>>>>>> 3a599dd642348e48a93f58a5cdd8a50114af0a2c
};