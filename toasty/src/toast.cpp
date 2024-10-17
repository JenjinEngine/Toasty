// This file focuses specifcally on the toast class
// It is not concerned with the rendering of the toast
// and instead just the logic of the toast

#include "toasty.h"

#include <imgui.h>

#include <iostream>
#include <cmath>

using namespace Toasty;

Toast::Toast(const char *text, float duration, ToastType type)
    : text(text), duration(duration), type(type) {
  startTime = std::chrono::steady_clock::now();
}

Toast::~Toast() {}

ImVec2 Toast::GetPosition() {
  auto now = std::chrono::steady_clock::now();
  auto displaySize = ImGui::GetIO().DisplaySize;

  // Calculate elapsed time since the toast appeared
  float elapsedTime = std::chrono::duration<float>(now - startTime).count();

  // Fixed animation duration after the toast is visible
  float animationDuration = 1.0f;  // For example, 1 second

  if (elapsedTime < duration) {
    // Toast is still static, hasn't started animating yet
    float x = displaySize.x - ImGui::CalcTextSize(text.c_str()).x - 16;
    return ImVec2(x, displaySize.y - 32); // Static position
  } else {
    // Start animation after the toast's duration ends
    float animationElapsedTime = elapsedTime - duration;
    float normalizedTime = std::clamp(animationElapsedTime / animationDuration, 0.0f, 1.0f); // 0 -> 1

    // Apply quadratic easing-in-out to normalized time
    if (normalizedTime < 0.5f) {
      normalizedTime = 2 * std::pow(normalizedTime, 2);
    } else {
      normalizedTime = 1 - std::pow(-2 * normalizedTime + 2, 2) / 2;
    }

    float x = normalizedTime * displaySize.x;
    float xR = x + (displaySize.x - ImGui::CalcTextSize(text.c_str()).x) - 16;

    return ImVec2(xR, displaySize.y - 32); // Animated position
  }
}

void Toast::Render() {
	static auto fg = ImGui::GetWindowDrawList();
	auto pos = this->GetPosition();

	// Draw a rounded rectangle
	static auto bg_c = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
	/*static auto fg_c = ImGui::GetStyle().Colors[ImGuiCol_Text];*/
	auto fg_c = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	if (type == ToastType::Info) {
		fg_c = ImVec4(0.2f, 1.0f, 0.2f, 1.0f);
	} else if (type == ToastType::Success) {
		fg_c = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
	} else if (type == ToastType::Warning) {
		fg_c = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
	} else if (type == ToastType::Error) {
		fg_c = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	}

	std::cout << "type: " << (int)type << std::endl;
	std::cout << "color: " << fg_c.x << ", " << fg_c.y << ", " << fg_c.z << ", " << fg_c.w << std::endl;

	auto padded = ImVec2(pos.x - 8, pos.y - 8);
	auto width = ImGui::CalcTextSize(text.c_str()).x + 16;
	auto height = ImGui::CalcTextSize(text.c_str()).y + 16;

	auto offset = ImVec2(padded.x + width, padded.y + height);
	auto dualPadded = ImVec2(padded.x + 8, padded.y + 8);

	// Rounded rectangle with border
	fg->AddRectFilled(padded, offset, (ImColor)bg_c, 8.0f);
	fg->AddRect(padded, offset, (ImColor)fg_c, 2, ImDrawFlags_RoundCornersAll, 2);

	fg->AddText(dualPadded, (ImColor)fg_c, text.c_str());
}
