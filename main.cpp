#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <assert.h>
#include <unordered_map>
#include "radix.h"

using namespace std;

int main() {
    //tree root
    Radix tree;

    // additionally, I used the wordbank.txt to test (contains the most common 100 words)

    int choice, totalCmp = 0;
    bool finished = false;

    while (!finished) {
        //recieve operation
        cout << "0. Insert a File." << endl;
        cout << "1. Insert a Word." << endl;
        cout << "2. Delete." << endl;
        cout << "3. Search." << endl;
        cout << "4. Exit" << endl;
        cout << "What would you like to do?: ";
        cin >> choice;
        cout << endl; //linebreak
        if (choice == 0) { 
            // Insert Entire File (for inputing large sets of data)
            string filename, toInsert;
            int numWords;
            cout << "Filename: " << endl; //full file name with file type 
            cin >> filename;
            ifstream inFile (filename.c_str());
            if (inFile.fail ()) {
                cout << "failed" << endl;
                break;
            }
            inFile >> numWords;

            for (int i = 0; i < numWords; i++) {
                inFile >> toInsert;
                tree.Insert(toInsert, tree.root, totalCmp);
                cout << "Total Comparisons: " <<  totalCmp << endl;
            }
            inFile.close();

        } else if (choice == 1) {
            //Insert
            cout << "Word to Insert: " << endl;
            string toInsert;
            cin >> toInsert;
            tree.Insert(toInsert, tree.root, totalCmp);
            cout << "Total Comparisons: " <<  totalCmp << endl;

        } else if (choice == 2) {
            //Delete
            cout << "Word to Delete: " << endl;
            string deletingWord;
            cin >> deletingWord;
            tree.Delete(deletingWord, tree.root, totalCmp);
            cout << "Total Comparisons: " <<  totalCmp << endl;

        } else if (choice == 3) {
            //Search
            string wordToSearch;
            cout << "Word to Search: " << endl; 
            cin >> wordToSearch;
            if (tree.Search(wordToSearch, tree.root, totalCmp)) {
                cout << "true" << endl;
            } else {
                cout << "false" << endl;
            }
            cout << "Total Comparisons: " <<  totalCmp << endl;

        } else if (choice == 4) {
            finished = true;
        } else {
            cout << "You didn't put in a number." << endl;
            break;
        }
        cout << endl; //linebreak
    }
    return 0;
}