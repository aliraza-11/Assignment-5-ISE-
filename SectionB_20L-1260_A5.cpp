#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

//Made by Ali Raza (20L-1260)

using namespace std;


int StringLenght(char* str){//Finds length of char pointer
	
	int length = 0;
	for(int i = 0; str[i] != '\0'; i++)
	{
		length++;
	}
	return length;
}
char* GetStringFromBuffer(char* str){//Allocates only required memory for char pointer

	int length = StringLenght(str);
	int count = 0;
	for(int i = 0; str[i]  != '\0'; i++)
	{
		if(str[i] == ' ')
		{
			count++;
			continue;
		}
	}
	length = length - count;
	char* strNew = 0;
	strNew = new char[length+1];
	int temp = 0;

	for(int i = 0; str[i]  != '\0'; i++)
	{
		if(str[i] == ' ')
		{
			continue;
		}
		int x = int(str[i]);
		if(x > 96 && x < 123)
		{
			str[i] = str[i] - 32;
		}
		strNew[temp] = str[i];
		temp++;
	}
	strNew[temp] = '\0';

	return strNew;
}
char** DefaultGrid(int max = 0)
{
	char** grid = new char*[max];
	for(int i = 0; i < max; i++)
	{
		grid[i] = new char[max];
	}
	
	return grid;
}
void OutputGrid(char** &grid,int max)
{
	cout<<endl;
	string outputfile;
	for(int i = 0; i < max; i++)
	{
		for(int j = 0; j < max; j++)
		{
			cout<<grid[i][j]<<"  ";
		}
		cout<<endl;
	}
	cout<<endl<<"** Enter name of output file: ";
	cin>>outputfile;
	ofstream fout(outputfile);
	if(fout.is_open())
	{
		cout<<endl<<"** File made successfully! **";
		for(int i = 0; i < max; i++)
		{
			for(int j = 0; j < max; j++)
			{
				fout<<grid[i][j]<<"  ";
			}
			fout<<endl;
		}
	}
}

bool WordPlacingLeftToRight(char** &grid, char* word, int index_i, int index_j, const int& max)
{
	int length = StringLenght(word);

	int check = max - index_j;
	if(check < length)			//Checks if there is enough space for the word from starting index index_j to the length of the word
	{
		return false;
	}

	for(int j = index_j, k = 0; k < length; j++, k++)
	{
		int x = int(grid[index_i][j]);
		int w = int(word[k]);
		if(w == x)
		{
			continue;		//Allows index if the char for both words is same
		}
		if(x >= 65 && x <= 90)
		{
			return false;		//Returns false if it tries to overwrite any word
		}
	}
	
	for(int j = index_j, k = 0; k < length; j++, k++)
	{
		grid[index_i][j] = word[k];			//Copying of word on grid
	}
	return true;
}
bool WordPlacingRightToLeft(char** &grid, char* word, int index_i, int index_j, const int& max)
{
	//Same checks as in LeftToRight except for overwrite check ..... word is copied in reverse order
	int length = StringLenght(word);

	int check = max - index_j;
	if(check < length)
	{
		return false;
	}

	for(int j = index_j, k = length-1; k >= 0; j++, k--) //Word is checked in reversed order
	{
		int x = int(grid[index_i][j]);
		int w = int(word[k]);
		if(w == x)
		{
			continue;
		}
		if(x >= 65 && x <= 90)
		{
			return false;
		}
	}
	for(int j = index_j, k = length-1; k >= 0; j++, k--) //Reverserd copying
	{
		grid[index_i][j] = word[k];
	}
	return true;
}
bool WordPlacingTopToBottom(char** &grid, char* word, int index_i, int index_j, const int& max)
{
	int length = StringLenght(word);

	int check = max - index_i;
	if(check < length)
	{
		return false;
	}

	for(int i = index_i, k = 0; k < length; i++, k++)
	{
		int x = int(grid[i][index_j]);
		int w = int(word[k]);
		if(w == x)
		{
			continue;
		}
		if(x >= 65 && x <= 90)
		{
			return false;
		}
	}
	for(int i = index_i, k = 0; k < length; i++, k++)
	{
		grid[i][index_j] = word[k];
	}
	return true;
}
bool WordPlacingBottomToTop(char** &grid, char* word, int index_i, int index_j, const int& max)
{
	int length = StringLenght(word);

	int check = max - index_i;
	if(check < length)
	{
		return false;
	}


	for(int i = index_i, k = length-1; k >= 0; i++, k--)
	{
		int x = int(grid[i][index_j]);
		int w = int(word[k]);
		if(w == x)
		{
			continue;
		}
		if(x >= 65 && x <= 90)
		{
			return false;
		}
	}
	for(int i = index_i, k = length-1; k >= 0; i++, k--)
	{
		grid[i][index_j] = word[k];
	}

	return true;
}

