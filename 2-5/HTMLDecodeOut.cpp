#include "stdafx.h"
#include "HTMLDecode.h"
using namespace std;


int main (int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Wrong input string! Usage: HTMLDecodeOut.Exe \"string\"\n";
        return 1;
    }
    cout << "Hand testing \n";
    cout << DecodeHTML(argv[1]);
    return 0;
}