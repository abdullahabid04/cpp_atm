#include<iostream>
#include<iomanip>
using namespace std;
#include "Screen.h"

void Screen::displayMessage(string message) const
{
	cout<<message;
}
void Screen::displayMessageLine(string message) const
{
	cout<<message<<endl;
}
void Screen::displayDollarAmount(double amount) const
{
	cout<<fixed<<setprecision(2)<<"$"<<amount;
}
