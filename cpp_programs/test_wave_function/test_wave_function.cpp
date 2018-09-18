#include "../classes/Wave_Function.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
using namespace std; 

int main()
{
int size = 1000; 
double H=1; double V=0; 
double pt = 0.001; 
psi  psiI(size,1,1,1); 
int its = 1; 
srand(time(NULL)); 
double T = 1e-8; 
double A =sqrt(2.0/size); 
//double a =0.6; double b=.5; 
double pi = 3.14159; 
//vector<double> Ap; vector<double> Bp; 
//vector<double> ap; vector<double>bp;

for(int x=1; x<=size; x++)
{
	if(x==1){psiI.set_psi(x,1,1,0,0);}
	if(x==size){psiI.set_psi(x,1,1,0,0);}
	if(x!=1&&x!=size){psiI.set_psi(x,1,1,A*sin(pi*(x-1)/((size-1)*1.0)),0); }
}
cout << "\n\n" << psiI.get_totEn(H,V); 
for(int x=1; x<=10000; x++)
{
psiI.normalize();
}
cout << "\n\n" << psiI.get_totEn(H,V) << "\n\n";
for(int x=1; x<=its; x++)
{
	
	double Ap = A +  pt*((rand()%9+8)-12);
	psi  psiIp(size,1,1,1); for(int ii=2; ii<=size-1; ii++){psiIp.set_psi(ii,1,1,Ap*sin(pi*(ii-1)/((size-1)*1.0)),0);}
	psiIp.normalize();
	double EI = psiI.get_totEn(H,V); double EIp = psiIp.get_totEn(H,V); 
	if(x%1000==0){cout << "\n" << EI<<"\t" << A  ;}
	double p = (rand()%RAND_MAX +1)/(1.0*RAND_MAX); 
	if (p < exp(-(EIp-EI)/T)  )
	{
		//if(x%1000==0){cout << "\n" << exp(-(EIp-EI)/T) << "\t" << EIp << "\t" << EI << "\t" << EIp - EI; }
		A = Ap; 
		for(int xi=2; xi<=size-1; xi++)
		{
			psiI.set_psi(xi,1,1,Ap*sin(pi*(xi-1)/((size-1)*1.0)),0); 
		}
		
	}
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

cout << "\n\n" << psiI.get_totEn(H,V) << "\n\n" ;
return 0; 
}
