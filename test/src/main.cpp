#include "imdecorated.h"
#include "toasty.h"

#include <spdlog/common.h>
#include <spdlog/spdlog.h>

#include <imgui.h>

int main() {
	spdlog::set_level(spdlog::level::trace);

	ImDecorated::Window window(800, 600, "ImDecorated");

	window.gui([&](GLFWwindow* context) {
		ImGui::Text("Hello, world!");

		static auto toastType = Toasty::ToastType::Info;
		static char toastText[256] = { 0 };

		if (ImGui::BeginCombo("Toast Type", toastType == Toasty::ToastType::Info ? "Info" : toastType == Toasty::ToastType::Warning ? "Warning" : "Error")) {
			if (ImGui::Selectable("Info", toastType == Toasty::ToastType::Info)) {
				toastType = Toasty::ToastType::Info;
			}
			if (ImGui::Selectable("Warning", toastType == Toasty::ToastType::Warning)) {
				toastType = Toasty::ToastType::Warning;
			}
			if (ImGui::Selectable("Error", toastType == Toasty::ToastType::Error)) {
				toastType = Toasty::ToastType::Error;
			}
			ImGui::EndCombo();
		}

		ImGui::InputText("Toast Text", toastText, sizeof(toastText));

		if (ImGui::Button("Toast it!")) {
			ImGui::NewToast(toastType, toastText);
		}

		ImGui::ToastedRender();
	});

	window.launch();
}
