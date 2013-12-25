#include "GUIFPS.h"
#include <sstream>
#include <mmsystem.h>


GUIFPS::GUIFPS(int x, int y)
{
	text = "FPS: ";
	textX = x;
	textY = y;
	boundBoxOriginal.x = x;
	boundBoxOriginal.y = y;
	count = 0;
	time = 0;
	for (int i = 0; i < 10; i++)
		fps.push_back(0);
	start_count = timeGetTime();
}


GUIFPS::~GUIFPS(void)
{
}

void GUIFPS::Update()
{
	timeBeginPeriod( 1 );

	end_count = timeGetTime();
	time += (end_count - start_count);
	start_count = timeGetTime();
	count++;

	if(time > 100)
	{
		fps.pop_front();
		fps.push_back(count);

		int fpsCount = 0;
		for (auto i =  fps.begin(); i != fps.end(); i++)
		{
			fpsCount += (*i);
		}

		std::stringstream ss;
		ss << fpsCount;
		SetText("FPS: " + ss.str());
		time = 0;
		count = 0;
	}
}