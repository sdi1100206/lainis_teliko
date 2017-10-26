#pragma once
#include <iostream>
#include <cstddef>
#include"object_list.h"
#include"Functions.h"
using namespace std;
/* definition of the linked list class */
class Linked_List_C{
		friend class  Curve           ;//class Curve has access 
		friend class  hash_table	;//class hash_table has acces here
	private:
		Curve 	* 	Head         ;/* pointer of Head node */
		int 		Size_of_list ;/*size of list  */
		int 		dimensions   ;//diastaseis(den xrisimopoihthike)
	public:
		/* Constructors */
		Linked_List_C(void);
		Linked_List_C( int ,string , vector<vector <double> > , vector<vector <double> >);

    		/* Destructor */
		~Linked_List_C(void);

		/* Traverse and print the list */
		void Traverse_and_print_C();

		/*Add curve to the end of the list*/
		void Add_curve_on_tail_C(string ,vector<vector <double> > , vector <vector <double> >) ;
		/* This function returns the size of the list  */
		int size_of_list_C();
		//This function deletes  the list
		void Delete_all_the_curves();
		//This function deletes a defined curve by user
		void Delete_a_curve_C( vector<vector <double> > );
		//This function returns a connections searcing it by its elements
		Curve* Return_a_curve_C( vector<vector <double> > );
		//sunarthsh gia thn epilektikh anazitish se lista(koitame an exoun idio grid curve kai meta upologizoume thn apostash)
		bool  Is_in_C( vector<vector <double> >,vector<vector <double> >);
		//Sunarthsh gia thn eksantlitikh anazithsh se lista
		struct dis_name  Is_in_full_C( vector<vector <double> >);
};

