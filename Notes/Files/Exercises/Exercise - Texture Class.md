
#### fw::Texture class

- members:
	- GLuint m_TextureID
- methods: constructor, destructor, getter for texture ID
	- Constructor will create an temporary array of unsigned chars, every 4 is one color (RGBA).
		- Keep it small, 8x8 will work, draw a non-symmetric bitmap in code
		- then create a texture out of it with this code (don't just cut and paste, read through the code, it's similar to VBO creation) (w, h, pixels are my local variable names)

```c++
glGenTextures( 1, &m_TextureID );
	
glActiveTexture( GL_TEXTURE0 );
glBindTexture( GL_TEXTURE_2D, m_TextureID );

glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );

glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

glBindTexture( GL_TEXTURE_2D, 0 );
```

- Destructor will delete the texture (you can figure it out)

#### Frag Shader

- Add a new uniform:
	- uniform sampler2D u_Texture;
- Grab the color at the calculated UV coordinate:
	- vec4 color = texture2D( u_Texture, v_UVCoord );

#### Mesh::Draw

- Setup the texture and program the uniform

```c++
	int textureUnitNumber = 8;
	glActiveTexture( GL_TEXTURE0 + textureUnitNumber );
	glBindTexture( GL_TEXTURE_2D, pTexture->GetTextureID() );
	GLint colorTexture = glGetUniformLocation( pShader->GetProgram(), "u_Texture" );
	glUniform1i( colorTexture, textureUnitNumber );
```

#### Load an actual texture

Don't do this until you see your texture.

- Grab stb_image.h from https://github.com/nothings/stb
- Put it in a new folder under "Framework/Libraries"
- Create a 2nd Texture constructor: Texture(const char* filename);
- Read the FAQ and try to integrate it into your project
	- You should only include this new files in Texture.cpp since it's the only class that will use it
- Read the notes in the header and try to load a png (keep it low res, 32x32 or 64x64 is fine).
- If you got it loading and displaying, you might notice it's flipped
	- There's an "stbi" function to flip the image in memory as it's being loaded
