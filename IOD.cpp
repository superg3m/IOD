#include <IOD.hpp>
#include <algorithm>

std::unordered_map<IOD_InputCode, IOD_InputState> IOD::input_state = {
    {IOD_KEY_A, IOD_InputState::UP}, {IOD_KEY_B, IOD_InputState::UP}, {IOD_KEY_C, IOD_InputState::UP},
    {IOD_KEY_D, IOD_InputState::UP}, {IOD_KEY_E, IOD_InputState::UP}, {IOD_KEY_F, IOD_InputState::UP},
    {IOD_KEY_G, IOD_InputState::UP}, {IOD_KEY_H, IOD_InputState::UP}, {IOD_KEY_I, IOD_InputState::UP},
    {IOD_KEY_J, IOD_InputState::UP}, {IOD_KEY_K, IOD_InputState::UP}, {IOD_KEY_L, IOD_InputState::UP},
    {IOD_KEY_M, IOD_InputState::UP}, {IOD_KEY_N, IOD_InputState::UP}, {IOD_KEY_O, IOD_InputState::UP},
    {IOD_KEY_P, IOD_InputState::UP}, {IOD_KEY_Q, IOD_InputState::UP}, {IOD_KEY_R, IOD_InputState::UP},
    {IOD_KEY_S, IOD_InputState::UP}, {IOD_KEY_T, IOD_InputState::UP}, {IOD_KEY_U, IOD_InputState::UP},
    {IOD_KEY_V, IOD_InputState::UP}, {IOD_KEY_W, IOD_InputState::UP}, {IOD_KEY_X, IOD_InputState::UP},
    {IOD_KEY_Y, IOD_InputState::UP}, {IOD_KEY_Z, IOD_InputState::UP},

    {IOD_KEY_0, IOD_InputState::UP}, {IOD_KEY_1, IOD_InputState::UP}, {IOD_KEY_2, IOD_InputState::UP},
    {IOD_KEY_3, IOD_InputState::UP}, {IOD_KEY_4, IOD_InputState::UP}, {IOD_KEY_5, IOD_InputState::UP},
    {IOD_KEY_6, IOD_InputState::UP}, {IOD_KEY_7, IOD_InputState::UP}, {IOD_KEY_8, IOD_InputState::UP},
    {IOD_KEY_9, IOD_InputState::UP},

    {IOD_KEY_SPACE, IOD_InputState::UP}, {IOD_KEY_ENTER, IOD_InputState::UP},
    {IOD_KEY_ESCAPE, IOD_InputState::UP}, {IOD_KEY_TAB, IOD_InputState::UP},
    {IOD_KEY_BACKSPACE, IOD_InputState::UP},

    {IOD_KEY_LEFT, IOD_InputState::UP}, {IOD_KEY_RIGHT, IOD_InputState::UP},
    {IOD_KEY_UP, IOD_InputState::UP}, {IOD_KEY_DOWN, IOD_InputState::UP},
    {IOD_KEY_CTRL, IOD_InputState::UP}, {IOD_KEY_SHIFT, IOD_InputState::UP},
    {IOD_KEY_ALT, IOD_InputState::UP},

    {IOD_KEY_F1, IOD_InputState::UP}, {IOD_KEY_F2, IOD_InputState::UP},
    {IOD_KEY_F3, IOD_InputState::UP}, {IOD_KEY_F4, IOD_InputState::UP},
    {IOD_KEY_F5, IOD_InputState::UP}, {IOD_KEY_F6, IOD_InputState::UP},
    {IOD_KEY_F7, IOD_InputState::UP}, {IOD_KEY_F8, IOD_InputState::UP},
    {IOD_KEY_F9, IOD_InputState::UP}, {IOD_KEY_F10, IOD_InputState::UP},
    {IOD_KEY_F11, IOD_InputState::UP}, {IOD_KEY_F12, IOD_InputState::UP},

    {IOD_MOUSE_BUTTON_LEFT, IOD_InputState::UP},
    {IOD_MOUSE_BUTTON_RIGHT, IOD_InputState::UP},
    {IOD_MOUSE_BUTTON_MIDDLE, IOD_InputState::UP}
};

std::unordered_map<std::string, IOD_Profile*> IOD::profiles;
float IOD::mouse_x = 0.0f;
float IOD::mouse_y = 0.0f;

inline bool IOD_input_state_has_flag(IOD_InputState value, IOD_InputState flag) {
    return (static_cast<uint8_t>(value) & static_cast<uint8_t>(flag)) != 0;
}

void IOD::updateInputCode(IOD_InputCode code, bool down) {
    if (down) {
        IOD::input_state[code] = (IOD::input_state[code] == IOD_InputState::UP || IOD::input_state[code] == IOD_InputState::RELEASED) ? IOD_InputState::PRESSED : IOD_InputState::DOWN;
    } else {
        IOD::input_state[code] = (IOD::input_state[code] == IOD_InputState::DOWN || IOD::input_state[code] == IOD_InputState::PRESSED) ? IOD_InputState::RELEASED : IOD_InputState::UP;
    }
}

void IOD::updateMousePosition(float x, float y) {
    mouse_x = x;
    mouse_y = y;
}

float IOD::getMouseX() { return mouse_x; }
float IOD::getMouseY() { return mouse_y; }

IOD_InputState IOD::getState(IOD_InputCode code) {
    return IOD::input_state[code];
}

void IOD::poll() {
    for (const auto& [key, profile] : profiles) {
        if (!profile->active) {
            continue;
        }

        for (const auto& [key_pair, fn] : profile->bindings) {
            IOD_InputCode code = key_pair.first;
            IOD_InputState desired_states = key_pair.second;
            IOD_InputState actual_state = IOD::input_state[code];
            if (IOD_input_state_has_flag(desired_states, actual_state) && fn) {
                fn();
            }
        }
    }
}

IOD_Profile* IOD::createProfile(const std::string &key) {
    IOD_Profile* ret = new IOD_Profile;
    ret->active = true;
    IOD::profiles[key] = ret;

    return ret;
}

IOD_Profile* IOD::getProfile(const std::string &key) {
    return IOD::profiles.at(key);
}

void IOD::deleteProfile(const std::string &key) {
    IOD::profiles.erase(key);
}


void IOD::enableProfile(const std::string& key) {
    IOD::profiles.at(key)->active = true;
}

void IOD::disableProfile(const std::string& key) {
    IOD::profiles.at(key)->active = false;
}

void IOD_Profile::bind(IOD_InputCode code, IOD_InputState state, const std::function<void ()> fn) {
    this->bindings[std::make_pair(code, state)] = fn;
}
void IOD_Profile::unbind(IOD_InputCode code, IOD_InputState state) {
    auto key = std::pair(code, state);
    this->bindings.erase(key);
}
    
