#pragma once

#include "stdafx.h"

void UnlockHitman();

enum ZInputKey : uint32_t
{
	HM_VK_NONE = 0x0,
	HM_VK_ESCAPE = 0x1,
	HM_VK_1 = 0x2,
	HM_VK_2 = 0x3,
	HM_VK_3 = 0x4,
	HM_VK_4 = 0x5,
	HM_VK_5 = 0x6,
	HM_VK_6 = 0x7,
	HM_VK_7 = 0x8,
	HM_VK_8 = 0x9,
	HM_VK_9 = 0xA,
	HM_VK_0 = 0xB,
	HM_VK_BACK = 0xE,
	HM_VK_TAB = 0xF,
	HM_VK_Q = 0x10,
	HM_VK_W = 0x11,
	HM_VK_E = 0x12,
	HM_VK_R = 0x13,
	HM_VK_T = 0x14,
	HM_VK_Y = 0x15,
	HM_VK_U = 0x16,
	HM_VK_I = 0x17,
	HM_VK_O = 0x18,
	HM_VK_P = 0x19,
	HM_VK_RETURN = 0x1C,
	HM_VK_CONTROL = 0x1D,
	HM_VK_A = 0x1E,
	HM_VK_S = 0x1F,
	HM_VK_D = 0x20,
	HM_VK_F = 0x21,
	HM_VK_G = 0x22,
	HM_VK_H = 0x23,
	HM_VK_J = 0x24,
	HM_VK_K = 0x25,
	HM_VK_L = 0x26,
	HM_VK_SHIFT = 0x2A,
	HM_VK_Z = 0x2C,
	HM_VK_X = 0x2D,
	HM_VK_C = 0x2E,
	HM_VK_V = 0x2F,
	HM_VK_B = 0x30,
	HM_VK_N = 0x31,
	HM_VK_M = 0x32,
	HM_VK_DIVIDE = 0x35,
	HM_VK_RSHIFT = 0x36,
	HM_VK_MULTIPLY = 0x37,
	HM_VK_MENU = 0x38,
	HM_VK_SPACE = 0x39,
	HM_VK_CAPITAL = 0x3A,
	HM_VK_F1 = 0x3B,
	HM_VK_F2 = 0x3C,
	HM_VK_F3 = 0x3D,
	HM_VK_F4 = 0x3E,
	HM_VK_F5 = 0x3F,
	HM_VK_F6 = 0x40,
	HM_VK_F7 = 0x41,
	HM_VK_F8 = 0x42,
	HM_VK_F9 = 0x43,
	HM_VK_F10 = 0x44,
	HM_VK_NUMLOCK = 0x45,
	HM_VK_SCROLL = 0x46,
	HM_VK_NUMPAD7 = 0x47,
	HM_VK_NUMPAD8 = 0x48,
	HM_VK_NUMPAD9 = 0x49,
	HM_VK_SUBTRACT = 0x4A,
	HM_VK_NUMPAD4 = 0x4B,
	HM_VK_NUMPAD5 = 0x4C,
	HM_VK_NUMPAD6 = 0x4D,
	HM_VK_ADD = 0x4E,
	HM_VK_NUMPAD1 = 0x4F,
	HM_VK_NUMPAD2 = 0x50,
	HM_VK_NUMPAD3 = 0x51,
	HM_VK_NUMPAD0 = 0x52,
	HM_VK_DECIMAL = 0x53,
	HM_VK_SNAPSHOT = 0x54,
	HM_VK_F11 = 0x57,
	HM_VK_F12 = 0x58,
	HM_VK_HELP = 0x63,
	HM_VK_F13 = 0x64,
	HM_VK_F14 = 0x65,
	HM_VK_F15 = 0x66,
	HM_VK_F16 = 0x67,
	HM_VK_F17 = 0x68,
	HM_VK_F18 = 0x69,
	HM_VK_F19 = 0x6A,
	HM_VK_F20 = 0x6B,
	HM_VK_F21 = 0x6C,
	HM_VK_F22 = 0x6D,
	HM_VK_F23 = 0x6E,
	HM_VK_F24 = 0x76,
	HM_VK_NUMRETURN = 0x11C,
	HM_VK_RCONTROL = 0x11D,
	HM_VK_NUMDIVIDE = 0x135,
	HM_VK_RMENU = 0x138,
	HM_VK_UP = 0x148,
	HM_VK_LEFT = 0x14B,
	HM_VK_RIGHT = 0x14D,
	HM_VK_DOWN = 0x150,
	HM_VK_LBUTTON = 0x164,
	HM_VK_RBUTTON = 0x165,
	HM_VK_MBUTTON = 0x166,
	HM_VK_SELECT = 0x167,
	HM_VK_CANCEL = 0x146,
	HM_VK_HOME = 0x147,
	HM_VK_PRIOR = 0x149,
	HM_VK_CLEAR = 0x14C,
	HM_VK_END = 0x14F,
	HM_VK_NEXT = 0x151,
	HM_VK_INSERT = 0x152,
	HM_VK_DELETE = 0x153,
	HM_VK_OEM_2 = 0xC,
	HM_VK_OEM_3 = 0xD,
	HM_VK_OEM_4 = 0x1A,
	HM_VK_OEM_5 = 0x1B,
	HM_VK_OEM_6 = 0x27,
	HM_VK_OEM_7 = 0x28,
	HM_VK_OEM_8 = 0x29,
	HM_VK_OEM_9 = 0x2B,
	HM_VK_OEM_10 = 0x34,
	HM_VK_OEM_12 = 0x55,
	HM_VK_OEM_13 = 0x56,
	HM_VK_OEM_14 = 0x59,
	HM_VK_OEM_15 = 0x5A,
	HM_VK_OEM_16 = 0x5B,
	HM_VK_OEM_17 = 0x5C,
	HM_VK_OEM_18 = 0x5D,
	HM_VK_OEM_19 = 0x5E,
	HM_VK_OEM_20 = 0x5F,
	HM_VK_OEM_21 = 0x60,
	HM_VK_OEM_22 = 0x61,
	HM_VK_OEM_23 = 0x62,
	HM_VK_OEM_24 = 0x6F,
	HM_VK_OEM_25 = 0x70,
	HM_VK_OEM_26 = 0x71,
	HM_VK_OEM_27 = 0x72,
	HM_VK_OEM_28 = 0x73,
	HM_VK_OEM_29 = 0x74,
	HM_VK_OEM_30 = 0x75,
	HM_VK_INVALID = 0x10FF
};

