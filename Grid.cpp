#include"Grid.h"
#include<cstdlib>
#include<iomanip>
#include<math.h>
#include<algorithm>
#include <iostream>
#include <string>
#include <random>


Grid :: Grid ()
	:delta(2*dimensions),t(0),dimensions(2){}

Grid :: Grid(float delta)
        :delta(delta),t(this->dimensions * ((((float) rand()) / (float) RAND_MAX))   ){
		this->grid_measurement = delta + t;
		cout << delta << t << grid_measurement<<endl <<endl <<endl ;
	}

Grid :: ~Grid( ) { }

void Grid :: print_grid(){
	cout << "grids' delta = "  << this->delta << "\n";
	cout << "grids' t = " << this->t << "\n";
	cout << "grids' metric unit : " << this->grid_measurement <<  "\n"; 
	//cout << fixed << setprecision(10) << this->t <<"\n";
}

void Grid :: pick_delta(){
	double delta = 8 ;
	this->delta = delta*0.001;
}

void Grid :: pick_t(double rand_t){//dialekse t delta kanonika(main)
  	this->t = rand_t*0.001;
	grid_measurement = (this->t + this->delta) ;

}


vector< vector<double> > Grid :: grid_a_curve( vector <double> Non_grided_curve){
	vector<double> Grided_Curve;//edw tha bei h gridarismenh kampulh

		for(int j = 0; j< Non_grided_curve.size(); j+=2 ){//vres to kontinotero shmeio sto grid
		//gia kathe shmeio ths mh gridarismenhs kampulhs
			double grids_x ;
			double grids_x_ ;
			//ksekinaei na metraei apo to -10(gia kalutero xrono) 
			//tha prepei na alaksei isws an to dataset einai diaforetiko
			//apo afto pou mas dothike
			double reach_non_grided_x = -10;
			while (Non_grided_curve[j] >= reach_non_grided_x ){
				reach_non_grided_x += this->grid_measurement;
			}
			grids_x_ = reach_non_grided_x;
			grids_x = reach_non_grided_x - this->grid_measurement;
			double grids_y ;
                        double grids_y_ ;
                        double reach_non_grided_y = -10;
                        while (Non_grided_curve[j+1] >= reach_non_grided_y ){
                                reach_non_grided_y += this->grid_measurement;

                        }
                        grids_y_ = reach_non_grided_y;
                        grids_y = reach_non_grided_y - this->grid_measurement;

		//vres tis apostaseis apo tza 4 kontinotera shmeia tou grid
		//apostash apo panw deksia
  		double distancex_p_d = (grids_x_ - Non_grided_curve[j]) * (grids_x_ - Non_grided_curve[j]);
  		double distancey_p_d = (grids_y_ - Non_grided_curve[j+1]) * (grids_y_ - Non_grided_curve[j+1]);
  		double distance_p_d = sqrt(distancex_p_d + distancey_p_d);
		//cout << "apostash apo panw deksia :" << distance_p_d  <<endl;
		
		//apostash apo panw aristera
		double distancex_p_a = (grids_x - Non_grided_curve[j]) * (grids_x - Non_grided_curve[j]);
                double distancey_p_a = (grids_y_ - Non_grided_curve[j+1]) * (grids_y_ - Non_grided_curve[j+1]);
                double distance_p_a = sqrt(distancex_p_a + distancey_p_a);
                //cout << "apostash apo panw aristera : " << distance_p_a <<endl ;
		
		//apostash apo katw deksia
		double distancex_k_d = (grids_x_ - Non_grided_curve[j]) * (grids_x_ - Non_grided_curve[j]);
                double distancey_k_d = (grids_y - Non_grided_curve[j+1]) * (grids_y - Non_grided_curve[j+1]);
                double distance_k_d = sqrt(distancex_k_d + distancey_k_d);
                //cout << "apostash apo katw deksia  : " << distance_k_d <<endl;
		
		//apostash apo katw aristera
		double distancex_k_a = (grids_x - Non_grided_curve[j]) * (grids_x - Non_grided_curve[j]);
                double distancey_k_a = (grids_y - Non_grided_curve[j+1]) * (grids_y - Non_grided_curve[j+1]);
                double distance_k_a = sqrt(distancex_k_a + distancey_k_a);
                //cout << "apostash apo katw aristera : " << distance_k_a << endl;

		//upologise to min apo ta 4 kontinotera shmeia
		double min_distance_from_curve = min(min(distance_k_d,distance_k_a),min(distance_p_d,distance_p_a));

		//kai analoga pio einai ekei tha provlithei to sugekrimeno shmeio
		//kai tha bei sto grid curve me push back sto duanisma
		if (min_distance_from_curve == distance_p_d){
			Grided_Curve.push_back(grids_x_);
			Grided_Curve.push_back(grids_y_);
		}
		else if (min_distance_from_curve == distance_p_a){ 
                        Grided_Curve.push_back(grids_x);
                        Grided_Curve.push_back(grids_y_);
     
                }
		else if (min_distance_from_curve == distance_k_d){
                        Grided_Curve.push_back(grids_x_);
                        Grided_Curve.push_back(grids_y);
                }
		else if (min_distance_from_curve == distance_k_a){
                        Grided_Curve.push_back(grids_x);
                        Grided_Curve.push_back(grids_y);
                }

	}
//afairese ta diplotupa
	vector <vector <double> > vec;
	vector <double> vec_d;

	for(int i =0; i < Grided_Curve.size() ; i +=2){
		vector <double> vec_in;
		for(int j = 0 ; j <=1 ; j++){
			vec_in.push_back(Grided_Curve[i]);
			vec_in.push_back(Grided_Curve[i+1]);
		}
		vec.push_back(vec_in);
		sort( vec.begin(), vec.end() );
		vec.erase( unique( vec.begin(), vec.end() ), vec.end() );
	}
	//epestrepse to grid curve
	return vec;
}
