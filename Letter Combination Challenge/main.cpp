/*
* Author: Ethan Goodchild
*/
#include <iostream>
#include <Vector>
#include <fstream>
#include <string>
using namespace std;

enum DataLoadType {
    dictionary, wheels
};


/**
 * Loads a dictionary given a pointer to a file and pointer
 * to a vector of strings
 *
 * @param the vector to put the words into extracted from
 * dictionary, the file to extract dictionary words from
 */
void loadDictionary(vector<string>* words, ifstream* file) {
    string line;
    while (getline(*file, line))
        words->emplace_back(line);

    cout << "Dictionary sucessfully loaded" << endl;

}

/**
 * Loads a dictionary given a filename, if file not found
 * then an empty vector<string> is returned.
 *
 * @param the string of the filename
 * @return list of all the words in the dictionary
 */
vector<string> loadDictionary(string filename) {
    ifstream myfile(filename);
    vector<string> words;

    if (myfile.is_open()){
        loadDictionary(&words, &myfile);
            myfile.close();
            return words;
    }

   cout << "Invalid dictionary, please try again..." << endl;
   return words;
}


/**
 * Checks if string value can be converted into valid integer
 *
 * @param the string value to be tested
 * @return true if can be converted to int, false otherwise
 */
bool isValidInt(string val) {
    for (int i = 0; i < val.length(); i++)
        if (!isdigit(val[i])) return false;


    return true;
}

/**
 * Checks if string value contains only alphabetical chars
 *
 * @param the string value to be tested
 * @return true if contains only alphabetical chars, false otherwise
 */
bool isValidAlpha(string val) {
    for (int i = 0; i < val.length(); i++)
        if (!isalpha(val[i])) return false;

    return true;
}


/**
 * Loads wheels given a file, if file contains invalid
 * information *wheels will have a nullptr
 *
 * @param the pointer to file, the pointer to the wheels, pointer to num of wheels
 * pointer to num of letters
 */
void loadWheels(ifstream* file, char** wheels, int* numOfWheels, int* numOfLetters) {

    string line;
    
    getline(*file, line);
    *numOfWheels = isValidInt(line) ? stoi(line) : -1; 
    
    getline(*file, line);
    *numOfLetters = isValidInt(line) ? stoi(line) : -1;

    if (*numOfLetters == -1 || *numOfWheels == -1) {
        cout << "Number of Wheels Or Letters is invalid " << endl;
        return;
    }

    *wheels = new char[*numOfLetters * *numOfWheels];
    int y =0;
    while (getline(*file, line)) {
        if (isValidAlpha(line) && line.length() == *numOfLetters) {
            for (int x = 0; x < *numOfLetters; x++) {
               (*wheels)[x + y*(*numOfLetters)] = line.at(x);
           }
        }
        else {
            cout << "Wheel word: " << line << "is invalid" << endl;
            wheels = nullptr;
            return;
        }
        y++;
    }
    cout << "Wheels sucessfully loaded" << endl;

}


/**
 * Loads wheels given a filename, if no file found
 * *wheels will have a nullptr
 *
 * @param the filename, the pointer to the wheels, pointer to num of wheels
 * pointer to num of letters, pointer to file
 */
void loadWheels(string filename, char** wheels, int* numOfWheels, int* numOfLetters) {
    ifstream myfile(filename);

    if (myfile.is_open()) {
        loadWheels(&myfile, wheels, numOfWheels, numOfLetters);


        myfile.close();
        return;
    }

    cout << "Invalid wheels, please try again..." << endl;

}





int main()
{
    int numOfWheels = 0;
    int numOfLetters = 0;
    vector<string> dictionary = loadDictionary("dictionary.txt");
    char* wheels = nullptr;
    loadWheels("wheels.txt", &wheels, &numOfWheels, &numOfLetters);

    if (dictionary.size() == 0 || !wheels) return -1;



    return 0;
}

