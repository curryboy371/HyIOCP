#pragma once

#include "resource.h"


extern HWND hEditOutput;   // 출력 창 핸들
void AddTextToOutput(const std::wstring& text);
void AddTextToOutput(const std::string& text);
void SendUserMessage(const std::wstring& text);
void SendUserMessage(const std::string& text);

