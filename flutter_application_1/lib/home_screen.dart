import 'package:flutter/material.dart';
// Import the bindings

class HomeScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    // Call the C++ function and display its output
    final message = backend.getMessage();

    return Scaffold(
      appBar: AppBar(
        title: Text('C++ Integration'),
      ),
      body: Center(
        child: Text('Message from C++: $message'),
      ),
    );
  }
}
