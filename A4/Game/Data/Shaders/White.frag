uniform sampler2D u_Texture;

varying vec2 v_UVCoord;

void main()
{
	vec4 color = texture2D( u_Texture, v_UVCoord );

	if (color.a < 0.1)
	{
		discard;
	}

	gl_FragColor = color;
}
