import 'package:flutter/material.dart';

class PortfolioScreen extends StatelessWidget {
  final List<Map<String, dynamic>> portfolio = [
    {'crypto': 'BTC', 'artist': 'Taylor Swift', 'value': 150.25},
    {'crypto': 'ETH', 'artist': 'Billie Eilish', 'value': 100.75},
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Portfolio Screen'),
      ),
      body: ListView.builder(
        itemCount: portfolio.length,
        itemBuilder: (context, index) {
          final item = portfolio[index];
          return ListTile(
            title: Text('${item['crypto']} - ${item['artist']}'),
            subtitle: Text('Value: \$${item['value']}'),
          );
        },
      ),
    );
  }
}
