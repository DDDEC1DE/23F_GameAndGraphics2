#pragma once

#include "Framework.h"
#include "Math/vec2.h"
#include "Camera/Camera.h"

class TrackingCamera : public fw::Camera
{
public:
    TrackingCamera(fw::vec2 Position, float Zoom);

    ~TrackingCamera();

    void AddTrackedObject(fw::GameObject* object);

    void RemoveTrackedObject(fw::GameObject* object);

    fw::vec2 CalculateCenterPosition();


    
   
   
   
private:
    std::vector<fw::GameObject*> m_TrackedObjects;
    fw::vec2 m_Position;
    float m_ProjectionScale;
   
};
