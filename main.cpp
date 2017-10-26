#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include "Functions.h"
#include "linked_list_of_curves.h"
#include "hash_table.h"
#include "read_file.h"
#include <random>
#include<iomanip>

using namespace std;

int main(int argc, const char *argv[]) {
	int K = 3, L = 2, index;// Default K kai L se periptwsh pou den dothoun apo ton xrhsth
	string d, q, o;	// strings gia apothikeush arxeiwn 
  	for (index = 1; index < argc; index++) {//arxikopoiei to input tou xrhsth
		if (strcmp(argv[index], "-d") == 0) {//meta apo to -d vriskete to dataset file
			d = string(argv[index+1]);
        	}
        	else if (strcmp(argv[index], "-q") == 0) {//meta apo to -q vriskete to querry file
            		q = string(argv[index+1]);
        	}
        	else if (strcmp(argv[index], "-k") == 0) {//meta apo to -K vriskete to K(for grid)
            		K = atoi(argv[index+1]);
        	}
        	else if (strcmp(argv[index], "-L") == 0) {//meta apo to -L vriskete o arithmos twn pinakwn katakermatismou pou tha kataskevastoun
            		L = atoi(argv[index+1]);
        	}
        	else if (strcmp(argv[index], "-o") == 0) {//meta apo to -q vriskete to output file
            		o = string(argv[index+1]);
        	}

	}
	Grid gridaki[K];//fiaxnode K grids san enas pinakas apo grids
	double ts[K];//edw apothikevonte ta diaforetika t twn grid


	ofstream kout("output");//anoikse ena arxeio gia na vazeis ta LSH apotelesmata
	ofstream outt("outpuT");//anoikse ena arxeio gia na vazeis ta True apotelesmata

	hash_table **hash_tables;//deikths sta hash tables
	hash_tables = new hash_table *[L];//dimiourghse xwro gia L hash tables
	default_random_engine generator;
        normal_distribution<double> distribution(4.0,1.0);//kanonikh katanomh sto zitoumeno evros gia epilogh t twn grid

	for(int i = 0;i < L;i++){//Gia kathe pinaka
		for(int i = 0 ; i < K ; i++){//gia diaforetika K grids pare tuxaia to t 
        	        double number = distribution(generator)  ; 
                	ts[i] = number ;
	        }
        	for(int i = 0 ; i <K ; i++){//gia ta diaforetika K grids pare to delta (idio)kai to t(apo ton pinaka pou exoun apothikeftei ta diaforetika t) 
                	gridaki[i].pick_delta() ;
                	gridaki[i].pick_t(ts[i]);
        	}
   		hash_tables[i] = new hash_table(1021);//kataskevase ena hash table kathe fora

		load_hash_table_with_curves(d,(hash_tables[i]),gridaki,K);//fwrtose ta hash table me to dataset
		cout << "\nI am loading 1 hash table with  dataset\n";
		
		//an einai to prwto hash table epou kataskevasthke tote vres apo to query dataset 
		//tous kontinoterous geitones kai apothikefse tous sto outpuT(standard)
		//(ginete mia fora )
		if(i==0){
			cout << "\nI am finding the true nearest neigbors\n";
			open_querry_file_and_find_nearest_n(q,hash_tables[0],gridaki,K);
		}
		cout << "\nI am finding the LSH Nearest neighbors of the last table which constructed\n";
		open_querry_file(q,(hash_tables[i]),gridaki,K);//vres ta LSH kontinotera
		//hash_tables[i]->print();//ektupwse to hash table(an thelei o eksetasths )
		//na eksetasei ta diaforetika tables
	}


	string line;//gramh apo to output
	ifstream lsh("output");//anoikse to output(standard),einai to arxeio pou exoun graftei 
	//ta LSH apotelesmata

	int n_o_l=0 ;//akaireos gia na apothikeftoun oi grammes tou output file
	if(lsh.is_open()){
        	while(!lsh.eof()){//metra tis grammes
            		getline(lsh,line);
            		n_o_l++;
        	}
        	lsh.close();//kleise to arxeio
    	}

	ifstream lshh("output"); //ksanaanoikse to output apo thn arxh

	ofstream lsh_o(o);//anoikse to arxeio eksodou pou edwse o xrhsths gia grapsimo

	for(int j = 0; j <L ; j++ ){//antegrapse to arxeio output(standard) sto output tou xrhsth(changing)
		for(int i = 0 ; i < n_o_l /L; i ++ ){
			getline(lshh,line);
			lsh_o << line;
			lsh_o << endl;

		}
	}
	//Katestrepse ola ta hash tables
	for(int i = 0;i < L;i++){
		hash_tables[i]->destroy_hash_table();
	}
	delete [] hash_tables;
	cout << "\nYour output is ready\n";
	return 0 ;
	
}



