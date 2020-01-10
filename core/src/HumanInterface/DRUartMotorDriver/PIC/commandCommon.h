#ifndef _COMMAND_COMMON_H
#define _COMMAND_COMMON_H

#include "env.h"
#ifndef _COMMANDID_CS
#define _COMMANDID_CS
#include "../PCRobokey/commandId.cs"
#endif

//extern unsigned char boardId;
extern enum CommandId commandId;
#include "CommandTemplate.h"

enum B1M_PARAM{
	B1M_MODEL_NUMBER = 1,
	B1M_NTARGET = 12,
    B1M_NMOTOR = 4,
    B1M_NCURRENT = 0,
    B1M_NFORCE = 0,
    B1M_NTOUCH = 0,
};
enum B1F_PARAM{
	B1F_MODEL_NUMBER = 2,
    B1F_NTARGET = 12,
    B1F_NMOTOR = 3,
    B1F_NCURRENT = 0,
    B1F_NFORCE = 2,
    B1F_NTOUCH = 0,
};
enum B2M_PARAM{
	B2M_MODEL_NUMBER = 3,
	B2M_NTARGET = 12,
    B2M_NMOTOR = 4,
    B2M_NCURRENT = 0,
    B2M_NFORCE = 0,
    B2M_NTOUCH = 0,
};
enum B2F_PARAM{
	B2F_MODEL_NUMBER = 4,
    B2F_NTARGET = 12,
    B2F_NMOTOR = 3,
    B2F_NCURRENT = 0,
    B2F_NFORCE = 2,
    B2F_NTOUCH = 0,
};
enum B3M_PARAM{
	B3M_MODEL_NUMBER = 5,
	B3M_NTARGET = 12,
    B3M_NMOTOR = 4,
    B3M_NCURRENT = 4,
    B3M_NFORCE = 0,
    B3M_NTOUCH = 0,
};
enum B3F_PARAM{
	B3F_MODEL_NUMBER = 6,
    B3F_NTARGET = 12,
    B3F_NMOTOR = 3,
    B3F_NCURRENT = 3,
    B3F_NFORCE = 2,
    B3F_NTOUCH = 0,
};

#ifndef _WIN32
DEFINE_Packets(B1M)
DEFINE_Packets(B1F)
DEFINE_Packets(B2M)
DEFINE_Packets(B2F)
DEFINE_Packets(B3M)
DEFINE_Packets(B3F)
#endif

#endif
