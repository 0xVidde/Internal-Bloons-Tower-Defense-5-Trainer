#pragma once
#include <Windows.h>
#include <vector>

namespace Offsets
{
	DWORD PlayerBase = 0x00A2EA10;

	std::vector<DWORD> dollar_offsets = { 0xC0, 0x118 };
	std::vector<DWORD> coin_offsets = { 0xC0, 0x120 };
	std::vector<DWORD> money_offsets = { 0xC4, 0x90 };
	std::vector<DWORD> health_offsets = { 0xC4, 0x88 };
	std::vector<DWORD> round_offsets = { 0x7C, 0x14 };
	std::vector<DWORD> rank_offsets = { 0xC0, 0x20 };
}