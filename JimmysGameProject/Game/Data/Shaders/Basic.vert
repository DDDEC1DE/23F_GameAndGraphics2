attribute vec2 a_Position;
attribute vec2 a_UVCoord;

uniform vec2 u_Offset;
uniform vec2 u_ObjectScale;
uniform vec2 u_CameraPosition;
uniform vec2 u_ProjectionScale;

varying vec2 v_UVCoord;

void main()
{
	vec2 objectSpacePosition = a_Position;
	vec2 worldSpacePosition = objectSpacePosition * u_ObjectScale + u_Offset;
	vec2 viewSpacePosition = worldSpacePosition - u_CameraPosition;
	vec2 clipSpacePosition = viewSpacePosition * u_ProjectionScale;

	gl_Position = vec4( clipSpacePosition, 0.0, 1.0 );

	v_UVCoord = a_UVCoord;
}
