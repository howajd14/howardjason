#include "file.hpp"
#include <math.h>
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
	void normalize(double eps); 
	void  add_psi(const psi & Psi);
	void  minus_psi(const psi & Psi);
	void smooth(); 
	void equals(const psi & Psi){for (int x=1; x<=sz; x++){R[x-1] = Psi.get_psiR_byindex(x); I[x-1] = Psi.get_psiI_byindex(x);}}
	

	//access functions
        double get_psiR(int i, int j, int k) const;//get the value of the wave function
	double get_psiI(int i ,int j , int k) const; 
	double get_psiR_byindex(int i) const {return R[i-1];}
	double get_psiI_byindex(int i) const  {return I[i-1];}
        double dL_R(int i, int j, int k,int axis); // get the real part of the local gradient along specified axis
        double dL_I(int i, int j, int k,int axis); // get imaginary part of the local gradient along specified axis
        double get_totEn(double H, double V); 
	double get_localEn(double H, double V,int i, int j, int k); 
	double get_local_ovlpEn(double H, double V, const psi & Psi, int i, int j, int k); 
	double get_ovlpEn(double H, double V, const psi & Psi);
	double get_normF(); 

	private:
	vector<double> R; 
	vector<double> I; 
	int xs,ys,zs; 
	int sz; 
	double del; 

};

//default constructor
psi::psi()
{
R.push_back(0); I.push_back(0); 
xs = 1; ys =1; zs =1; del = 1; sz=1; 
}

//basic constructor
psi::psi(int x, int y, int z, double D)
{
	del = D; xs =x; ys=y; zs=z; sz=x*y*z; 
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
// add another wave function to this wave function
void psi::add_psi(const psi & Psi)
{
		for(int i = 1; i<=xs; i++)
		{
			for(int j=1; j<=ys; j++)
			{
				for(int k=1; k<=zs; k++)
				{
					int index =(j-1)*xs + (k-1)*xs*ys + i -1;
					R[index] = R[index] + Psi.get_psiR(i,j,k); 
					I[index] = I[index] + Psi.get_psiI(i,j,k); 
				}
			}
		}
}
// substract another wave function from this wavefunction
void psi::minus_psi(const psi & Psi)
{
		for(int i = 1; i<=xs; i++)
		{
			for(int j=1; j<=ys; j++)
			{
				for(int k=1; k<=zs; k++)
				{
					int index =(j-1)*xs + (k-1)*xs*ys + i -1;
					R[index] = R[index] - Psi.get_psiR(i,j,k); 
					I[index] = I[index] - Psi.get_psiI(i,j,k); 
				}
			}
		}
}
// smooth the wavefunction
void psi::smooth()
{
	vector<double> copyR; vector<double> copyI; 
	for(int i =1; i<=xs; i++)
	{
		for(int j=1; j<=ys; j++)
		{
			for(int k=1; k<=zs; k++)
			{
				int index =(j-1)*xs + (k-1)*xs*ys + i -1;
				double xmR=0; double xpR=0; 
				double ymR=0; double ypR=0; 
				double zmR=0; double zpR=0; 
				double xmI=0; double xpI=0; 
				double ymI=0; double ypI=0; 
				double zmI=0; double zpI=0; 
				if(i!=xs&&i!=1)
				{
				xpR = R[(j-1)*xs + (k-1)*xs*ys + i ]; xpI=I[(j-1)*xs + (k-1)*xs*ys + i ];
				xmR  = R[(j-1)*xs + (k-1)*xs*ys + i -2];xmI=I[(j-1)*xs + (k-1)*xs*ys + i -2];
				}

				if(j!=ys&&j!=1)
				{
				ypR = R[(j)*xs + (k-1)*xs*ys + i -1]; ypI= I[(j)*xs + (k-1)*xs*ys + i -1];
				ymR = R[(j-2)*xs + (k-1)*xs*ys + i -1]; ymI = I[(j-2)*xs + (k-1)*xs*ys + i -1];
				}
				if(k!=zs&&k!=1)
				{
				zpR = R[(j-1)*xs + (k)*xs*ys + i -1]; zpI = I[(j-1)*xs + (k)*xs*ys + i -1];
				zmR = R[(j-1)*xs + (k-2)*xs*ys + i -1];  zpI = I[(j-1)*xs + (k-2)*xs*ys + i -1];
				}
				double avg_factor = 1; 
				if(xs>1){avg_factor = avg_factor +2;}
				if(ys>1){avg_factor = avg_factor + 2;}
				if(zs>1){avg_factor = avg_factor +2;}
				copyR.push_back(( R[index] + xmR + xpR + ymR + ypR + zmR + zpR)/avg_factor); 
				copyI.push_back(( I[index] + xmI + xpI + ymI + ypI + zmI + zpI)/avg_factor); 
				//cout << "\n" <<  i<< "\t" << xmR << "\t" << xpR << "\t" << ymR << "\t" << ypR << "\t" << zmR << "\t" << zpR; 
								
			}
		}
	}
	for(int x=1; x<=xs*ys*zs; x++){R[x-1]=copyR[x-1]; I[x-1]=copyI[x-1]; }
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
				R[index]=R[index]/sqrt(sum); I[index]=I[index]/sqrt(sum);  
			}
		}
	}
}
//Normailize to a value other than 1
void psi::normalize(double eps)
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
				R[index]=sqrt(eps)*R[index]/sqrt(sum); I[index]=sqrt(eps)*I[index]/sqrt(sum);  
			}
		}
	}
}
// get the normalization factor
double psi::get_normF()
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
return sqrt(sum); 
}

