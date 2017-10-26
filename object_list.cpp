#include"object_list.h"
#include<string>
#include<cstring>

using namespace std;

//construct a curve
Curve :: Curve( string onoma , vector < vector<double> > coors,vector <vector <double> > coors_in_grid)//Defining a curve
	:Next_Curve(NULL),onoma_kampulhs(onoma),coordinates(coors),coordinates_in_grid(coors_in_grid){}

Curve :: Curve(void) // construct a curve by default
	:Next_Curve(NULL){}

