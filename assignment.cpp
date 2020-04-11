/* @Author
* Student Name: Lkhagva-Erdene Byambatsogt
* Student ID : 040100923
* Date: <date> */

#include "function.cpp"

typedef vocab_list DataStructure;
DataStructure vocabulary;
//prototypes
void readData();
double calculateProbability(char ch1, char ch2);


int main(){
	int choice = 1;
	char ch1,ch2;
	vocabulary.create();
	readData();
	while(choice == 1 || choice == 2){
		cout<<"1 - Print Entire Language model"<<endl<<"2 - Enter Two char to get Probability of occurence"<<endl<<"3 - to end."<<endl;
		cin>>choice;
		if(choice == 1){
			vocabulary.print();
		}else if( choice == 2){
			cout<<"Enter two chars to get probability of union occurence: ";
			cin>>ch1>>ch2;
			cout<<"Prorability of "<<ch2<<" after "<<ch1<<" is "<<calculateProbability(ch1,ch2)<<endl;
		}
		if (choice == 3){
			cout<<"Terminated."<<endl;
			return 0;
		}
	}

	return 0;
}

void readData(){
	ifstream line("input.txt");
	
	if(!line.is_open()){
		cout<<"File could not be opened"<<endl;
		exit(0);
	}
	char ch1,ch2;
	
	while (line >> ch1 >> noskipws){
		if(ch1 == '\n'){ //skipping new line
//		vocabulary.print();
//		cout<<"aaaaaaaaaaaaaaaaaaaaaaaaaaaa"<<endl;
			continue;
		}
		vocabulary.add_char(tolower(ch1));
	}
	line.clear();
	line.seekg(0); //coming back to the begging of the file to read again
	line >> ch1 >> noskipws;
//------------------------------ADD OCC STARTS---------------------------------------------------
	while (ch1){
		if(line >> ch2 >> noskipws){
			if(ch2 == '\n'){
				line>>ch1>>ch2>>noskipws;
			}
			vocabulary.add_occurence(tolower(ch1), tolower(ch2));
			ch1 = ch2;
		}else{
			break;
		}
	}
}

double calculateProbability(char ch1, char ch2){
	double x=vocabulary.get_union_occurence(ch1,ch2),y=vocabulary.get_occurence(ch1);
	if(x != 0 && y != 0){
		return x/y;
	}
	return 0;
}
