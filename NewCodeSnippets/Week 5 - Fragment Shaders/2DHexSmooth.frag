uniform float u_Time;
uniform vec2 u_Resolution;

// Created by Stephane Cuillerdier - @Aiekick/2016
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// Tuned via XShade (http://www.funparadigm.com/xshade/)
// based on https://www.shadertoy.com/view/XdKGRD

const float sections = 9.; // count radial section
const vec3 startColor = vec3(1,0.26,0);
const vec3 endColor = vec3(0.33,0.2,0.49);
const float zoom = 1.6; // screen coord zoom
const float neutralSection = 5.; // if of central section
const float neutralZone = 0.5; // radius of neutral zone (in center) wich show the neutralSection id

// uv:screenCoord 
// v:vec3(hex width, hex height, hex height limit, hex scale)  
// k:vec3(Alternance, Density, Glow)
vec3 GetHexPattern(vec2 uv, vec4 v, vec3 k) 
{
    // transfrom cartesian to polar
	float a = atan(uv.x, uv.y)/3.14159*floor(k.y); 
	float r = length(uv)*4.; 
	uv = vec2(a,r);// polar uv
    
    // homogeneise cells
	uv.x *= floor(uv.y)-k.x; //along r with alternance
	uv.x += u_Time; // rotate each radius offset with constant speed
    
    // apply 4 gradiant color along radius offset
	vec3 color = mix(startColor, endColor, vec3(floor(uv.y)/4.));
    
    // repeat without dommain break (mod)
	uv = abs(fract(uv)-0.5);
    
    // apply pattern
	float x = uv.x*v.x;
	float y = uv.y*v.y;
	float z = uv.y*v.z;
	return color / (abs(max(x + y,z) - v.w)*k.z);
}

// return central uv from h / h can be mouse or gl_FragCoord
// s:screenSize / h:pixelCoord / z:zoom
vec2 GetUV(vec2 s, vec2 h, float z) 
{
	return z * (h+h-s)/s.y; // central uv
}

float cAtan(vec2 uv)
{
	float a = 0.;
	if (uv.x >= 0.) a = atan(uv.x, uv.y);
    if (uv.x < 0.) a = 3.14159 - atan(uv.x, -uv.y);
    return a;
}

// return id of region pointed by h / h can be mouse or gl_FragCoord
// s:screenSize / h:pixelCoord
float GetID(vec2 s, vec2 h) 
{
	vec2 uv = GetUV(s, h, zoom);
	
	float a = cAtan(uv) * floor(sections)*.5/3.14159;
	float r = length(uv);
    return ( r < neutralZone ? neutralSection : a);
}

vec4 Params(float id)
{
	vec4 p = vec4(0);
	if (id > 0.) {p = vec4(1.2,0.92,1.88,0.8);}
	if (id > 1.) {p = vec4(2.2,0,1.88,0.8);}
	if (id > 2.) {p = vec4(2.2,0,4,0.8);}
	if (id > 3.) {p = vec4(1,0,4,0.8);}
	if (id > 4.) {p = vec4(1.2,0,2.12,0.64);}
	if (id > 5.) {p = vec4(4,4,1,0.8);}
	if (id > 6.) {p = vec4(1,2.96,4,0.8);}
	if (id > 7.) {p = vec4(1.5,0.96,1.8,0.4);}
	if (id > 8.) {p = vec4(1.2,2.24,0,0.68);}
	return p;
}

//void mainImage( out vec4 f, in vec2 g )
void main()
{
	vec2 pos = gl_FragCoord.xy;
    
	vec2 uv = GetUV(u_Resolution.xy, pos, zoom);
	
	//if(iMouse.z>0.) pos = iMouse.xy;
    
	float id = GetID(u_Resolution.xy, pos);

	vec4 p = vec4(0); // hex width, hex height, hex height limit, hex scale  
	vec3 k = vec3(-.3, 5, 4); // Alternance, Density, Glow

    // circular sections id 
    float cid = id; 				// current section id
	float lid = cid - 1.; 			// last section id
	if (lid < 0.) lid = id + 8.;	// circular becasue 8 section
	p = mix(Params(lid), Params(cid), fract(cid)); // id range [0-1]

	vec3 hexPattern = GetHexPattern(uv, p, k);
	
	vec3 col = clamp(hexPattern, 0., 1.); // intensity limit for glow
    
	gl_FragColor = vec4(col, 1);
}
