#include<iostream>
#include<fstream>
#include <ctime>
#include <cstdlib>
#include<cstring>
using namespace std;

int StringLenght(char* str){
	int stringLen = 0;
	for (char* temp = str; *temp != '\0'; temp++)
		stringLen++;

	return stringLen;
}
char* GetStringFromBuffer(char* buffer){
	int strLen = StringLenght(buffer);
	char* str = 0;
	if (strLen > 0)
	{
		str = new char[strLen + 1];
		char* tempDest = str;
		for (char* tempSrc = buffer; *tempSrc != '\0'; tempSrc++, tempDest++)
		{
			*tempDest = *tempSrc;
		}
		*tempDest = '\0';
	}
	return str;
}
void ConverttoCapital(char* word) {
	int lengthofstr=StringLenght(word);
	for (int i=0; i<lengthofstr;i++) {
		if (word[i] >= 97 && word[i] <= 122) {
			word[i]=word[i] - 32;
		}
	}
}
char** Fileopen(int& size,int lettercount[]){
    string Filename;
    cout<<"Please enter file name again (Don't forget to add '.txt' after files name): ";
    cin>>Filename;
	ifstream file(Filename);

	int  lengthofstr = 0;
	
	char** list = new char* [size];
	char temp[100];
	for (int i=0; i<size;i++){
		lengthofstr = 0;
		file.getline(temp, 80);
		int lengthofstr = StringLenght((temp));
	for (int k=0; *(temp+k) != '\0'; k++) {
		if (*(temp+k) == ' ') {
			for (int j=k; j<lengthofstr-1; j++) {
				temp[j] = temp[j+1];
			}
			temp[lengthofstr-1] = '\0';
		}
	}
		ConverttoCapital(temp);
		lengthofstr = StringLenght(temp);
		lettercount[i] = lengthofstr;
	    char* word = GetStringFromBuffer(temp);
		list[i] = new char[lengthofstr];
        *(list + i) = word;
	}
	file.close();
	return list;

}
int NumberOfWords(){
	 string Filename;
    cout<<"Please enter file name (Don't forget to add '.txt' after files name): ";
    cin>>Filename;
	ifstream file(Filename);
	int i;
	if (file.is_open()){
    	int lengthofstr=1;
		char temp[100];
		for (i=0;lengthofstr != 0; i++){
			file.getline(temp,100);
			lengthofstr = StringLenght(temp);
			if (lengthofstr == 0)
				break;
		}
		file.close();
	}
	else{
		cout << "No such file exists!" << endl;
	}
	return i;
}
void SortandSwap(char** list, int size){   
    char* temp;	
	for(int i = 0; i < size-1; i++)
	{
		for(int j = i+1; j < size; j++){
			int sizeofstr1 = StringLenght(list[i]);					
			int sizeofstr2= StringLenght(list[j]);
			if(sizeofstr2 > sizeofstr1){
				temp = GetStringFromBuffer(list[i]);
				delete[] list[i];
				list[i] = GetStringFromBuffer(list[j]);
				delete[] list[j];
				list[j] = GetStringFromBuffer(temp);
				delete[] temp;
			}
		}
	}
}
bool makepuzzle(char** puzzle, char* word, int row, int col, int rowscol){

	int lengthofStr = StringLenght(word);
	int Rows = (rand() % rowscol), Columns = rand() % rowscol;

	if (col != 0)
	{
		if (col==1) 
		{
			if (lengthofStr != rowscol) {
				while (Columns + lengthofStr >= rowscol)
					Columns = rand() % rowscol;
			}
			else
				Columns = 0;
		}
		
		else 
		{
			if (lengthofStr != rowscol) 
			{
				while (Columns - lengthofStr < 0)
					Columns = rand() % rowscol + 0;
			}
			else
				Columns = rowscol - 1;		
		}
		}
	if (row != 0)
	{
		if (row==1) 
		{
			if (lengthofStr != rowscol) {
				while (Rows + lengthofStr >= rowscol)
					Rows = rand() % rowscol;
			}
			else
				Rows = 0;
		}

		else
		{
			if (lengthofStr != rowscol) {
				while (Rows - lengthofStr < 0)
					Rows = rand() % rowscol;
			}
			else
				Rows = rowscol - 1;
		}
	}
	int check = 0;
	for (int i = Rows, j = Columns, l = 0; l < lengthofStr; i += row, j += col,l++){
		if (word[l] != puzzle[i][j] && puzzle[i][j] != '-'){
			return false;}
			else {
				continue;
			}
	}

	for (int x = Rows, y = Columns, k = 0; k < lengthofStr; x += row, y += col,k++){
		puzzle[x][y] = word[k];
		check++;
	}
	if(check == lengthofStr)
		return true;

	return false;
	}
