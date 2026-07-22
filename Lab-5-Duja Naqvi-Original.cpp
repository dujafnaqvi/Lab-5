#include <iostream>
#include <iomanip>
using namespace std;

int main () {

    const int MAX_MONTHS = 100;

    // One extra position is needed for the loyalty bonus record
    double monthly_deposits[MAX_MONTHS + 1];
    double monthly_withdrawals[MAX_MONTHS + 1];
    double monthly_interest[MAX_MONTHS + 1];
    double closing_balances[MAX_MONTHS + 1];

    double starting_balance;
    double annual_interest_rate;
    int number_of_months = 0;
    int total_records = 0;

    double total_deposits = 0.0;
    double total_withdrawals = 0.0;
    double total_interest_earned = 0.0;
    double final_savings_balance = 0.0;

    cout << fixed << setprecision(2);

    cout << "Enter the annual interest rate as a decimal"
         << "(e.g., 0,05 for 5%): ";
         cin >> annual_interest_rate;

    cout << "Enter the starting balance of your account: $";
    cin >> starting_balance;
    if (starting_balance <0 ) {
        cout << "Error: Starting balance cannot be negative." << endl;
        return 1;
    }

    cout << "Enter the number of months that your back account has been open: ";
    cin >> number_of_months;
    if (number_of_months < 1 || number_of_months > MAX_MONTHS) {
        cout << "Error: Number of months must be between 1 and " << MAX_MONTHS << "." << endl;
        return 1;
    }

    double current_balance = starting_balance;

    // Populate the monthly records
    for (int i = 0; i < number_of_months; ++i) {
        cout << "Enter the amount deposite during month " << i + 1 << ": $";
        cin >> monthly_deposits[i];

        cout << "Enter the amounth withdrawn during month " << i + 1 << ": $";
        cin >> monthly_withdrawals[i];

        current_balance = current_balance
                        + monthly_deposits[i]
                        - monthly_withdrawals[i];

    if (current_balance < 0) {
        cout << "Error: The account balance became negative." << endl;
        return 1;
    }
    monthly_interest [i] = current_balance * (annual_interest_rate / 12.0);
    current_balance += monthly_interest[i];
    closing_balances[i] = current_balance;
    ++total_records;
    }

    // Append loyalty bonus record
    cout << "\n---Applying Account Loyalty Bonus Item --\n";

    monthly_deposits[total_records] = 50.00;
    monthly_withdrawals[total_records] = 0.00;
    monthly_interest[total_records] = 0.00;

    current_balance += monthly_deposits[total_records];
    closing_balances[total_records] = current_balance;
    ++total_records;

    // Calculate totals form the arrays
    for (int i = 0; i < total_records; ++i) {
        total_deposits += monthly_deposits[i];
        total_withdrawals += monthly_withdrawals[i];
        total_interest_earned += monthly_interest[i];
    }
    final_savings_balance = closing_balances[total_records - 1];

    //Display transaction history
    cout << "\n========================================================\n";
    cout << "TRANSACTION HISTORY LOG\n";
    cout << "========================================================\n";

    cout << left
         << setw(7) << "Month"
         << setw(15) << "Deposit"
    << setw(15) << "Withdrawal"
         << setw(15) << "Interest"
         << setw(15) << "Balance" << endl;

    for (int i = 0; i < total_records; ++i)
    {
        cout << left << setw(7) << i + 1;

        cout << "$" << right << setw(11)
             << monthly_deposits[i] << "  ";

        cout << "$" << right << setw(11)
             << monthly_withdrawals[i] << "  ";

        cout << "$" << right << setw(11)
             << monthly_interest[i] << "  ";

        cout << "$" << right << setw(11)
             << closing_balances[i] << endl;
    }

    cout << "--------------------------------------------------------\n";

    cout << left << setw(46)
         << "The final savings account balance is:"
         << "$" << right << setw(12)
         << final_savings_balance << endl;

    cout << left << setw(46)
         << "The total amount you have deposited is:"
         << "$" << right << setw(12)
         << total_deposits << endl;

    cout << left << setw(46)
         << "The total amount you have withdrawn is:"
         << "$" << right << setw(12)
         << total_withdrawals << endl;

    cout << left << setw(46)
         << "The total amount of interest earned is:"
         << "$" << right << setw(12)
         << total_interest_earned << endl;

    return 0;
}
