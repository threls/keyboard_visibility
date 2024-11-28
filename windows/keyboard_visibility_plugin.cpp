#include "keyboard_visibility_plugin.h"

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include <flutter/event_channel.h>

#include <map>
#include <memory>
#include <sstream>

#include <windows.h>

namespace keyboard_visibility {

    class KeyboardVisibilityEventSink : public flutter::StreamHandler<flutter::EncodableValue> {
    public:
        std::unique_ptr <flutter::EventSink<flutter::EncodableValue>> onListen(
                const flutter::EncodableValue &arguments,
                std::unique_ptr<flutter::EventSink<flutter::EncodableValue>> &&events) override {
            event_sink_ = std::make_unique < flutter::EventSink < flutter::EncodableValue >> ();
            StartMonitoring();
            return std::move(event_sink_);
        }

        void onCancel(const flutter::EncodableValue &arguments) override {
            StopMonitoring();
            event_sink_.reset();
        }

    private:
        void StartMonitoring() {
            // Start a timer to periodically check keyboard visibility
            timer_id_ = SetTimer(NULL, 0, 100, TimerProc, (DWORD_PTR)
            this);
        }

        void StopMonitoring() {
            KillTimer(NULL, timer_id_);
        }

        static VOID CALLBACK
        TimerProc(HWND
        hwnd,
        UINT uMsg, UINT_PTR
        idEvent,
        DWORD dwTime
        ) {
            KeyboardVisibilityEventSink *sink = (KeyboardVisibilityEventSink *) idEvent;
            sink->CheckKeyboardVisibility();
        }

        void CheckKeyboardVisibility() {
            HWND hWnd = GetForegroundWindow();
            if (hWnd) {
                DWORD dwThreadId = GetWindowThreadProcessId(hWnd, NULL);
                HKL hkl = GetKeyboardLayout(dwThreadId);
                if (hkl) {
                    UINT uFlags = GetKeyboardState(NULL);
                    bool isVisible = (uFlags & KF_EXTENDED) != 0;
                    if (event_sink_) {
                        event_sink_->Success(flutter::EncodableValue(isVisible));
                    }
                }
            }
        }

        std::unique_ptr <flutter::EventSink<flutter::EncodableValue>> event_sink_;
        UINT_PTR timer_id_;
    };

// static
    void KeyboardVisibilityPlugin::RegisterWithRegistrar(
            flutter::PluginRegistrarWindows *registrar) {
        auto channel =
                std::make_unique < flutter::MethodChannel < flutter::EncodableValue >> (
                        registrar->messenger(), "keyboard_visibility",
                                &flutter::StandardMethodCodec::GetInstance());

        auto plugin = std::make_unique<KeyboardVisibilityPlugin>();

        channel->SetMethodCallHandler(
                [plugin_pointer = plugin.get()](const auto &call, auto result) {
                    plugin_pointer->HandleMethodCall(call, std::move(result));
                });

        registrar->AddPlugin(std::move(plugin));

        auto event_channel =
                std::make_unique < flutter::EventChannel < flutter::EncodableValue >> (
                        registrar->messenger(), "keyboard_visibility/events",
                                &flutter::StandardMethodCodec::GetInstance());

        auto event_sink = std::make_unique<KeyboardVisibilityEventSink>();

        event_channel->SetStreamHandler(std::move(event_sink));
    }

    KeyboardVisibilityPlugin::KeyboardVisibilityPlugin() {}

    KeyboardVisibilityPlugin::~KeyboardVisibilityPlugin() {}

    void KeyboardVisibilityPlugin::HandleMethodCall(
            const flutter::MethodCall <flutter::EncodableValue> &method_call,
            std::unique_ptr <flutter::MethodResult<flutter::EncodableValue>> result) {
        // This plugin doesn't implement any methods
        result->NotImplemented();
    }

}  // namespace keyboard_visibility