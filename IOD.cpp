#include <IOD.hpp>

std::unordered_map<IOD_InputCode, IOD_InputState> IOD::input_state;
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
    return input_state[code];
}

void IOD::poll() {
    for (const auto& [key, profile] : profiles) {
        if (!profile->active) {
            continue;
        }

        for (const auto& [key_pair, fn] : profile->bindings) {
            IOD_InputCode code = key_pair.first;
            IOD_InputState desired_states = key_pair.second;
            IOD_InputState actual_state = input_state[code];
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
    
