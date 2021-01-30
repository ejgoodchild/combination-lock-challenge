/*
* Author: Ethan Goodchild
*/
#include <iostream>
#include <Vector>
#include <fstream>
#include <string>
#include <algorithm>  
using namespace std;


/**
 * Contains all information about the combination lock
 */
struct Lock {
    Lock() {};
    int numOfWheels = 0;
    int numOfLetters = 0;
    char* wheels = nullptr;

    bool isValid() { return numOfWheels > 0 && numOfLetters > 0 && wheels; }
};


/**
 * Comparision function to compare strings on where they appear
 * alphabetically
 *
 * @param the two strings to compare
 */
bool alphaCompare(string a, string b) {
    return a < b;
}

/**
 * Loads a dictionary given a pointer to a file, a pointer
 * to a vector of strings and the max word length. Words 
 * greater than the max word length are removed to improve
 * search speed.
 *
 * @param  the file to extract dictionary words from, the 
 * vector to put the words into extracted from the dictionary 
 * and the maximum possible size of a word that could be searched
 */
void loadDictionary( ifstream* file, vector<string>* words, int maxWordLen) {
    string line;
    while (getline(*file, line)) {
        if (line.length() <= maxWordLen) {
            for (int i = 0; i < line.length(); i++) 
                line[i] = toupper(line[i]);
            

            words->emplace_back(line);

        }
    }
   
    sort(words->begin(), words->end(), alphaCompare);

    cout << "Dictionary sucessfully loaded" << endl;

}

/**
 * Loads a dictionary given a filename, if file not found
 * then an empty vector<string> is returned.
 *
 * @param the string of the filename
 * @return list of all the words in the dictionary
 */
vector<string> loadDictionary(string filename, int maxWordLen) {
    ifstream myfile(filename);
    vector<string> words;
    cout << "Loading dictionary..." << endl;

    if (myfile.is_open()){
        loadDictionary(&myfile, &words, maxWordLen);
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
 * Loads lock given a file, if file contains invalid
 * information then the lock will be invalid
 *
 * @param the pointer to file and the pointer to the
 * lock.
 */
void loadLock(ifstream* file, Lock* lock) {
    cout << "Loading lock..." << endl;

    string line;
   
    getline(*file, line); 
    lock->numOfWheels = isValidInt(line) ? stoi(line) : -1;
    
    getline(*file, line);
    lock->numOfLetters = isValidInt(line) ? stoi(line) : -1;

    if (lock->numOfWheels <=0 || lock->numOfLetters <= 0) {
        cout << "Number of Wheels Or Letters is invalid " << endl;
        return;
    }

    lock->wheels = new char[lock->numOfLetters * lock->numOfWheels];
    int y =0;
    while (getline(*file, line)) {
        if (isValidAlpha(line) && line.length() == lock->numOfLetters) {
            for (int x = 0; x < lock->numOfLetters; x++) {
                lock->wheels[x + y* lock->numOfLetters] = toupper(line.at(x));
           }

        }
        else {
            cout << "This line is invalid: " << line << "is invalid" << endl;
            lock->wheels = nullptr;
            return;
        }
        y++;
    }

    cout << "Lock sucessfully loaded" << endl;

}


/**
 * Loads lock given a filename, if no file found
 * the lock woll be invalid
 *
 * @param the filename and the pointer to the lock
 */
void loadLock(string filename, Lock* lock) {
    ifstream myfile(filename);

    if (myfile.is_open()) {
        loadLock(&myfile, lock);


        myfile.close();
        return;
    }

    cout << "Invalid wheels, please try again..." << endl;

}

/**
 * Scans string from position n and works backwards to
 * attempt to find some words. If found the word it is
 * printed out. 
 *
 * @param the string to scan, the n position and a pointer
 * to the dictionary
 */
void scanString(string val, int n, vector<string>* dictionary) {
    for (int s = 0; s < n; s++) {
        if (binary_search(dictionary->begin(), dictionary->end(), val.substr(s, n - s)))
            cout << val.substr(s, n - s) << endl;
    }
}


/**
 * Checks every possible combination on the lock to find out
 * if and how many words can be made.
 *
 * @param a pointer to the lock, a pointer to the dictionary,
 * column to check, the temporary string
 */
void checkCombinations(Lock* lock, vector<string>* dictionary, int n = 0,  string temp = "") {
    char val;
    for (int i = 0; i < lock->numOfLetters; i++) {
        val = lock->wheels[n * lock->numOfLetters + i ];
        
        if (n > 0) scanString(temp + val, n+1, dictionary);
        
        if (n == lock->numOfWheels - 1)  continue;
        else checkCombinations(lock,dictionary,n+1,temp+val);
          
    }

}


int main()
{
    Lock lock;
    loadLock("wheels2.txt", &lock);
    if (!lock.isValid()) return -1;

    vector<string> dictionary = loadDictionary("dictionary.txt", lock.numOfWheels);    
    if (dictionary.size() == 0) return -1;

    cout << "Computing..." << endl;
    checkCombinations(&lock, &dictionary);

    return 0;
}

