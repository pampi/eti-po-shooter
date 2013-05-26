#include "headers.h"

int main()
{
    CScreenManager::GetInstance()->run();

    CScreenManager::DestroyInstance();
	
	return 0;
}
