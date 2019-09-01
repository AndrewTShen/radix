/* Notes
Computer Science Problem 11
Language: C++11
Platform: Mac (Sierra/HighSierra)

Running Instructions:
I used Command Line Tools to build and run my code from terminal with the commands "make Problem11" and "./Problem11" respectively.
If you want to run the test cases, uncomment testcase1(); and testcase2(); from int main() and they will run when the code is ran.
The program will display a list of options that the user can choose (the different functions), as well as functionality to insert 
an entire file (must have the first line with the number of strings N, followed by N lines of strings), though the files must all
be in the same directory. Each function can be called by typing its respective number (giving by the choice menu). Functions will 
require the user to type a word (insert, delete, search) to standard input (cin) and will print any results to standard output (cout).
*/

#include "radix.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <assert.h>
#include <unordered_map>

using namespace std;

bool Radix::Search(string searchingFor, Node root, int &totalCmp) {
    // Begin at the root
    Node traverseNode = root;
    int elementsFound = 0, numCmp = 0;
    string checking = "";

    //Traverse until checking is equal to or longer in size than the searchingFor string
    while (checking.size() < searchingFor.size()) {
        Edge nextEdge;
        // Get the next edge to explore based on the elements not yet found in x
        bool edgeFound = false;

        char nextChar = searchingFor[checking.size()];

        numCmp++; //increment
        unordered_map<char, Edge>::const_iterator checkChar = traverseNode.subEdges.find(nextChar);

        if (checkChar != traverseNode.subEdges.end()) {
            nextEdge = checkChar->second;
            edgeFound = true;
            checking += checkChar->second.value;
        } else {
            cout << "Search Comparisons: " << numCmp << endl;
            totalCmp += numCmp;
            return false;
        }
        
        traverseNode = *nextEdge.to; // Set the next node to explore
    }

    if (searchingFor.size() > checking.size()) numCmp += checking.size(); //increment by total size of smallest string
    else numCmp += searchingFor.size(); 

    if ((traverseNode.isLeaf) and (searchingFor == checking)) { //check if
        cout << "Search Comparisons: " << numCmp << endl;
        totalCmp += numCmp;
        return true;
    } else {
        cout << "Search Comparisons: " << numCmp << endl;
        totalCmp += numCmp;
        return false;
    }
}  

void Radix::Insert (string insertingWord, Node &root, int &totalCmp) {
    // if (Search(insertingWord, root)) { //uncomment to make sure word is not already inserted
    //     cout << "Word is already inserted." << endl;
    //     return;
    // }

    // Begin searching for the word at the root
    Node *traverseNode = new Node;
    traverseNode = &root;
    string testing = ""; 
    bool notInserted = true, noNewNode;
    int numCmp = 0;

    while (true) { //go until the we find where to inter the node
        Edge nextEdge;
        bool addEntireNode = false, noNewNode = true;

        char nextChar = insertingWord[testing.size()]; //next char to test for equality

        numCmp++;
        if (traverseNode->subEdges.find(nextChar) == traverseNode->subEdges.end()) { //no node was found continue going down, add the new word to this node

            if (testing.size() > insertingWord.size()) numCmp += insertingWord.size();
            else numCmp += testing.size();

            if (testing == insertingWord) traverseNode->isLeaf = true;
            else {
                Node *insertNode = new Node;
                insertNode -> isLeaf = true;

                Edge insertEdge;
                insertEdge.to = insertNode;
                insertEdge.value = insertingWord.substr(testing.size(), insertingWord.size() - testing.size());
                traverseNode->subEdges.insert(make_pair(insertEdge.value[0], insertEdge));
            }

            cout << "Insert Comparisons: " << numCmp << endl;
            totalCmp += numCmp;
            return;
        }

        addEntireNode = false;

        numCmp++;
        if (!(testing.size()+ traverseNode->subEdges.at(nextChar).value.size() > insertingWord.size()) && (testing + traverseNode->subEdges.at(nextChar).value == insertingWord.substr(0, testing.size() + traverseNode->subEdges.at(nextChar).value.size()))) { //check if it goes encompasses the entire value
            addEntireNode = true;
        }

        if (addEntireNode) { //if the entire edge is equal, then add the entirity of it and move on 
            noNewNode = false;
            testing += traverseNode->subEdges.at(nextChar).value; 
            traverseNode = traverseNode->subEdges.at(nextChar).to;

        } else { //if its in the node but cannot traverse all the way through --> must cleave it in half and add a leaf node (either the cleave or an extension)
            int indexToCleave;
            for (int j = 0; j < traverseNode->subEdges.at(nextChar).value.size(); j++) { //continue until we find the proper index of the edge value to cleave at
                if (!(testing.size() + 1 > insertingWord.size())) { //make sure we dont index out of bounds

                    numCmp++;
                    if (traverseNode->subEdges.at(nextChar).value[j] == insertingWord[testing.size()]) {
                        testing += traverseNode->subEdges.at(nextChar).value[j];
                        indexToCleave = j;
                    } else { //break when it no longer matches
                        break;
                    }
                }
            }

            //cleave the edge into two
            Edge lowerCleave;
            lowerCleave.value = traverseNode->subEdges.at(nextChar).value.substr(indexToCleave + 1, traverseNode->subEdges.at(nextChar).value.size() - indexToCleave - 1);
            lowerCleave.to = traverseNode->subEdges.at(nextChar).to;

            Node* cleaveNode = new Node;
            cleaveNode->subEdges.insert(make_pair(lowerCleave.value[0], lowerCleave));

            numCmp += testing.size();
            if (testing == insertingWord.substr(0, testing.size()+1)) { //mark the cleaveNode as true, dont add another node since entire word is contained 
                cleaveNode->isLeaf = true;
            } else { //add new node that is the rest of the leaf
                Node* leafNode = new Node;
                leafNode->isLeaf = true;

                Edge connectToLeaf;
                connectToLeaf.value = insertingWord.substr(testing.size(), insertingWord.size() - testing.size());
                connectToLeaf.to = leafNode;
                cleaveNode->subEdges.insert(make_pair(connectToLeaf.value[0], connectToLeaf));
            }

            Edge highCleave;
            highCleave.value = traverseNode->subEdges.at(nextChar).value.substr(0, indexToCleave + 1);
            highCleave.to = cleaveNode; 
            traverseNode->subEdges.at(nextChar) = highCleave; //replace the old edge with the highCleave

            cout << "Insert Comparisons: " << numCmp << endl;
            totalCmp += numCmp; 
            return;
        }
    }
}