char** puzzle(char** list, const int size,const int rowscols){
	char** puzzle = new char* [rowscols];
	for (int i = 0; i < rowscols; i++){
		puzzle[i] = new char[rowscols+1];
	}

	for (int i = 0; i < rowscols; i++){
		for (int j = 0; j < rowscols; j++)
			puzzle[i][j] = '-';
		puzzle[i][rowscols] = '\0';
	}
	srand((unsigned)time(0));
	for (int i = 0,count=0; i < size;i++){
		int pattern = rand() % 8 + 1;		
		//left to right
		if (pattern == 1){
			bool position = makepuzzle(puzzle, list[i], 0, +1,rowscols);		
			if (position == false){
				count++;
				i--;
			}
		}
		//Right to Left
		else if (pattern == 2){
			bool position = makepuzzle(puzzle, list[i], 0, -1, rowscols);;
			if (position == false){
				count++;
				i--;
			}
		}
		//Top to bottom
		else if (pattern == 3){
			bool position = makepuzzle(puzzle, list[i], 1, 0, rowscols);
			if (position == false){
				count++;
				i--;
			}
		}
		//Bottom to Top	
		else if (pattern == 4){				
			bool position = makepuzzle(puzzle, list[i], -1, 0, rowscols);
			if (position == false){
				count++;
				i--;
		    }
		}
		//Top left to Bottom right
		else if (pattern == 5){
			bool position = makepuzzle(puzzle, list[i], 1, 1, rowscols);
			if (position == false){
				count++;
				i--;
			}
		}
		//Bottom Right to Top Left
		else if (pattern == 6){
			bool position = makepuzzle(puzzle, list[i], -1, -1, rowscols);
			if (position == false){
				count++;
				i--;
			}
		}
		//Top Right to Bottom left
		else if (pattern == 7){
			bool position = makepuzzle(puzzle, list[i], 1, -1, rowscols);
			if (position == false){
				count++;
				i--;
			}
		}
		//Bottom Left to Top Right
		else if (pattern == 8){
			bool position = makepuzzle(puzzle, list[i], -1, 1, rowscols);
			if (position == false){
				count++;
				i--;
			}
		}
	}
		srand((unsigned)time(0));
	for (int i = 0; i < rowscols; i++)
	{
		for (int j = 0; j < rowscols; j++)
		{
			if (puzzle[i][j] == '-')
			{
				puzzle[i][j]= (char)((rand() % 26) + 65);
			}
		}
	}
	return puzzle;
}
int maxwordsize(char** list,const int sizeofstr){
	int max=StringLenght(*(list + 0));
     	for (int i = 0; i < sizeofstr; i++) {		
		int lengthofStr = StringLenght(*(list + i));
		for (int j = 0; *(*(list + i) + j) != '\0'; j++){
			if (*(*(list + i) + j) == ' ')
				lengthofStr--;
		}
		if (lengthofStr >= max){
			max = lengthofStr;
		
		}
	}
	return max;
}
void OutputPuzzle(char** &puzzle, int rowscols){
	string outputp;
	cout<<"Enter name of output file (Don't forget to add '.txt' after files name): ";
	cin>>outputp;
	ofstream fout(outputp);
	for(int i = 0; i < rowscols; i++)
	{
		for(int j = 0; j < rowscols; j++)
		{
			fout<<puzzle[i][j]<<"  ";
		}
		fout<<endl;
	}
}
void Finishallspaces(char* word){
	int lengthofstr = StringLenght((word));
	for (int i=0,j=0 ; *(word+i)!='\0';i++){
		if (*(word+i)==' '){
			for (int j=i;j<lengthofstr-1;j++){
				word[j]=word[j+1];}
            word[lengthofstr-1]='\0';
		}
	}
}
char** InputFile(int length){ 
	int  lengthofStr=0;
	char** List=new char* [length];
    char Temp[100];
	for (int i =0; i < length; i++){
		cout << "Enter "<<i+1<<": ";
		cin>>Temp;
		lengthofStr=StringLenght(Temp);
		char* word=GetStringFromBuffer(Temp);
		List[i]=new char[lengthofStr];
		*(List+i)=word;
	}
	return List;
}
char** InputFileWords(ifstream& file,int rows){
	char** List=new char* [rows];
	char Temp[100];
	for (int i = 0; i < rows; i++){
		file.getline(Temp,100);
        char* word = 0;
		word = GetStringFromBuffer(Temp);
		Finishallspaces(word);
		*(List + i) = word;
	}
	file.close();
	return List;
}
char** InputFileGrid(ifstream& file,int rows,int cols){
	char** List=new char* [rows];
	for (int i = 0; i < rows; i++){
		 List[i] = new char[cols];
	}
	for (int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			file >> List[i][j];
		}
	}
	file.close();
	return List;
}
bool Solve(char** Puzzle, char* word, int Row, int Col, int Columns, int r, int c, int size) {
	if (c != 0){
		if (c==1){
			if (Col+size>=Columns)
				return false;
		}
		else {
			if (Col-size<0) {
				return false;
			}
		}
	}
	if (r!=0) {
		if (r==1) {
			if (Row+size>=Columns)
				return false;
		}
		else {
			if (Row-size<0) {
				return false;
			}
		}
	}
	for (int k=0;k<size;Row+=r,Col+=c,k++) {
		if (word[k] != Puzzle[Row][Col]) {
			return false;
		}
	}
	return true;
}
void Positionofwords(int Position[][4], char** Puzzle, char** list, int Rows, int Cols, int totalwords){	 
	for (int i = 0; i < totalwords; i++)
	{
		bool searchword = false;
		for (int j = 0; j < Rows; j++) {
			for (int k = 0; k < Cols; k++) {
				int counter = 0;
				if (Puzzle[j][k] == list[i][0]) {
					int lengthofStr = StringLenght(list[i]);
					for (; counter < 8 && searchword == false; counter++) {
						int row = 0, col = 0;
						if (counter == 0) {
							col = 1;
						}
						else if (counter == 1) {
							col = -1;
						}
						else if (counter == 2) {
							row = 1;
						}
						else if (counter == 3) {
							row = -1;
						}
						else if (counter == 4) {
							row = 1;
							col = 1;
						}
						else if (counter == 5) {
							row = -1;
							col = -1;
						}
						else if (counter == 6) {
							row = -1;
							col = 1;
						}
						else if (counter == 7) {
							row = 1;
							col = -1;
						}
						searchword = Solve(Puzzle, list[i], j,  k,Cols, row, col, lengthofStr);
						if (searchword == true)
							break;
					}
					if (searchword == true) {
						Position[i][0] = j;
						Position[i][1] = k;
						if (counter == 0) {
							Position[i][2] = j;
							Position[i][3] = k + lengthofStr - 1;
						}
						else if (counter == 1) {
							Position[i][2] = j;
							Position[i][3] = k - lengthofStr + 1;
						}
						else if (counter == 2) {
							Position[i][2] = j + lengthofStr - 1;
							Position[i][3] = k;
						}
						else if (counter == 3) {
							Position[i][2] = j - lengthofStr + 1;
							Position[i][3] = k;
						}
						else if (counter == 4) {
							Position[i][2] = j + lengthofStr - 1;
							Position[i][3] = k + lengthofStr - 1;
						}
						else if (counter == 5) {
							Position[i][2] = j - lengthofStr + 1;
							Position[i][3] = k - lengthofStr + 1;
						}
						else if (counter == 6) {
							Position[i][2] = j - lengthofStr + 1;
							Position[i][3] = k + lengthofStr - 1;
						}
						else if (counter == 7) {
							Position[i][2] = j + lengthofStr - 1;
							Position[i][3] = k - lengthofStr + 1;
						}
						break;
					}
					if (searchword == false && counter == 8) {
						Position[i][0] = Cols + Rows;
					}
				}
			}
			if (searchword == true)
				break;
		}
	}
	return;
}
void DeallocateMemory(char** matrix, const int& rows){
	for (int i = 0; i < rows; i++)
		if (matrix[i])
			delete[] matrix[i];
	if (matrix)
		delete[] matrix;
} 
void creategrid(){
	int Size=NumberOfWords();
	int SizeOfStr[80];
	char** WordList = Fileopen(Size,SizeOfStr);
	int Max=maxwordsize(WordList, Size);
	SortandSwap(WordList, Size);
	char** Grid = puzzle(WordList, Size, Max);
	OutputPuzzle(Grid, Max);
	cout << "Results have been saved successfully!"<< endl;
	DeallocateMemory(Grid, Max);
	DeallocateMemory(WordList, Size);
}
void searchword(){
	int Rows, Cols, totalwords = 0,Coordinates[100][4];
	string Filen;
    cout<<"Please enter file name for grid (Don't forget to add '.txt' after files name): ";
    cin>>Filen;
	ifstream file(Filen);
	char** list=0;
	char** Puzzle=0;
	if (file.is_open()){
		file >> Rows;
		file >> Cols;
		file.ignore();
		char** Puzzle = InputFileGrid(file, Rows, Cols);
		cout << "1. Take input from text file." << endl << "2. Enter words yourself!" << endl;
		int input;
		cin >> input;
		if (input != 2 && input != 1){
			cout << "Error!" << endl
				<< "1. Take input from text file." << endl
				<< "2. Enter words yourself!" << endl;
			cin >> input;
		}
		if (input == 1){
			string wordsFile;
            cout<<"Please enter file name for list of words (Don't forget to add '.txt' after files name): ";
            cin>>wordsFile;
			ifstream file(wordsFile);
			if (file.is_open()){
				file >> totalwords;
				file.ignore();
				list = InputFileWords(file, totalwords);

			}
			else{
				cout << "Error!" << endl;
				list = 0;
			}

		}
		else{
			cout << "Totalwords: " << endl;
			cin >> totalwords;
			list = InputFile(totalwords);
		}
		for (int i = 0; i < totalwords; i++){
			ConverttoCapital(list[i]);
			Finishallspaces(list[i]);
		}
	Positionofwords(Coordinates, Puzzle, list, Rows, Cols, totalwords);

	int maxc=Cols + Rows;
	string outputs;
	cout<<"Enter name of output file (Don't forget to add '.txt' after files name): ";
	cin>> outputs;
   	ofstream out(outputs);    //output
	for (int i = 0; i < totalwords; i++)
	{
		out << list[i] << "\t ( ";
		for (int j = 0; j < 4; j++)
		{
			if (j == 2)
				out << " ) to ( ";
			if (Coordinates[i][0] == maxc)
			{
				out << "Not Found  ";
				break;
			}
			out << Coordinates[i][j] << " ";
		}		
		out <<")"<< endl;
	}
	out << endl << endl;

		cout << "You may check your answers :)" << endl;
}
	DeallocateMemory(list, totalwords);
}
int main(){
	char choice=0;
	cout<<"Enter desired choice! \n\n 1) Create Grid (Press C) \n 2) Search Words from Grid (Press S) \n 3) Quit (Press Q) \n\n Choice: ";
	cin>>choice;
	if (choice=='C'){
	   creategrid();
	}
	else{
	if (choice=='S'){
		searchword();
	}
	else{
	if (choice=='Q'){
		system("pause");;
	}
	else{
	  return 0;
	}	
	}
  }
}










