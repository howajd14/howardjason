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
double hx,hy,hz; hx=15.2;hy=15.2; hz=15.2;
double del = 1; 
int S = 1;  
psi  psiI(size,size,size,del); 
psi zeropsi(size,size,size,del); 
vector<psi>  eps; for(int x=1; x<=S; x++){eps.push_back(psiI);}
int its = 4e6; 
srand(time(NULL)); 
double T = 1e-11; 
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
psi psiIp(size,size,size,del);psiIp.equals(psiI);
//psi monitor(size,size,size,0.25); monitor.equals(psiI); 
psiI.normalize();

for(int x=1; x<=its; x++)
{
	
	
          for(int ii = 1; ii<=S; ii++)
	 {
		eps[ii-1].equals(zeropsi);
		int pl = (rand()%(size-4)+3); 
		int pl2 = (rand()%(size-4)+3); 
		int pl3 = (rand()%(size-4)+3); 
		double mag= 1.0*(rand()%100+1); 
		eps[ii-1].set_psi(pl,pl2,pl3,mag*pt,0); 
		eps[ii-1].set_psi(pl-1,pl2,pl3,mag*pt/2,0);
		eps[ii-1].set_psi(pl+1,pl2,pl3,mag*pt/2,0);
		eps[ii-1].set_psi(pl,pl2-1,pl3,mag*pt/2,0);
		eps[ii-1].set_psi(pl,pl2+1,pl3,mag*pt/2,0);
		eps[ii-1].set_psi(pl,pl2,pl3-1,mag*pt/2,0);
		eps[ii-1].set_psi(pl,pl2,pl3+2,mag*pt/2,0);
		
		
		
	 }
	// psiI.normalize(); 
	 psiIp.equals(psiI); 
	  for(int ii = 1; ii<=S; ii++)
	 {
		psiIp.add_psi(eps[ii-1]);
		
	 }
	psiIp.normalize(); 

	int tf=0; 
	double toten  = 0; double delEn=0; 
	for(int ii =1; ii<=S; ii++)
	{
		 delEn=0; 
		for(int i=1; i<=size; i++)
		{
			for(int j=1; j<=size; j++)
			{
			   for(int k=1; k<=size; k++)
			   {
				double R = sqrt(( (i-hx)*(i-hx) + (j-hy)*(j-hy) + (k-hz)*(k-hz))*del*del ); 
				//cout << "\n" << i << "\t" << j << "\t" << k << "\t" <<-1.0/R; 
				double E2 = psiI.get_localEn(H,-1.0/R,i,j,k);
				//IPe = IPe + psiIp.get_localEn(H,-1.0/R,i,j,k);
				delEn = delEn + psiIp.get_localEn(H,-1.0/R,i,j,k) - E2; 
				toten = toten + E2; 
			   }
			}
		}
		
		
		
		double p = (rand()%RAND_MAX +1)/(1.0*RAND_MAX);
		//if(x%10==0&&ii==1){cout << "\n" << exp(-delEn/T) << "\t" << delEn; }
		if(p < exp(-delEn/T))
		{
			
			psiI.add_psi(eps[ii-1]);
		tf=1; 
				
		}
		
		
	}
	//psiI.smooth();
	if(x%40==0){cout << "\n" << toten ; } 
	if(tf==1){psiI.normalize();}
	//psiI.smooth();


}

file outfile1; string outline1,outline2;
file outfile2;  
for(int x=1; x<=size; x++)
{
	stringstream ss; ss.width(10);ss.precision(10); 
	ss << x; ss >> outline1; outline2 = outline1; ss.clear(); ss.str(""); 
	ss << psiI.get_psiR(15,x,15); string holder; ss >> holder; 
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
