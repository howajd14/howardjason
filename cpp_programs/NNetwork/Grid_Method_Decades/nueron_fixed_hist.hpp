#include "dataset_fixed_hist.hpp"
#include "math.h"
using namespace std; 

class nueron
{
   public:
	nueron(); 
	nueron(int sz); 
	~nueron();
	double get_W(int index){return nw[index-1];}
	void  set_W(int index, double val){nw[index-1]=val;}
	int   get_nw() {return nw.size();}
	void  set_nb(double val){nb=val;}
	double get_nb(){return nb;}

   private:
   vector<double>  nw; 
   double nb; 
   int  size; 

};

//default constructor
nueron::nueron()
{
 nw.push_back(0); size=1; 
}
//basic constructor
nueron::nueron(int sz)
{
	nb =0;
	for(int x=1; x<=sz; x++){nw.push_back(0);}
	//cout << "\n" << nw.size(); 
	size = sz ;
}

//destructor
nueron::~nueron()
{}