bool WordPlacingTopLeftToBottomRight(char** &grid, char* word, int index_i, int index_j, int max)
{
	int length = StringLenght(word);

	//Checks for range of word as in functions before
	int check_i = max - index_i; 
	int check_j = max - index_j; 
	if(check_i > max || check_j > max)
	{
		return false;
	}
	if(check_i < length || check_j < length)
	{
		return false;
	}

	if(index_j + length > max || index_i + length > max)
	{
		return false;
	}

	for(int i = index_i, j = index_j, k = 0; k < length; i++, j++, k++)
	{
		int x = int(grid[i][j]);
		int w = int(word[k]);
		if(w == x)
		{
			continue;
		}
		if(x >= 65 && x <= 90)
		{
			return false;
		}
	}
	for(int i = index_i, j = index_j, k = 0; k < length; i++, j++, k++)
	{
		grid[i][j] = word[k];
	}
	return true;
}
bool WordPlacingTopRightToBottomLeft(char** &grid, char* word, int index_i, int index_j, const int& max)
{
	int length = StringLenght(word);

	int check_i = max - index_i; 
	int check_j = index_j - length; 
	if(index_i > max || index_j < 0)
	{
		return false;
	}
	if(check_i < length || check_j > length)
	{
		return false;
	}

	if(index_j - length < 0 || index_i + length > max)
	{
		return false;
	}

	for(int i = index_i, j = index_j, k = 0; k < length; i++, j--, k++)
	{
		int x = int(grid[i][j]);
		int w = int(word[k]);
		if(w == x)
		{
			continue;
		}
		if(x >= 65 && x <= 90)
		{
			return false;
		}
	}
	for(int i = index_i, j = index_j, k = 0; k < length; i++, j--, k++)
	{
		grid[i][j] = word[k];
	}
	return true;
}
bool WordPlacingBottomLeftToTopRight(char** &grid, char* word, int index_i, int index_j, const int& max)
{
	int length = StringLenght(word);

	int check_i = index_i - length; 
	int check_j = max - index_j; 
	if(index_i < 0 || index_j > max)
	{
		return false;
	}
	if(check_j < length || check_i > length)
	{
		return false;
	}

	if(index_j + length > max || index_i - length < 0)
	{
		return false;
	}

	for(int i = index_i, j = index_j, k = 0; k < length; i--, j++, k++)
	{
		int x = int(grid[i][j]);
		int w = int(word[k]);
		if(w == x)
		{
			continue;
		}
		if(x >= 65 && x <= 90)
		{
			return false;
		}
	}
	for(int i = index_i, j = index_j, k = 0; k < length; i--, j++, k++)
	{
		grid[i][j] = word[k];
	}
	return true;
}
bool WordPlacingBottomRightToTopLeft(char** &grid, char* word, int index_i, int index_j, const int& max)
{
	int length = StringLenght(word);

	int check_i = index_i - length; 
	int check_j = index_j - length; 
	if(index_i < 0 || index_j < 0)
	{
		return false;
	}
	if(check_j > length || check_i > length)
	{
		return false;
	}

	if(index_j - length < 0 || index_i - length < 0)
	{
		return false;
	}

	for(int i = index_i, j = index_j, k = 0; k < length; i--, j--, k++)
	{
		int x = int(grid[i][j]);
		int w = int(word[k]);
		if(w == x)
		{
			continue;
		}
		if(x >= 65 && x <= 90)
		{
			return false;
		}
	}
	for(int i = index_i, j = index_j, k = 0; k < length; i--, j--, k++)
	{
		grid[i][j] = word[k];
	}
	return true;
}

