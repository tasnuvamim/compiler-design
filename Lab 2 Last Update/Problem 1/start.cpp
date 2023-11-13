#include <iostream>
#include <fstream>

using namespace std;

const int MAX_KEYWORDS = 100;
const int MAX_VARIABLES = 100;
const int MAX_FUNCTIONS = 100;
const int MAX_INVALID_ID = 100;
const int MAX_OPERATOR = 100;
const int MAX_PUNCTUATION = 100;

// Function to find keywords in the 'keywords.txt' file
bool findKeywords(const string &token, string foundKeywords[MAX_KEYWORDS], int &numKeywords)
{
    // Open the file containing keywords
    ifstream keywordsFile("keywords.txt");

    if (!keywordsFile.is_open())
    {
        cerr << "Error opening keywords file." << endl;
        return false;
    }

    // Temporary string to store alphanumeric characters
    string temp;

    // Iterate through each character in the token
    for (char c : token)
    {
        if (!isalnum(c))
        {
            break; // stop when a non-alphanumeric character is found
        }
        temp += c; // append the character to the temp string
    }

    // Compare the temp string with keywords from the file
    string keyword;
    while (keywordsFile >> keyword && numKeywords < MAX_KEYWORDS)
    {
        if (temp == keyword)
        {
            foundKeywords[numKeywords++] = temp;
            return true;
        }
    }

    return false;
}

// Function to find variables in the code
bool findVariables(string &token, string foundVariables[MAX_VARIABLES], int &numVariables, string &prevToken, string foundInvalidId[MAX_INVALID_ID], int &numInvalidId)
{
    // Check if the previous token is a datatype

    char last = token[token.size() - 1];
    int size = token.size();
    if (!findKeywords(token, foundVariables, numVariables))
    {
        // Check if the token satisfies the conditions of a valid variable identifier
        bool isValidVariable = true;
        int i = 0;

        // Iterate through each character in the token
        for (char c : token)
        {
            if (token[i] == ';' && i == size)
            {
                token.erase(i, 1);
                i--;
            }

            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) && i == 0)
            {
                isValidVariable = false;
                break;
            }
            else
            {
                if (!(isalnum(c) || c == '_' || (last == ';' && last == c)))
                {
                    isValidVariable = false;
                    break;
                }
            }

            i++;
        }

        if (isValidVariable)
        {
            foundVariables[numVariables++] = token;
            return true;
        }
    }

    return false;
}

bool findFunctions(string &token, string foundFunctions[MAX_VARIABLES], int &numFunctions, string foundInvalidId[MAX_INVALID_ID], int &numInvalidId)
{
    int length = token.size() - 1;
    bool flag = false;
    // Check if the token is a valid C++ variable name
    if (!token.empty() && (isalpha(token[0]) || token[0] == '_'))
    {

        for (int i = 1; i < token.size(); i++)
        {
            if (token[i] == '(')
            {
                flag = true;
                break;
            }
        }

        // Check if the rest of the token contains valid characters
        for (int i = 1; i < token.size(); i++)
        {

            if (token[i] == ';' && i == length)
            {
                token.erase(i, 1);
                i--;
            }

            if (!isalnum(token[i]) && token[i] != '_' && token[i] != '(' && token[i] != ')')
            {

                return false;
            }
        }
        if (flag == true)
        {
            foundFunctions[numFunctions++] = token;
            return true;
        }
    }

    return false;
}

bool findOperators(const string &token, string foundOperator[MAX_OPERATOR], int &numOperator)
{
    for (int i = 0; i < token.size(); i++)
    {
        if (token[i] == '+' || token[i] == '-' || token[i] == '/' || token[i] == '*' || token[i] == '%')
        {
            foundOperator[numOperator++] = token[i];
            return true;
        }
    }

    return false;
}

bool findPunctuations(const string &token, string foundPunctuation[MAX_PUNCTUATION], int &numPunctuation)
{
    for (int i = 0; i < token.size(); i++)
    {
        if (token[i] == '[' || token[i] == ']' || token[i] == '{' || token[i] == '}' || token[i] == ',' || token[i] == '"' || token[i] == '"' || (token[i] == '<' && token[i + 1] == '<') ||
            (token[i] == '>' && token[i + 1] == '>'))
        {
            foundPunctuation[numPunctuation++] = token[i];
            return true;
        }
    }

    return false;
}

void ShowDetail(string found[], int num, string c)
{
    cout << endl << "===========================" << endl << endl;
    cout << c << " fetched from the file are: " << endl;
    for (int i = 0; i < num; ++i)
    {
        cout << found[i] << endl;
    }
    cout << "===========================" << endl;
}

int main()
{
    // Open the input file
    ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    string line;
    string foundKeywords[MAX_KEYWORDS];
    string foundVariables[MAX_VARIABLES];
    string foundFunctions[MAX_FUNCTIONS];
    string foundInvalidId[MAX_INVALID_ID];
    string foundOperators[MAX_OPERATOR];
    string foundPunctuations[MAX_PUNCTUATION];
    int numKeywords = 0;
    int numVariables = 0;
    int numFunctions = 0;
    int numInvalidId = 0;
    int numPunctuation = 0;
    int numOperator = 0;
    string prevToken;
    string identity;

    // Read each line from the input file
    while (inputFile >> line)
    {
        // Find keywords and variables in the current line
        if (findKeywords(line, foundKeywords, numKeywords))
        {
        }
        else if (findVariables(line, foundVariables, numVariables, prevToken, foundInvalidId, numInvalidId))
        {
        }
        else if (findFunctions(line, foundFunctions, numFunctions, foundInvalidId, numInvalidId))
        {
        }
        else if (findOperators(line, foundOperators, numOperator))
        {
        }
        else if (findPunctuations(line, foundPunctuations, numPunctuation))
        {
        }
        else
        {
            foundInvalidId[numInvalidId++] = line;
        }

        // Store the current token as the previous token for the next iteration
        prevToken = line;
    }

    ShowDetail(foundKeywords, numKeywords, " Keywords");
    ShowDetail(foundVariables, numVariables, "Variables");
    ShowDetail(foundFunctions, numFunctions, "Functions");
    ShowDetail(foundOperators, numOperator, "Operators");
    ShowDetail(foundPunctuations, numPunctuation, "Punctuations");

    // close the file
    inputFile.close();

    return 0;
}
