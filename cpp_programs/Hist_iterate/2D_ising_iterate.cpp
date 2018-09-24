#include "../classes/2D_ising.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std; 

int main()
{
  int S = 100; 
  int its = 100000;
  double J= -0.005; 
  int  n = 4; 
  double omega = 2; for(int x=1; x<=(n*n)-1; x++){omega=omega*2;} cout << "\n" << omega << "\n"; 
  ising2d  is_a[S]; 
  srand(time(NULL)); 
  vector<double> ens; 
  for(int x=1; x<=S; x++)
  {
	for(int y=1; y<=n; y++)
	{
		for(int k=1; k<=n; k++)
		{
			int  rand_s = (rand() % 2 + 1)*2 -3;
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
  hist GE(tempens); 
  GE.make_file("GE1");
for(int x=1; x<=its; x++)
{
	ising2d n_a[S]; 
	for(int xx=1; xx<=S; xx++)
	{
		for(int yy=1; yy<=n; yy++)
		{
			for(int zz=1; zz<=1; zz++)
			{
				n_a[xx-1].set_s(is_a[xx-1].get_s(yy,zz),yy,zz);
			} 
		}
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
	hist HE(tempensp); 
	hist GEI(GE,HE); 
	for(int y=1; y<=S; y++)
	{
		int b1 = GEI.get_bin(ens[y-1]); 
		int b2 = GEI.get_bin(ensp[y-1]); 
		double p  = (rand()%RAND_MAX + 1)/(RAND_MAX*1.0); 
		if(p <  GEI.get_count(b1)/GEI.get_count(b2))
		{
			
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
	hist Hp(tempens); 
	for(unsigned int kk=1; kk<=Hp.num_bins(); kk++)
	{
		int  wb =  GEI.get_bin(Hp.get_en(kk)); 
		Hp.set_count(kk,Hp.get_count(kk)*GEI.get_count(wb)/GEI.get_sum()); 
	}
	GE.combine(Hp); 
}

double Nf = (omega/GE.get_sum()); 
for(unsigned int x=1; x<=GE.num_bins(); x++) 
{
	GE.set_count(x,GE.get_count(x)*Nf); 
}

GE.make_file("fileHist"); 
return 0; 
}
