/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: Casey Mills Davis 
 * Section: Robert Hintz
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * Outputs 2000 characters of 'random writing' using an input text
 * as the basis and an input integer for the order of Markov model
 * to be used.
 */

/* includes */
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "simpio.h"
using namespace std;

/* prototypes */
map<string, Vector<char> > AnalyzeInput(string filename, int orderOfAnalysis);
void outputText(int numChars, map<string, Vector<char> > analysisMap);

/* module variables */
static const int NUM_CHARS = 2000;

int main() {
    // User interface
    string filename = getLine("Please enter filename containing source text: ");
    int orderOfAnalysis = getInteger("What order of analysis (1 to 10): ");
    cout << "Analyzing..." << endl << endl << endl;
    map<string, Vector<char> > analysisResults = AnalyzeInput(filename, orderOfAnalysis);
    outputText(NUM_CHARS, analysisResults);
    
	return 0;
}

map<string, Vector<char> > AnalyzeInput(string filename, int orderOfAnalysis) {
    // Read in file
    ifstream infile(filename.c_str());
    
    // Populate string-vector map with seed - character occurences
    map<string, Vector<char> > seedProbabilities;
    string currentSeed;
    Vector<string> chVec;
    char ch;
    int chCount = 0;
    while (infile.get(ch)) {
        if (chCount < orderOfAnalysis) {
            currentSeed += ch;
            chCount++;
        } else {
            seedProbabilities[currentSeed].add(ch);
            currentSeed = currentSeed.substr(1) + ch;
        }
    }
    
    return seedProbabilities;
}

void outputText(int numChars, map<string, Vector<char> > analysisMap) {
    // Find which seed occurs most frequently
    string firstSeedKey;
    int seedCount = 0;
    foreach(string str in analysisMap) {
        if (analysisMap[str].size() > seedCount) {
            seedCount = analysisMap[str].size();
            firstSeedKey = str;
        }
    }
    
    // Output most frequent seed
    cout << firstSeedKey;
    
    // Output the rest of the text based on the initial seed and random sampling
    string currentSeed = firstSeedKey;
    char currentChar;
    int n = currentSeed.size();
    while (n < numChars) {
        currentChar = analysisMap[currentSeed][randomInteger(0, analysisMap[currentSeed].size()-1)];
        cout << currentChar;
        currentSeed = currentSeed.substr(1) + currentChar;
        n++;
    }
}
    