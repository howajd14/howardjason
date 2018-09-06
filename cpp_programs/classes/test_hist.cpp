#include "histogram.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std; 

int main()
{
srand(time(NULL)); 
vector<double> ens1,ens2; 
for(int x=1; x<=1e4; x++)
{
 double en =  (rand()%1000+1)/10.0; 
ens1.push_back(en); 
	en = (rand()%1000+1)/10.0;
ens2.push_back(en); 
}
sort(ens1.begin(),ens1.end()); 
sort(ens2.begin(),ens2.end()); 
hist GE1(ens1); 
hist GE2(ens2);
hist GE3(GE1,GE2); 
GE1.make_file("GE1"); 
GE2.make_file("GE2"); 
GE3.make_file("GE3"); 

GE1.combine(GE2); 
GE1.make_file("GE4"); 


return 0; 
}
