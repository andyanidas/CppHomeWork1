/* @Author
* Student Name: Lkhagva-Erdene Byambatsogt
* Student ID : 040100923
* Date: <date> */


#include "Structs.h"

using namespace std;

void vocab_list::create(){
	vocab_node *head = NULL;
}

void vocab_list::print(){
	vocab_node *trav;
	occur_node *o_trav, *temp;
	trav = head;

	while (trav){
		o_trav = trav->list;
		if (trav->character == char(32)){
				cout << "<SP>:"<<endl;
		}else{
			cout <<trav->character<<":"<<endl;
		}
		while (o_trav){
			cout<<"\t";
			if (o_trav->character == char(32)){
				cout << "<" << "<SP>";
			}
			else{
				cout << "<" << o_trav->character;
			}
			cout << "," << o_trav->occurence << ">" << endl;
			o_trav = o_trav->next;
		}
		trav = trav->next;
	}
}

vocab_node *vocab_list::createChar(char ch1){
	vocab_node *newChar;
	newChar = new vocab_node;
	newChar->character = ch1;
	newChar->next = NULL;
	newChar->list = NULL;
	return newChar;
}

occur_node *vocab_list::createOcc(char ch2){
	occur_node *newOcc;
	newOcc = new occur_node;
	newOcc->character = ch2;
	newOcc->next = NULL;
	newOcc->occurence = 0;
	return newOcc;
}

void vocab_list::add_char(char charToAdd){
	vocab_node *newNode, *trav, *priv;
	newNode = new vocab_node;
	newNode = createChar(charToAdd);
	priv = head;
	trav = head;
	char a;

	if (head == NULL){ // empty vocab and adding as first
		head = newNode;
		return;
	}
	if(charToAdd<65){//if char is not alphabet
		while(trav && trav->character>64){//passing all alphabetics
			priv = trav;
			trav=trav->next;
		}
		while(trav && trav->character<charToAdd){//searching position for ws between whitespaces
			priv = trav;
			trav = trav->next;
		}
		if (!trav){
			priv->next = newNode;
			return;
		}else if(trav->character==charToAdd){
			return;
		}else{ //between
			priv->next = newNode;
			newNode->next = trav;
			return;
		}
	}else if(head->character>charToAdd){//if char is an alphabet and adding to the begging of the list
		newNode->next = head;
		head = newNode;
		return;
	}
	while (trav && trav->character<charToAdd){//finding the correct position for character to add
		priv = trav;
		trav = trav->next;
	}
	if (!trav){
		priv->next = newNode;
	}else if(trav->character != charToAdd){
		priv->next = newNode;
		newNode->next = trav;
	}
	return;
}

void vocab_list::add_occurence(char ch1, char ch2){ //counting occurances
	vocab_node *trav;
	occur_node *o_trav,*o_priv,*newOccNode;
	bool found = false;
	trav = head;
	while (trav){ 
		if (trav->character == ch1){ //before end of the file it will be found bcuz we already checked and added all chars
			break;
		}
		trav = trav->next;
	}
	o_trav=trav->list;
	o_priv = trav->list;
	if(trav->list == NULL){//list is empty and adding as first element of the list 
		newOccNode=createOcc(ch2);
		newOccNode->character = ch2;
		newOccNode->occurence++;
		trav->list = newOccNode;
	}else if(ch2<65){//list is not empty and if ch2 is not alphabet
		if(ch2<o_trav->character){//adding to the very first of o_trav
			newOccNode = createOcc(ch2);
			newOccNode->next = o_trav;
			trav->list = newOccNode;
			newOccNode->occurence++;
			return;
		}
		while(o_trav && o_trav->character>64){//passing all alphabetics since its not alphabetics
			o_priv = o_trav;
			o_trav=o_trav->next;
		}
		while(o_trav && o_trav->character<ch2){//finding correct position for ch2
			o_priv = o_trav;
			o_trav = o_trav->next;
		}
		
		if (!o_trav){//adding to the end of the list by creating new occur_node
			newOccNode = createOcc(ch2);
			o_priv->next = newOccNode;
			newOccNode->occurence++;
			return;
		}else if(o_trav->character == ch2){//if char already exists
			o_trav->occurence++;
			return;
		}else{//in middle
			newOccNode = createOcc(ch2);
			newOccNode->next = o_trav;
			o_priv->next = newOccNode;
			newOccNode->occurence++;
			return;
		}
	}else{//if ch2 is an alphabet
		if(ch2<o_trav->character){//adding to the very first of o_trav
			newOccNode = createOcc(ch2);
			newOccNode->next = o_trav;
			trav->list = newOccNode;
			newOccNode->occurence++;
			return;
		}
		while (o_trav && o_trav->character < ch2){//finding position for ch2
			o_priv = o_trav;
			o_trav = o_trav->next;
		}
		if(!o_trav){//adding to the end
			newOccNode = createOcc(ch2);
			o_priv->next = newOccNode;
			newOccNode->occurence++;
		}else if (o_trav->character == ch2){//increasing only occurence
			o_trav->occurence++;
		}else{//between
			newOccNode = createOcc(ch2);
			o_priv->next = newOccNode;
			newOccNode->next = o_trav;
			newOccNode->occurence++;
		}
	}

	return;
}

int vocab_list::get_occurence(char ch){//returns total occurence of given character
	vocab_node *trav;
	occur_node *o_trav;
	trav = head;
	int count = 0;
	
	while(trav){
		if(trav->character == ch){
			break;
		}
		trav = trav->next;
	}
	if(trav){
		o_trav = trav->list;
		while(o_trav){
			count = count + o_trav->occurence;
			o_trav = o_trav->next;
		}
		return count;	
	}else{
		return 0;
	}
	
}

int vocab_list::get_union_occurence(char ch1, char ch2){
	vocab_node *trav;
	occur_node *o_trav;
	trav = head;
	int count = 0;
	
	while(trav->character != ch1){
		trav = trav->next;
	}
	if(trav){
		o_trav = trav->list;
		while(o_trav){
			if(o_trav->character == ch2){
				return o_trav->occurence;
			}
			o_trav= o_trav->next;
		}
	}
	return 0;
}




