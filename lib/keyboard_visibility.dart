import 'dart:async';

import 'package:flutter/services.dart';

class KeyboardVisibility {
  static const MethodChannel _channel = MethodChannel('keyboard_visibility');

  static Future<bool?> isKeyboardVisible() async {
    try {
      final bool? isVisible = await _channel.invokeMethod('isKeyboardVisible');
      return isVisible;
    } on PlatformException catch (e) {
      print('Failed to check keyboard visibility: ${e.message}');
      return false;
    }
  }
}