bool RandomSequence(char** &grid, char* word, const int& max, int sequence)
{  //Calls functions for copying words depending of the randome value sequence

	if(sequence == 0)
	{
		for(int i = 0; i < max; i++)
		{
			for(int j = 0; j < max; j++)
			{
				if(WordPlacingLeftToRight(grid, word, i, j, max))
				{
					return true;
				}
				else if(WordPlacingTopToBottom(grid, word, i, j, max))
				{
					return true;
				}
			}
		}
	}
	if(sequence == 1)
	{
		for(int i = 0; i < max; i++)
		{
			for(int j = 0; j < max; j++)
			{
				if(WordPlacingRightToLeft(grid, word, i, j, max))
				{
					return true;
				}
				else if(WordPlacingBottomToTop(grid, word, i, j, max))
				{
					return true;
				}
			}
		}
	}
	if(sequence == 2)
	{
		for(int i = 0; i < max; i++)
		{
			for(int j = 0; j < max; j++)
			{
				if(WordPlacingTopLeftToBottomRight(grid, word, i, j, max))
				{
					return true;
				}
				else if(WordPlacingTopRightToBottomLeft(grid, word, i, j, max))
				{
					return true;
				}
			}
		}
	}
	if(sequence == 3)
	{
		for(int i = max-1; i >= 0; i--)
		{
			for(int j = max-1; j >= 0; j--)
			{
				if(WordPlacingBottomRightToTopLeft(grid, word, i, j, max))
				{
					return true;
				}
				else if(WordPlacingBottomLeftToTopRight(grid, word, i, j, max))
				{
					return true;
				}
			}
		}	
	}
	if(sequence == 4)
	{
		for(int i = max-1; i >= 0; i--)
		{
			for(int j = max-1; j >= 0; j--)
			{
				if(WordPlacingBottomLeftToTopRight(grid, word, i, j, max))
				{
					return true;
				}
				else if(WordPlacingLeftToRight(grid, word, i, j, max))
				{
					return true;
				}
			}
		}	
	}
	if(sequence == 5)
	{
		for(int i = max-1; i >= 0; i--)
		{
			for(int j = max-1; j >= 0; j--)
			{
				if(WordPlacingTopRightToBottomLeft(grid, word, i, j, max))
				{
					return true;
				}
				else if(WordPlacingBottomToTop(grid, word, i, j, max))
				{
					return true;
				}
			}
		}	
	}
	return false;
}
void FillEmptySpaces(char** &grid, const int &max)
{  //Puts random characters in empty spaces b/w words

	char x = 'A';
	for(int i = 0; i < max; i++)
	{
		for(int j = 0; j < max; j++)
		{
			int y = int(grid[i][j]);
			if(y < 65 || y > 90)
			{
				grid[i][j] = x;
				x++;
				if(i % 2 == 0)
				{
					x = x + 2;
				}
				if(j % 2 == 0)
				{
					x = x + 7;
				}
				int c = int(x);
				if(c > 90)
				{
					x = x - 26;
				}
			}
		}
	}
}
void DeallocateArray(char** arr, const int max)
{ //Memory deallocation of 2D arrays

	for(int i = 0; i < max; i++)
	{
		delete[] arr[i];
		arr[i] = 0;
	}
	delete[] arr;
	arr =0;
}

char** AllocateArray(int rows = 0, int cols = 0)
{
	char** grid = new char*[rows];
	for(int i = 0; i < rows; i++)
	{
		grid[i] = new char[cols];
	}
	return grid;
}
void Input(ifstream& fin, char** grid, int rows, int cols)
{
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			fin>>grid[i][j];
		}
	}
}
void Output(char** grid, int rows, int cols)
{
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			cout<<grid[i][j]<<" ";
		}
		cout<<endl;
	}
}

