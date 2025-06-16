#pragma once

#include <set>
#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <functional>
#include <unordered_map>

enum class IOD_InputState : uint8_t {
    UP       = 0x1,
    PRESSED  = 0x2,
    DOWN     = 0x4,
    RELEASED = 0x8
};

#define IOD_INPUT_STATE_HAS_FLAG(value, flag) ((static_cast<uint8_t>(value) & static_cast<uint8_t>(flag)) != 0)

inline constexpr IOD_InputState operator|(IOD_InputState lhs, IOD_InputState rhs) {
    return static_cast<IOD_InputState>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

enum IOD_InputCode : uint8_t {
    IOD_KEY_A = 'A', IOD_KEY_B = 'B', IOD_KEY_C = 'C', IOD_KEY_D = 'D',
    IOD_KEY_E = 'E', IOD_KEY_F = 'F', IOD_KEY_G = 'G', IOD_KEY_H = 'H',
    IOD_KEY_I = 'I', IOD_KEY_J = 'J', IOD_KEY_K = 'K', IOD_KEY_L = 'L',
    IOD_KEY_M = 'M', IOD_KEY_N = 'N', IOD_KEY_O = 'O', IOD_KEY_P = 'P',
    IOD_KEY_Q = 'Q', IOD_KEY_R = 'R', IOD_KEY_S = 'S', IOD_KEY_T = 'T',
    IOD_KEY_U = 'U', IOD_KEY_V = 'V', IOD_KEY_W = 'W', IOD_KEY_X = 'X',
    IOD_KEY_Y = 'Y', IOD_KEY_Z = 'Z',

    IOD_KEY_0 = '0', IOD_KEY_1 = '1', IOD_KEY_2 = '2', IOD_KEY_3 = '3',
    IOD_KEY_4 = '4', IOD_KEY_5 = '5', IOD_KEY_6 = '6', IOD_KEY_7 = '7',
    IOD_KEY_8 = '8', IOD_KEY_9 = '9',

    IOD_KEY_SPACE = 32, IOD_KEY_ENTER = 13, IOD_KEY_ESCAPE = 27,
    IOD_KEY_TAB = 9, IOD_KEY_BACKSPACE = 8,

    IOD_KEY_LEFT = 128, IOD_KEY_RIGHT, IOD_KEY_UP, IOD_KEY_DOWN,
    IOD_KEY_CTRL, IOD_KEY_SHIFT, IOD_KEY_ALT,

    IOD_KEY_F1, IOD_KEY_F2, IOD_KEY_F3, IOD_KEY_F4, IOD_KEY_F5, IOD_KEY_F6,
    IOD_KEY_F7, IOD_KEY_F8, IOD_KEY_F9, IOD_KEY_F10, IOD_KEY_F11, IOD_KEY_F12,

    IOD_MOUSE_BUTTON_LEFT = 200,
    IOD_MOUSE_BUTTON_RIGHT,
    IOD_MOUSE_BUTTON_MIDDLE
};

struct IOD_Profile {
    bool active;
    std::map<std::pair<IOD_InputCode, IOD_InputState>, std::function<void()>> bindings;

    void bind(IOD_InputCode code, IOD_InputState state, std::function<void()> fn);
    void unbind(IOD_InputCode code, IOD_InputState state);
};

struct IOD {
    static void poll();
    static void updateInputCode(IOD_InputCode code, bool down);
    static void updateMousePosition(float x, float y);

    static IOD_InputState getState(IOD_InputCode code);
    static float getMouseX();
    static float getMouseY();

    static IOD_Profile* createProfile(const std::string &key);
    static IOD_Profile* getProfile(const std::string &key);
    static void deleteProfile(const std::string &key);
    static void enableProfile(const std::string &key);
    static void disableProfile(const std::string &key);

    static std::unordered_map<IOD_InputCode, IOD_InputState> input_state;
    static std::unordered_map<std::string, IOD_Profile*> profiles;
private:
    static float mouse_x;
    static float mouse_y;
};