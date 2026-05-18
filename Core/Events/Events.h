#ifndef EVENTS_H__INCLUDED
#define EVENTS_H__INCLUDED

#include "../TMath.h"

struct KeyPressEvent
{
	uint32 keyCode;
	bool isRepeat;
};

#endif // !EVENTS_H__INCLUDED