bool WordCheckLeftToRight(char** grid, int index_i, int index_j, int rows, int cols,char* word)
{
	int length = StringLenght(word);

	int check = index_j + length-1;
	if(check > rows)
	{
		return false;
	}

	for(int i = index_i, j = index_j, k = 0; k < length; j++, k++)
	{
		if(j >= cols)
		{
			return false;
		}
		if(grid[i][j] != word[k])
		{
			return false;
		}
	}
	return true;
	
}
bool WordCheckRightToLeft(char** grid, int index_i, int index_j, int rows, int cols,char* word)
{
	int length = StringLenght(word);

	int check = index_j - length+1;
	if(check < 0)
	{
		return false;
	}

	for(int i = index_i, j = index_j, k = 0; k < length ; j--, k++)
	{
		if(j < 0)
		{
			return false;
		}
		if(grid[i][j] != word[k])
		{
			return false;
		}
	}
	return true;
}
bool WordCheckTopToBottom(char** grid, int index_i, int index_j, int rows, int cols,char* word)
{
	int length = StringLenght(word);

	int check = index_i + length-1;
	if(check > cols)
	{
		return false;
	}

	for(int i = index_i, j = index_j, k = 0; k < length; i++, k++)
	{
		if(i >= rows)
		{
			return false;
		}
		if(grid[i][j] != word[k])
		{
			return false;
		}
	}
	return true;

}
bool WordCheckBottomToTop(char** grid, int index_i, int index_j, int rows, int cols,char* word)
{
	int length = StringLenght(word);

	int check = index_i - length+1;
	if(check < 0)
	{
		return false;
	}

	for(int i = index_i, j = index_j, k = 0; k < length; i--, k++)
	{
		if(i < 0)
		{
			return false;
		}
		if(grid[i][j] != word[k])
		{
			return false;
		}
	}
	return true;
}

bool WordCheckTopLeftToBottomRight(char** grid, int index_i, int index_j, int rows, int cols,char* word)
{
	int length = StringLenght(word);

	int check_i = index_i + length-1;
	int check_j = index_j + length-1;
	if(check_i > length || check_j > length)
	{
		return false;
	}
	for(int i = index_i, j = index_j, k = 0; k < length; i++, j++, k++)
	{
		if(i >= rows || j >= cols)
		{
			return false;
		}
		if(grid[i][j] != word[k])
		{
			return false;
		}
	}
	return true;
}
bool WordCheckTopRightToBottomLeft(char** grid, int index_i, int index_j, int rows, int cols,char* word)
{
	int length = StringLenght(word);

	int check_i = index_i + length-1;
	int check_j = index_j - length+1;
	if(check_i > length || check_j < 0)
	{
		return false;
	}
	for(int i = index_i, j = index_j, k = 0; k < length; i++, j--, k++)
	{
		if(i >= rows || j < 0)
		{
			return false;
		}
		if(grid[i][j] != word[k])
		{
			return false;
		}
	}
	return true;
	
}
bool WordCheckBottomLeftToTopRight(char** grid, int index_i, int index_j, int rows, int cols,char* word)
{
	int length = StringLenght(word);

	int check_i = index_i - length+1;
	int check_j = index_j + length-1;
	if(check_i < 0)
	{
		return false;
	}
	if(check_i > length || check_j < length)
	{
		return false;
	}
	for(int i = index_i, j = index_j, k = 0; k < length; i--, j++, k++)
	{
		if(i < 0 || j >= cols)
		{
			return false;
		}
		if(grid[i][j] != word[k])
		{
			return false;
		}
	}
	return true;
}
bool WordCheckBottomRightToTopLeft(char** grid, int index_i, int index_j, int rows, int cols,char* word)
{
	int length = StringLenght(word);

	int check_i = index_i - length+1;
	int check_j = index_j - length+1;
	if(check_i < 0|| check_j < 0)
	{
		return false;
	}
	if(check_i > length || check_j > length)
	{
		return false;
	}
	for(int i = index_i, j = index_j, k = 0; k < length; i--, j--, k++)
	{
		if(i < 0 || j < 0)
		{
			return false;
		}
		if(grid[i][j] != word[k])
		{
			return false;
		}
	}
	return true;
	
}

