#include "RecourceManager.h"


namespace fw {
    ResourceManager::ResourceManager()
    {

    }

    ResourceManager::~ResourceManager()
    {
        for (auto& resourceCategoryPair : m_Resources)
        {
            for (auto& resource : resourceCategoryPair.second)
            {
                delete resource.second;
                resource.second = nullptr;
            }
        }
    }
}