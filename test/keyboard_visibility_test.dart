import 'package:flutter_test/flutter_test.dart';
import 'package:keyboard_visibility/keyboard_visibility.dart';
import 'package:keyboard_visibility/keyboard_visibility_platform_interface.dart';
import 'package:keyboard_visibility/keyboard_visibility_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockKeyboardVisibilityPlatform
    with MockPlatformInterfaceMixin
    implements KeyboardVisibilityPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final KeyboardVisibilityPlatform initialPlatform = KeyboardVisibilityPlatform.instance;

  test('$MethodChannelKeyboardVisibility is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelKeyboardVisibility>());
  });

  test('getPlatformVersion', () async {
    KeyboardVisibility keyboardVisibilityPlugin = KeyboardVisibility();
    MockKeyboardVisibilityPlatform fakePlatform = MockKeyboardVisibilityPlatform();
    KeyboardVisibilityPlatform.instance = fakePlatform;

    expect(await keyboardVisibilityPlugin.getPlatformVersion(), '42');
  });
}
