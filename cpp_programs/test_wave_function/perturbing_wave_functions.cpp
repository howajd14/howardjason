#include "../classes/Wave_Function.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std; 

int main()
{
int size = 1000; 
double H=1; double V=0; 
double pt = 0.00001;
int S = 1;  
psi  psiI(size,1,1,1); 
psi zeropsi(size,1,1,1); 
vector<psi>  eps; for(int x=1; x<=S; x++){eps.push_back(psiI);}
int its = 4e7; 
srand(time(NULL)); 
double T = 2e-9; 
double pi = 3.14159; 
for(int x=1; x<=size; x++)
{

	if(x==1){psiI.set_psi(x,1,1,0,0);}
	if(x==size){psiI.set_psi(x,1,1,0,0);}
	if(x!=1&&x!=size){psiI.set_psi(x,1,1,sin(10.25*pi*(x-1)/((size-1)*1.0)),0); }
}
psi psiIp(size,1,1,1);psiIp.equals(psiI);
psi monitor(size,1,1,1); monitor.equals(psiI); 
psiI.normalize();

for(int x=1; x<=its; x++)
{
          for(int ii = 1; ii<=S; ii++)
	 {
		eps[ii-1].equals(zeropsi); 
		int  pl = rand()%(size - 2) + 2; 
		double enh = 1.0*(rand()%10); 
		int  pm = (rand()%2 +1)*2  -3; 
		
		eps[ii-1].set_psi(pl,1,1, pm*pt*enh,0);
		if(pl>2&&pl<size-2)
		{
			eps[ii-1].set_psi(pl-1,1,1, pm*pt/2*enh,0);
			eps[ii-1].set_psi(pl+1,1,1, pm*pt/2*enh,0);
		}
	 }
	// psiI.normalize(); 
	 psiIp.equals(psiI); 
	  for(int ii = 1; ii<=S; ii++)
	 {
		psiIp.add_psi(eps[ii-1]);
		
	 }
	 psiIp.normalize(); 
	if(x%1000==0){monitor.equals(psiI); monitor.normalize(); cout << "\n" <<  monitor.get_totEn(H,V); }
	for(int ii =1; ii<=S; ii++)
	{
		double delEn =0; 
		delEn = delEn + eps[ii-1].get_ovlpEn(H,V,psiIp); 
		delEn = delEn - eps[ii-1].get_totEn(H,V); 
		delEn = delEn + psiIp.get_ovlpEn(H,V,eps[ii-1]); 
		//double E1 = psiIp.get_totEn(H,V); 
		//psiIp.minus_psi(epsp[ii-1]); double E2 = psiIp.get_totEn(H,V); 
		//cout << "\n" << delEn << "\t" << x << "\t" << ii; 
		
		
		double p = (rand()%RAND_MAX +1)/(1.0*RAND_MAX);
		//if(x%1000==0&&ii==1){cout << "\n" << exp(-delEn/T) << "\t" << delEn; }
		if(p < exp(-delEn/T))
		{
			eps[ii-1].add_psi(eps[ii-1]); 
			psiI.add_psi(eps[ii-1]); 
			
		}
		
	}
	//psiI.smooth(); 
	psiI.normalize();


}

file outfile1; string outline1,outline2;
file outfile2;  
for(int x=1; x<=size; x++)
{
	stringstream ss; ss.width(10);ss.precision(10); 
	ss << x; ss >> outline1; outline2 = outline1; ss.clear(); ss.str(""); 
	ss << psiI.get_psiR(x,1,1); string holder; ss >> holder; 
	outline1 = outline1 + "\t" + holder; 
	outfile1.add_line(outline1); ss.clear(); ss.str(""); 
	ss << psiI.get_psiI(x,1,1);  ss >> holder; 
	outline2 = outline2 + "\t" + holder; 
	outfile2.add_line(outline2); 
	 
}
outfile1.make_file("PsiR.dat"); 
outfile2.make_file("PsiI.dat"); 
 



return 0; 
}
