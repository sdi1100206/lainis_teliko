#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Curve {

	friend class Linked_List_C		;//class Linked_List_C has access here
	private:
		Curve* 	        Next_Curve	;//Pointer to the next curve

		vector< vector <double> > coordinates ;//dianusma atofias kampulhs
		vector<vector <double> > coordinates_in_grid ; // dianusma K gridarismenhs kampulhs
		string		onoma_kampulhs	;// onoma kampulhs

	public :
		//Constructor with values
		Curve( string ,vector< vector <double> >,vector<vector <double> > );
		Curve(void)		;	//default constructor
};
