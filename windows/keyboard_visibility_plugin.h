#ifndef FLUTTER_PLUGIN_KEYBOARD_VISIBILITY_PLUGIN_H_
#define FLUTTER_PLUGIN_KEYBOARD_VISIBILITY_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace keyboard_visibility {

class KeyboardVisibilityPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  KeyboardVisibilityPlugin();

  virtual ~KeyboardVisibilityPlugin();

  // Disallow copy and assign.
  KeyboardVisibilityPlugin(const KeyboardVisibilityPlugin&) = delete;
  KeyboardVisibilityPlugin& operator=(const KeyboardVisibilityPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace keyboard_visibility

#endif  // FLUTTER_PLUGIN_KEYBOARD_VISIBILITY_PLUGIN_H_
