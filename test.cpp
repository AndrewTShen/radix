#include "radix.h"
#include <string>
#include <fstream>
#include <iostream>

void testcase1() { //make sure Radix.inserting words
    int numReadIn, totalCmp = 0;
    Radix tree;
    std::string toInsert;

    std::ifstream inFile ("testcase1.in");
    inFile >> numReadIn;
    for (int i = 0; i < numReadIn; i++) {
        inFile >> toInsert;
        tree.Insert (toInsert, tree.root, totalCmp);    
    }    
    inFile.close();

    assert (!tree.Search("CTGATCGATCGTAGTCG", tree.root, totalCmp));

    //check if all words are there
    assert (tree.Search("CTGATCGA", tree.root, totalCmp)); 
    assert (tree.Search("CTGCTAGC", tree.root, totalCmp)); //check side spliter and extension
    assert (tree.Search("CTAGTGTG", tree.root, totalCmp));

    tree.Insert ("CTGATCGAA", tree.root, totalCmp); //check extension
    assert (tree.Search("CTGATCGAA", tree.root, totalCmp));

    tree.Insert ("CTGATC", tree.root, totalCmp); //check just side split and no extension
    assert (tree.Search("CTGATC", tree.root, totalCmp));

    tree.Insert ("ACTGATC", tree.root, totalCmp); // try adding to the tree.root
    assert (tree.Search("ACTGATC", tree.root, totalCmp));
    // Radix.Insert ("ACTGATC", tree.root, numStrings, numNodes); // attempt to add the smae thing
}

// void testcase2() { //testing deleting
//     int numReadIn, totalCmp = 0;
//     Node tree;
//     std::string toRadix.Insert;

//     std::ifstream inFile ("testcase2.in");
//     inFile >> numReadIn;
//     for (int i = 0; i < numReadIn; i++) {
//         inFile >> toInsert;
//         // cout << toRadix.Insert << endl;
//         Radix.Insert (toInsert, tree.root, totalCmp);    
//     }    
//     inFile.close();

//     assert (Radix.Search("AGG", tree.root, totalCmp)); //make sure everything is there
//     assert (Radix.Search("ACT", tree.root, totalCmp)); 
//     assert (Radix.Search("T", tree.root, totalCmp));
//     assert (Radix.Search("A", tree.root, totalCmp));
//     assert (Radix.Search("GG", tree.root, totalCmp));
//     assert (Radix.Search("GGA", tree.root, totalCmp));
//     assert (Radix.Search("AT", tree.root, totalCmp));

//     Delete ("GG", tree.root, totalCmp); //check if the edge merging works
//     assert (!Radix.Search("GG", tree.root, totalCmp));
//     assert (Radix.Search("AGG", tree.root, totalCmp));
//     assert (Radix.Search("GGA", tree.root, totalCmp));

//     Delete ("A", tree.root, totalCmp); //check if switch from isLeaf = true to isLeaf = false works
//     assert (!Radix.Search("A", tree.root, totalCmp));
//     assert (Radix.Search("AGG", tree.root, totalCmp));
//     assert (Radix.Search("AT", tree.root, totalCmp));
//     assert (Radix.Search("ACT", tree.root, totalCmp));

//     Delete ("ACT", tree.root, totalCmp); //delete a leaf
//     assert (!Radix.Search("ACT", tree.root, totalCmp));

//     Delete ("AT", tree.root, totalCmp); //make sure that after deleting the edges above merge
//     assert (!Radix.Search("AT", tree.root, totalCmp));
//     assert (Radix.Search("T", tree.root, totalCmp));
//     assert (Radix.Search("AGG", tree.root, totalCmp));
//     assert (Radix.Search("GGA", tree.root, totalCmp));

//     Delete ("T", tree.root, totalCmp); //deleting from the tree.root
//     assert (!Radix.Search("T", tree.root, totalCmp));

//     // Delete ("T", tree.root, numStrings, numNodes); //attempt to delete something thats not there
//     // Delete ("AT")
// }

int main() {
    std::cout << "Hello world" << std::endl;
    testcase1(); //uncomment these testcases to test 
    // testcase2();

    return 0;
}