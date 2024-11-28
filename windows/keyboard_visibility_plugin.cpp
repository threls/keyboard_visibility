#include "keyboard_visibility_plugin.h"

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <map>
#include <memory>
#include <sstream>

#include <windows.h>

namespace keyboard_visibility {

// static
    void KeyboardVisibilityPlugin::RegisterWithRegistrar(
            flutter::PluginRegistrarWindows *registrar) {
        auto channel =
                std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
                        registrar->messenger(), "keyboard_visibility",
                                &flutter::StandardMethodCodec::GetInstance());

        auto plugin = std::make_unique<KeyboardVisibilityPlugin>();

        channel->SetMethodCallHandler(
                [plugin_pointer = plugin.get()](const auto &call, auto result) {
                    plugin_pointer->HandleMethodCall(call, std::move(result));
                });

        registrar->AddPlugin(std::move(plugin));
    }

    KeyboardVisibilityPlugin::KeyboardVisibilityPlugin() {}

    KeyboardVisibilityPlugin::~KeyboardVisibilityPlugin() {}

    void KeyboardVisibilityPlugin::HandleMethodCall(
            const flutter::MethodCall<flutter::EncodableValue> &method_call,
            std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
        if (method_call.method_name().compare("isKeyboardVisible") == 0) {
            HWND hWnd = GetForegroundWindow();
            if (hWnd) {
                DWORD dwThreadId = GetWindowThreadProcessId(hWnd, NULL);
                HKL hkl = GetKeyboardLayout(dwThreadId);
                if (hkl) {
                    UINT uFlags = GetKeyboardState(NULL);
                    if (uFlags & KF_EXTENDED) {
                        result->Success(flutter::EncodableValue(true)); // Keyboard is open
                        return;
                    }
                }
            }
            result->Success(flutter::EncodableValue(false)); // Keyboard is closed
        } else {
            result->NotImplemented();
        }
    }

}  // namespace keyboard_visibility