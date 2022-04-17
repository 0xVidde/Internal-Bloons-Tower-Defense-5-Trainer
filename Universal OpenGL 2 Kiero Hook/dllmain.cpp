#include <Windows.h>
#include "include/imgui_hook.h"
#include "include/imgui/imgui.h"
#include <vector>
#include "Offsets.h"
#include <chrono>
#include <thread>

int desDollars;
int desCoins;
int desMoney;
int desHealth;
int desRound;
int desRank;

bool open = true;
bool openTemp = true;

static int tabb = 0;


static float textColor[] = { 1.f, 1.f, 1.f, 1.f };
static float buttonColor[] = { .1f, .3f, 0.4f, 1.f };
static float tabColor[] = { .1f, .3f, 0.4f, 1.f };
static float backgroundColor[] = { 0.f, 0.f, 0.f, 0.7f };

bool showTCW = false;
bool showBCW = false;
bool showWBCW = false;
bool showTTCW = false;

DWORD GetPointerAdress(DWORD ptr, std::vector<DWORD> offsets) {
	DWORD addr = ptr;
	for (int i = 0; i < offsets.size(); ++i) {
		addr = *(DWORD*)addr;
		addr += offsets[i];
	}
	return addr;
}


DWORD WINAPI AllocateConsole(LPVOID lp)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	return 0;
}

DWORD WINAPI MainThread(LPVOID lp) 
{
	DWORD moduleBase = (DWORD)GetModuleHandle(L"BTD5-Win.exe");

	while (true) {
		if (GetKeyState(VK_TAB) && 0x8000 && openTemp) {
			open = !open;
			openTemp = false;
		}
		if (!GetKeyState(VK_TAB) && 0x8000) {
			openTemp = true;
		}
	}

	return 0;
}

DWORD SetDollars() 
{
	DWORD moduleBase = (DWORD)GetModuleHandle(L"BTD5-Win.exe");
	int* dollars = (int*)GetPointerAdress(moduleBase + Offsets::PlayerBase, Offsets::dollar_offsets);
	*dollars = desDollars;
}

DWORD SetCoins()
{
	DWORD moduleBase = (DWORD)GetModuleHandle(L"BTD5-Win.exe");
	int* coins = (int*)GetPointerAdress(moduleBase + Offsets::PlayerBase, Offsets::coin_offsets);
	*coins = desCoins;
}

DWORD SetMoney()
{
	DWORD moduleBase = (DWORD)GetModuleHandle(L"BTD5-Win.exe");
	double* money = (double*)GetPointerAdress(moduleBase + Offsets::PlayerBase, Offsets::money_offsets);
	*money = desMoney;
}

DWORD SetHealth()
{
	DWORD moduleBase = (DWORD)GetModuleHandle(L"BTD5-Win.exe");
	int* health = (int*)GetPointerAdress(moduleBase + Offsets::PlayerBase, Offsets::health_offsets);
	*health = desHealth;
}

DWORD SetRound()
{
	DWORD moduleBase = (DWORD)GetModuleHandle(L"BTD5-Win.exe");
	int* round = (int*)GetPointerAdress(moduleBase + Offsets::PlayerBase, Offsets::round_offsets);
	*round = desRound;
}

DWORD SetRank()
{
	DWORD moduleBase = (DWORD)GetModuleHandle(L"BTD5-Win.exe");
	int* rank = (int*)GetPointerAdress(moduleBase + Offsets::PlayerBase, Offsets::rank_offsets);
	*rank = desRank;
}

void RenderMain() 
{
	if (open) {
		ImGui::Begin("Bloons TD5 Trainer By Vidde",
			&open
		);

		ImVec4* colors = ImGui::GetStyle().Colors;

		if (ImGui::BeginTabBar("Tabs")) {
			if (ImGui::BeginTabItem("Main Game")) {
				ImGui::Spacing();
				ImGui::SliderInt("Dollars", &desDollars, 0, 1000000);
				if (ImGui::Button("Apply Dollars"))
				{
					SetDollars();
				}
				ImGui::Spacing();
				ImGui::SliderInt("Coins", &desCoins, 0, 1000000);
				if (ImGui::Button("Apply Coins"))
				{
					SetCoins();
				}
				ImGui::Spacing();
				ImGui::SliderInt("Rank", &desRank, 0, 200);
				if (ImGui::Button("Apply Rank"))
				{
					SetRank();
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("In Game")) {
				ImGui::Spacing();
				ImGui::SliderInt("Money", &desMoney, 0, 1000000);
				if (ImGui::Button("Apply Money"))
				{
					SetMoney();
				}
				ImGui::Spacing();
				ImGui::SliderInt("Health", &desHealth, 0, 1000000);
				if (ImGui::Button("Apply Health"))
				{
					SetHealth();
				}
				ImGui::Spacing();
				ImGui::SliderInt("Round", &desRound, 0, 1000);
				if (ImGui::Button("Apply Round"))
				{
					SetRound();
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Visuals")) {
				ImGui::Spacing();
				if (ImGui::Button("Edit Text Color"))
					showTCW = !showTCW;
				if (ImGui::Button("Edit Button Color"))
					showBCW = !showBCW;
				if (ImGui::Button("Edit Window Background Color"))
					showWBCW = !showWBCW;
				if (ImGui::Button("Edit Tab Color"))
					showTTCW = !showTTCW;

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Miscellaneous")) {
				ImGui::Spacing();
				if (ImGui::Button("Allocate Console")) {
					AllocateConsole(0);
				}

				ImGui::EndTabItem();
			}

			ImGui::EndTabItem();
		}

		ImGui::End();

		if (showTCW) {
			ImGui::Begin("Edit Text Color");

			ImGui::ColorEdit4("Edit", textColor);
			colors[ImGuiCol_Text] = ImVec4(textColor[0], textColor[1], textColor[2], textColor[3]);

			ImGui::End();
		}

		if (showBCW) {
			ImGui::Begin("Edit Button Color");

			ImGui::ColorEdit4("Edit", buttonColor);
			colors[ImGuiCol_Button] = ImVec4(buttonColor[0], buttonColor[1], buttonColor[2], buttonColor[3]);
			colors[ImGuiCol_ButtonHovered] = ImVec4(buttonColor[0], buttonColor[1], buttonColor[2], buttonColor[3] - 0.1);

			ImGui::End();
		}

		if (showWBCW) {
			ImGui::Begin("Edit Window Background Color");

			ImGui::ColorEdit4("Edit", backgroundColor);
			colors[ImGuiCol_WindowBg] = ImVec4(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);

			ImGui::End();
		}

		if (showTTCW) {
			ImGui::Begin("Edit Tab Color");

			ImGui::ColorEdit4("Edit", tabColor);
			colors[ImGuiCol_Tab] = ImVec4(tabColor[0], tabColor[1], tabColor[2], tabColor[3]);
			colors[ImGuiCol_TabHovered] = ImVec4(tabColor[0], tabColor[1], tabColor[2], tabColor[3] - 0.1);
			colors[ImGuiCol_TabActive] = ImVec4(tabColor[0], tabColor[1], tabColor[2], tabColor[3] + 0.4);

			ImGui::End();
		}
	}
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		ImGuiHook::Load(RenderMain);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		ImGuiHook::Unload();
		break;
	}
	return TRUE;
}