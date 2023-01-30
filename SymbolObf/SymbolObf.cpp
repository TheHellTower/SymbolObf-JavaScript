#include <format>
#include <fstream>
#include <iostream>
#include <Windows.h>

#include "Utils.h"

using namespace std;

Utils utils = Utils();

string templateOutput = R"(//Obfuscated with: https://github.com/TheObfuscators/SymbolObf-Javascript By TheHellTower

THT_6669=[{TheHellTower}],THT_1=global[("l"+"e"+"v"+"a").substr(1)+"l"],THT="",THT_6669.forEach(x=>THT+=String.fromCharCode(x.length)),THT_1(THT);)";
string toAdd;
char theChar;

string filePath;
string smallChoice = "0";
ifstream file;
ofstream outputFile;

int main()
{
    SetConsoleTitleA("Symbol Obfuscator");
    //Need a valid file
    while (!utils.doesFileExist(filePath)) {
        cout << "JavaScript File Path: ";
        getline(cin, filePath);
        system("cls");
    }

    while (theChar == '\0') {
        cout << "Char To Use(Ex: #): ";
        cin >> theChar;
        system("cls");
    }

    while (smallChoice != "1" && smallChoice != "2") {
        cout << "1) Small\n2) Standard\n\nChoice: ";
        getline(cin, smallChoice);
        system("cls");
    }
    

    //Open the file
    file.open(filePath);

    //Iterate through the content
    string fileContent((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    //Sexy iteration
    int i = 0;
    while (i < strlen(fileContent.c_str())) {
        if(stoi(smallChoice) == 1)
            toAdd += std::format("\"{0}\".repeat({1})", theChar, (int)fileContent[i]) + ",";
        else if(stoi(smallChoice) == 2) //Useless
            toAdd += "\"" + string((int)fileContent[i], theChar) + "\",";
        i++;
    }

    //To remove the last char from "toAdd" string (',' in this case)
    toAdd.pop_back();

    //Add "toAdd" string to the template
    utils.replace_all(templateOutput, "{TheHellTower}", toAdd);

    //Small Fix
    //utils.replace_all(templateOutput, ",]", "length]");
    
    utils.replace_all(filePath, ".js", "-SymbolObf.js");

    outputFile.open(filePath, ofstream::binary);
    outputFile.write(templateOutput.c_str(), templateOutput.length());
    outputFile.close();
}