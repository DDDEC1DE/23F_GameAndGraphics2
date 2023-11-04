#pragma once

#include "CoreHeaders.h"
#include "Math/vec2.h"
#include "GameCore.h"
namespace fw {


    class Mesh;
    class ShaderProgram;
    class Camera;
    class FWCore;

    class GameObject : public fw::GameCore {
    public:
        GameObject(FWCore* pFW, Mesh* mesh, ShaderProgram* shader, vec2 position);
        void Draw(Camera* camera);

        void SetPosition(const vec2 position) { m_position = position; }
        vec2 GetPosition() const { return m_position; }




        virtual void OnKeyDown(int keyCode) = 0;
        virtual void OnKeyUp(int keyCode) = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Draw() = 0;



    private:
        FWCore* m_pFW;
        Mesh* m_mesh;
        ShaderProgram* m_shader;
        vec2 m_position;
    };

}