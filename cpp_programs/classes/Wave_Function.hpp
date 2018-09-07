#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std; 

class psi
{
	public: 
	psi(); 
	psi(int i, int j, int k, double D); 
	~psi(); 
	//mainpulator functions
	void  set_psi(int i, int j , int k, double Rs, double Is); // set the wave function value
        void normalize(); 
	

	//access functions
        double get_psiR(int i, int j, int k);//get the value of the wave function
	double get_psiI(int i ,int j , int k); 
        double dL_R(int i, int j, int k,int axis); // get the real part of the local gradient along specified axis
        double dL_I(int i, int j, int k,int axis); // get imaginary part of the local gradient along specified axis
        double get_totEn(double H, double V); 

	private:
	vector<double> R; 
	vector<double> I; 
	int xs,ys,zs; 
	double del; 

};

//default constructor
psi::psi()
{
R.push_back(0); I.push_back(0); 
xs = 1; ys =1; zs =1; del = 1; 
}

//basic constructor
psi::psi(int x, int y, int z, double D)
{
	del = D; xs =x; ys=y; zs=z; 
	for(int ii=1; ii<=x*y*z; ii++)
	{
		R.push_back(0); I.push_back(0); 
	}
}

//set wave function value
void psi:: set_psi(int i, int j, int k, double Rs, double Is)
{
	int index = (j-1)*xs + (k-1)*xs*ys + i -1;
	R[index] = Rs; 
	I[index] = Is; 
}
//normalize the wave function
void psi::normalize()
{
	double delx , dely, delz; 
	delx = del; dely=del; delz = del; 
	if(xs==1){delx=1;}if(ys==1){dely=1;}if(zs==1){delz=1;}
	double sum =0; 
	for(int i=1; i<=xs; i++)
	{
		for(int j=1; j<=ys; j++)
		{
			for(int k=1; k<=zs; k++)
			{
				int index = (j-1)*xs + (k-1)*xs*ys + i -1;
				sum = sum +(R[index]*R[index] + I[index]*I[index])*delx*dely*delz;
				
			}
		}
	}
	
	for(int i=1; i<=xs; i++)
	{
		for(int j=1; j<=ys; j++)
		{
			for(int k=1; k<=zs; k++)
			{
				int index = (j-1)*xs + (k-1)*xs*ys + i -1;
				R[index]=R[index]/sum; I[index]=I[index]/sum;  
			}
		}
	}
}

//get Real part of wave function value
double psi::get_psiR(int i, int j, int k)
{
	int index = (j-1)*xs + (k-1)*xs*ys + i -1;
	return R[index];	
}
//get Imaginary part of wave function value
double psi::get_psiI(int i, int j, int k)
{
        int index = (j-1)*xs + (k-1)*xs*ys + i -1;
	return R[index];
}
//get the real part Local gradient using central approximation 
double psi::dL_R(int i, int j, int k, int axis)
{
	
	double f,fp,fm; f=0; fp=0; fm=0;
	if(axis == 1)
	{
		if(xs>1)
		{
		int xp = i+1; if(xp>xs){xp =0;}  
		int xm = i-1; if(xm==0){xm =0;}
		f=R[(j-1)*xs + (k-1)*xs*ys + i -1];
		if(xp!=0){fp = R[(j-1)*xs + (k-1)*xs*ys + i];} 
		if(xm!=0){fm = R[(j-1)*xs + (k-1)*xs*ys + i -2];}
		}
		
	}
	if(axis == 2)
	{
		if(ys>1)
		{
		int yp = j+1; if(yp>ys){yp =0;}
		int ym = j-1; if(ym==0){ym =0;}
		f=R[(j-1)*xs + (k-1)*xs*ys + i -1];
		if(yp!=0){fp = R[(j)*xs + (k-1)*xs*ys + i-1];}
		if(ym!=0){fm = R[(j-2)*xs + (k-1)*xs*ys + i -1];}
		}
		
	}
	if(axis == 3)
	{
		if(zs>1)
		{
		int zp = k+1; if(zp>zs){zp =0;}
		int zm = k-1; if(zm==0){zm =0;}
		f=R[(j-1)*xs + (k-1)*xs*ys + i -1];
		if(zp!=0){fp = R[(j-1)*xs + (k)*xs*ys + i-1];}
		if(zm!=0){fm = R[(j-1)*xs + (k-2)*xs*ys + i -1];}
		}
		
	}
	
	return (fp - 2*f + fm)/(del*del); 
}

//get the imaginary part Local gradient using central approximation 
double psi::dL_I(int i, int j, int k, int axis)
{
	
	double f,fp,fm; f=0; fp=0; fm=0;
	if(axis == 1)
	{
		if(xs>1)
		{
		int xp = i+1; if(xp>xs){xp =0;}
		int xm = i-1; if(xm==0){xm =0;}
		f=R[(j-1)*xs + (k-1)*xs*ys + i -1];  
		if(xp!=0){fp = I[(j-1)*xs + (k-1)*xs*ys + i];}
		if(xm!=0){fm = I[(j-1)*xs + (k-1)*xs*ys + i -2];}
		}
		
	}
	if(axis == 2)
	{
		if(ys>1)
		{
		int yp = j+1; if(yp>ys){yp =0;}
		int ym = j-1; if(ym==0){ym =0;}
		f=R[(j-1)*xs + (k-1)*xs*ys + i -1]; 
		if(yp!=0){fp = I[(j)*xs + (k-1)*xs*ys + i-1];}
		if(ym!=0){fm = I[(j-2)*xs + (k-1)*xs*ys + i -1];}
		}
		
	}
	if(axis == 3)
	{
		if(zs>1)
		{
		int zp = k+1; if(zp>zs){zp =0;}
		int zm = k-1; if(zm==0){zm =0;}
		f=R[(j-1)*xs + (k-1)*xs*ys + i -1]; 
		if(zp!=0){fp = I[(j-1)*xs + (k)*xs*ys + i-1];}
		if(zm!=0){fm = I[(j-1)*xs + (k-2)*xs*ys + i -1];}
		}
		
		
	}
	return (fp - 2*f + fm)/(del*del); 
}

double psi::get_totEn(double H, double V)
{
	double delx,dely,delz; delx=del; dely=del;delz=del; 
	if(xs==1){delx=1;}if(ys==1){dely=1;}if(zs==1){delz=1;}
	double toten=0; 
	for(int i=1; i<=xs; i++)
	{
		for(int j=1; j<=ys; j++)
		{
			for(int k=1; k<=zs; k++)
			{
				int index = (j-1)*xs + (k-1)*xs*ys + i -1;
				double Ken=0; double Ven=0; 
				Ven = V*(R[index]*R[index]+I[index]*I[index]); 
				Ken = Ken + H*R[index]*(  dL_R(i,j,k,1)+dL_R(i,j,k,2)+dL_R(i,j,k,3)  ); 
				Ken = Ken + H*I[index]*(dL_I(i,j,k,1)+dL_I(i,j,k,2)+dL_I(i,j,k,3)); 
				toten =toten+ (-Ken + Ven)*delx*dely*delz; 
				//cout << "\n" << dL_R(i,j,k,1)<<"\t" << dL_R(i,j,k,2)<<"\t" << dL_R(i,j,k,3);
			}
		}
	}
	return toten; 
}



psi::~psi(){}

