#include <iostream>
#include <algorithm> // need algo to sort my file data which has multiple words 
#include<vector>
#include<fstream>
#include<string>


using namespace std;

// get words dATA FROM file
vector<string>wordsdata(const string& filerec) // make a vector string data type to store all the words that will be read from my file and ill call it wordsdata ,also has a constant string call file rec
{
	vector<string>lwords; // declare another vector of string called list words 
	ifstream file(filerec); // ifstream use fille access function and access filerec above vector 
	string word; // declare a string called words so  my file can store all the data in that word string 
	while (file >> word) // while file is being read and linked to word
	{
		lwords.push_back(word); // my vector called lwords as above should add thses word to it using the pushback function 
	}
	return lwords; // retuen me my list of words.
}

//filter the words in the list words vector 

vector<string>filterW(const vector<string>& lwords, int len) // made another vector to store the fillterd vector which contains a constant vector made up of a string and int len which is short for length
{
	vector<string>fwords;// make another vector to store all the filterd words called fwords

	for (const auto& word:lwords ) // for constant auto data type let my word access my list word vector 
	{
		if (word.length() == len)// and if my words length  in the list of words vector is same as my len which is length of letter that the player will select at first 
		{
			fwords.push_back(word);// it will select all the filtered words and push it to my fwords vector
		}
	}

	return fwords; // return me my fwords vector 
}


// to filter guessed letter 

vector<string>filterW(const vector<string>& lwords, char l, const string& gl) // making a vector of string filterW which will house a constant vector of lwords, char L which is letters and a constant string called gl which is gussed letter 
{
	vector<string>fwords; // refer my vector of filtered words 
	for (const auto& word:lwords ) //for constant auto data type let my word access my list word vector
	{
		bool sameletter = true; // same letter by player true 
		for (size_t i = 0; i < gl.length(); ++i)// for my i =0 i needs to be less then the gussed letters length ++i
		{
			if (gl[i] != '_' && gl[i] != word[i]) // if my gussed letter which refers to i is not equal to either '_' or the word in my list of words letter 
			{
				sameletter = false; // then this is false exit loop 
				break;
			}
		}

		if (sameletter && word.find(l) == string::npos) // but if letter  is same then add it to my word 
		{
			fwords.push_back(word);//and push it back tin my vector
		}

	}
	return fwords;// give me the filtered words vector 

}

int main()
{
	
	vector<string>recwords = wordsdata("dictionary.txt");// get file acces to my words data 

	// get user input 
	int userwl; // int user word length which is when we start the game it asks players for length of word they want 
	cout << " Enter words Length choice";
	cin >> userwl; // get input 

	// filter by length 
	vector<string>possibleword = filterW(recwords, userwl);// made a vector called possible word which will run my filterW function in my recwords which is my words data with respect to user wotrds length

	// initialize game state

	string currentgl(userwl, '_');
	int trysleft = 10; // set a number of trys a player can guess the letter 
	string gussedletter; // make aa string called gussed letter which will be gussed by the player 


	// game loop
	while (trysleft > 0 && currentgl.find('_') != string::npos)// run this while my trys left is > then 0 and my current gl is '_' and my string is not equla to nopos .NPOS is a -1 postion that will return you the correct value 
	{
		cout << "Current word: " << currentgl << endl; // show the current word as currentgl which is the letter player has to guess
		cout << "Guesses left: " << trysleft << endl;// the num of trys left 
		cout << "Guessed letters: " << gussedletter << endl; // players current letter that has been guessed


		// get guss from user 
		char ug; // make a char as ug or user guess
		cout << "Enter your guess: "; // show
		cin >> ug; 

		// check if letter was gussed before
		if (gussedletter.find(ug) != string::npos)// if the guessed letter is same aas  the ug with respect to npos 
		{
			cout << "You already guessed that letter!" << endl; // show


		}

		gussedletter += ug; 

		// filter words based on the guess
		vector<string>newposword = filterW(possibleword, ug, currentgl);// making a vector called newposword to store new possible word then calling the filterW fuction with respect to my possible word above ,userguess and the current letter to be guessed

		if (!newposword.empty())// if the new vector is empty then 
		{
			possibleword = newposword; // make the possible word same as the newpossible word 
			cout << "Sorry, no " << ug << " in the word." << endl; // then show that the user gussed letter is not in the word 
			--trysleft; // then subtract from my trys which was 10 

			continue; // keep game playing 

		}
		else // otherwise 
		{
			cout << "Good guess!" << endl; // show if letter was guessed corectly 

			for (size_t i = 0; i < possibleword[0].length(); i++) // for i is smaller then the length size of my possible word 
			{
				if (possibleword[0][i] == ug) // if possible word and my i is same as user guessed word 
				{
					currentgl[i] = ug;// then make the current letter to guess equal to user guess
				}

			}

		}

		

	}

	// game over 

	if (currentgl.find('_') == string::npos) // if the char has run out of '_' and the guess are correct then 
	{
		cout << "Congratulations! You guessed the word: " << currentgl << endl; // show the gussed word 
	}
	else {
		cout << "You ran out of guesses. The word was: " << possibleword[0] << endl; // otherwise no the correct word was , show possibleword
	}



	return 0;

}