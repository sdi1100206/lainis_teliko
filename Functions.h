#ifndef Functions_H
#define Functions_H

#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include"Grid.h"
#include<random>
#include<iomanip>
#include"Functions.h"
//#include"random_array.h"

using namespace std;

string ReadLine();
//gridare k fores kai epestrepse ton grammiko sundiasmo ths kampulhs me tuxaious arithmous

struct Concatenated Grid_a_curve_K_times_and_return_riConnation(vector <double>,Grid[],int);
//sunarthsh gia ulopohsh thn DFD
double discrete_frechet_distance(vector < vector<double> > ,vector < vector<double> > );

//struct, krataei mia gridarismenh kampulh kai to apotelesma tou grammikou sundiasmou(long double)
struct Concatenated{
	vector< vector <double> > K_grided_curve ; 
	long double Hadd ; 
};
//struct krataei ena onoma kampulhs kai mia apostash
struct dis_name{
	double distance ; 
	string name ;
};

#endif
