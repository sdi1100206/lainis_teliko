#pragma once
#include<cstdlib>
#include<iostream>
#include"linked_list_of_curves.h"

using namespace std;

class hash_table {
	friend class linked_list_of_curves;//h klash ths listas exei prosvash edw
	private:
		int  Table_size  ;//arithmos twn bucket
		Linked_List_C** Hash_table ;//to hash table apoteleite apo Table_size listes dianismatwn
	public :

		hash_table(void);//default Constructor
		hash_table(int );  //Constructor of hash structure
		int hash_function( int ) ;//Hash function-->gives the position on table of an account by its key
/////////////////////////REQUIRED FUNCTIONS//////////////////////////////
		//prosthese ena curve (kai ena grid curve) ston pinaka
		void add_curve(string onoma , vector<vector <double> > ,vector<vector <double> >,int ); // add connections
		//destroy all the structures
		void destroy_hash_table () ;
		//ektupwse to hash table
		void print  () ;
		//ektupwse ena bucket tou hash table
		void print_a_bucket(int);
		//psakse ton LSH kontinotero geitona sto bucket pou peftei to curve
		void Search_vector_in_bucket(vector <vector <double> >,vector<vector <double> >,long int);
		//psakse ton TRUE kontinotero geitona se olo  table
		double Search_vector_in_table(vector <vector <double> >);
};
