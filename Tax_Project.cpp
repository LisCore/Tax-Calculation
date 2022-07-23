#include <iostream> 
#include <iomanip>
#include <cmath>

using namespace std;

void welcome();
//This void function will ask the user to unput agi, userStatus, and taxWithheld
//and reference it back to main
void getInput(int &userAGI, int &userStatus, int &taxWithheld);
//This function takes userStatus as argument and returns which case corresponding 
//to user input
int getDeduction(int userStatus);
//This function will take AGI and deduction, subtract the two arguments and retuyrn the 
//taxable amount
int getTaxable(int userAGI, int deduction);
//This function takes 3 arguments and references 2 arguments. Calculates tax table user 
//is within for federal tax. THis is subtracted from taxWithheld and referenced taxDue
void calcTaxDue(int deduction, int taxable, int taxWithheld, int &federalTax, int &taxDue);

const double TEN = .10;
const double TWELVE = .12;
const double TWENTY_TWO = .22;
const double TWENTY_FOUR = .24;
const int FILING_0 = 6000;
const int FILING_1 = 12000;
const int FILING_2 = 24000;

int main () {
	int userAGI = 0;
	int userStatus = 0;
	int taxWithheld = 0;
	int deduction = 0;
	int taxable = 0;
	int federalTax = 0;
	int taxDue = 0;

	welcome();
	getInput(userAGI, userStatus, taxWithheld);
	deduction = getDeduction(userStatus);
	taxable = getTaxable(userAGI, deduction);
	calcTaxDue(deduction, taxable, taxWithheld, federalTax, taxDue);

	cout << "Tax Summary:" << endl;
	cout << "     AGI: $" << userAGI << endl;
	cout << "     Deduction: $" << deduction << endl;
	cout << "     Taxable Income: $" << taxable << endl;
	cout << "     Federal Tax: $" << federalTax << endl;
	cout << "     Tax Due: $" << taxDue << endl;
	cout << "'\n' Thank you for using my Income Tax Calculator!" << endl;

	return 0;
}
void welcome() {
	cout << "Welcome to my Income Tax Calculator" << endl;
	cout << "Please enter the following information and I will calculate";
	cout << " your Income Tax for you! '\n'" << endl; 
}
void getInput(int &refAGI, int &refStatus, int &refTaxWithheld) {
	cout << "Enter your Adjusted Gross Income: $";
	cin >> refAGI;
	while ((!cin) || (refAGI < 0)) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Invalid Input, please try again!" << endl;
		cout << "Enter your Adjusted Gross Income: $";
		cin >> refAGI;
	}
	cout << "Enter your filing status \
(0 = dependent, 1 = single, 2 = married) " << endl;
	cin >> refStatus;
	while ((!cin) || (refStatus < 0) || (refStatus > 2)) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Invalid Input, please try again!" << endl;
		cout << "Enter your filing status \
(0 = dependent, 1 = single, 2 = married)" << endl;
		cin >> refStatus;
	}
	cout << "Enter the taxes withheld: $";
	cin >> refTaxWithheld; 
	while ((!cin) || (refTaxWithheld < 0)) {
	cin.clear();
	cin.ignore(100, '\n');
	cout << "Invalid Input, please try again!" << endl;
	cout << "Enter the taxes withheld: $";
	cin >> refTaxWithheld;
	}
}
int getDeduction(int statusAmount) {
	switch (statusAmount) {
		case 0: 
			return FILING_0;
			break;
		case 1:
			return FILING_1;
			break;
		case 2:
			return FILING_2;
			break; 
	}
}
int getTaxable(int AGI, int deduction){
	int taxable = 0;
	taxable = AGI - deduction;
	if (taxable < 0) {
		taxable = 0;
	}
	return taxable;
}
void calcTaxDue(int deduction, int taxable, int withheld, int &federalTax, int &taxDue) {
	double taxAmount = 0.0;
	if (deduction == FILING_0 || deduction == FILING_1) {
		if (taxable <= 10000) {
			taxAmount = (taxable * TEN);
		}
		else if (taxable <= 40000) {
			taxAmount = (1000 + (TWELVE * (taxable - 10000)));
		}
		else if (taxable <= 85000) {
			taxAmount = (4600 + (TWENTY_TWO * (taxable - 40000)));
		}
		else if (taxable > 85000) {
			taxAmount = (14500 + (TWENTY_FOUR * (taxable - 85000)));
		}
	}
	else {
		if (taxable <= 20000) {
			taxAmount = (taxable * TEN);
		}
		else if (taxable <= 80000) {
			taxAmount = (2000 + (TWELVE * (taxable - 20000)));
		}
		else if (taxable > 80000) {
			taxAmount = (9200 + (TWENTY_TWO * (taxable - 80000)));
		}
	}
	taxAmount = round(taxAmount);
	federalTax = static_cast<int>(taxAmount);
	taxDue = federalTax - withheld;
}
