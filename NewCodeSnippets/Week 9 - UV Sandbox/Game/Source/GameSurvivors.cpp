#include "GameSurvivors.h"
#include "DataTypes.h"

GameSurvivors::GameSurvivors(fw::FWCore* pFW) : fw::GameCore( pFW )
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f);
	glPointSize( 20 );
	glLineWidth( 5 );

	m_pWhiteShader = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/White.frag" );

	std::vector<fw::VertexFormat> attribs = {
		{ 25, 55,  0.0f,0.0f },
		{ 75, 55,  1.0f,0.0f },
		{ 50,105,  0.5f,1.0f },
	};
	m_LinesMesh.Create( attribs, GL_TRIANGLES );

	m_pTexture = new fw::Texture( "Data/Textures/Flower.png" );
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

	m_LinesMesh.Draw( m_pWhiteShader, m_pTexture, vec2(0,0) );

	m_pFW->SwapBuffers();
}