bool WordCheck(ofstream& fout, char** grid, char* word, int size, int rows, int cols)
{
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			if(WordCheckLeftToRight(grid, i, j, rows, cols, word))
			{
				int length = StringLenght(word);
				fout<<"{"<<i<<","<<j<<"} {"<<i<<","<<j+length-1<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i<<","<<j+length-1<<"}"<<endl;
				return true;
			}
			if(WordCheckRightToLeft(grid, i, j, rows, cols, word))
			{
				int length = StringLenght(word);
				fout<<"{"<<i<<","<<j<<"} {"<<i<<","<<j-length+1<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i<<","<<j-length+1<<"}"<<endl;
				return true;
			}
			if(WordCheckTopToBottom(grid, i, j, rows, cols, word))
			{
				int length = StringLenght(word);
				fout<<"{"<<i<<","<<j<<"} {"<<i+length-1<<","<<j<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i+length-1<<","<<j<<"}"<<endl;
				return true;
			}
			if(WordCheckBottomToTop(grid, i, j, rows, cols, word))
			{
				int length = StringLenght(word);
				fout<<"{"<<i<<","<<j<<"} {"<<i-length+1<<","<<j<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i-length+1<<","<<j<<"}"<<endl;
				return true;
			}
			if(WordCheckTopLeftToBottomRight(grid, i, j, rows, cols, word))
			{
				int length = StringLenght(word);
				fout<<"{"<<i<<","<<j<<"} {"<<i+length-1<<","<<j+length-1<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i+length-1<<","<<j+length-1<<"}"<<endl;
				return true;
			}
			if(WordCheckTopRightToBottomLeft(grid, i, j, rows, cols, word))
			{
				int length = StringLenght(word);
				fout<<"{"<<i<<","<<j<<"} {"<<i+length-1<<","<<j-length+1<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i+length-1<<","<<j-length+1<<"}"<<endl;
				return true;
			}
			if(WordCheckBottomLeftToTopRight(grid, i, j, rows, cols, word))
			{
				int length = StringLenght(word);
				fout<<"{"<<i<<","<<j<<"} {"<<i-length+1<<","<<j+length-1<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i-length+1<<","<<j+length-1<<"}"<<endl;
				return true;
			}
			if(WordCheckBottomRightToTopLeft(grid, i, j, rows, cols, word))
			{
				int length = StringLenght(word);
				fout<<"{"<<i<<","<<j<<"} {"<<i-length+1<<","<<j-length+1<<"}"<<endl;
				cout<<"{"<<i<<","<<j<<"} {"<<i-length+1<<","<<j-length+1<<"}"<<endl;
				return true;
			}
			
		}
	}
	return false;

}

