#pragma once

#include "CoreHeaders.h"
#include "Math/vec2.h"

namespace fw {


class Camera
{
public:
    Camera(vec2 Position, float Zoom);
   ~Camera();
     
    float m_ProjectionScale;
   // float m_AspectRatio;
    vec2 m_Position;
};

} // namespace fw
