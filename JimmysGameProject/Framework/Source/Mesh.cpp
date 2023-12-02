#include "CoreHeaders.h"

#include "Mesh.h"
#include "Texture.h"
#include "Utility/ShaderProgram.h"
#include "Utility/Utility.h"

namespace fw {

	Mesh::Mesh()
	{
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers( 1, &m_VBO );
	}

	void Mesh::Create(std::vector<VertexFormat>& verts, GLenum primitiveType)
	{
		assert( m_VBO == 0 );

		m_NumVerts = (int)verts.size();
		m_PrimitiveType = primitiveType;

		// Generate a buffer for our vertex attributes.
		glGenBuffers( 1, &m_VBO );

		// Set this VBO to be the currently active one.
		glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

		// Copy our attribute data into the VBO.
		// Once copied into the VBO, the stack copy above isn't needed anymore.
		glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*verts.size(), verts.data(), GL_STATIC_DRAW);
	}

	void Mesh::Draw(ShaderProgram* pShader, Texture* pTexture, vec2 offset, vec2 objectScale, vec2 camPos, float zoom)
	{
		float aspectRatio = 1280.0f/720.0f;

		// Enable our shader.
		glUseProgram( pShader->GetProgram() );

		// Set our uniforms.
		pShader->SetUniform2f( "u_Offset", offset );
		pShader->SetUniform2f( "u_ObjectScale", objectScale );
		pShader->SetUniform2f( "u_CameraPosition", camPos );
		pShader->SetUniform2f( "u_ProjectionScale", vec2(1.0f/(zoom * aspectRatio), 1.0f/zoom) );
		pShader->SetUniform1f( "u_Time", (float)GetHighPrecisionTimeSinceGameStarted() );

		// Setup Texture.
		{
			// Set texture unit 5 to be the current active TIU
			int textureUnitIndex = 5; // I picked 5 at random for demo purposes.
			glActiveTexture( GL_TEXTURE0 + textureUnitIndex );

			// Bind the texture to the GL_TEXTURE_2D target of the active TIU
			glBindTexture( GL_TEXTURE_2D, pTexture->GetTextureID() );

			// Get the uniform location and fill it with the texture unit number
			GLint loc = glGetUniformLocation( pShader->GetProgram(), "u_Texture" );
			glUniform1i( loc, textureUnitIndex );
		}

		// Set this VBO to be the currently active one.
		glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

		// Get the attribute variable’s location from the shader.
		// The shader part is commented out here, we'll discuss that later.
		// Describe the attributes in the VBO to OpenGL.
		GLint pos = glGetAttribLocation( pShader->GetProgram(), "a_Position" );
		glEnableVertexAttribArray( pos );
		glVertexAttribPointer( pos, 2, GL_FLOAT, GL_FALSE, 16, (void*)0 );

		GLint uv = glGetAttribLocation( pShader->GetProgram(), "a_UVCoord" );
		if( uv != -1 )
		{
			glEnableVertexAttribArray( uv );
			glVertexAttribPointer( uv, 2, GL_FLOAT, GL_FALSE, 16, (void*)8 );
		}

		// Draw the primitive.
		glDrawArrays( m_PrimitiveType, 0, m_NumVerts );
	}

} // namespace fw
