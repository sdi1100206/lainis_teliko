#include<cstdio>
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<cstdlib>
#include<cstring>
#include"linked_list_of_curves.h"
#include"read_file.h"
#include "hash_table.h"
#include<iomanip>
#include"Grid.h"
#include<random>
#include<iomanip>
#include"Functions.h"
using namespace std;

void open_querry_file(string dataset,hash_table* table,Grid gridaki[],int K ){

//	cout <<"DATSET:" << dataset << endl ;
        ifstream set(dataset);//auto to arxeio anoigw
        string word  ;//edw tha vazeis tis lekseis tou dataset
	char c ;
        int numbers = 0 ;
        while( set >> c  ){//PARE to R(panta 0 )
          if (c == ':'){break;} 
        }
	set >> word ; 
//	cout << word ; 
        while(set >> word  ){//oso uparxoun lekseis sto dataset pare mia
        	bool only_digits;//flag gia to an oi lekseis periexoun mono noumera(prosdioristes kampulhs)
      		string curve_name = word ;
                set >> word ; 
                numbers=2;
		string curve;

		if (numbers == 2 ){// An uparxoun 2 sunexomena noumera shmainei oti ksekinaei kainouria $
                        numbers = 0 ;
                        //kai afta ta 2 noumera einai o arithmos ths kai o aritmos twn shmeiwn ths
                        //string curve ;
                        bool only_digits; 
                        int arithmos_shmeiwn = stoi(word) ;//edw apothikevete o arithmos trwn shmeiwn th$
                        for(int i = 0 ; i <2*arithmos_shmeiwn; i++ ){//fiakse to string ths kampulhs gnw$
                                set >> word ;
                                curve.append(word);

                        }
                        //numbers= 0 ;
                        //while continiues we have one new curve as string
                        int number_of_points = arithmos_shmeiwn ;
                        string V;
			for (int i = 0 ; i <= curve.length(); i ++ ){
                                if (curve[i] == ',' && curve[i+1] == '('){
                                        curve.erase(curve.begin() + i );
                                }
                        }
                        string points[2*number_of_points];
                        long double points_d[2*number_of_points];

                        int k = 0 ;
                        int n = 0 ;
                        while(curve[n] != '\0' && k < 2*number_of_points && n < curve.length()){
                                if(curve[n] == '(' /*|| curve[n] ==',' */){
                                        n++;
                                //continue;
                                }
                                if(isdigit(curve[n]) || curve[n] == '.' || curve[n] == '-'){
                                                points[k].push_back(curve[n]);
                                }
                                else if(curve[n] == ')' || curve[n] == ',' ){
 //100cout                               << "-----"<<points[k] << endl;
                                        size_t size = 16;
                                        points_d[k]  = (long double)stod(points[k],NULL);
                                        points[k] = "";
                                        k++;
                                }
                                n++;
                        }

                        vector<vector <double> > Curve ;//To diplo vector(kampulh) pou tha bei se ena bu$
                        vector <double> Curve_go_grid ;//to mono vector(kampulh-idio me to apw panw) pou$
                        for (int i= 0 ; i<2*number_of_points ; i+=2){
                                vector<double> suntetagmenes ;
                                        suntetagmenes.push_back(points_d[i]);
                                        suntetagmenes.push_back(points_d[i+1]);
                                        Curve.push_back(suntetagmenes);

					Curve_go_grid.push_back(points_d[i]);
                                        Curve_go_grid.push_back(points_d[i+1]);
                        }
                        //Sunarthsh gia na gridaei thn kampulh K fores kai na epistrepsei ton grammiko s$
			struct Concatenated Con = Grid_a_curve_K_times_and_return_riConnation(Curve_go_grid,gridaki,K);                
                        //Hash Function prosdiorizei to bucket pou tha psaksoume
                        int H = table->hash_function(Con.Hadd);
        		//cout << H << endl;
			ofstream kout("output",ios_base::app);
			//grapse sto output to onoma tou epomenou querry
			kout << "Query:" << curve_name << endl  ;
			//psakse sto bucket H, se olh thn lista na vreis ton LSH nearest an uparxei
			table->Search_vector_in_bucket(Con.K_grided_curve,Curve,H);
		}


        }

//	table;
        set.close();
}

