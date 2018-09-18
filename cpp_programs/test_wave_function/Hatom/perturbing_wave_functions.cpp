#include "../../classes/Wave_Function.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std; 

int main()
{
int size = 30; 
double H=1.0/2.0; double V=0; 
double pt = 0.00001;
double hx,hy,hz; hx=15.5;hy=15.5; hz=15.5;
double del = 0.25; 
int S = 1;  
psi  psiI(size,size,size,0.25); 
psi zeropsi(size,size,size,1); 
vector<psi>  eps; for(int x=1; x<=S; x++){eps.push_back(psiI);}
int its = 1e6; 
srand(time(NULL)); 
double T = 2e-9; 
double pi = 3.14159; 
for(int x=1; x<=size; x++)
{
     for(int y=1; y<=size; y++)
     {
	for(int z=1; z<=size; z++)
	{
	if(x==1){psiI.set_psi(x,y,z,0,0);}
	if(x==size){psiI.set_psi(x,y,z,0,0);}
	if(y==1||y==size){psiI.set_psi(x,y,z,0,0);}
	if(z==1||z==size){psiI.set_psi(x,y,z,0,0);}
	if(((x!=1&&x!=size)&&(y!=size&&y!=1))&&(z!=size&&z!=1))
	{psiI.set_psi(x,y,z,1,0); }

	}
     }
}
psi psiIp(size,size,size,0.25);psiIp.equals(psiI);
//psi monitor(size,size,size,0.25); monitor.equals(psiI); 
psiI.normalize();

for(int x=1; x<=its; x++)
{
          for(int ii = 1; ii<=S; ii++)
	 {
		eps[ii-1].equals(zeropsi); 
		int  pl1 = rand()%(size - 2) + 2; 
		int  pl2 = rand()%(size - 2) + 2;
		int  pl3 = rand()%(size - 2) + 2;
		double enh = 1.0*(rand()%10); 
		int  pm = (rand()%2 +1)*2  -3; 
		
		eps[ii-1].set_psi(pl1,pl2,pl3, pm*pt*enh,0);
		
	 }
	// psiI.normalize(); 
	 psiIp.equals(psiI); 
	  for(int ii = 1; ii<=S; ii++)
	 {
		psiIp.add_psi(eps[ii-1]);
		
	 }
	 psiIp.normalize(); 
	if(x%1000==0){cout << "\n" <<  psiI.get_totEn(H,V); }
	for(int ii =1; ii<=S; ii++)
	{
		double delEn=0; 
		for(int i=1; i<=size; i++)
		{
			for(int j=1; j<=size; j++)
			{
			   for(int k=1; k<=size; k++)
			   {
				double R = sqrt((i-15.15)*(i-15.15)*del*del + (j-15.5)*(j-15.5)*del*del + (k-15.5)*(k-15.5)*del*del); 
				delEn = delEn + eps[ii-1].get_local_ovlpEn(H,-1.0/R,psiIp,i,j,k); 
				delEn = delEn - eps[ii-1].get_localEn(H,-1.0/R,i,j,k); 
				delEn = delEn + psiIp.get_local_ovlpEn(H,-1.0/R,eps[ii-1],i,j,k); 
			   }
			}
		}
		
		
		
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
	ss << psiI.get_psiR(x,15,15); string holder; ss >> holder; 
	outline1 = outline1 + "\t" + holder; 
	outfile1.add_line(outline1); ss.clear(); ss.str(""); 
	ss << psiI.get_psiI(x,15,15);  ss >> holder; 
	outline2 = outline2 + "\t" + holder; 
	outfile2.add_line(outline2); 
	 
}
outfile1.make_file("PsiR.dat"); 
outfile2.make_file("PsiI.dat"); 
 



return 0; 
}
