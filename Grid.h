#pragma once
#include<cstdlib>
#include<iostream>
#include<vector>
//#include"linked_list_of_curves.h"

//#include<string>
using namespace std;
class Grid {
        //friend class linked_list_of_curves;
        private:
                float    delta     ;//delta (monada metrishs tou grid)
		float    t	   ; // t (kathe fora alazei ligo thn monada metrishs)
		float    dimensions;//float for the rand function 
		float grid_measurement;//delta + t
        public :
		Grid();//default constructor of grid
		Grid(float );  //Constructor of Grid structure
                ~Grid();//destructor of grid
                void print_grid  () ;          //Print the grid
		void pick_delta();//dialekse delta (stahero)
		void pick_t(double );//dialekse t(metavalomeno)
		vector <vector <double> > grid_a_curve(vector <double> );//Gridare mia kampulh 
		//analoga me ta tafs
};


