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
                result.push_back(move(token));
                result.push_back(".");
                starter = true;
                break;
            }
            case '!':{
                token[token.size()-1]='\0';
                result.push_back(move(token));
                result.push_back("!");
                starter = true;
                break;
            }
            case '?':{
                token[token.size()-1]='\0';
                result.push_back(move(token));
                result.push_back("?");
                starter = true;
                break;
            }
            default:{
                result.push_back(move(token));
                if(starter==true){
                    starters.push_back(move(token));
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
	//string scentence  = "We the people of the United States, in order to form a more perfect union, establish justice, insure domestic tranquility, provide for the common defense, promote the general welfare, and secure the blessings of liberty to ourselves and our posterity, do ordain and establish this Constitution for the United States of America.";
	//string scentence  = "It was the best of times, it was the worst of times, it was the age of wisdom, it was the age of foolishness, it was the epoch of belief, it was the epoch of incredulity, it was the season of Light, it was the season of Darkness, it was the spring of hope, it was the winter of despair, we had everything before us, we had nothing before us, we were all going direct to Heaven, we were all going direct the other way - in short, the period was so far like the present period, that some of its noisiest authorities insisted on its being received, for good or for evil, in the superlative degree of comparison only.";
    //string scentence  = "Space. The final frontier. These are the voyages of the star ship Enterprise. It's five year mission: to explore strange new worlds. To seek out new life and new civilizations. To boldly go where no man has gone before.";
    //string scentence = "I am he as you are me as you are he as we are all together";
    //string scentence = "It is a truth universally acknowledged, that a single man in possession of a good fortune must be in want of a wife.";
    string scentence = "To be or not to be, that is the question. Whether tis nobler in the mind to suffer the slings and arrows of outrageous fortune or to take up arms against a sea of troubles. To die, to sleep. No more. And by a sleep we mean to say to end the heartache and the thousand natural shocks that flesh is heir to. To die to sleep. To sleep, perchance to dream. Aye, there's the rub, for in that sleep of death what dreams may come when we have shuffled off the mortal coil.";
    //string scentence = "The basic narrative expresses the central theme: God creates the world and appoints man as his regent, but man proves disobedient and God destroys his world through the Flood. The new post-Flood world is equally corrupt, but God does not destroy it, instead calling one man, Abraham, to be the seed of its salvation. At God's command Abraham descends from his home into the land of Canaan, given to him by God, where he dwells as a sojourner, as does his son Isaac and his grandson Jacob. Jacob's name is changed to Israel, and through the agency of his son Joseph, the children of Israel descend into Egypt, 70 people in all with their households, and God promises them a future of greatness. Genesis ends with Israel in Egypt, ready for the coming of Moses and the Exodus. The narrative is punctuated by a series of covenants with God, successively narrowing in scope from all mankind (the covenant with Noah) to a special relationship with one people alone (Abraham and his descendants through Isaac and Jacob).[2]";
    //string scentence = "One of the earliest civilizations in India is now known as the Indus Valley civilization. Since their language has not been decoded, much of what we know about them comes from artifacts, especially from around their two major cities Mohenjo-Daro and Harappa. These artifacts suggest an important preoccupation with fertility and the religious significance of certain animals. The main Vedic/Brahmanical religious traditions, however, come mainly from migrating and migrating Aryan nomads from the northwest. Their takeover had a profound effect on Indian history, and much of Hinduism today stems from the beliefs and traditions they brought with them. This includes the teachings of the Veda, which in time was collected into a book of hymns, rituals, and philosophical analyses that is still thought of as the final truth in some way by all Hindus even today. The earliest and most directly related to the beliefs of the early Aryans of these is the Rig Veda.The nomadic lifestyle of the Aryans had an important effect on their religion. Many of the hymns glorify their conquest over the indigenous people they called dasas. Indra, the war god, was extremely important to them. Along with this was an intense focus on prayer. They believed that the very creation of the universe had been accomplished through a sacrifice and sought to maintain cosmic order through reenactments of it and other myths. Other rituals, basically spells, could even be used to control the forces of nature.Certain gods and deified forces stand out in the early texts. Agni, fire personified, was extremely important. Having three forms, terrestrial, atmospheric (lightning), and celestial, he was thought of as the one conveyed sacrifices between earth and the gods. Heaven and Earth themselves were worshiped, apparently often involving clarified butter, and could be asked to provide wealth. Varuna, the world king, set and maintains the laws that govern the world. Illness can sometimes be seen as punishment by Varuna. Indra, a large focus of the Rig Veda, was the king of the gods and the warrior god. He defeated Vritra, the massive serpent who was holding back the waters of the world. The Sun and Dawn were worshipped as they were, dawn often being personified as a beautiful woman and the sun often standing for the eye of the gods. The was especially important as highly worshipped as practically an extension of fire worship. Soma was a hallucinogenic liquid extracted from a plant used often in rituals and for divine insight. Even the gods loved soma (especially Indra), and soma itself was deified into god. Part of the Rig Veda describes how the world and social system arose from the first sacrifice of Purusha: from his head came the priests (brahman), his arms the warriors (rajanya), his thighs the herders and farmers (vaishyas) and his feet the slaves (shudra/dasas). Some hymns speculate on the unnamed originator of creation, later named as Prajapati. Somehow, from this figure, existence came out of nonexistence, and not even the gods can know how this happened. Other parts describe ways to protect from harm and bring good fortune such as spells against sickness, snakes, and evils in general.The Upanishads, the final part of the Vedas, provide analysis and insight into the rest of the texts. Many are inconsistent with each other and provide different opinions, so they are often considered conjectural. Certain themes, however, stand out between them. The nature of sacrifice: one passage in the Upanishads describes in detail the symbolism behind the elaborate horse sacrifice ritual while another claims sacrifices are a distraction to those who only seek easy spiritual knowledge. The true self: practically all are in agreement, however, that the self we see and sense the world with is not the true self. The true self is something deeper, more pure, and in truth indistinguishable from the deeper reality of the world at large. One important passage describes Indra learning this truth through 101 years as a student under Prajapati. The true reality is integral to the world, all permeating but unseen except through deep meditation and thought.";
    time_t tim = time(0);
    srand(time(0));

    int seed = rand() * 434888678676587845;
    vector<string> beginWords;
    vector<string> fullText = smartExplode(scentence,' ',beginWords);

    word wordTable[1000];
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
    cout<<beginWords[0];
    int n = findWord(wordTable,arraySize,beginWords[0]);//seed%beginWords.size()]);
    for(int i = 0;i<900;i++){
        cout<<wordTable[n].value;
        n=wordTable[n].followers[seed%wordTable[n].followers.size()];
        if(wordTable[n].value=="."){
            cout<<"."<<endl;
            break;
        }
        cout<<" ";
        seed=(seed*rand())%911;
    }
    return 0;
}
