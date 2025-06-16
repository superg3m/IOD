#include <IOD.hpp>

std::unordered_map<IOD_InputCode, IOD_InputState> IOD::input_state;
std::unordered_map<std::string, IOD_Profile*> IOD::profiles;
float IOD::mouse_x = 0.0f;
float IOD::mouse_y = 0.0f;

void IOD::updateInputCode(IOD_InputCode code, bool down) {
    IOD_InputState& state = input_state[code];
    if (down) {
        state = (state == IOD_INPUT_STATE_UP || state == IOD_INPUT_STATE_RELEASED) ? IOD_INPUT_STATE_PRESSED : IOD_INPUT_STATE_DOWN;
    } else {
        state = (state == IOD_INPUT_STATE_DOWN || state == IOD_INPUT_STATE_PRESSED) ? IOD_INPUT_STATE_RELEASED : IOD_INPUT_STATE_UP;
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
            const auto &[code, desired_states] = key_pair;
            auto state = input_state[code];
            if ((state & desired_states) != 0 && fn) {
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
    
