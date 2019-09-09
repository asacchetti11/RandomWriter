/*
randwriter.cc
Alessandro Sacchetti
10/25/2018
"random writer"
dependencies: list.h, list.cc
*/
#include <cstdlib>
#include "list.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <map>

using namespace std;
//Example usage
//   ./randwriter 2 20 easy.txt output.txt 
//   ./randwriter 6 200 seuss-notallowed.txt output.txt;

void correctUseage(){//Usage Message
	cerr<<"-------------------------------------------------"<<endl
		<<"Correct Useage: ./randwriter k length source result"<<endl
		<<"k: A non-negative integer"<<endl
		<<"length: A non-negative integer"<<endl
		<<"source: Input file that contains more than k characters"<<endl
		<<"result: The name of an output file"<<endl
		<<"-------------------------------------------------"<<endl;
}

//takes an int list but prints it in char
void specialCharPrint(list &toPrint){
	cout<<"< ";
	for(int i(0);i<toPrint.size();i++){
		cout<<char(toPrint.get(i));
		if(i!=toPrint.size()-1){
			cout<<", ";
		}
	}cout<<" >"<<endl;
}

//handles adding indices to the charMap
void addToMap(char c, size_t index, map<char,list> & charMap){

	if (charMap.count(c)==0){//if it doesnt exist yet ->make new list and add index
		list temp = list();
		temp.add((index),0);
		charMap[c]=temp;
	}else{//otherwise just add index
		charMap[c].add((index),charMap[c].size());
	}

}

//returns the in file in a string format along with the inputSize and charMap which are passed by reference
string ifstreamToStringandMap(ifstream & in, map<char,list> & charMap, size_t & inputSize){
	string input = "";

	char temp;
	inputSize=0;
	while(in.get(temp)){//
		input = input + temp;
		addToMap(temp, inputSize, charMap);

		inputSize++;

	}in.close();

	return input;
}

//returns a new sudo-random seed
string newSeed(size_t seedLength, string & input, size_t inputSize){
	string seed="";
	//random start of seed must be k away from the end of input
	int startIndex = rand()%(inputSize-seedLength+1);
	for(int i(0); i<seedLength;i++){
		seed += input[startIndex+i];
	}
	return seed;
}

//True if the seed is found starting at the index and its not at the end of the input
bool isSeedEqual(string seed, size_t seedLength, size_t startIndex, string & input, size_t inputSize){

	for(int i(0); i<seedLength;i++){
		if(seed[i]!=input[startIndex+i]){
			return false;
		}
	}

	return startIndex+seedLength < inputSize;// insures it doesnt grab last index
}

//Actual algorithim
void randomlyWrite(int k,int length, string & input, size_t inputSize, ofstream & out, map<char,list> & charMap){
	
	string seed="";

	//grab the first ones randomly
	srand(time(NULL));
	seed = newSeed(k,input, inputSize);


	while(length>0){
		list followingChars = list();//make a list of all the characters that follow the seed

		 list *tempList = &charMap[ seed[0] ];//the list of indices that char is at

		for(size_t i(0); i<(*tempList).size(); i++){
			size_t tempIndex = ((*tempList).get(i));

			if(isSeedEqual(seed,k,tempIndex,input,inputSize)){

				followingChars.add( input[tempIndex+k], 0 );
			}
		}

		//---randomly picks next seed---
		if(followingChars.size()==0 && k!=0){//when k is 0 it ends up here
			//randomly pick a new seed
			seed = newSeed(k,input,inputSize);
		}else{	// delete the first char of seed and add new char to the back
			
			char nextChar;
			if(k<=0){//seed length of 0
				nextChar = input[rand()%inputSize]; //randomly pick from input string
			}else{//seed length >0
				nextChar = char(followingChars.get(rand()%followingChars.size()));	//randomly pick a char from following chars
				
				//change the seed
				string tempSeed = "";

				for(int j(k-1); j>0; j--){//last index it loops to is 1
					tempSeed = seed[j] + tempSeed;
				}

				//add the new char
				tempSeed = tempSeed + nextChar;
				seed = tempSeed;
			}


			out.put(nextChar);
			length--;
		}

	}
}

int main(int argc, char const *argv[]){
	
	//make sure the correct args are specified
	if(argc!=5){
		correctUseage();
		return 1;
	}
	int k = atoi(argv[1]);
	int length = atoi(argv[2]);

	//read in file
	ifstream in(argv[3]);

	if(k<0 or length <0 or !in.good() or k>length){//!in.good() == if it doesnt exist
		correctUseage();
		return 1;
	}

	//output file
	ofstream out(argv[4]);

	//put the input stream into a string and map the indices
	map<char,list> charMap; 
	size_t inputSize=0;
	string input = ifstreamToStringandMap(in, charMap, inputSize);


	randomlyWrite(k,length,input,inputSize,out,charMap);

	//when it first loads in the input list make a seperate map called possibleChars
	//and it maps any char in the input to a corresponding list of indices that the char is at

}