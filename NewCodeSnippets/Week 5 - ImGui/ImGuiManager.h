#pragma once

struct ImDrawData;

class ImGuiManager
{
public:
    ImGuiManager(fw::FWCore* pFramework);
    virtual ~ImGuiManager();

    void OnFocusLost();

    void StartFrame(float deltaTime);
    void EndFrame();

    void OnInputCharacter(unsigned int character);
    
protected:
    void Init();
    void Shutdown();

    void ClearInput();

    void RenderDrawLists(ImDrawData* draw_data);

    bool CreateFontsTexture();
    bool CreateDeviceObjects();
    void InvalidateDeviceObjects();

protected:
    fw::FWCore* m_pFramework;

    GLuint m_FontTexture;
    int m_ShaderHandle;
    int m_VertHandle;
    int m_FragHandle;
    int m_AttribLocationTex;
    int m_AttribLocationProjMtx;
    int m_AttribLocationPosition;
    int m_AttribLocationUV;
    int m_AttribLocationColor;
    unsigned int m_VBOHandle;
    unsigned int m_VAOHandle;
    unsigned int m_ElementsHandle;
};
