#pragma once

#include <chrono>
#include <imgui.h>

namespace Toasty {
enum class ToastType { Info, Success, Warning, Error };

class Toast {
public:
  Toast(const char *text, float duration = 1.0f, ToastType type = ToastType::Info);
  ~Toast();

  ImVec2 GetPosition();
  void Render();

	ImColor GetColor();

  std::string text;
	ToastType type;

private:
  std::chrono::time_point<std::chrono::steady_clock> startTime;
  float duration;
};
} // namespace Toasty

namespace ImGui {
extern std::vector<Toasty::Toast> toasts;

void NewToast(Toasty::ToastType type = Toasty::ToastType::Info,
              const char *text = nullptr, float duration = 1.0f);

void ToastedRender();
} // namespace ImGui
