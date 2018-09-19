#include "../../../classes/2D_ising.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std; 

int main()
{
  int S = 1; 
  int its = 0;
  double J= -0.001; 
  int  n = 12; 
  double omega = 2; for(int x=1; x<=(n*n)-1; x++){omega=omega*2;} cout << "\n" << omega << "\n"; 
  //double Osub = 1e250; 
  vector<ising2d>  is_a; for(int x=1; x<=S; x++){is_a.push_back(ising2d(n)); }
  srand(time(NULL)); 
  vector<double> ens;
  file exact("Exact_logGE.dat"); 
  vector<double> exactvals; 
  double  eps = 0.005; double error = 100; double error1=100; 
  file error_out; 
  int count =1; 
  for(int x=1; x<=exact.num_lines(); x++)
  {
	stringstream ss; ss << exact.get_line(x); 
	double val ; ss >> val ; ss >> val; 
	exactvals.push_back(val); 
  } 
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
          E = (1.0/2.0)*is_a[x-1].get_en(J); 
	}
	ens.push_back(E); 
  }
  vector<double> tempens; for(int x=1; x<=S; x++){tempens.push_back(ens[x-1]);}
  sort(tempens.begin(),tempens.end()); 
  hist GE(tempens); 
  GE.make_file("GE1");
int x =0; 
while(error1>eps)
{
	x=x+1; 
	vector<ising2d> n_a; if(x%1000==0){cout << "\n" << x;}
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
		
		
		  E1 = (1.0/2.0)*n_a[y-1].get_en(J); 
		
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
		Hp.set_count(kk,omega*Hp.get_count(kk)*GEI.get_count(wb)/GEI.get_sum()); 
	}
	GE.combine(Hp);
	/* 
        double sumtemp = GE.get_sum(); 
	for(unsigned int kk=1; kk<=GE.num_bins(); kk++)
	{
		if(GE.get_count(kk)*omega/sumtemp < 1.0){GE.set_count(kk,sumtemp/omega);}
	}
	*/
	if(x%1000==0)
	{
		unsigned int nbins = GE.num_bins(); cout << "\t" << nbins; 
		if(nbins == exactvals.size())
		{
			double sum =0; 
			double Nf = (omega/GE.get_sum());
			for(unsigned int uii =1; uii<=nbins; uii++)
			{
			double v1 = (exactvals[uii-1]-log(GE.get_count(uii)*Nf));
			double v2 = exactvals[uii-1]*exactvals[uii-1];
		sum = sum + sqrt(v1*v1/(v2*v2));
			}
		if(count==1){error = sum/(nbins*1.0); cout << "\t" << error; its = x; }
		if(count>1){error = (error + sum/(nbins*1.0)); cout << "\t" << error/(count*1.0)<<"\t" << sum/(nbins*1.0); its =x; }
		error1 = sum/(nbins*1.0);
		stringstream er; er << x;  string erout; er >> erout; string holder; er.clear();er.str(""); er << error/count; 
		er >> holder; erout = erout + "\t" + holder; 
		er.clear();er.str(""); er << error1; er >> holder; 
		erout = erout + "\t" + holder; error_out.add_line(erout); 
		count = count+1;
		}
	}
}
double Nf = (omega/GE.get_sum()); 
for(unsigned int x=1; x<=GE.num_bins(); x++) 
{
	GE.set_count(x,log(GE.get_count(x)*Nf)); 
}

GE.make_file("fileHist.dat"); 
file outits; 
stringstream ki; ki << its; string outfinal; ki >> outfinal; 
outits.add_line(outfinal); outits.make_file("number_its"); 
error_out.make_file("error_vs_T.dat"); 
return 0; 
}