void Radix::Delete(string deletingWord, Node &root, int &totalCmp) {
        // if (!Search(deletingWord, root)) { //uncomment to test if a string is not there
        //     cout << "Word is not in trie." << endl;
        //     return;
        // }

        Node *traverseNode = new Node;
        traverseNode = &root;
        string testing = ""; 
        int numCmp = 0;
        bool finished = false;
        Edge *lastEdge = new Edge; //last edge (before we reach the node that is the parent to the one we want to remove)
        char nextChar;

        while (!finished) { //continue until we find the node to delete
            nextChar = deletingWord[testing.size()];

            numCmp++;
            if (traverseNode->subEdges.find(nextChar) != traverseNode->subEdges.end()) {

                numCmp++; //increment
                if (!(testing.size() + traverseNode->subEdges.at(nextChar).value.size() > deletingWord.size()) && (testing + traverseNode->subEdges.at(nextChar).value == deletingWord.substr(0, testing.size() + traverseNode->subEdges.at(nextChar).value.size()))) { //make sure not out of bounds 
                    testing += traverseNode->subEdges.at(nextChar).value;

                    if (testing.size() != deletingWord.size()) {
                        lastEdge = &traverseNode->subEdges.at(nextChar);
                        traverseNode = traverseNode->subEdges.at(nextChar).to;
                    } else {
                        finished = true;
                    }
                }
            }
        }
        Node *deleteNode = traverseNode->subEdges.at(nextChar).to;

        if (deleteNode->subEdges.size() > 1) { //more than 1 node depend on this node, regardless if it's a leaf or not
            deleteNode->isLeaf = false;
            //no nodes are deleted here

        } else if (deleteNode->subEdges.size() == 0) {
            if (traverseNode->subEdges.size() == 2) { //if when we remove this leaf, will we have to merge two edges together
                char secondChar;
                for (auto pair : traverseNode->subEdges) {
                    numCmp++;
                    if (pair.first != nextChar) {
                        secondChar = pair.first;
                        break;
                    }
                }

                lastEdge->value += traverseNode->subEdges.at(secondChar).value;
                lastEdge->to = traverseNode->subEdges.at(secondChar).to;
                traverseNode->subEdges.erase(nextChar);

            } else { //else we can just freely delete the node
                traverseNode->subEdges.erase(nextChar);
            }

        } else { //if there is only one deleteNode of the node we are at to be deleting (deleteNode)
            Edge connection;
            connection.to = deleteNode->subEdges.at(deleteNode->subEdges.begin()->first).to;
            connection.value = traverseNode->subEdges.at(nextChar).value + deleteNode->subEdges.begin()->second.value;
            deleteNode->subEdges.erase(deleteNode->subEdges.begin());
            traverseNode->subEdges.erase(nextChar);
            traverseNode->subEdges.insert(make_pair(connection.value[0], connection));

        }
        cout << "Delete Comparisons: " << numCmp << endl;
        totalCmp += numCmp;
}


/* Comemnts
Implementation Choices:
I decided to use a very similar code to Problem 6, because the code for that problem also fit this question very well. 
However, I got rid of unnecessary functionality in the Problem6 code used to keep track of nodes, strings, and also 
the ablity to print out words in alphabetical order. This allowed me to replace the vector<Edge> in the Node struct 
with an unordered map to allow constant look up time rather than linear look up allowing me to traverse faster.
*/