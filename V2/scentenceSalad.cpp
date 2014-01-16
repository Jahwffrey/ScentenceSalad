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

vector<string> smartExplode(string const & s, char delim,vector<string> &starters)
{
    vector<string> result;
    istringstream iss(s);

    bool starter = true;

    for (string token; getline(iss, token, delim); )
    {
        switch(token[token.size()-1]){
            case '.':{
                token[token.size()-1]='\0';
                result.push_back(token);
                result.push_back(".");
                starter = true;
                break;
            }
            case '!':{
                token[token.size()-1]='\0';
                result.push_back(token);
                result.push_back("!");
                starter = true;
                break;
            }
            case '?':{
                token[token.size()-1]='\0';
                result.push_back(token);
                result.push_back("?");
                starter = true;
                break;
            }
            case '\n':{
                token[token.size()-1]='\0';
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

    const int MAXSIZE = 10000;
    char middleMan[MAXSIZE];
    srand(time(0));
    string scentence;
    vector<string> beginWords;

    //The final thign that will hold it all:
    vector<string> fullText;


    ifstream reader("text.txt");
    reader.getline(middleMan,MAXSIZE,'\n');
    while(!reader.eof()){
        scentence=middleMan;
        vector<string> tempHolder = smartExplode(scentence,' ',beginWords);
        for(int i = 0;i<tempHolder.size();i++){
            fullText.push_back(tempHolder[i]);
        }
        reader.getline(middleMan,MAXSIZE,'\n');
    }
    int seed = rand() * 434888678676587845;

    word wordTable[10000];
    int arraySize = 1;
    word *firstWord = new word();
    firstWord->value=fullText[0];
    wordTable[0]=*firstWord;
    for(int i = 0;i<fullText.size();i++){
        int tempy = findWord(wordTable, arraySize, fullText[i]);
        if(i!=fullText.size()-1){
            int followNumm = findWord(wordTable, arraySize,fullText[i+1]);
            if(followNumm == arraySize ){
                arraySize+=1;
                word *tempor = new word;
                tempor->value = fullText[i+1];
                wordTable[followNumm]=*tempor;
                wordTable[tempy].followers.insert(wordTable[tempy].followers.end(),followNumm);
            }
            else{
                wordTable[tempy].followers.insert(wordTable[tempy].followers.end(),followNumm);
            }
        }
    }
    int n = findWord(wordTable,arraySize,beginWords[seed%beginWords.size()]);

    //show list tree:
    if(showALLthings){
        for(int  i = 0;i<arraySize;i++){
            cout<<wordTable[i].value;
            cout<<" [";
            for(int ii = 0;ii<wordTable[i].followers.size();ii++){
                cout<<wordTable[wordTable[i].followers[ii]].value;
            }
            cout<<"]"<<endl;
        }
    }

    for(int i = 0;i<900;i++){
        //cout<<"["<<wordTable[i].value<<"]";
        cout<<wordTable[n].value;
        n=wordTable[n].followers[seed%wordTable[n].followers.size()];
        if(wordTable[n].value=="."){
            cout<<"."<<endl;
            break;
        }
        if(wordTable[n].value=="!"){
            cout<<"!"<<endl;
            break;
        }
        if(wordTable[n].value=="?"){
            cout<<"?"<<endl;
            break;
        }
        cout<<" ";
        seed=(seed*rand())%7919 ;
    }
    return 0;
}
