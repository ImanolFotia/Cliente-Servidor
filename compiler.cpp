#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

typedef unsigned short U16;
const U16 NOP = 0x00;
const U16 ADD = 0x01;
const U16 SUB = 0x02;
const U16 AND = 0x03;
const U16 OR  = 0x04;
const U16 XOR = 0x05;
const U16 TIME = 0x06;

int main()
{
    ifstream inFile("program.cs");
    ofstream outFile("program.csc", ios::binary);

    std::string inStr;


    while(inFile >> inStr)
    {
        if(inStr == "ADD")
        {

            outFile.write((char*)&ADD, sizeof(U16));
            string var1S, var2S;
            U16 var1, var2;
            inFile >> var1S;
            inFile >> var2S;
            var1 = (U16)atoi(var1S.c_str());
            var2 = (U16)atoi(var2S.c_str());
            outFile.write((char*)&var1, sizeof(U16));
            outFile.write((char*)&var2, sizeof(U16));
        }
        else if(inStr == "SUB")
        {
            outFile.write((char*)&SUB, sizeof(U16));
            string var1S, var2S;
            U16 var1, var2;
            inFile >> var1S;
            inFile >> var2S;
            var1 = (U16)atoi(var1S.c_str());
            var2 = (U16)atoi(var2S.c_str());
            outFile.write((char*)&var1, sizeof(U16));
            outFile.write((char*)&var2, sizeof(U16));
        }
        else if(inStr == "AND")
        {
            outFile.write((char*)&AND, sizeof(U16));
            string var1S, var2S;
            U16 var1, var2;
            inFile >> var1S;
            inFile >> var2S;
            var1 = (U16)atoi(var1S.c_str());
            var2 = (U16)atoi(var2S.c_str());
            outFile.write((char*)&var1, sizeof(U16));
            outFile.write((char*)&var2, sizeof(U16));
        }
        else if(inStr == "OR")
        {
            outFile.write((char*)&OR, sizeof(U16));
            string var1S, var2S;
            U16 var1, var2;
            inFile >> var1S;
            inFile >> var2S;
            var1 = (U16)atoi(var1S.c_str());
            var2 = (U16)atoi(var2S.c_str());
            outFile.write((char*)&var1, sizeof(U16));
            outFile.write((char*)&var2, sizeof(U16));
        }
        else if(inStr == "XOR")
        {
            outFile.write((char*)&XOR, sizeof(U16));
            string var1S, var2S;
            U16 var1, var2;
            inFile >> var1S;
            inFile >> var2S;
            var1 = (U16)atoi(var1S.c_str());
            var2 = (U16)atoi(var2S.c_str());
            outFile.write((char*)&var1, sizeof(U16));
            outFile.write((char*)&var2, sizeof(U16));
        }
        else if(inStr == "TIME")
        {
            outFile.write((char*)&TIME, sizeof(U16));
            int zero = 0;
            outFile.write((char*)&zero, sizeof(U16));
            outFile.write((char*)&zero, sizeof(U16));
        }
        else
        {
            cout << "Error de compilacion" <<  endl;
            return 0;
        }
    }




    return 0;
}
