#pragma once
#include <Windows.h>
#include "Vector.h"
#include <string>

class WindowsAPI final
{
private:
	HWND hwnd;
	WNDCLASSEX w{};
	WindowsAPI() = default;
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:
	// ウィンドウサイズ
	static const Vector2 WIN_SIZE;

	static WindowsAPI* GetInstance();
	WindowsAPI(const WindowsAPI& obj) = delete;
	void Initialize(const std::wstring& windowName = L"");
	bool ProcessMessage();
	void Finalize();
	HDC SetFont(const std::wstring& fontName);
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return w.hInstance; }
};