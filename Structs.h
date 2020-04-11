/* @Author
* Student Name: Lkhagva-Erdene Byambatsogt
* Student ID : 040100923
* Date: <date> */


#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>

struct occur_node {
	char character;
	occur_node *next;
	int occurence;
};

struct vocab_node {
	char character;
	vocab_node *next;
	occur_node *list;
};

struct vocab_list{
	char *filename;
	vocab_node *head;
	void create();
	vocab_node *createChar(char ch1);
	occur_node *createOcc(char ch2);
	void print();
	void add_char(char);
	void add_occurence(char, char);
	int get_occurence(char);
	int get_union_occurence(char, char);
};

/*struct language_model {
	vocab_list *vocabularylist;
	void readData(const char *);
	double calculateProbability(char, char);
};
*/