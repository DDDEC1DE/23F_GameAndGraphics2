#pragma once

#include "Framework.h"
#include "Datatypes.h"

class GameCamera : public fw::Camera
{
public:

    void Update(float deltaTime);

    GameCamera(vec2 position, float zoom);
    ~GameCamera();

    // Makes sure no duplicates are added.
    void AddNewTrackedObject(fw::GameObject* newObject);
    void RemoveLastTrackedObject();

protected:

    std::vector<fw::GameObject*> m_ObjectsToTrack;
    vec2 m_CameraVelocity;
    float m_CameraSpeed = 3;

    float m_MinimumZoom = 30;
    float m_MaxZoom = 70;
    float m_CameraZoomSpeed = 3;

    void UpdatePosition(float deltaTime);
    void UpdateZoom(float deltaTime);
};
