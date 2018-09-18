#include "../../classes/Wave_Function.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std; 

int main()
{
int size = 20; 
double H=1.0/2.0; double V=0; 
double pt = 0.01;
double hx,hy,hz; hx=10.2;hy=10.2; hz=10.2;
double del = 3; 
int S = 1;  
psi  psiI(size,size,size,del); 
psi zeropsi(size,size,size,del); 
vector<psi>  eps; for(int x=1; x<=S; x++){eps.push_back(psiI);}
int its = 1e5; 
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
	
	vector<psi> localeps; for(int oo=1; oo<=S ; oo++){localeps.push_back(zeropsi);}
          for(int ii = 1; ii<=S; ii++)
	 {
		
		
		for(int lll=1; lll<=20; lll++)
		{
		int  pl1 = rand()%(40) + 1; 
		double amp = 1.0*(rand()%20+1); 
		double pm = 1.0*((rand()%2+1)*2 -3 ); 
		for(int i=1; i<=size; i++)
		{
			for(int j=1; j<=size; j++)
			{
				for(int k=1; k<=size; k++)
				{
				if(((i!=1&&i!=size)&&(j!=1&&j!=size))&&(k!=1&&k!=size))
				{
				        double val =0; 
					
					val = val+ amp*pm*sin(pl1*pi*(i-1)/(size-1))*sin(pl1*pi*(j-1)/(size-1))*sin(pl1*pi*(k-1)/(size-1));
					
					localeps[ii-1].set_psi(i,j,k,val,0); 
				}
				}
			}
		}
		}
		localeps[ii-1].normalize(pt); 
		
		
	 }
	// psiI.normalize(); 
	 psiIp.equals(psiI); 
	  for(int ii = 1; ii<=S; ii++)
	 {
		psiIp.add_psi(eps[ii-1]);
		psiIp.add_psi(localeps[ii-1]); 
		
	 }
	psiIp.normalize(); 

	
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
			eps[ii-1].add_psi(localeps[ii-1]); 
			psiI.add_psi(eps[ii-1]);
				
		}
		
		
	}
	//psiI.smooth();
	if(x%40==0){cout << "\n" << toten ; } 
	psiI.normalize();
	//psiI.smooth();


}

file outfile1; string outline1,outline2;
file outfile2;  
for(int x=1; x<=size; x++)
{
	stringstream ss; ss.width(10);ss.precision(10); 
	ss << x; ss >> outline1; outline2 = outline1; ss.clear(); ss.str(""); 
	ss << psiI.get_psiR(10,x,10); string holder; ss >> holder; 
	outline1 = outline1 + "\t" + holder; 
	outfile1.add_line(outline1); ss.clear(); ss.str(""); 
	ss << psiI.get_psiI(x,10,10);  ss >> holder; 
	outline2 = outline2 + "\t" + holder; 
	outfile2.add_line(outline2); 
	 
}
outfile1.make_file("PsiR.dat"); 
outfile2.make_file("PsiI.dat"); 
 



return 0; 
}
