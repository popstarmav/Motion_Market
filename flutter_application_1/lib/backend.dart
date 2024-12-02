import 'dart:ffi';
import 'package:ffi/ffi.dart';

typedef GetMessageFunc = Pointer<Utf8> Function();
typedef GetMessage = Pointer<Utf8> Function();

class Backend {
  final DynamicLibrary _library;

  Backend()
      : _library =
            DynamicLibrary.open('libbackend.so'); // Ensure the correct path.

  String getMessage() {
    final getMessagePointer =
        _library.lookupFunction<GetMessageFunc, GetMessage>('getMessage');
    final messagePointer = getMessagePointer();
    return messagePointer.toDartString(); // Convert from Utf8 to Dart String.
  }
}
