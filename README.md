# IOD

```cpp
// Usage Code

GLFWwindow* window = (GLFWwindow*)IOD::glfw_window_instance;
const bool SHIFT = IOD::GetKey(IOD::KEY_SHIFT, IOD::PRESSED|IOD::DOWN);

if (IOD::GetKeyPressed(IOD::KEY_ESCAPE)) {
    glfwSetWindowShouldClose(window, true);
}

if (IOD::GetKeyPressed(IOD::KEY_R)) {
    cloud_shader.compile();
    terrain_shader.compile();
    uniform_shader.compile();
}

if (IOD::GetKeyPressed(IOD::KEY_K)) {
    smooth_camera = !smooth_camera;
    IOD::ToggleProfile(MOVEMENT_PROFILE, movement_profile_active && !smooth_camera);
}

if (IOD::GetKeyPressed(IOD::KEY_0)) {
    emit = !emit;
}

if (SHIFT && IOD::GetKeyPressed(IOD::KEY_W)) {
    movement_profile_active = !movement_profile_active;
    IOD::ToggleProfile(MOVEMENT_PROFILE, movement_profile_active && !smooth_camera);
    IOD::ToggleProfile(LIGHT_PROFILE, !movement_profile_active);
}

if (IOD::GetKeyPressed(IOD::KEY_L)) {
    Renderer::SetWireFrame(true);
} else if (IOD::GetKeyReleased(IOD::KEY_L)) {
    Renderer::SetWireFrame(false);
}

if (IOD::GetKeyPressed(IOD::KEY_C)) {
    mouse_captured = !mouse_captured;
    glfwSetIODMode(window, GLFW_CURSOR, mouse_captured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

if (IOD::GetKeyPressed(IOD::KEY_0)) {
    render_shading = !render_shading;
}

if (IOD::GetKeyPressed(IOD::KEY_N)) {
    render_normals = !render_normals;
}

if (IOD::GetKey(IOD::KEY_UP, IOD::PRESSED|IOD::DOWN)) {
    height_boost += 2;
}

if (IOD::GetKey(IOD::KEY_DOWN, IOD::PRESSED|IOD::DOWN)) {
    height_boost -= 2;
}
```