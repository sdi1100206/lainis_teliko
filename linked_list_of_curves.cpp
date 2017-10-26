#include <iostream>
#include <cstddef>
#include "linked_list_of_curves.h"
#include<string>
#include"Functions.h"
using namespace std;
////////////////////////////////CONSTRUCTORS//////////////////////////
Linked_List_C :: Linked_List_C(void)//Default definition of the list with no elements only the root(head->default)
        : Size_of_list(0){ 
        Head = new Curve();
        //cout << "I just constructed a list with Head \n";
        //cout << Head->Start << "\n" ;
}

//Construct list by demand
Linked_List_C :: Linked_List_C( int dim ,string onoma_kampulhs,vector< vector <double> > coors, vector <vector <double> > coors_in_grid)
        : Size_of_list(1),dimensions(2){//definition of a list with one element(head) 
        /* Create a new node, acting as both the head and tail node */
      
	Head = new Curve(onoma_kampulhs ,coors,coors_in_grid);
        cout << "I just constructed a list of edges with Head \n";
        //cout << Head->coordinates ;
        cout << endl;
}
 
////////////////////////////////DESTRUCTOR///////////////////////////////

Linked_List_C :: ~Linked_List_C(){
        Delete_all_the_curves(); //call the function which del;etes the list
        cout <<"I just delete a List of edges\n" ;
}
//////////////////////////////////////////////////////////////////////////

/////////////////////////////   FUNCTIONS  /////////////////////////////

//Just return the size of the list 
int Linked_List_C  :: size_of_list_C() {
	cout << Size_of_list;
        return (Size_of_list);
}


////////////////////////////////////////////////////////////////////////////
void Linked_List_C ::  Add_curve_on_tail_C(string onoma,vector<vector <double> > New_Curve,vector<vector <double> > New_Curve_in_grid){
	Curve* new_curve =  new Curve(onoma,New_Curve,New_Curve_in_grid);//new  curve(class construction)
	Curve* Tail = Head;//make this connection equal to the head of the list(memory-position)
        while(Tail-> Next_Curve)//While this new connection points to a an other connection(Not NULL)
		Tail = Tail->Next_Curve;//go on the list

	Tail->Next_Curve = new_curve;//make the end of the list our new curve 
	new_curve->Next_Curve = NULL ;//make the next curve of  tsil  be a NULL ptr
	Size_of_list++; //Just make our list of connections bigger by one
}
///////////////////////////////////////////////////////////////////////////////
void Linked_List_C :: Delete_all_the_curves(){
	Curve *Deletor = Head;
    	/* Traverse the list and delete the curves one by one from the head */

  	while (Deletor != NULL) {
        	// delete the head 
        	Head = Head-> Next_Curve;
        	delete Deletor;
        	// update the head  
        	Deletor = Head;
    	}
    	/* Reset the head  */
	Size_of_list = 0;//make the size of list 0 as it is
    	Head = NULL;
}
//////////////////////////////////////////////////////////////////////////////
void Linked_List_C :: Traverse_and_print_C(){
        int nn = -1 ;
	Curve *Conductor = Head;       //create a conductor of the list

        if (Head == NULL) {           // The list is empty? 
                cout << "No Edges" << endl;//if yes make the user knows about it
                return;
	}
	cout << "Linked List of curves ->";
        while (Conductor != NULL ) { /* while there are some more Curves in the list */

		if (Size_of_list==0){
			break;
		}
		else{   //cout << endl;
			int n=-1; 
			//print the curve
			cout  <<"(" << Conductor->onoma_kampulhs << ")"<<"->" ;
                	Conductor = Conductor->Next_Curve;
        	}

	}

}
//////////////////////////////////////////////////////////////////////////////
//PSAKSE EPILEKTIKA STO BUCKET KAI MONO TA curves pou exoun to idio grid curve me afto pou psaxnoume
bool Linked_List_C :: Is_in_C(  vector<vector <double> > K_grided, vector<vector <double> > curve ){
        ofstream kout("output",ios_base::app );//anoikse se mode append gia na 
	//grapseis sto output  gia thn epomenh kampulh(an vrethike LSH nearest ssto bucket kai thn apostaash)

	int i_k_g = 0;
	double kontinoi_geitones[10000];
	string onomata_k_geitones[10000];
//	cout << "\nALAGH KAMPULHS\n";
	bool idio ;
	Curve* Conductor = Head ;//creatae a conductor for our list
	if(Conductor!= NULL){
		while (Conductor!=NULL){//while we wre not at the end of the list
			if((Conductor->coordinates_in_grid.size() == K_grided.size() )){
//			  	exoun idio megethos ta grid curves??
				for (int i = 0 ; i < Conductor->coordinates_in_grid.size() ; i++){
					for(int j = 0 ; j < 2 ; j++){
					if(Conductor->coordinates_in_grid[i][j] == K_grided[i][j]){
							idio = 1;
						}
				else if(Conductor->coordinates_in_grid[i][j] != K_grided[i][j]){
							idio = 0 ;
							//return 0 ;
							//break;
						}
					}
				}
				if (idio == 1){
//					Exoun panomoiothpo grid curve??
					//an nai Kane Frechet distance anamesa sthn arxikh kampulh tou bucket
					//kai ths arxikhs kampulhs tou querry
double d_f_d_c1_c2 = discrete_frechet_distance(curve,Conductor->coordinates);
					//an d_frechet = 0 einai h idia kampulh den mas endiaferei 
					if(d_f_d_c1_c2 != 0 ){//diaforetika
					//vaze se enan pinaka tous kontinous
						kontinoi_geitones[i_k_g] = d_f_d_c1_c2;
						onomata_k_geitones[i_k_g] = Conductor->onoma_kampulhs;
						i_k_g++;
					}
				}

			}
			Conductor = Conductor->Next_Curve; //go on
		}
	if(Conductor == NULL ){
	double min = 10000;
	string min_name;
	for(int i = 0 ; i < i_k_g ; i++){//vres ton kontinotero
			if (kontinoi_geitones[i] < min){
				min = kontinoi_geitones[i];
				min_name = onomata_k_geitones[i];
			} 
        }
		if(min <10000){//an uparxei  kontinoteros rikston sto output
			//out << "Query: " << curve.onoma_kampulhs;
			kout << "FoundGridCurve: True\n";
			kout << "LSH nearest neighbor: " << min_name << endl ;
			kout << "distance LSH: " << min << endl<<endl ; 
		
		}
		else{//diaforetika pes sto output oti den vrethike
			//geitonas
			//auto shmainei oti den vrethike kampulh sto bucket 
			//pou na exei  to idio grid curve ths kampulhs pou eksetazoume

			kout << "FoundGridCurve: False\n\n\n\n";

		}
		return 0 ; 
	}
	}
	else{
		return 0;
	}

}

