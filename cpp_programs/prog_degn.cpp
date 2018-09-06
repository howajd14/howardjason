#include "classes/histogram.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std; 
int main()
{
  int S = 100; 
  int its = 1000; 
  int sz =1; 
  double dat1[sz][2]; for(int x=1; x<=sz; x++){for(int y=1; y<=2; y++){dat1[x-1][y-1]=0;};}
  double dat2[sz][2]; for(int x=1; x<=sz; x++){for(int y=1; y<=2; y++){dat2[x-1][y-1]=0;};}
for(int x=1; x<=sz; x++)
{
    int range =  1e3 + 1e3*(x-1); 
    dat1[x-1][0]=range; dat2[x-1][0]=range; 
     vector<double> D; 

    for (int jj=1; jj<=its; jj++)
    { 
	vector<int>  vals;
	int count=0; 
    	for(int ii=1; ii<=S; ii++){vals.push_back(rand()%range + 1);}
	for(int pp=1; pp<=S; pp++)
	{
		for(int oo=1; oo<=S; oo++)
		{
			if(oo!=pp&&vals[oo-1]==vals[pp-1]){count++;}
		}
	}
        
	D.push_back(count); 
    }
   sort(D.begin(),D.end()); 
   hist  valHist(D); 
   double p4  =  0; 
    if(valHist.get_bin(4)!=0){p4 = vaDlHist.get_count(valHist.get_bin(4))/valHist.get_sum(); }
   dat1[x-1][1]=p4; 
   double p18 =0; 
    if(valHist.get_bin(18)!=0){p18= valHist.get_count(valHist.get_bin(18))/valHist.get_sum();}
   dat2[x-1][1]=p18; 
    
}

file outfile1; file outfile2; 
for(int x=1; x<=sz; x++)
{
	stringstream ss; ss << dat1[x-1][0]; string rnge; ss >> rnge; 
	string outline; outline = rnge; 
	ss.clear(); ss.str(""); ss << dat1[x-1][1]; string holder; ss >> holder; 
	outline = outline + "\t" + holder; 
	ss.clear(); ss.str(""); 
	outfile1.add_line(outline); 
	ss << dat2[x-1][1]; ss >> holder; outline = rnge + "\t" + holder; 
	outfile2.add_line(outline); 
}
outfile1.make_file("D4_probs"); 
outfile2.make_file("D18_probs"); 

return 0; 
}
