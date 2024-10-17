// This file focuses on the API of the toasty library
// and integration with Dear ImGui, it is not concerned
// with how the toasts are positioned, their logic, etc.

#include "toasty.h"

#include <iostream>
#include <vector>

#include <imgui.h>

namespace ImGui {
std::vector<Toasty::Toast> toasts;

void ToastedRender() {
	int it = 0;
  for (Toasty::Toast &toast : toasts) {
    // If the position of the toast is off the screen, we need to just delete it
    // (muhahaha)
		auto pos = toast.GetPosition();
		auto screenSize = ImGui::GetIO().DisplaySize;

		if (pos.x < 0 || pos.y < 0 || pos.x > screenSize.x + 32 || pos.y > screenSize.y + 32) {
			toasts.erase(toasts.begin() + it++);
			continue;
		}

		toast.Render();
  }
}

void NewToast(Toasty::ToastType type, const char *text, float duration) {
  if (text) {
    toasts.emplace_back(text, duration, type);
  }
}
} // namespace ImGui