/////////////////////////////////////////////////////////////////
//FIND TRUE NEAREST
struct dis_name Linked_List_C :: Is_in_full_C(vector<vector <double> > curve ){
        //ofstream out("outpuT",ios_base::app );
	int i_k_g = 0;
	//pinakes gia na apothikevonte oloi oi geitones (sto telos tha vroume ton Nearest tou bucket)
        double kontinoi_geitones[10000];
      	string onomata_k_geitones[10000];

        bool idio ;
        Curve* Conductor = Head ;//creatae a conductor for our list
        if(Conductor!= NULL){
                while (Conductor!=NULL){//while we are not at the end of the list
//kane frechet ths arxikhs kampulhs me oles tis kampules tou bucket 
//xwris na koitas an exoun to idio grid curve
                        double d_f_d_c1_c2 = discrete_frechet_distance(curve,Conductor->coordinates);
                        if(d_f_d_c1_c2 != 0 ){
				//vaze stous pinakes ta apotelesmata
                        	kontinoi_geitones[i_k_g] = d_f_d_c1_c2;
				onomata_k_geitones[i_k_g] = Conductor->onoma_kampulhs;
                                                i_k_g++;
			}

                        Conductor = Conductor->Next_Curve; //go on
                }
        if(Conductor == NULL ){
		string min_name;
		double min = 10000 ;
		for (int i = 0 ; i < i_k_g ; i++){//vres ton kontinotero sto bucket
			if (kontinoi_geitones[i] < min && kontinoi_geitones[i] > 0.0000000001 ){
				min = kontinoi_geitones[i];
				min_name = onomata_k_geitones[i];
			}
		}
		//fiakse ena struct kai valle mesa to onoma ths kontinoterhs kampulhs
		//kai thn apostash
		struct dis_name d_n;
		d_n.distance = min;
		d_n.name = min_name ; 
		return d_n;//epestrepse afto to apotelesma sthn sunarthsh tou hash table
		//ekeinh tha apofasisei poios einai o kontinoteros geitonas 
		//dhladh apo kathe bucket epistrefoume ton kontinotero 
		//kai meta h sunarthsh pou kalei thn parousa vriskei ton kontinotero 
		//tou pinaka(TRUE NEAREST)
	}

        }
}

