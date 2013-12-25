#ifndef GUIFPS_h__
#define GUIFPS_h__


#include "guilabel.h"
#include <list>


class GUIFPS : public GUILabel
{
private:
	DWORD start_count;
	DWORD end_count;
	double time;
	int count;

	std::list<int> fps;

public:
	GUIFPS(int x, int y);
	~GUIFPS(void);

	virtual void Update();


};


#endif // GUIFPS_h__