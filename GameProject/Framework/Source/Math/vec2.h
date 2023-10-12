#pragma once

namespace fw {

class vec2
{
public:
	vec2() {}
	vec2(float nx, float ny) : x(nx), y(ny) {}

	vec2 operator+(vec2 o) {


		return vec2( x + o.x, y + o.y );
	}
	vec2 operator-(vec2 o) { return vec2( x - o.x, y - o.y ); }

	vec2 operator*(float o) { return vec2( x * o, y * o ); }
	vec2 operator/(float o) { return vec2( x / o, y / o ); }

	void operator+=(vec2 o) { x += o.x; y += o.y; }
	void operator-=(vec2 o) { x -= o.x; y -= o.y; }

	void operator*=(float o) { x *= o; y *= o; }
	void operator/=(float o) { x /= o; y /= o; }

	float DistanceTo(fw::vec2 point2)
	{
		int dx = x - point2.x;
		int dy = y - point2.y;
		return sqrt(dx * dx + dy * dy);
	}


	float Distance(fw::vec2 point1, fw::vec2 point2)
	{
		float dx = point2.x - point1.x;
		float dy = point2.y - point1.y;
		return sqrt(dx * dx + dy * dy);
	}

public:
	float x = 0;
	float y = 0;
};








class intvec2
{
public:
	intvec2() {}
	intvec2(int nx, int ny) : x(nx), y(ny) {}

	intvec2 operator+(intvec2 o) {


		return intvec2(x + o.x, y + o.y);
	}
	intvec2 operator-(intvec2 o) { return intvec2(x - o.x, y - o.y); }

	intvec2 operator*(int o) { return intvec2(x * o, y * o); }
	intvec2 operator/(int o) { return intvec2(x / o, y / o); }

	void operator+=(intvec2 o) { x += o.x; y += o.y; }
	void operator-=(intvec2 o) { x -= o.x; y -= o.y; }

	void operator*=(int o) { x *= o; y *= o; }
	void operator/=(int o) { x /= o; y /= o; }
	int DistanceTo(fw::intvec2 point2)
	{
        int dx = x- point2.x;
        int dy = y- point2.y;
        return sqrt(dx * dx + dy * dy);
    }
	int Distance(fw::intvec2 point1, fw::intvec2 point2)
	{
		int dx = point2.x - point1.x;
		int dy = point2.y - point1.y;
		return sqrt(dx * dx + dy * dy);
	}
public:
	int x = 0;
	int y = 0;
};








} // namespace fw
