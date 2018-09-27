#include "AppClass.h"


void Application::InitVariables(void)
{
	//create all the cubes
	for (int i = 0; i < 46; i++) {
		cubes.push_back(new MyMesh());
		cubes[i]->GenerateCube(1.0f, C_BLACK);
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	//create the value that will change for them to move
	static float value = 0.0f;
	static float sinValue = 0.0f;
	//vector to hold all the transforms
	std::vector<matrix4> positions;

	//afer thinking about it while typing all of these out, just using a 2d array of cubes and translating them based on their index would have been so much better but im already halfway through so ¯\_(QQ)_/¯
#pragma region sadness
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue, 0.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue, 1.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue, 2.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 1.0f, 2.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 1.0f, 3.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 2.0f, 4.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 2.0f, 3.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 2.0f, 2.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 2.0f, 1.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 2.0f, 0.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 2.0f, 6.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 3.0f, 5.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 3.0f, 4.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 3.0f, 2.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 3.0f, 1.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 3.0f, -1.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 4.0f, -1.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 4.0f, 1.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 4.0f, 2.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 4.0f, 3.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 4.0f, 4.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 5.0f, 4.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 5.0f, 3.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 5.0f, 2.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 5.0f, 1.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 6.0f, -1.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 6.0f, 1.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 6.0f, 2.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 6.0f, 3.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 6.0f, 4.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 7.0f, 5.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 7.0f, 4.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 7.0f, 2.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 7.0f, 1.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 7.0f, -1.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 8.0f, 0.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 8.0f, 1.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 8.0f, 2.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 8.0f, 3.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 8.0f, 4.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 8.0f, 6.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 9.0f, 2.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 9.0f, 3.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 10.0f, 2.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 10.0f, 1.0f, 0.0f)));
	positions.push_back(glm::translate(IDENTITY_M4, vector3(sinValue + 10.0f, 0.0f, 0.0f)));
#pragma endregion

	value += 0.01f; //add to the value so it moves
	sinValue = sin(value); //do the sin of the value so it goes back and forth
	//apply the translation matrix coressponding to each cube
	for (int i = 0; i < 46; i++) {
		cubes[i]->Render(m4Projection, m4View, positions[i]);
	}
		
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//delete all the cubes
	for each (MyMesh* cube in cubes) {
		SafeDelete(cube);
	}
	//release GUI
	ShutdownGUI();
}