#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main()
{
    const int MAX_MONTHS = 100;
    const int MAX_RECORDS = MAX_MONTHS + 1;
    const double LOYALTY_BONUS = 50.00;
    const int MONTHS_PER_YEAR = 12;

    double monthly_deposits[MAX_RECORDS] = {};
    double monthly_withdrawals[MAX_RECORDS] = {};
    double monthly_interest[MAX_RECORDS] = {};
    double closing_balances[MAX_RECORDS] = {};

    double starting_balance = 0.0;
    double annual_interest_rate = 0.0;
    double current_balance = 0.0;

    double total_deposits = 0.0;
    double total_withdrawals = 0.0;
    double total_interest_earned = 0.0;
    double final_savings_balance = 0.0;

    int number_of_months = 0;
    int total_records = 0;

    cout << fixed << setprecision(2);

    // Validate annual interest rate
    cout << "Enter the annual interest rate as a decimal "
         << "(e.g., 0.05 for 5%): ";

    while (!(cin >> annual_interest_rate) || annual_interest_rate < 0)
    {
        cout << "Invalid input. Enter a nonnegative decimal rate: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Validate starting balance
    cout << "Enter the starting balance of your account: $";

    while (!(cin >> starting_balance) || starting_balance < 0)
    {
        cout << "Invalid input. Enter a nonnegative balance: $";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Validate number of months
    cout << "Enter the number of months that your bank account "
         << "has been open: ";

    while (!(cin >> number_of_months) ||
           number_of_months < 1 ||
           number_of_months > MAX_MONTHS)
    {
        cout << "Invalid input. Enter a number from 1 to "
             << MAX_MONTHS << ": ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    current_balance = starting_balance;

    // Store each month's information in synchronized arrays
    for (int i = 0; i < number_of_months; ++i)
    {
        cout << "Enter the amount deposited during month "
             << i + 1 << ": $";

        while (!(cin >> monthly_deposits[i]) ||
               monthly_deposits[i] < 0)
        {
            cout << "Invalid input. Enter a nonnegative deposit: $";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter the amount withdrawn during month "
             << i + 1 << ": $";

        while (!(cin >> monthly_withdrawals[i]) ||
               monthly_withdrawals[i] < 0)
        {
            cout << "Invalid input. Enter a nonnegative withdrawal: $";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        double balance_after_transactions =
            current_balance
            + monthly_deposits[i]
            - monthly_withdrawals[i];

        if (balance_after_transactions < 0)
        {
            cout << "Error: The withdrawal would make the account "
                 << "balance negative." << endl;
            return 1;
        }

        monthly_interest[i] =
            balance_after_transactions *
            (annual_interest_rate / MONTHS_PER_YEAR);

        current_balance =
            balance_after_transactions + monthly_interest[i];

        closing_balances[i] = current_balance;

        ++total_records;
    }

    cout << "\n--- Applying Account Loyalty Bonus Item ---\n";

    // Safely append the bonus at the next available index
    if (total_records < MAX_RECORDS)
    {
        const int bonus_index = total_records;

        monthly_deposits[bonus_index] = LOYALTY_BONUS;
        monthly_withdrawals[bonus_index] = 0.00;
        monthly_interest[bonus_index] = 0.00;

        current_balance += monthly_deposits[bonus_index];
        closing_balances[bonus_index] = current_balance;

        ++total_records;
    }
    else
    {
        cout << "Error: There is no available array position "
             << "for the loyalty bonus." << endl;
        return 1;
    }

    // Process the completed arrays
    for (int i = 0; i < total_records; ++i)
    {
        total_deposits += monthly_deposits[i];
        total_withdrawals += monthly_withdrawals[i];
        total_interest_earned += monthly_interest[i];
    }

    final_savings_balance = closing_balances[total_records - 1];

    // Display the transaction ledger
    cout << "\n============================================================\n";
    cout << "TRANSACTION HISTORY LOG\n";
    cout << "============================================================\n";

    cout << left
         << setw(8) << "Month"
         << setw(14) << "Deposit"
         << setw(15) << "Withdrawal"
         << setw(14) << "Interest"
         << setw(14) << "Balance" << endl;

    for (int i = 0; i < total_records; ++i)
    {
        cout << left << setw(8) << i + 1;

        cout << "$" << right << setw(10)
             << monthly_deposits[i] << "   ";

        cout << "$" << right << setw(10)
             << monthly_withdrawals[i] << "   ";

        cout << "$" << right << setw(10)
             << monthly_interest[i] << "   ";

        cout << "$" << right << setw(10)
             << closing_balances[i] << endl;
    }

    cout << "------------------------------------------------------------\n";

    cout << left << setw(47)
         << "The final savings account balance is:"
         << "$" << right << setw(12)
         << final_savings_balance << endl;

    cout << left << setw(47)
         << "The total amount you have deposited is:"
         << "$" << right << setw(12)
         << total_deposits << endl;

    cout << left << setw(47)
         << "The total amount you have withdrawn is:"
         << "$" << right << setw(12)
         << total_withdrawals << endl;

    cout << left << setw(47)
         << "The total amount of interest earned is:"
         << "$" << right << setw(12)
         << total_interest_earned << endl;

    return 0;
} 
