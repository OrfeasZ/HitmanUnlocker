#include "HitmanUnlocker.h"

BOOL APIENTRY DllMain(HMODULE p_Module, DWORD p_Reason, LPVOID p_Reserved)
{
	switch (p_Reason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) UnlockHitman, NULL, NULL, NULL);
		break;
	}

	return TRUE;
}

extern "C"
{
	typedef BOOL (CALLBACK* LPDSENUMCALLBACKA)(LPGUID, LPCSTR, LPCSTR, LPVOID);
	typedef BOOL (CALLBACK* LPDSENUMCALLBACKW)(LPGUID, LPCWSTR, LPCWSTR, LPVOID);

	FARPROC GetDSoundFunction(const char* p_Function)
	{
		wchar_t s_DLLPath[MAX_PATH] = { 0 };

		wchar_t const *s_DLLFilename = L"\\dsound.dll";
		GetSystemDirectoryW(s_DLLPath, MAX_PATH);
		wcscat_s(s_DLLPath, MAX_PATH, s_DLLFilename);

		HMODULE s_DsoundDLL = LoadLibraryW(s_DLLPath);

		if (!s_DsoundDLL)
			return NULL;

		return GetProcAddress(s_DsoundDLL, p_Function);
	}

	typedef HRESULT (WINAPI* DirectSoundCreate_t)(LPGUID lpGuid, void** ppDS, void* pUnkOuter);
	HRESULT WINAPI DirectSoundCreate(LPGUID lpGuid, void** ppDS, void* pUnkOuter)
	{
		DirectSoundCreate_t s_Function = (DirectSoundCreate_t) GetDSoundFunction("DirectSoundCreate");

		if (!s_Function)
			return NULL;

		return s_Function(lpGuid, ppDS, pUnkOuter);
	}

	typedef HRESULT (WINAPI* DirectSoundEnumerateA_t)(LPDSENUMCALLBACKA lpDSEnumCallback, LPVOID lpContext);
	HRESULT WINAPI DirectSoundEnumerateA(LPDSENUMCALLBACKA lpDSEnumCallback, LPVOID lpContext)
	{
		DirectSoundEnumerateA_t s_Function = (DirectSoundEnumerateA_t) GetDSoundFunction("DirectSoundEnumerateA");

		if (!s_Function)
			return NULL;

		return s_Function(lpDSEnumCallback, lpContext);
	}

	typedef HRESULT (WINAPI* DirectSoundEnumerateW_t)(LPDSENUMCALLBACKW lpDSEnumCallback, LPVOID lpContext);
	HRESULT WINAPI DirectSoundEnumerateW(LPDSENUMCALLBACKW lpDSEnumCallback, LPVOID lpContext)
	{
		DirectSoundEnumerateW_t s_Function = (DirectSoundEnumerateW_t) GetDSoundFunction("DirectSoundEnumerateW");

		if (!s_Function)
			return NULL;

		return s_Function(lpDSEnumCallback, lpContext);
	}

	typedef HRESULT (WINAPI* DllCanUnloadNow_t)();
	HRESULT WINAPI DllCanUnloadNow()
	{
		DllCanUnloadNow_t s_Function = (DllCanUnloadNow_t) GetDSoundFunction("DllCanUnloadNow");

		if (!s_Function)
			return NULL;

		return s_Function();
	}

	typedef HRESULT (WINAPI* DllGetClassObject_t)(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
	HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
	{
		DllGetClassObject_t s_DllGetClassObject = (DllGetClassObject_t) GetDSoundFunction("DllGetClassObject");

		if (!s_DllGetClassObject)
			return NULL;

		return s_DllGetClassObject(rclsid, riid, ppv);
	}

	typedef HRESULT (WINAPI* DirectSoundCaptureCreate_t)(LPGUID lpGUID, void** lplpDSC, void* pUnkOuter);
	HRESULT WINAPI DirectSoundCaptureCreate(LPGUID lpGUID, void** lplpDSC, void* pUnkOuter)
	{
		DirectSoundCaptureCreate_t s_Function = (DirectSoundCaptureCreate_t) GetDSoundFunction("DirectSoundCaptureCreate");

		if (!s_Function)
			return NULL;

		return s_Function(lpGUID, lplpDSC, pUnkOuter);
	}

	typedef HRESULT (WINAPI* DirectSoundCaptureEnumerateA_t)(LPDSENUMCALLBACKA lpDSEnumCallback, LPVOID lpContext);
	HRESULT WINAPI DirectSoundCaptureEnumerateA(LPDSENUMCALLBACKA lpDSEnumCallback, LPVOID lpContext)
	{
		DirectSoundCaptureEnumerateA_t s_Function = (DirectSoundCaptureEnumerateA_t) GetDSoundFunction("DirectSoundCaptureEnumerateA");

		if (!s_Function)
			return NULL;

		return s_Function(lpDSEnumCallback, lpContext);
	}

	typedef HRESULT (WINAPI* DirectSoundCaptureEnumerateW_t)(LPDSENUMCALLBACKW lpDSEnumCallback, LPVOID lpContext);
	HRESULT WINAPI DirectSoundCaptureEnumerateW(LPDSENUMCALLBACKW lpDSEnumCallback, LPVOID lpContext)
	{
		DirectSoundCaptureEnumerateW_t s_Function = (DirectSoundCaptureEnumerateW_t) GetDSoundFunction("DirectSoundCaptureEnumerateW");

		if (!s_Function)
			return NULL;

		return s_Function(lpDSEnumCallback, lpContext);
	}

	typedef HRESULT (WINAPI* GetDeviceID_t)(LPCGUID lpGuidSrc, LPGUID lpGuidDest);
	HRESULT WINAPI GetDeviceID(LPCGUID lpGuidSrc, LPGUID lpGuidDest)
	{
		GetDeviceID_t s_Function = (GetDeviceID_t) GetDSoundFunction("GetDeviceID");

		if (!s_Function)
			return NULL;

		return s_Function(lpGuidSrc, lpGuidDest);
	}

	typedef HRESULT (WINAPI* DirectSoundFullDuplexCreate_t)(LPCGUID pcGuidCaptureDevice, LPCGUID pcGuidRenderDevice, void* pcDSCBufferDesc, void* pcDSBufferDesc, HWND hWnd, DWORD dwLevel, void** ppDSFD, void** ppDSCBuffer8, void** ppDSBuffer8, void* pUnkOuter);
	HRESULT WINAPI DirectSoundFullDuplexCreate(LPCGUID pcGuidCaptureDevice, LPCGUID pcGuidRenderDevice, void* pcDSCBufferDesc, void* pcDSBufferDesc, HWND hWnd, DWORD dwLevel, void** ppDSFD, void** ppDSCBuffer8, void** ppDSBuffer8, void* pUnkOuter)
	{
		DirectSoundFullDuplexCreate_t s_Function = (DirectSoundFullDuplexCreate_t) GetDSoundFunction("DirectSoundFullDuplexCreate");

		if (!s_Function)
			return NULL;

		return s_Function(pcGuidCaptureDevice, pcGuidRenderDevice, pcDSCBufferDesc, pcDSBufferDesc, hWnd, dwLevel, ppDSFD, ppDSCBuffer8, ppDSBuffer8, pUnkOuter);
	}

	typedef HRESULT (WINAPI* DirectSoundCreate8_t)(LPCGUID lpGUID, void** ppDS8, void* pUnkOuter);
	HRESULT WINAPI DirectSoundCreate8(LPCGUID lpGUID, void** ppDS8, void* pUnkOuter)
	{
		DirectSoundCreate8_t s_Function = (DirectSoundCreate8_t) GetDSoundFunction("DirectSoundCreate8");

		if (!s_Function)
			return NULL;

		return s_Function(lpGUID, ppDS8, pUnkOuter);
	}

	typedef HRESULT (WINAPI* DirectSoundCaptureCreate8_t)(LPCGUID lpGUID, void** ppDSC8, void* pUnkOuter);
	HRESULT WINAPI DirectSoundCaptureCreate8(LPCGUID lpGUID, void** ppDSC8, void* pUnkOuter)
	{
		DirectSoundCaptureCreate8_t s_Function = (DirectSoundCaptureCreate8_t) GetDSoundFunction("DirectSoundCaptureCreate8");

		if (!s_Function)
			return NULL;

		return s_Function(lpGUID, ppDSC8, pUnkOuter);
	}
}