struct ZInput
{
	const char* m_Action;
	ZInputKey m_DefaultInput;
	ZInputKey m_WASDInput;
};

ALIGN(1) struct ZInputAction
{
	const char* m_Action;
	uint32_t m_Unknown01;
	const char* m_FirstInput;
	const char* m_SecondInput;
	uint64_t m_Unknown02;
	bool m_Unknown03;
};

ALIGN(1) class ZSysInput
{
public:
	virtual void unk001() = 0; // 0
	virtual void unk002() = 0; // 4
	virtual void unk003() = 0; // 8
	virtual void unk004() = 0; // 12
	virtual void unk005() = 0; // 16
	virtual void unk006() = 0; // 20
	virtual void unk007() = 0; // 24
	virtual void unk008() = 0; // 28
	virtual void unk009() = 0; // 32
	virtual bool isPressed(const char* key, int a2) = 0; // 36
	virtual void unk011() = 0; // 40
	virtual void unk012() = 0; // 44
	virtual void unk013() = 0; // 48
	virtual void unk014() = 0; // 52
	virtual void unk015() = 0; // 56
	virtual void unk016() = 0; // 60
	virtual void unk017() = 0; // 64
	virtual void unk018() = 0; // 68
	virtual void unk019() = 0; // 72
	virtual void unk020() = 0; // 76
	virtual void unk021() = 0; // 80
};

ALIGN(1) class ZSysInterface
{
public:
	PAD(0x37B1);
	ZSysInput* m_Input;
}; 