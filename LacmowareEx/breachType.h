#pragma once

enum class BreachType
{
    NTF_MODEL = 1,
    GUARD_MODEL = 2,
    CLASSD_MODEL = 3,
    SCIENTIST_MODEL = 4,
    MODEL_173 = 5,
    MODEL_049 = 6,
    HAOS_MODEL = 7,
    JANITOR_MODEL = 8,
    WORKER_MODEL = 9,
    MODEL_939 = 10,
    MODEL_106 = 11,
    MODEL_966 = 12,
    MODEL_ZOMBIE = 13,
    MODEL_096 = 14,
    MODEL_860 = 15,
    MODEL_035 = 16,
    MODEL_CLERK = 17,
    MODEL_WAIT = 18,
};

static const char *const g_breachType[] =
{
    "SPECTATOR",
    "MTF",
    "GUARD",
    "CLASS-D",
    "SCIENTIST",
    "SCP-173",
    "SCP-049",
    "CHAOS",
    "JANITOR",
    "WORKER",
    "SCP-939",
    "SCP-106",
    "SCP-966",
    "SCP-049-1",
    "SCP-096",
    "SCP-860-2",
    "SCP-035",
    "CLERK",
    "LOBBY",
};
