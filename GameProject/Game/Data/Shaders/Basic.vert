attribute vec2 a_Position;

void main()
{
	a_Position+= vec2(10,5);
	gl_Position = vec4( a_Position/50.0 - 1.0, 1.0, 2.0 );
}