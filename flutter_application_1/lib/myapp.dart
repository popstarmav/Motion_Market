import 'package:flutter/material.dart';
import 'home_screen.dart'; // Ensure HomeScreen is correctly implemented

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'My Application',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: HomeScreen(), // Your home screen widget
    );
  }
}
