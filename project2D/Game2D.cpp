#include "Game2D.h"
#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();

	// Create some textures for testing.
	m_font = new aie::Font("./font/consolas.ttf", 44);
	
	_GameManager = new GameManager(20);
}

Game2D::~Game2D()
{
	// Deleted the textures.
	delete m_font;

	// Delete the renderer.
	delete m_2dRenderer;

	//Delete Gamemanager
	delete _GameManager;
}

void Game2D::Update(float deltaTime)
{
	// Update game manager
	_GameManager->Update(deltaTime);

	// Input example: Update the camera position using the arrow keys.
	aie::Input* input = aie::Input::GetInstance();

	// Exit the application if escape is pressed.
	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}
}

void Game2D::Draw()
{
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();
	
	// Draw GameManager
	_GameManager->Draw(m_2dRenderer);

	// Draw some text.
	m_2dRenderer->SetRenderColour(1.0f, 1.0f, 1.0f);
	float windowHeight = (float)application->GetWindowHeight();
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", application->GetFPS());
	m_2dRenderer->DrawText2D(m_font, fps, 15.0f, windowHeight - 32.0f);

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}