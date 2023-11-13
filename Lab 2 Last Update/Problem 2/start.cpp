#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void classifyNumber(double num)
{
    // Check if the number is an integer
    if (num == int(num))
        cout << num << " is an Integer number." << endl;
    else
        cout << num << " is a Real number." << endl;
}

int main()
{
    ifstream inputFile("numbers.txt");

    if (!inputFile.is_open())
    {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    string inputLine;
    while (getline(inputFile, inputLine))
    {
        istringstream ss(inputLine);
        double number;

        while (ss >> number)
            classifyNumber(number);
    }

    inputFile.close();

    return 0;
}
