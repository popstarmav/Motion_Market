import 'package:flutter/material.dart';
import 'investment_screen.dart';
import 'portfolio_screen.dart';

class HomeScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Crypto Investment App'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            ElevatedButton(
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) => InvestmentScreen()),
                );
              },
              child: Text('Make an Investment'),
            ),
            ElevatedButton(
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) => PortfolioScreen()),
                );
              },
              child: Text('View Portfolio'),
            ),
          ],
        ),
      ),
    );
  }
}
