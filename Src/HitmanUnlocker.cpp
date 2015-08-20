#include "HitmanUnlocker.h"

#include "detours.h"

#pragma comment(lib, "detours")

static ZSysInterface* g_pSysInterface = nullptr;

static double g_CameraFar = -1.f;

static const char* g_Actions[] =
{
	"WalkForward",
	"Run",
	"WalkLeft",
	"WalkRight",
	"WalkBackWard",
	"TurnLeft",
	"TurnRight",
	"LeanOutLeft",
	"LeanOutRight",
	"DoAction",
	"Sneak",
	"ToggleMouseControl",
	"DropItemInHand",
	"Binoculars",
	"EmptyHands",
	"FireWeapon",
	"ReloadWeapon",
	"ToggleWeaponMode",
	"SelectNext2",
	"SelectPrev2",
	"ShowMap",
	"ShowLaptop",
	"ShowStatus",
	"IncreaseDrawDistance",
	"DecreaseDrawDistance",
	nullptr
};

static ZInput g_DefaultInputs[] = 
{
	{ "WalkForward", HM_VK_NUMPAD5, HM_VK_S },
	{ "WalkBackWard", HM_VK_NUMPAD2, HM_VK_X },
	{ "WalkLeft", HM_VK_NUMPAD1, HM_VK_Z },
	{ "WalkRight", HM_VK_NUMPAD3, HM_VK_C },
	{ "Run", HM_VK_NUMPAD8, HM_VK_W },
	{ "TurnLeft", HM_VK_NUMPAD4, HM_VK_A },
	{ "TurnRight", HM_VK_NUMPAD6, HM_VK_D },
	{ "LeanOutLeft", HM_VK_NUMPAD7, HM_VK_Q },
	{ "LeanOutRight", HM_VK_NUMPAD9, HM_VK_E },
	{ "Sneak", HM_VK_ADD, HM_VK_4 },
	{ "ToggleMouseControl", HM_VK_NUMDIVIDE, HM_VK_3 },
	{ "FireWeapon", HM_VK_LBUTTON, HM_VK_LBUTTON },
	{ "ReloadWeapon", HM_VK_HOME, HM_VK_1 },
	{ "ToggleWeaponMode", HM_VK_END, HM_VK_TAB },
	{ "SelectNext2", HM_VK_NEXT, HM_VK_G },
	{ "SelectPrev2", HM_VK_PRIOR, HM_VK_T },
	{ "DropItemInHand", HM_VK_SUBTRACT, HM_VK_F },
	{ "DoAction", HM_VK_NUMRETURN, HM_VK_SPACE },
	{ "ShowMap", HM_VK_M, HM_VK_M },
	{ "ShowLaptop", HM_VK_F1, HM_VK_F1 },
	{ "ShowStatus", HM_VK_F2, HM_VK_F2 },
	{ "Binoculars", HM_VK_MULTIPLY, HM_VK_2 },
	{ "EmptyHands", HM_VK_INSERT, HM_VK_R },
	{ "IncreaseDrawDistance", HM_VK_OEM_5, HM_VK_OEM_5 },
	{ "DecreaseDrawDistance", HM_VK_OEM_4, HM_VK_OEM_4 },
	{ nullptr, HM_VK_NONE, HM_VK_NONE }
};

static ZInputAction g_InputActions[] = 
{
	{ "Jump", 0, "VK_J", "0", 0, true },
	{ "BackToLife", 1, "VK_F", "0", 0, true },
	{ "ToggleT1Display", 1, "VK_F9+VK_SHIFT", "VK_CONTROL", 0, true },
	{ "CheatMove", 1, "VK_F9+VK_CONTROL", "VK_SHIFT", 0, true },
	{ "DropBody", 1, "VK_RBUTTON", "0", 0, false },
	{ "FireWeapon", 0, "VK_LBUTTON", "0", 0, false },
	{ "ToggleWeaponMode", 1, "VK_DELETE", "0", 0, false },
	{ "ReloadWeapon", 1, "VK_HOME", "0", 0, false },
	{ "RunBackward", 3, "VK_NUMPAD2", "0", 0, false },
	{ "Run", 0, "VK_NUMPAD8", "0", 0, false },
	{ "RunStop", 2, "VK_NUMPAD8", "0", 0, false },
	{ "LeanOutLeft", 0, "VK_NUMPAD7", "0", 0, false },
	{ "LeanOutRight", 0, "VK_NUMPAD9", "0", 0, false },
	{ "LeanOutLeftShoot", 3, "VK_NUMPAD7", "0", 0, false },
	{ "LeanOutRightShoot", 3, "VK_NUMPAD9", "0", 0, false },
	{ "WalkForward", 0, "VK_NUMPAD5", "0", 0, false },
	{ "WalkBackward", 0, "VK_NUMPAD2", "0", 0, false },
	{ "TurnRight", 0, "VK_NUMPAD6", "0", 0, false },
	{ "TurnLeft", 0, "VK_NUMPAD4", "0", 0, false },
	{ "WalkLeft", 0, "VK_NUMPAD1", "0", 0, false },
	{ "WalkRight", 0, "VK_NUMPAD3", "0", 0, false },
	{ "Sneak", 1, "VK_ADD", "0", 0, false },
	{ "ToggleMouseControl", 1, "VK_NUMDIVIDE", "0", 0, false },
	{ "IncreaseDrawDistance", 0, "?5", "0", 0, false },
	{ "DecreaseDrawDistance", 0, "?4", "0", 0, false },
	{ nullptr, 0, nullptr, nullptr, 0, 0 }
};

