#include <core.h>
#include <drivers/CRTC.h>
#include <drivers/Port.hpp>

typedef port::CDigitalPin< port::PORTB, 10 > led;
CRTC rtc;

void Setup()
{
	rtc.Initialize();
}

void Loop()
{
    led::Set();
    led::Clear();
}