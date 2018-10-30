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
	int   get_nw() {return size;}

   private:
   vector<double>  nw; 
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
	for(int x=1; x<=sz; x++){nw.push_back(0);}
	size = sz ;
}

//destructor
nueron::~nueron()
{}
