#pragma once

namespace patterns
{
    const std::string keycodeValidation = xorstr_("24 5F DE E1 BB 00 00 00 42 53 D9 04 24 5B DE E9 57 DB 1C 24 5F 89 7C 24 08 C7 44 24");
    const std::string staminaSpending =   xorstr_("8B 1D ? ? ? ? 53 D9 04 24 5B DE E1 53 D9 1C 24 5B 89 1D ? ? ? ? 8B 05 ? ? ? ? 50 D9 04 24 58 BB 00 00 00 00 53");
    const std::string voicechatUpdate =   xorstr_("89 04 24 C7 44 24 04 20 00 00 00 E8 ? ? ? ? 89 45 F4 81 7D 18 00 00 00 00 89 D8 0F 94");
    const std::string wallhack096 =       xorstr_("DB 1C 24 5B 89 1C 24 89 D8 E8 ? ? ? ? 89 C3 81 3D");
}
