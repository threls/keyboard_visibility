#include "include/keyboard_visibility/keyboard_visibility_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "keyboard_visibility_plugin.h"

void KeyboardVisibilityPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  keyboard_visibility::KeyboardVisibilityPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
