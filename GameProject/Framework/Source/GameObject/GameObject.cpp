
#include "GameObject.h"
#include "../Mesh.h"
#include "../Utility/ShaderProgram.h"
#include "FWCore.h"

namespace fw
{

 GameObject::GameObject(FWCore* pFW, Mesh* mesh, ShaderProgram* shader, vec2 position) :
     GameCore(pFW),
     m_pFW(pFW),
     m_mesh(mesh),
     m_shader(shader),
     m_position(position)
{
}

void  GameObject::Draw(Camera* camera)
{
    m_mesh->Draw( m_shader, camera, m_position);
}
 



















}