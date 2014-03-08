#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include <fstream>
using namespace std;

vector<string> explode(string const & s, char delim)
{
    vector<string> result;
    istringstream iss(s);

    for (string token; getline(iss, token, delim); )
    {
        result.push_back(move(token));
    }

    return result;
}

vector<string> smartExplode(string const & s, char delim,vector<string> &starters,bool &starter)
{
    vector<string> result;
    istringstream iss(s);

    for (string token; getline(iss, token, delim); )
    {
        //clean special end chars
        switch(token[token.size()-1]){
            case '.':{
                token.erase(token.size()-1,1);
                result.push_back(token);
                result.push_back(".");
                starter = true;
                break;
            }
            case '!':{
                token.erase(token.size()-1,1);
                result.push_back(token);
                result.push_back("!");
                starter = true;
                break;
            }
            case '?':{
                token.erase(token.size()-1,1);
                result.push_back(token);
                result.push_back("?");
                starter = true;
                break;
            }
            case '\n':{
                token.erase(token.size()-1,1);
                result.push_back(token);
                break;
            }
            default:{
                result.push_back(token);
                if(starter==true){
                    starters.push_back(token);
                    starter = false;
                }
                break;
            }
        }
    }

    return result;
}

struct word{
    string value;
    //string* followers[100];
    vector<int> followers;
};

int findWord(word theTable[],int tableSize,string theWord){
    for(int i = 0;i<tableSize;i++){
        if(theTable[i].value==theWord){
            return i;
        }
    }
    return (tableSize);
}

int main(){

    //show the full tree?
    bool showALLthings = false;
    bool tooBig = false;
    bool startWord = true;

    //some instance creation:
    const int MAXSIZE = 10000;
    char middleMan[MAXSIZE];
    srand(time(0));
    string scentence;
    vector<string> beginWords;

    //The final thign that will hold it all:
    vector<string> fullText;

    //read in first line
    ifstream reader("text1.txt");
    reader.getline(middleMan,MAXSIZE,'\n');
    scentence=middleMan;
    while(!reader.eof()){//read in the file into smartExplode
        scentence=middleMan;
        vector<string> tempHolder = smartExplode(scentence,' ',beginWords,startWord);
        for(int i = 0;i<tempHolder.size();i++){
            fullText.push_back(tempHolder[i]);
        }
        reader.getline(middleMan,MAXSIZE,'\n');
    }

    startWord = true;
    ifstream readeer("text2.txt");
    readeer.getline(middleMan,MAXSIZE,'\n');
    scentence=middleMan;
    while(!readeer.eof()){//read in the file into smartExplode
        scentence=middleMan;
        vector<string> tempHolder = smartExplode(scentence,' ',beginWords,startWord);
        for(int i = 0;i<tempHolder.size();i++){
            fullText.push_back(tempHolder[i]);
        }
        readeer.getline(middleMan,MAXSIZE,'\n');
    }

    int seed = rand() * 84982798598321;//random number

    //create a table of words!
    word wordTable[40000];
    int arraySize = 1;
    word *firstWord = new word();
    firstWord->value=fullText[0];
    wordTable[0]=*firstWord;//add the first word
    for(int i = 0;i<fullText.size();i++){//loop through the text
        int tempy = findWord(wordTable, arraySize, fullText[i]);//check im in the list
        if(i!=fullText.size()-1){ //check if at the end
            int followNumm = findWord(wordTable, arraySize,fullText[i+1]);//look in the table for the word that comes next
            if(followNumm == arraySize ){ //if it is not
                arraySize+=1;
                word *tempor = new word;    //add it
                tempor->value = fullText[i+1];
                wordTable[followNumm]=*tempor;
                wordTable[tempy].followers.insert(wordTable[tempy].followers.end(),followNumm);//make it follow me
            }
            else{
                wordTable[tempy].followers.insert(wordTable[tempy].followers.end(),followNumm);//or just make it follow me
            }
        }
        if(arraySize>39998){
            cout<<"Oh child! It's too big!"<<endl;
            tooBig = true;
            break;
        }
    }

    ofstream output("outputFile.txt");

    //show list tree:
    if(showALLthings){
        for(int  i = 0;i<arraySize;i++){
            output<<wordTable[i].value;
            output<<"::[|";
            for(int ii = 0;ii<wordTable[i].followers.size();ii++){
                output<<wordTable[wordTable[i].followers[ii]].value<<"|";
            }
            output<<"]"<<endl;
        }
    }



    int numTimes =5;
    int numOn = 0;

    int n;

    if(tooBig){
        output<<"Oh child! There are over 40,000 unique words in this text! Too many!"<<endl;
    }

    //output to a file, breaking at punctuation.
    while(numOn<numTimes){
        n = findWord(wordTable,arraySize,beginWords[seed%beginWords.size()]);
        for(int i = 0;i<900;i++){
            output<<wordTable[n].value;
            n=wordTable[n].followers[seed%wordTable[n].followers.size()];
            if(wordTable[n].value=="."){
                output<<"."<<endl;
                break;
            }
            else if(wordTable[n].value=="!"){
                output<<"!"<<endl;
                break;
            }
            else if(wordTable[n].value=="?"){
                output<<"?"<<endl;
                break;
            }
            else{
                output<<" ";
            }
            seed=(seed*rand()*1200739*1221601)%101719;
        }
        output<<"\n--------------------------------------------------\n\n\n\n\n\n\n";
        numOn+=1;
    }
    return 0;
}