void main(){
	cout<<endl<<"********************* WORD SEARCH *********************"<<endl;
	string Option = "Temp";
	char key;
	while(Option!="Q"){
	//the menu will keep appearing till user presses Q
		cout<<"\n\t     --------- Main Menu ---------";
		cout<<endl<<"\nChoose one of the following optons:  \n\n";
		cout<<"** To Create Grid : Press C **"<<endl;
		cout<<"** To Search Word from Grid : Press S **";
		cout<<endl<<"** Quit : Press Q **"<<endl<<endl;
		cout<<"Your choice : ";
		std::cin>>Option;
		if(Option=="C"){
			char** words;
			int size = 0;		//No. of words (size for memory allocation of char** words)
			int User_size;
			char temp[100];		//Temp char array for input (skipping values for increment of size)
			string filename;
			cout<<endl<<"** Enter the input file name:  ";
			cin>>filename;
			ifstream fin(filename);
			if (! fin.is_open()){
				cout<<endl<<" !! There was an error opening file :( !! \n";
				cout<<"Press any key to return to home screen: ";
				cin>>key;
			}
			else
			{
				cout<<endl<<"** File opened successfully! **";
				while(!fin.eof())			//Loop to calculate size for char** words
				{
					fin.getline(temp, 20);
					size++;
				}
				fin.close();
			
				cout<<"\n\n** Enter the number of words in the input file: ";
				cin>>User_size;
				if(User_size == size){
					words = new char*[size];
					int index = 0;		//Index for words
					int max = 0;		//Length of longest word
					char arr[20];		//Temp char array for input

					ifstream fin2(filename);
					while(!fin2.eof())
					{
						fin2.getline(arr, 20);						//Loop for input
						words[index] = GetStringFromBuffer(arr);	

						int temp = StringLenght(words[index]);
						if(max < temp)				//Calculating max (length of longest word)
						{
							max = temp;
						}
						index++;
					}
					if(max < size)			
					{
						max = size;		//longest word and num of words are compared, larger value will be used to form grid
					}

					char* temp2;	//For Swapping
					for(int i = 0; i < size-1; i++)
					{
						for(int j = i+1; j < size; j++)
						{
							int L1 = StringLenght(words[i]);					//Sorting of words (length wise)
							int L2 = StringLenght(words[j]);
							if(L2 > L1)
							{
								temp2 = GetStringFromBuffer(words[i]);
								delete[] words[i];
								words[i] = GetStringFromBuffer(words[j]);
								delete[] words[j];
								words[j] = GetStringFromBuffer(temp2);
								delete[] temp2;
							}
						}
					}

					char** grid = DefaultGrid(max);			//Memory allocation of grid

					srand((unsigned)time(0));
					int sequence;	//Stores randomised value

					for(int k = 0; k < size; )
					{
						sequence = rand() % 6;
						if(RandomSequence(grid, words[k], max, sequence))		//Loopp to copy values on grid
						{
							k++;
						}
						else
						{
							sequence = rand() % 6;
						}
					}

					FillEmptySpaces(grid, max);
					OutputGrid(grid, max);

					DeallocateArray(grid, max);
					DeallocateArray(words, size);

					cout<<endl<<"\nPress any key to return to home screen: ";
					cin>>key;
				}
				else{ 
					cout<<endl<<" !! Total number of words entered were wrong :( !! \n";
					cout<<"Press any key to return to home screen: ";
					cin>>key;
				}
			}
		}
		if(Option=="S"){
				int rows = 0;
				int cols = 0;
				int test;
				string filename;

				cout<<endl<<"** Enter the input file name:  ";
				cin>>filename;
				ifstream fin(filename);
				if (! fin.is_open()){
					cout<<endl<<" !! There was an error opening file :( !! \n";
				}
				else
				{
					cout<<"\n** File opened successfully! **";
					fin>>rows>>cols;
					fin>>test;
					char** grid = AllocateArray(rows, cols);
					Input(fin, grid, rows, cols);
					cout<<endl<<endl;
					Output(grid, rows, cols);
					char** words = new char*[test];
					char temp[20];

					for(int i = 0; i < test; i++)
					{
						fin>>temp;
						words[i] = GetStringFromBuffer(temp);
					}

					fin.close();

					cout<<endl<<"** Enter the output file name:  ";
					cin>>filename;
					ofstream fout(filename);
					if(fout.is_open()){
						cout<<"\n** File made successfully! **\n";
						cout<<"\n**** Results ****\n";
						for(int k = 0; k < test; k++)
						{
							if(WordCheck(fout, grid, words[k], test, rows, cols))
							{
								continue;
							}
							else
							{
								cout<<"Not Found"<<endl;
							}
						}
					}
					else
					{
						cout<<endl<<" !! There was an error opening file :( !! \n";
					}
				}
				cout<<endl<<"Press any key to return to home screen: ";
				cin>>key;

		}
	}
	if(Option == "Q"){
		cout<<endl<<"Bye! ^^"<<endl;
	}
	system("pause");
}