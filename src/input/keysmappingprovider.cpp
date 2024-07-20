#include "input/keysmappingprovider.h"

KeysMappingProvider::KeysMappingProvider(std::map<Uint32, KeysMapping> bindingsMap)
: m_bindingsMap{bindingsMap}
{

}

std::optional<KeysMapping> KeysMappingProvider::mapKey(SDL_Keycode sdkKey)
{
    auto foundIt = m_bindingsMap.find(sdkKey);
    if (foundIt != m_bindingsMap.end())
    {
        return foundIt->second;
    }
    else
    {
        return {};
    }
}
