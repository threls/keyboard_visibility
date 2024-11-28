import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'keyboard_visibility_platform_interface.dart';

/// An implementation of [KeyboardVisibilityPlatform] that uses method channels.
class MethodChannelKeyboardVisibility extends KeyboardVisibilityPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('keyboard_visibility');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }
}
