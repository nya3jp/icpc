/*
 * UVA 401 Palindromes
 * 2004-12-18
 * by nya
 */


#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

bool checkPalindrome(const string& str)
{
    string::size_type len = str.length();

    for(int i=0; i<len/2; i++) {
        if (str[i] != str[len-i-1])
            return false;
    }
    return true;
}

#define CC(a,b) case (a): return (b)

char mirror(char c)
{
    switch(c) {
        CC('A', 'A');
        CC('E', '3');
        CC('H', 'H');
        CC('I', 'I');
        CC('J', 'L');
        CC('L', 'J');
        CC('M', 'M');
        CC('O', 'O');
        CC('S', '2');
        CC('T', 'T');
        CC('U', 'U');
        CC('V', 'V');
        CC('W', 'W');
        CC('X', 'X');
        CC('Y', 'Y');
        CC('Z', '5');
        CC('1', '1');
        CC('2', 'S');
        CC('3', 'E');
        CC('5', 'Z');
        CC('8', '8');
    default:
        return 0;
    }
}





bool checkMirror(const string& str)
{
    string::size_type len = str.length();

    for(int i=0; i<(len+1)/2; i++) {
        if (str[i] != mirror(str[len-1-i]))
            return false;
    }
    return true;
}



int main(int argc, char** argv)
{
    while(true) {

        string str;
        cin >> str;
        if (! cin)
            break;

        bool bPalindrome, bMirror;

        bPalindrome = checkPalindrome(str);
        bMirror = checkMirror(str);

        cout << str << " -- is ";
        if ((! bPalindrome) && (! bMirror)) {
            cout << "not a palindrome." << endl;
        }
        else if (bPalindrome && (! bMirror)) {
            cout << "a regular palindrome." << endl;
        }
        else if ((! bPalindrome) && bMirror) {
            cout << "a mirrored string." << endl;
        }
        else {
            cout << "a mirrored palindrome." << endl;
        }
        cout << endl;
    }

    return 0;
}
