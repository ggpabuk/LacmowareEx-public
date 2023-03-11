#include "pch.h"
#include "CNoBlink.h"

CNoBlink::CNoBlink(CHotkey COHotkey) :
    CFeature("No Blink", COHotkey, Tab::Visuals)
{

}

void CNoBlink::fnEnable()
{
    CFeature::fnEnable();
    freezeManager::noblinkFreeze = true;
}

void CNoBlink::fnDisable()
{
    CFeature::fnDisable();
    freezeManager::noblinkFreeze = false;
}
