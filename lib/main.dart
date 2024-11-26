import 'package:flutter/material.dart';
import 'screens/home_screen.dart';

void main() {
  runApp(CryptoInvestmentApp());
}

class CryptoInvestmentApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Crypto Investment App',
      theme: ThemeData(primarySwatch: Colors.blue),
      home: HomeScreen(),
    );
  }
}
