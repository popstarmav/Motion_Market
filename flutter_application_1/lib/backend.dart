import 'dart:ffi';
import 'package:ffi/ffi.dart';

typedef GetMessageFunc = Pointer<Utf8> Function();
typedef GetMessage = Pointer<Utf8> Function();

class BackendBindings {
  late DynamicLibrary _backend;

  BackendBindings() {
    _backend = DynamicLibrary.open('libcpp_backend.so');
  }

  String getBlockchainMessage() {
    final GetMessage getBlockchainMessage = _backend
        .lookup<NativeFunction<GetMessageFunc>>('get_blockchain_message')
        .asFunction();
    return getBlockchainMessage().toDartString();
  }

  String getGraphMessage() {
    final GetMessage getGraphMessage = _backend
        .lookup<NativeFunction<GetMessageFunc>>('get_graph_message')
        .asFunction();
    return getGraphMessage().toDartString();
  }
}
