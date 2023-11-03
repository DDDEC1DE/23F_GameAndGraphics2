#include "CoreHeaders.h"

#include "Mesh.h"
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

	
	void Mesh::Create(const std::vector<VertexFormat>& verts, GLenum primitiveType)
	{
		assert(m_VBO == 0);
		
		//m_NumVerts = (int)verts.size()/2;
		//m_PrimitiveType = primitiveType;
		m_NumVerts = static_cast<int>(verts.size()); 
		m_PrimitiveType = primitiveType;

		// Generate a buffer for our vertex attributes.
		glGenBuffers( 1, &m_VBO );

		// Set this VBO to be the currently active one.
		glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

		// Copy our attribute data into the VBO.
		// Once copied into the VBO, the stack copy above isn't needed anymore.
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * verts.size(), verts.data(), GL_STATIC_DRAW);
		// Describe the attributes in the VBO to OpenGL.
	// Since our vertices include position and UV, we have to tell OpenGL about both attributes.
		glEnableVertexAttribArray(0); // We'll assume 0 is the position attribute location.
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

		glEnableVertexAttribArray(1); // We'll assume 1 is the UV attribute location.
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(float) * 2));
		// The (void*)(sizeof(float) * 2) is the offset into the buffer where the UVs start.
	}

	void Mesh::Draw(ShaderProgram* pShader, vec2 offset)
	{
		// Enable our shader.
		glUseProgram( pShader->GetProgram() );

		// Set our uniforms.
		pShader->SetUniform2f( "u_Offset", offset );
		pShader->SetUniform1f( "u_Time", (float)GetHighPrecisionTimeSinceGameStarted() );

		// Set this VBO to be the currently active one.
		glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

		// Get the attribute variable’s location from the shader.
		// The shader part is commented out here, we'll discuss that later.
		GLint loc = 0; //glGetAttribLocation( pShader->m_Program, "a_Position" );
		glEnableVertexAttribArray( loc );

		// Describe the attributes in the VBO to OpenGL.
		glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 8, (void*)0 );

		// Draw the primitive.
		glDrawArrays( m_PrimitiveType, 0, m_NumVerts );
	}

} // namespace fw
