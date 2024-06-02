#pragma once

#include "Resource.h"
#include <locale>
#include <codecvt>

extern HWND hEditOutput;   // 출력 창 핸들

std::string ConvertUTF8(const std::wstring& wstr);
std::wstring ConvertUTF8(const std::string& str);


void AddTextToOutput(const std::wstring& text);
void AddTextToOutput(const std::string& text);
void SendUserMessage(const std::wstring& text);
void SendUserMessage(const std::string& text);

