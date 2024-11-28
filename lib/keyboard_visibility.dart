import 'dart:async';

import 'package:flutter/services.dart';

class KeyboardVisibility {
  static const EventChannel _eventChannel = EventChannel('keyboard_visibility/events');

  static Stream<bool> get keyboardVisibilityStream {
    return _eventChannel.receiveBroadcastStream().map((dynamic event) => event as bool);
  }
}
