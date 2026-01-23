#define NOMINMAX
#include "ScreenBuffer.h"

#include <cstring>
#include <cstddef>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define CONIOEX
#include "conioex.h"

wchar_t ScreenBuffer::base[ScreenBuffer::HEIGHT][ScreenBuffer::WIDTH + 1];
wchar_t ScreenBuffer::overlay[ScreenBuffer::HEIGHT][ScreenBuffer::WIDTH + 1];
unsigned short ScreenBuffer::ttl[ScreenBuffer::HEIGHT][ScreenBuffer::WIDTH];

namespace {
	std::wstring utf8_to_wstring(const std::string& s) {
		if (s.empty()) return L"";

		const int len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), static_cast<int>(s.size()), nullptr, 0);
		if (len <= 0) return L"";

		std::wstring out(static_cast<std::size_t>(len), L'\0');
		MultiByteToWideChar(CP_UTF8, 0, s.c_str(), static_cast<int>(s.size()), out.data(), len);
		return out;
	}

	// 簡易: ASCII は 1セル、それ以外は 2セル（全角想定）
	int cell_width(wchar_t ch) {
		if (ch >= 0 && ch <= 0x7F) return 1;
		return 2;
	}
}

void ScreenBuffer::Initialize() {
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			base[y][x] = L' ';
			overlay[y][x] = L' ';
			ttl[y][x] = 0;
		}
		base[y][WIDTH] = L'\0';
		overlay[y][WIDTH] = L'\0';
	}

	// 出力を Unicode 想定に寄せる（WriteConsoleW を使うので必須ではないが保険）
	SetConsoleOutputCP(CP_UTF8);
}

void ScreenBuffer::Clear() {
	// base は従来通り毎フレーム全面消去
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			base[y][x] = L' ';
		}
		base[y][WIDTH] = L'\0';
	}

	// overlay は ttl を減らして、切れたセルだけ消す
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			if (ttl[y][x] > 0) {
				--ttl[y][x];
				if (ttl[y][x] == 0) {
					overlay[y][x] = L' ';
				}
			}
		}
		overlay[y][WIDTH] = L'\0';
	}
}

void ScreenBuffer::Print(int x, int y, const std::string& text, int frames) {
	int px = x - 1;
	int py = y - 1;

	if (py < 0 || py >= HEIGHT) return;
	if (px >= WIDTH) return;
	if (px < 0) px = 0;

	const bool useOverlay = (frames > 0);
	const unsigned short f = useOverlay ? static_cast<unsigned short>(frames) : 0;

	const std::wstring w = utf8_to_wstring(text);

	int cx = px;
	for (wchar_t ch : w) {
		if (cx < 0) { cx = 0; }
		if (cx >= WIDTH) break;

		const int wcell = cell_width(ch);

		// 1セルでも2セルでも、書き込み先が範囲内かで厳密に判定
		if (wcell == 1) {
			if (useOverlay) {
				overlay[py][cx] = ch;
				ttl[py][cx] = f;
			}
			else {
				base[py][cx] = ch;
			}
			++cx;
			continue;
		}

		// 2セル：2マス分の確保ができないなら終了（cx+1 を安全にする）
		if (cx + 1 >= WIDTH) break;

		if (useOverlay) {
			overlay[py][cx] = ch;
			ttl[py][cx] = f;

			overlay[py][cx + 1] = L' ';   // 後続セルを潰す
			ttl[py][cx + 1] = f;
		}
		else {
			base[py][cx] = ch;
			base[py][cx + 1] = L' ';      // 後続セルを潰す
		}

		cx += 2;
	}
}

void ScreenBuffer::Show() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE || hOut == nullptr) return;

	// (0,0) に移動（gotoxy より WriteConsoleW と整合しやすい）
	{
		CONSOLE_SCREEN_BUFFER_INFO info{};
		if (GetConsoleScreenBufferInfo(hOut, &info)) {
			COORD home{ 0, 0 };
			SetConsoleCursorPosition(hOut, home);
		}
	}

	std::wstring output;
	output.reserve(WIDTH * HEIGHT + HEIGHT);

	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			const wchar_t c = (overlay[y][x] != L' ') ? overlay[y][x] : base[y][x];
			output.push_back(c);
		}
		if (y < HEIGHT - 1) output.push_back(L'\n');
	}

	DWORD written = 0;
	if (!WriteConsoleW(hOut, output.c_str(), static_cast<DWORD>(output.size()), &written, nullptr)) {
		// フォールバック（コンソール以外に出ている時など）
		// UTF-8に戻して std::cout へ（最低限落ちないように）
		const int len = WideCharToMultiByte(CP_UTF8, 0, output.c_str(), static_cast<int>(output.size()),
			nullptr, 0, nullptr, nullptr);

		if (len > 0) {
			std::string u8(static_cast<std::size_t>(len), '\0');
			WideCharToMultiByte(CP_UTF8, 0, output.c_str(), static_cast<int>(output.size()),
				u8.data(), len, nullptr, nullptr);

			OutputDebugStringA(u8.c_str());
		}
	}
}

void ScreenBuffer::Print(int x, int y, std::u8string_view text, int frames) {
	// char8_t -> char のバイト列として渡す（UTF-8として解釈する前提）
	const auto* p = reinterpret_cast<const char*>(text.data());
	std::string s(p, p + text.size());
	Print(x, y, s, frames);
}