//get Real part of wave function value
 double psi::get_psiR(int i, int j, int k) const
{
	int index = (j-1)*xs + (k-1)*xs*ys + i -1;
	return R[index];	
}
//get Imaginary part of wave function value
 double psi::get_psiI(int i, int j, int k) const
{
        int index = (j-1)*xs + (k-1)*xs*ys + i -1;
	return I[index];
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
		f=I[(j-1)*xs + (k-1)*xs*ys + i -1];  
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
		f=I[(j-1)*xs + (k-1)*xs*ys + i -1]; 
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
		f=I[(j-1)*xs + (k-1)*xs*ys + i -1]; 
		if(zp!=0){fp = I[(j-1)*xs + (k)*xs*ys + i-1];}
		if(zm!=0){fm = I[(j-1)*xs + (k-2)*xs*ys + i -1];}
		}
		
		
	}
	return (fp - 2*f + fm)/(del*del); 
}

//get the total energy using simple numerical techniques
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
				Ken = Ken + H*R[index]*(dL_R(i,j,k,1)+dL_R(i,j,k,2)+dL_R(i,j,k,3)); 
				Ken = Ken + H*I[index]*(dL_I(i,j,k,1)+dL_I(i,j,k,2)+dL_I(i,j,k,3)); 
				toten =toten+ (-Ken + Ven)*delx*dely*delz; 
				
			}
		}
	}
	return toten; 
}
// get the local energy
double psi::get_localEn(double H, double V,int i, int j, int k)
{
	double delx,dely,delz; delx=del; dely=del;delz=del; 
	if(xs==1){delx=1;}if(ys==1){dely=1;}if(zs==1){delz=1;}
	double toten=0; 

				int index = (j-1)*xs + (k-1)*xs*ys + i -1;
				double Ken=0; double Ven=0; 
				Ven = V*(R[index]*R[index]+I[index]*I[index]); 
				Ken = Ken + H*R[index]*(dL_R(i,j,k,1)+dL_R(i,j,k,2)+dL_R(i,j,k,3)); 
				Ken = Ken + H*I[index]*(dL_I(i,j,k,1)+dL_I(i,j,k,2)+dL_I(i,j,k,3)); 
				//cout << "\n" << Ven << "\t" << Ken << "\t" << i << "\t" << j << "\t" << k; 
				toten =toten+ (-Ken + Ven)*delx*dely*delz; 
				
		
	return toten; 
}

//get the overlap energy
double psi::get_ovlpEn(double H, double V, const psi & Psi)
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
				Ven = V*(R[index]*Psi.get_psiR(i,j,k)+I[index]*Psi.get_psiI(i,j,k)); 
				Ken = Ken + H*Psi.get_psiR(i,j,k)*(dL_R(i,j,k,1)+dL_R(i,j,k,2)+dL_R(i,j,k,3)); 
				Ken = Ken + H*Psi.get_psiI(i,j,k)*(dL_I(i,j,k,1)+dL_I(i,j,k,2)+dL_I(i,j,k,3)); 
				toten =toten+ (-Ken + Ven)*delx*dely*delz; 
			}
		}
	}	
	return toten; 
}

//get the local overlap energy
double psi::get_local_ovlpEn(double H, double V, const psi & Psi, int i, int j, int k)
{
	double delx,dely,delz; delx=del; dely=del;delz=del; 
	if(xs==1){delx=1;}if(ys==1){dely=1;}if(zs==1){delz=1;}
	double toten=0; 
	 
	
				int index = (j-1)*xs + (k-1)*xs*ys + i -1;
				double Ken=0; double Ven=0; 
				Ven = V*(R[index]*Psi.get_psiR(i,j,k)+I[index]*Psi.get_psiI(i,j,k)); 
				Ken = Ken + H*Psi.get_psiR(i,j,k)*(dL_R(i,j,k,1)+dL_R(i,j,k,2)+dL_R(i,j,k,3)); 
				Ken = Ken + H*Psi.get_psiI(i,j,k)*(dL_I(i,j,k,1)+dL_I(i,j,k,2)+dL_I(i,j,k,3)); 
				toten =toten+ (-Ken + Ven)*delx*dely*delz; 
				
	return toten; 
}



psi::~psi(){}