hash_table* load_hash_table_with_curves(string dataset,hash_table* table, Grid gridaki[], int K) {

	ifstream set(dataset);
	
	string word  ;//edw tha vazeis tis lekseis tou dataset
	int n_c;
	int numbers = 0 ;
	int kampules = 0 ;
	int k = 0 ;
	string first_line;
	getline(set,first_line);//parakampse thn 1h grammh dioti exw ulopoihsei mono tis 2 diastaseis

	while(set >> word  ){//oso uparxoun lekseis sto dataset pare mia
		bool only_digits;//flag gia to an oi lekseis periexoun mono noumera(prosdioristes kampulhs)
		string curve_name = word ;
		set >> word ;
		numbers=2;
		string curve;

		if (numbers == 2 ){// An uparxoun 2 sunexomena noumera shmainei oti ksekinaei kainouria kampulh  
			numbers = 0 ;
			//kai afta ta 2 noumera einai o arithmos ths kai o aritmos twn shmeiwn ths
			//string curve ;
			bool only_digits; 
			int arithmos_shmeiwn = stoi(word) ;//edw apothikevete o arithmos trwn shmeiwn ths kampulhs 
			for(int i = 0 ; i <2*arithmos_shmeiwn; i++ ){//fiakse to string ths kampulhs gnwrizodas ton arithmo twn shmeiwn ths
				set >> word ;
				curve.append(word);

			}

			//while continiues we have one new curve as string
			int number_of_points = arithmos_shmeiwn ;
			string V;
			for (int i = 0 ; i <= curve.length(); i ++ ){
				if (curve[i] == ',' && curve[i+1] == '('){
					curve.erase(curve.begin() + i );
				}
			}
			string points[2*number_of_points];
                	long double points_d[2*number_of_points];

			int k = 0 ;
                	int n = 0 ;
                	while(curve[n] != '\0' && k < 2*number_of_points && n < curve.length()){
                        	if(curve[n] == '(' /*|| curve[n] ==',' */){
                                	n++;
                                //continue;
                        	}
                         	if(isdigit(curve[n]) || curve[n] == '.' || curve[n] == '-'){
                                	        points[k].push_back(curve[n]);
                        	}
                        	else if(curve[n] == ')' || curve[n] == ',' ){
 //100cout                               << "-----"<<points[k] << endl;
   					size_t size = 16;
					points_d[k]  = (long double)stod(points[k],NULL);
					points[k] = "";
                                	k++;
                        	}
                		n++;
			}

                	vector<vector <double> > Curve ;//To diplo vector(kampulh) pou tha bei se ena bucket
                	vector <double> Curve_go_grid ;//to mono vector(kampulh-idio me to apw panw) pou tha gridarisete K fores
			for (int i= 0 ; i<2*number_of_points ; i+=2){
                        	vector<double> suntetagmenes ;
                                	suntetagmenes.push_back(points_d[i]);
                                	suntetagmenes.push_back(points_d[i+1]);
					Curve.push_back(suntetagmenes);

					Curve_go_grid.push_back(points_d[i]);
					Curve_go_grid.push_back(points_d[i+1]);
			}
			//Sunarthsh gia na gridaei thn kampulh K fores kai na epistrepsei ton grammiko sundiasmo tou concatanated dianismatos kampulhs
			struct Concatenated Con = Grid_a_curve_K_times_and_return_riConnation(Curve_go_grid,gridaki,K);
			//Hash Function- gia na prosdiorisei to bucket pou tha bei h kampulh
        		int H = table->hash_function(Con.Hadd);
			//Rikse thn kampulh sto bucket pou eipe h sunarthsh katakermatismou
			table->add_curve(curve_name,Curve,Con.K_grided_curve,H);
		}


	}
	set.close(); 
}


