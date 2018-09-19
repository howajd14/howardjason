#include "../../classes/2D_ising.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std; 

int main()
{
  int S = 40; 
  int its = 5e6;
  double J= 1; 
  double T = 6; 
  double avgM=0; 
  int  n = 8; 
  double omega = 2; for(int x=1; x<=(n*n)-1; x++){omega=omega*2;} cout << "\n" << omega << "\n"; 
  vector<ising2d>  is_a; for(int x=1; x<=S; x++){is_a.push_back(ising2d(n)); }
  srand(time(NULL)); 
  vector<double> ens; 
  for(int x=1; x<=S; x++)
  {
   
	for(int y=1; y<=n; y++)
	{
		for(int k=1; k<=n; k++)
		{
			int  rand_s = 1;//(rand() % 2 + 1)*2 -3;
			is_a[x-1].set_s(rand_s,y,k); 
		}
	}
	double E=0; 
	for(int y=1; y<=n-1; y++)
	{
          E = is_a[x-1].get_en(J); 
	}
	ens.push_back(E); 
  }
  vector<double> tempens; for(int x=1; x<=S; x++){tempens.push_back(ens[x-1]);}
  sort(tempens.begin(),tempens.end()); 
  
for(int x=1; x<=its; x++)
{
//	T = T - ((T/1.25)/(its-(x-1) )); 
	vector<ising2d> n_a; if(x%1000==0){cout << "\n" << x << "\tavgM:   " << avgM/(x) ; }
	for(int xx=1; xx<=S; xx++)
	{
		n_a.push_back(is_a[xx-1]);
	}
	vector<double> ensp;
	vector<double> ensp_oorder; 
	for(int y=1; y<=S; y++)
	{
		int ri1 = rand()%n + 1; int ri2 = rand()%n + 1;
		n_a[y-1].set_s(n_a[y-1].get_s(ri1,ri2)*-1,ri1,ri2); 
		double E1=0; 
		
		
		  E1 = n_a[y-1].get_en(J); 
		
	       ensp.push_back(E1); 
 	       
	}
	vector<double> tempensp; for(int oo=1; oo<=S; oo++){tempensp.push_back(ensp[oo-1]);}
	sort(tempensp.begin(),tempensp.end()); 
	double ZL =0; for(int xy = 1; xy <= S; xy++){ZL = ZL + exp(-(tempens[xy-1]-tempens[0])/T);}
		      for(int xy =1; xy <= S; xy++){ avgM = avgM + 1.0*(is_a[xy-1].get_M())*exp(-(is_a[xy-1].get_en(J) - tempens[0])/T)/ZL;}
	 
		    
	vector<double> totens; for(int xy=1; xy<=S; xy++){totens.push_back(tempens[xy-1]);} 
				for(int xy=1; xy<=S; xy++){totens.push_back(tempensp[xy-1]);}
	sort(totens.begin(),totens.end()); 
	double ZIL=0; for(int xy=1; xy <= 2*S; xy++){ZIL = ZIL + exp(-(totens[xy-1]-totens[0])/T);}
	 
	for(int y=1; y<=S; y++)
	{
		
		double p  = (rand()%RAND_MAX + 1)/(RAND_MAX*1.0); 
		if(p <  exp(- (ensp[y-1]-ens[y-1]) /T )*(2*ZL/ZIL))
		{
			//cout << "\n" << 2*ZL/ZIL << "\t" << exp(-(ensp[y-1]-ens[y-1])/T) << "\t" << y;
			for(int ll=1; ll<=n; ll++)
			{
			   for(int hg=1; hg<=n; hg++)
			   {
				is_a[y-1].set_s(n_a[y-1].get_s(ll,hg),ll,hg);
			   }
			}
			ens[y-1]=ensp[y-1]; 	
		}
	}
	for(int z=1; z<=S; z++){tempens[z-1]=ens[z-1];}
	sort(tempens.begin(),tempens.end()); 
	
	
}

cout << "\n\n" << avgM/(its*1.0) << "\n\n"; 

return 0; 
}
