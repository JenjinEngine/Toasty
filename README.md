# Toasty

A Dear ImGui notification system.

## Usage

```cpp
while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    ImGui::Begin("Toasted demo");

    if (ImGui::Button("Show toast")) {
        ImGui::NewToast(Toasty::ToastType::Info, "Hello, world!");
    }

    ImGui::End();

    // Render notifications
    ImGui::ToastedRender();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
}
```

## License

MIT
