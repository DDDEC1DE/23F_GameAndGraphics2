#pragma once

#include "CoreHeaders.h"
#include "Texture.h"
#include "RecourceManager/RecourceManager.h"

namespace fw 
{

struct Frame
{
    Frame(Texture* texture, float length = 0.1f) : m_Texture(texture), m_Length(length) 
    {}

    Texture* m_Texture = nullptr;
    float m_Length = 0.1f;
};

class Animation : public Resource
{
public:
    Animation() {};
    virtual ~Animation() {};

    static Resource::Type GetType()
    {
        return Resource::Type::Animation;
    }

    void AddFrame(Texture* texture, float length = 0.1f)
    {
        m_AnimationFrames.push_back(Frame(texture, length));
    }

    std::vector<Frame> m_AnimationFrames;
    std::string AnimationName = "unassigned";
    bool m_bIsLooping = false;
};

class AnimationSet : public Resource
{
public:
    static Resource::Type GetType()
    {
        return Resource::Type::AnimationSet;
    }

    Animation* GetAnimation(std::string name)
    {
        return m_AnimationList[name];
    }

    std::map<std::string, Animation*> m_AnimationList;
};

class AnimationPlayer
{
public:

    AnimationPlayer(AnimationSet* animationSet, std::string animationName)
    {
        m_pAnimationSet = animationSet;
        SetAnimation(animationName);
    }

    static Resource::Type GetType()
    {
        return Resource::Type::AnimationSet;
    }

    void Update(float deltaTime)
    {
        if (!m_bPlaying)
            return;

        m_TimeOnFrame += deltaTime;

        if (m_TimeOnFrame >= m_pFrame->m_Length)
        {
            m_TimeOnFrame = 0;
            GoToNextFrame();
        }
    }

    void GoToNextFrame()
    {
        m_FrameIndex++;
        if (m_FrameIndex < m_pAnimation->m_AnimationFrames.size())
        {
            m_pFrame = &m_pAnimation->m_AnimationFrames[m_FrameIndex];
        }
        else if (m_pAnimation->m_bIsLooping)
        {
            m_FrameIndex = 0;
            m_pFrame = &m_pAnimation->m_AnimationFrames[m_FrameIndex];
        }
        else
        {
            m_bPlaying = false;
        }
    }

    void SetAnimation(std::string animationName)
    {
        m_pAnimation = m_pAnimationSet->GetAnimation(animationName);
        m_FrameIndex = 0;
        m_pFrame = &m_pAnimation->m_AnimationFrames[0];
        m_TimeOnFrame = 0;
    }

    void Play()
    {
        m_bPlaying = true;
        int m_FrameIndex = 0;
        m_pFrame = &m_pAnimation->m_AnimationFrames[0];
    }

    Texture* GetCurrentTexture()
    {
        return m_pFrame->m_Texture;
    }

private:
    AnimationSet* m_pAnimationSet;
    Animation* m_pAnimation;
    Frame* m_pFrame = nullptr;
    std::string m_AnimationName;
    float m_TimeOnFrame = 0;
    int m_FrameIndex = 0;
    bool m_bPlaying = false;
};


} // namespace fw