/*
* Author: Ethan Goodchild
*/
#include <iostream>
#include <Vector>
#include <fstream>
#include <string>
using namespace std;

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




int main()
{
    vector<string> dictionary = loadDictionary("dictionary.txt");
    if (dictionary.size() == 0) return -1;



    return 0;
}

