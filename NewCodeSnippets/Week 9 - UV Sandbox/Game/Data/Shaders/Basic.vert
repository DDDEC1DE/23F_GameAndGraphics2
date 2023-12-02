attribute vec2 a_Position;
attribute vec2 a_UVCoord;

uniform vec2 u_Offset;

varying vec2 v_UVCoord;

void main()
{
	vec2 objectScale = vec2(1.0, 1.0);
	vec2 cameraPosition = vec2(80.0, 100.0);
	vec2 projectionScale = vec2(1.0/50.0 * 720.0/1280.0, 1.0/50.0);

	vec2 objectSpacePosition = a_Position;
	vec2 worldSpacePosition = objectSpacePosition * objectScale + u_Offset;
	vec2 viewSpacePosition = worldSpacePosition - cameraPosition;
	vec2 clipSpacePosition = viewSpacePosition * projectionScale;

	gl_Position = vec4( clipSpacePosition, 0.0, 1.0 );

	v_UVCoord = a_UVCoord;
}
