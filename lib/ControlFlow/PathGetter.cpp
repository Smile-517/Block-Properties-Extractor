#include "ControlFlow/PathGetter.h"

#include <ctime>
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

int countFiles(const string& path) {
    int res = 0;
    fs::path p = path;
    fs::directory_iterator iter(p);

    while (iter != fs::end(iter)) {
        /* In Windows, when you change the properties of a folder, the information is saved in the Desktop.ini file.
        We need to ignore it.*/
        if (iter->path().generic_string().substr(iter->path().generic_string().length() - 4, 4) != ".ini") {
            res += 1;
        }
        iter++;
    }

    return res;
}

const string getResourceFilePath(const string& path, string& searchTarget, double& delay) {
    int fileNum = countFiles(path);
    string res = "";
    if (fileNum == 0) {
        cerr << "ERROR: No resource file is detected. 1 resource file is required!" << endl;
        system("pause");
        exit(1);
    } else if (fileNum == 1) {
        clog << "1 resource file is detected." << endl;

        fs::path p = path;
        fs::directory_iterator iter(p);

        bool pathRegistered = false;
        while (!pathRegistered) {
            if (iter->path().generic_string().substr(iter->path().generic_string().length() - 4, 4) != ".ini") {
                res = iter->path().generic_string();
                pathRegistered = true;
            } else {
                iter++;
            }
        }
    } else {
        cerr << "ERROR: Only 1 resource file is allowed. There are " << fileNum << " resource files existing!" << endl;
        system("pause");
        exit(1);
    }

    clog << '\n';
    clog << "Enter the mod you want to search for. Ex) \'create:\'" << endl << "Input: ";
    clock_t delayStartTime, delayEndTime;
    delayStartTime = clock();
    cin >> searchTarget;  // searchTarget looks like 'create' or 'create:'
    delayEndTime = clock();

    delay += delayEndTime - delayStartTime;

    return res;
}

const string checkResultFile(const string& path, const string& searchTarget, double& delay) {
    fs::path p = path;
    fs::directory_iterator iter(p);

    int searchTargetLen = searchTarget.length();
    string fileName;
    if (searchTarget[searchTargetLen - 1] == ':') {  // if searchTargetLen looks like 'create:'
        fileName = searchTarget.substr(0, searchTargetLen - 1) + ".properties";
    } else {  // if searchTargetLen looks like 'create'
        fileName = searchTarget + ".properties";
    }

    const string pathOfResult = path + fileName;

    clock_t delayStartTime, delayEndTime;
    bool isBlockPropertiesDetected = false;
    while (iter != fs::end(iter)) {                           // Read all directories in the folder.
        if (iter->path().generic_string() == pathOfResult) {  // if path/block.properties detected
            isBlockPropertiesDetected = true;
            clog << '\n'
                 << fileName
                 << " file in result directory is detected. Input y or Y to overwrite the result into this file. "
                    "Otherwise, type anything else to exit the program."
                 << endl
                 << "Input: ";

            string userInput;
            delayStartTime = clock();
            cin >> userInput;
            delayEndTime = clock();

            if (!(userInput == "y" || userInput == "Y")) {  // if user doesn't want to proceed
                clog << "Program terminated." << endl;
                system("pause");
                exit(0);
            }  // If user inputted y or Y, this function doesn't have any effect.
        }
        iter++;
    }

    delay += delayEndTime - delayStartTime;

    return pathOfResult;
}