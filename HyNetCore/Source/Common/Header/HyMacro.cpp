#pragma once
#include "Netpch.h"

#include <string>
#include <cstdio>
#include <cstring>

void log_message_string(const std::string& level, const char* message) {
    printf_s("[%s] %s\n", level.c_str(), message);
}