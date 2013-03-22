#include "headers.h"

Globals pGlobal;

int main()
{
	CScreenManager *mng = new CScreenManager();

	mng->run();
	
	delete mng;
	
	return 0;
}
