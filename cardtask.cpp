#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

const string suits[] = {"♥", "♠", "♣", "♦"};
const string cards[] = { "1", "2", "3", "4", "5", "6", "7" , "8", "9", "10", "J", "Q", "K"};
const size_t suitsSize = 4;
const size_t cardsSize = 13;

void printVec(vector<string> v){
	for( size_t pos = 0 ; pos < v.size(); pos++)
	{
		cout << v[pos] << " ";
	}
	cout << endl << endl;
}

vector<string> createDeck(){
 	vector<string> init;
	for(size_t suite = 0; suite < suitsSize ; suite++)
	{
		for(size_t card = 0; card < cardsSize; card++)
		{
			init.push_back(suits[suite] + cards[card]);
		} 
	} 
	printVec(init);
	return init;
}

int randfunc(int i){
	return rand() % i;
}

void shuffle(vector<string> & v){
	random_shuffle(v.begin(), v.end(), randfunc);
	printVec(v);
}

bool checkdup(vector<string> deck,vector<string> deck2){
	for(size_t pairPos1 = 1; pairPos1 < deck.size(); pairPos1++)
	{
		for(size_t pairPos2 = 1; pairPos2 < deck2.size(); pairPos2++)
		{
			if(deck[pairPos1] == deck2[pairPos2]){
				if( deck[pairPos1-1] == deck2[pairPos2-1]){
					return true;
				}
			}
		}
	}

	return false;
}

int main()
{
	srand(time(0)); 
 
 	//create deck 
 	vector<string> deck = createDeck();
  
 	//shuffle
 	shuffle(deck); 
 	vector<string> deck2 = deck;
        
	int shuffleCnt = -1;
 	bool ContainsSeqDup = true; 
  	do{ 
		//reshuffle
		shuffleCnt++;
		shuffle(deck2);
		ContainsSeqDup = checkdup(deck,deck2);
		deck = deck2;
  	} while(ContainsSeqDup);

	cout << "Total number of reshuffles : " << shuffleCnt << endl;
  	return 0;
}
