#include "stdafx.h"
#include "imgui.h"
#include "ImGuiManager.h"
#include "GlobalVar.h"



void IGAction() {
	ImGui::Begin("Global Var");

	ImGui::SliderInt("Base HP", &BASE_HP, 1, 20);

	ImGui::End();
}