typedef int (__thiscall* GetPropertyValueDouble_t)(void* th, const char* key, double* value);
GetPropertyValueDouble_t GetPropertyValueDouble;

int __fastcall c_GetPropertyValueDouble(void* th, int, const char* key, double* value)
{
	int s_Result = GetPropertyValueDouble(th, key, value);

	if (strcmp(key, "CameraFogBegin") == 0)
	{
		// Set the fog starting point based on the current distance.
		if (g_CameraFar < 2800.f)
			*value = 0.65f;
		if (g_CameraFar < 3700.f)
			*value = 0.72f;
		else if (g_CameraFar < 7000.f)
			*value = 0.80f;
		else
			*value = 0.95f;

		return 8;
	}

	if (strcmp(key, "CameraFogFull") == 0)
	{
		*value = 0.99f;
		return 8;
	}

	return s_Result;
}

typedef void(__thiscall* SetCameraFar_t)(void* th, double value);
SetCameraFar_t SetCameraFar;

void __fastcall c_SetCameraFar(void* th, int, double value)
{
	// Initialize the distance.
	if (g_CameraFar == -1.f)
		g_CameraFar = value;

	float s_Step = 0.f;

	// Set step based on current distance.
	if (g_CameraFar < 3500.f)
		s_Step = 12.f;
	else if (g_CameraFar < 7000.f)
		s_Step = 40.f;
	else if (g_CameraFar < 14000.f)
		s_Step = 100.f;
	else if (g_CameraFar < 30000.f)
		s_Step = 250.f;
	else
		s_Step = 500.f;

	if (g_pSysInterface && g_pSysInterface->m_Input)
	{
		// Increase draw distance.
		if (g_pSysInterface->m_Input->isPressed("IncreaseDrawDistance", 0))
			g_CameraFar += s_Step;

		// Decrease draw distance.
		if (g_pSysInterface->m_Input->isPressed("DecreaseDrawDistance", 0))
			g_CameraFar -= s_Step;

		// Limit distance so we don't break things.
		if (g_CameraFar < 2000.f)
			g_CameraFar = 2000.f;

		if (g_CameraFar > 50000.f)
			g_CameraFar = 50000.f;
	}

	// Override the game-set distance.
	value = g_CameraFar;

	return SetCameraFar(th, value);
}

void UnprotectModule(HMODULE p_Module)
{
	PIMAGE_DOS_HEADER s_Header = (PIMAGE_DOS_HEADER) p_Module;
	PIMAGE_NT_HEADERS s_NTHeader = (PIMAGE_NT_HEADERS) ((DWORD) p_Module + s_Header->e_lfanew);

	SIZE_T s_ImageSize = s_NTHeader->OptionalHeader.SizeOfImage;

	DWORD s_OldProtect;
	VirtualProtect((LPVOID) p_Module, s_ImageSize, PAGE_EXECUTE_READWRITE, &s_OldProtect);
}

void UnlockHitman()
{
	// Wait for all required modules to load.
	while (GetModuleHandleA("EngineData.dll") == NULL ||
		GetModuleHandleA("HitmanDlc.dlc") == NULL ||
		GetModuleHandleA("Globals.dll") == NULL)
		Sleep(1);

	HMODULE s_EngineDataModule = GetModuleHandleA("EngineData.dll");
	HMODULE s_HitmanDlcModule = GetModuleHandleA("HitmanDlc.dlc");
	HMODULE s_GlobalsModule = GetModuleHandleA("Globals.dll");

	// Unprotect all required modules so we can freely read/write their memory.
	UnprotectModule(s_EngineDataModule);
	UnprotectModule(s_HitmanDlcModule);
	UnprotectModule(s_GlobalsModule);

	// Get the global ZSysInterface.
	g_pSysInterface = *(ZSysInterface**) GetProcAddress(s_GlobalsModule, "?g_pSysInterface@@3PAVZSysInterface@@A");

	// Hook functions for setting camera parameters live.
	GetPropertyValueDouble = (GetPropertyValueDouble_t) DetourFunction((PBYTE) ((DWORD) s_EngineDataModule + 0x00028490), (PBYTE) c_GetPropertyValueDouble);
	SetCameraFar = (SetCameraFar_t) DetourFunction((PBYTE) ((DWORD) s_HitmanDlcModule + 0x000904A0), (PBYTE) c_SetCameraFar);

	// Patch actions and inputs to introduce our two new custom controls.
	*(const char***) ((DWORD) s_EngineDataModule + 0x000012B2) = g_Actions;
	*(const char***) ((DWORD) s_EngineDataModule + 0x000012BD) = g_Actions;
	*(const char***) ((DWORD) s_EngineDataModule + 0x00002EEF) = g_Actions;
	*(const char***) ((DWORD) s_EngineDataModule + 0x00002F01) = g_Actions;
	*(const char***) ((DWORD) s_EngineDataModule + 0x00003431) = g_Actions;

	*(void**) ((DWORD) s_EngineDataModule + 0x00002E7C) = g_DefaultInputs;
	*(void**) ((DWORD) s_EngineDataModule + 0x00002E86) = g_DefaultInputs;
	*(void**) ((DWORD) s_EngineDataModule + 0x00002E8D) = ((char*) g_DefaultInputs + 4);

	*(void**) ((DWORD) s_HitmanDlcModule + 0x0022FD68) = g_InputActions;
}