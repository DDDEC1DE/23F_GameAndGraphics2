attribute vec2 a_Position;
uniform vec2 u_CameraPos;
uniform float u_Zoom;

void main()
{
	vec2 Pos = (a_Position - u_CameraPos) * u_Zoom;
	gl_Position = vec4(Pos, 0.0, 1.0);

}
