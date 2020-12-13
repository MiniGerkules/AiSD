#include "h-files/Сalculator.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    Сalculator* calc = NULL;
    string expression;                          // The expression entered and the filename if the user enters it
    size_t answer;                              // User selection in the menu

    try
    {
        calc = new Сalculator;
        if (calc == NULL)
            throw out_of_range("Memory allocation error!");

        do
        {
            cout << "Menu:" << endl;
            cout << "1) -- Enter data from the specified file." << endl;
            cout << "2) -- Enter data from the default file." << endl;
            cout << "3) -- Enter data from the keyboard." << endl;
            cout << "4) -- Program features." << endl;
            cout << "5) -- Completion of work." << endl;
            answer = input("Your choice is -- ");
            switch (answer)
            {
                //-------------------------
            case(1):
                system("cls");
                try
                {
                    cout << "Entering data from the specified file:" << endl;
                    cout << "Enter the file name -- ";
                    cin >> expression;
                    expression = input_from_file(expression);

                    expression = calc->verification_and_forming(expression);

                    cout << "\nOriginal expression -- " << expression << endl;
                    cout << "Prefix notation expression -- ";
                    calc->print_result();
                    cout << "\nCalculation result = " << calc->count() << endl;
                }
                catch (domain_error error)
                {
                    cerr << "Error: " << error.what() << endl;
                }
                delay();
                break;
                //-------------------------
            case(2):
                system("cls");
                try
                {
                    cout << "Entering data from the default file:" << endl;
                    expression = input_from_file();
                    
                    expression = calc->verification_and_forming(expression);

                    cout << "\nOriginal expression -- " << expression << endl;
                    cout << "Prefix notation expression -- ";
                    calc->print_result();
                    cout << "\nCalculation result = " << calc->count() << endl;
                }
                catch (domain_error error)
                {
                    cerr << "Error: " << error.what() << endl;
                }
                delay();
                break;
                //-------------------------
            case(3):
                system("cls");
                try
                {
                    cout << "Entering data from the default file:" << endl;
                    cout << "Enter the expression:" << endl;
                    getline(cin, expression);

                    expression = calc->verification_and_forming(expression);

                    cout << "\nOriginal expression -- " << expression << endl;
                    cout << "Prefix notation expression -- ";
                    calc->print_result();
                    cout << "\nCalculation result = " << calc->count() << endl;
                }
                catch (domain_error error)
                {
                    cerr << "Error: " << error.what() << endl;
                }
                delay();
                break;
                //-------------------------
            case(4):
                system("cls");
                cout << "The program can:" << endl;
                cout << "1) -- Operate double numbers." << endl;
                cout << "2) -- The program supports the following characters: +, -, *, /, ^ and unary minus." << endl;
                cout << "3) -- Calculate the following functions: ln, lg, abs, rnd, tan, cot, atg, sin, cos, sqrt." << endl;
                cout << "\tln -- natural logarithm" << endl;
                cout << "\tlg -- decimal logarithm" << endl;
                cout << "\tabs -- absolute value" << endl;
                cout << "\trnd -- rounding to whole" << endl;
                cout << "\ttan -- tangent" << endl;
                cout << "\tcot -- cotangent" << endl;
                cout << "\tatg -- arctangent" << endl;
                cout << "\tsin -- sinus" << endl;
                cout << "\tcos -- cosine" << endl;
                cout << "\tsqrt -- square root" << endl;
                cout << "4) -- The program supports the constants pi and e." << endl;
                cout << "5) -- The program supports open and close brackets." << endl;
                cout << "6) -- Remove extra spaces in the entered expression." << endl;
                cout << "7) -- Recognize invalid lines." << endl;
                cout << "8) -- Calculate a value using the prefix notation." << endl;
                cout << "9) -- Read expression from default file, user-defined file from console." << endl;
                delay();
                break;
                //-------------------------
            case(5):
                cout << "Goodbye!" << endl;
                delete calc;
                break;
                //-------------------------
            default:
                cout << "Incorrect input. Try again." << endl;
                delay();
            }
        } while (answer != 5);
    }
    catch (out_of_range error)
    {
        if (calc != NULL)
            delete calc;
        cerr << "Error: " << error.what() << endl;
    }

    return 0;
}