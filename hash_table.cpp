#include<cstdlib>
#include<iostream>
#include"hash_table.h"
#include"linked_list_of_curves.h"

using namespace std;


///////////////////////////Constructors//////////////////////////

hash_table :: hash_table(void)//Default constructor
        :Table_size(1021){//kathe bucket tou table kanto na dixnei se mia lista
                Hash_table = new Linked_List_C*[Table_size];//desmevse xwro gia oles tis listes tou table
                for (int i = 0 ; i < Table_size ; i++){
                        Hash_table[i] = new Linked_List_C() ;   //kataskevase thn lista gia afto to bucket
                }
}

hash_table :: hash_table(int Table_siz)//Constructor(dinete xeirokoinhta to megethos tou pinaka)
	:Table_size(Table_siz){
		Hash_table = new Linked_List_C*[Table_size];
		for (int i = 0 ; i < Table_size ; i++){
			Hash_table[i] = new Linked_List_C() ;	
		}
}
//////////////////////////FUNCTIONS///////////////////////////////////
// Classic Hash Function
int hash_table :: hash_function(int Hadd){
	int H ;
	H = ((int)Hadd % 7541)%1021 ;//count its position on table
	return H ;           //return this position
}
//prosthese mia kampulh ston pinaka kalwntas to function tou class linked_list_of_curves ,
//vale to sto bucket (keli)
void hash_table :: add_curve(string onoma , vector<vector <double> > New_Curve,vector<vector <double> > New_Curve_in_grid,int keli){
	Hash_table[keli]->Add_curve_on_tail_C(onoma,New_Curve,New_Curve_in_grid);

}


//sunarthsh gia print tou table kalese ta prints olwn twn listwn pou apoteloun to table
void hash_table :: print( ){
	cout << "HASH TABLE\n";
	for (int i=0 ;  i < Table_size; i++){//Print every list of the table
		cout << "ANOTHER BUCKET:";
		Hash_table[i]->Traverse_and_print_C();
		cout << endl;
	}
}
//sunarthsh gia katastrofh tou pinaka(kalei ton destructor kathe listas)
void hash_table :: destroy_hash_table(){
	cout << "\n\nI  destroyed one hash table\n\n" ;
	for (int i=0 ;  i < Table_size; i++){
		Hash_table[i]->Delete_all_the_curves();
	}
}
//eksupwse ena sugekrimeno bucket
void hash_table :: print_a_bucket(int H){
	this->Hash_table[H]->Traverse_and_print_C();
}
//(LSH NEAREST)psakse se ena bucket an to kainourio curve exei to idio grid curve me ola ta stoixeia tou bycket
void hash_table :: Search_vector_in_bucket(vector <vector <double> > K_grided_curve,vector <vector <double> > Curve,long int bucket){
	this->Hash_table[bucket]->Is_in_C(K_grided_curve,Curve);	

}
//TRUE NEAREST psakse se olon ton pinaka kai vres ton true nearest neighbor
double hash_table :: Search_vector_in_table(vector <vector <double> > curve){
	struct dis_name min_in_hash ;
	min_in_hash.distance = 1000 ;
	min_in_hash.name = "";
	struct dis_name d_n ;
	for(int i = 0 ; i < this->Table_size ; i ++ ){
		d_n =  this->Hash_table[i]->Is_in_full_C(curve);//kathe fora 
		//epistrefei ton kontinotero sto sugekrimeno bucket
		//elegxei kathe fora an to kontinotero sto proigoumeno bucket
		//einai mikrotero apo to kontinotero se afto to bucket
		if(d_n.distance < min_in_hash.distance){//
			min_in_hash.distance = d_n.distance ; 
			min_in_hash.name = d_n.name;
		}
	}
	//anoikse ena arxeio(STANDARD) kai grapse gia thn sugekrimenh kampulh 
	// ton TRUE NEAREST
	ofstream outt("outpuT",ios_base::app );
	outt << fixed <<"True nearest neigbor : ";
	outt << min_in_hash.name << "\ndistance True : ";
	outt << min_in_hash.distance <<endl<<endl ;

}
