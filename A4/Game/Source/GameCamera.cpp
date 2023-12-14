#include "GameCamera.h"

GameCamera::GameCamera(vec2 position, float zoom) :
fw::Camera(position, zoom)
{

}

GameCamera::~GameCamera()
{

}

void GameCamera::Update(float deltaTime)
{
    if (m_ObjectsToTrack.empty())
        return;

    UpdatePosition(deltaTime);
    UpdateZoom(deltaTime);
}

void GameCamera::UpdatePosition(float deltaTime)
{
    vec2 targetPosition;

    if (m_ObjectsToTrack.size() == 1)
    {
        targetPosition = m_ObjectsToTrack[0]->GetPosition();
        m_CameraVelocity = targetPosition - m_Position;
        m_Position += m_CameraVelocity * deltaTime;
        return;
    }

    vec2 sumOfPositions(0, 0);

    for (fw::GameObject* trackedObject : m_ObjectsToTrack)
    {
        sumOfPositions += trackedObject->GetPosition();
    }

    targetPosition = sumOfPositions / m_ObjectsToTrack.size();
    m_CameraVelocity = (targetPosition - m_Position) * m_CameraSpeed;
    m_Position += m_CameraVelocity * deltaTime;
}

void GameCamera::UpdateZoom(float deltaTime)
{
    float farthestDistance = vec2::Magnitude(m_Position - m_ObjectsToTrack[0]->GetPosition());
    for (int i=1; i < m_ObjectsToTrack.size(); i++)
    {
        if (vec2::Magnitude(m_Position - m_ObjectsToTrack[i]->GetPosition()) > farthestDistance)
            farthestDistance = vec2::Magnitude(m_Position - m_ObjectsToTrack[i]->GetPosition());
    }

    float targetZoom = max(m_MinimumZoom, farthestDistance);

    if (targetZoom > m_MaxZoom)
    {
        targetZoom = m_MaxZoom;
    }

    m_CameraZoomSpeed = targetZoom - m_ProjectionScale;
    m_ProjectionScale += deltaTime * m_CameraZoomSpeed;
    

}

void GameCamera::AddNewTrackedObject(fw::GameObject* newObject)
{
    for (fw::GameObject* trackedObject : m_ObjectsToTrack)
    {
		if (trackedObject == newObject)
			return;
    }

    m_ObjectsToTrack.push_back(newObject);
}

void GameCamera::RemoveLastTrackedObject()
{
	if(m_ObjectsToTrack.size() > 1)
	{
		m_ObjectsToTrack.pop_back();
	}
}
