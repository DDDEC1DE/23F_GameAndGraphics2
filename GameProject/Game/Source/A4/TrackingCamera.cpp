#include "TrackingCamera.h"


TrackingCamera::TrackingCamera(fw::vec2 Position, float Zoom) : Camera(Position, Zoom),
    m_Position(Position),
    m_ProjectionScale(Zoom)
{

}


TrackingCamera::~TrackingCamera()
{
}

void TrackingCamera::AddTrackedObject(fw::GameObject* object)
{

    m_TrackedObjects.push_back(object);

}

void TrackingCamera::RemoveTrackedObject(fw::GameObject* object)
{

    m_TrackedObjects.erase(std::remove(m_TrackedObjects.begin(), m_TrackedObjects.end(), object), m_TrackedObjects.end());

}

fw::vec2 TrackingCamera::CalculateCenterPosition()
{
    fw::vec2 center(0.0f, 0.0f);
    if (!m_TrackedObjects.empty()) 
    {
        for (auto* obj : m_TrackedObjects) 
        {
            center += obj->GetPosition();
        }
        center /= static_cast<float>(m_TrackedObjects.size());
        return center;
    }
}



