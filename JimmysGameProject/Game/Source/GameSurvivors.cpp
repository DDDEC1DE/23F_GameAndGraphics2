#include "GameSurvivors.h"
#include "DataTypes.h"

GameSurvivors::GameSurvivors(fw::FWCore* pFW) : fw::GameCore( pFW )
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f);
	glPointSize( 20 );
	glLineWidth( 5 );

	m_pWhiteShader = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/White.frag" );
	m_pTexture = new fw::Texture( "Data/Textures/Flower.png" );

	std::vector<fw::VertexFormat> attribs = {
		{ -25,  25,  0.0f,1.0f },
		{  25,  25,  1.0f,1.0f },
		{ -25, -25,  0.0f,0.0f },
		{  25, -25,  1.0f,0.0f },
	};
	m_LinesMesh.Create( attribs, GL_TRIANGLE_STRIP );
}

GameSurvivors::~GameSurvivors()
{
}

void GameSurvivors::OnKeyDown(int keyCode)
{
	if( keyCode == VK_F1 )
	{
		wglSwapInterval( 1 ); // V-Sync on
	}
	if( keyCode == VK_F2 )
	{
		wglSwapInterval( 0 ); // V-Sync off
	}
}

void GameSurvivors::OnKeyUp(int keyCode)
{
}

void GameSurvivors::Update(float deltaTime)
{
}

void GameSurvivors::Draw()
{
	glClear( GL_COLOR_BUFFER_BIT );

	vec2 objectPosition( 50, 50 );
	vec2 objectScale( 1, 1 );
	vec2 cameraPosition( 50, 50 );
	float zoom = 50;

	m_LinesMesh.Draw( m_pWhiteShader, m_pTexture, objectPosition, objectScale, cameraPosition, zoom );

	m_pFW->SwapBuffers();
}