void open_querry_file_and_find_nearest_n(string dataset,hash_table* table,Grid gridaki[],int K ){
        ifstream set(dataset);//auto to arxeio anoigw
        string word  ;//edw tha vazeis tis lekseis tou dataset
        char c ;
        int numbers = 0 ;

        //table.print();
        while( set >> c  ){
          if (c == ':'){break;} 
             //set >> word;
                //int R = word;
                //cout <<"RRRRRRRRRRRRRRR"<< R ; 
        }
        set >> word ; 
	while(set >> word  ){//oso uparxoun lekseis sto dataset pare mia
        bool only_digits;//flag gia to an oi lekseis periexoun mono noumera(prosdioristes kampulhs)
		string curve_name = word ;
                set >> word ; 
                numbers=2;

//                string curve;
                string curve;
                if (numbers == 2 ){// An uparxoun 2 sunexomena noumera shmainei oti ksekinaei kainouria $
                        numbers = 0 ;
                        //kai afta ta 2 noumera einai o arithmos ths kai o aritmos twn shmeiwn ths
                        //string curve ;
			bool only_digits; 
                        int arithmos_shmeiwn = stoi(word) ;//edw apothikevete o arithmos trwn shmeiwn th$
                        for(int i = 0 ; i <2*arithmos_shmeiwn; i++ ){//fiakse to string ths kampulhs gnw$
                                set >> word ;
                                curve.append(word);

                        }
                        //numbers= 0 ;
                        //while continiues we have one new curve as string
                        int number_of_points = arithmos_shmeiwn ;
                        string V;
                        for (int i = 0 ; i <= curve.length(); i ++ ){
                                if (curve[i] == ',' && curve[i+1] == '('){
                                        curve.erase(curve.begin() + i );
                                }
                        }
                        string points[2*number_of_points];
                        long double points_d[2*number_of_points];

                        int k = 0 ;
			int n = 0 ;
                        while(curve[n] != '\0' && k < 2*number_of_points && n < curve.length()){
                                if(curve[n] == '(' /*|| curve[n] ==',' */){
                                        n++;
                                //continue;
                                }
                                if(isdigit(curve[n]) || curve[n] == '.' || curve[n] == '-'){
                                                points[k].push_back(curve[n]);
                                }
                                else if(curve[n] == ')' || curve[n] == ',' ){
 //100cout                               << "-----"<<points[k] << endl;
                                        size_t size = 16;
                                        points_d[k]  = (long double)stod(points[k],NULL);
                                        points[k] = "";
                                        k++;
                                }
                                n++;
                        }

                        vector<vector <double> > Curve ;
			vector <double> Curve_go_grid ;
                        for (int i= 0 ; i<2*number_of_points ; i+=2){
                                vector<double> suntetagmenes ;
                                        suntetagmenes.push_back(points_d[i]);
                                        suntetagmenes.push_back(points_d[i+1]);
                                        Curve.push_back(suntetagmenes);

                                        Curve_go_grid.push_back(points_d[i]);
                                        Curve_go_grid.push_back(points_d[i+1]);
                        }
                        //Sunarthsh gia na gridaei thn kampulh K fores kai na epistrepsei ton grammiko s$
                        struct Concatenated Con = Grid_a_curve_K_times_and_return_riConnation(Curve_go_grid,gridaki,K);
                        //Hash Function prosdiorizei to bucket pou tha psaksoume
                        int H = table->hash_function(Con.Hadd);
            //            cout << H << endl;
                        //con.K_grided_curve
                        //psakse se olo to table gia na vreis ton TRUE NEAREST
          //              cout << "\n\nAlagh Kampulhs\n\n";
			ofstream outt("outpuT",ios_base::app);
			outt << "Query:" << curve_name << endl ;

                        table->Search_vector_in_table(Curve);
			
			}


        }
        set.close();
}

