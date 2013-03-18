#include "headers.h"



int main()
{
	CScreenManager *mng = new CScreenManager();

	mng->run();
	
	delete mng;


	return 0;
}
