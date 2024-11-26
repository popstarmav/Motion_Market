import 'package:flutter/material.dart';

class InvestmentScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    final TextEditingController cryptoController = TextEditingController();
    final TextEditingController amountController = TextEditingController();
    final TextEditingController artistController = TextEditingController();

    return Scaffold(
      appBar: AppBar(
        title: Text('Investment Screen'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          children: [
            TextField(
              controller: cryptoController,
              decoration: InputDecoration(labelText: 'Cryptocurrency (e.g., BTC, ETH)'),
            ),
            TextField(
              controller: amountController,
              decoration: InputDecoration(labelText: 'Investment Amount (in USD)'),
              keyboardType: TextInputType.number,
            ),
            TextField(
              controller: artistController,
              decoration: InputDecoration(labelText: 'Artist Name'),
            ),
            SizedBox(height: 20),
            ElevatedButton(
              onPressed: () {
                // Mock calculation logic
                final investmentValue = double.tryParse(amountController.text) ?? 0;
                final crypto = cryptoController.text.toUpperCase();
                final artist = artistController.text;

                showDialog(
                  context: context,
                  builder: (context) => AlertDialog(
                    title: Text('Investment Results'),
                    content: Text(
                      'Cryptocurrency: $crypto\n'
                      'Artist: $artist\n'
                      'Investment Value: \$${investmentValue.toStringAsFixed(2)}',
                    ),
                    actions: [
                      TextButton(
                        onPressed: () => Navigator.pop(context),
                        child: Text('Close'),
                      ),
                    ],
                  ),
                );
              },
              child: Text('Invest'),
            ),
          ],
        ),
      ),
    );
  }
}
