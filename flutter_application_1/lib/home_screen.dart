import 'package:flutter/material.dart';
import 'backend.dart'; // Ensure this file exists and correctly implements the bindings to the C++ code.

class HomeScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    // Ensure the `Backend` class is defined in `backend.dart` and the `getMessage` method works.
    final backend = Backend(); // Create an instance of the Backend class.
    final message = backend.getMessage(); // Call the `getMessage` method.

    return Scaffold(
      appBar: AppBar(
        title: const Text('C++ Integration'),
      ),
      body: Center(
        child: Text('Message from C++: $message'),
      ),
    );
  }
}
