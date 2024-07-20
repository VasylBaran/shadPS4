#ifndef KEYSMAPPINGPROVIDER_H
#define KEYSMAPPINGPROVIDER_H

#include <SDL3/SDL_keycode.h>

#include <map>
#include <optional>

#include "input/keys_constants.h"

class KeysMappingProvider
{
public:
    KeysMappingProvider(std::map<Uint32, KeysMapping> bindingsMap);

    std::optional<KeysMapping> mapKey(SDL_Keycode sdkKey);

private:
    std::map<Uint32, KeysMapping> m_bindingsMap;
};

#endif // KEYSMAPPINGPROVIDER_H
