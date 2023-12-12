
#include "Camera.h"
namespace fw
{
    Camera::Camera(vec2 Position, float Zoom) :
        m_Position(Position),
        m_ProjectionScale(Zoom)
    {
    }

    Camera::~Camera()
    {
    }
}