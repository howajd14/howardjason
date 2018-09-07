#include "histogram.hpp"
using namespace std; 

class ising2d 
{
    public:
	ising2d(); 
	ising2d(int n); 
        ~ising2d();
        void set_s(int val, int x, int y)
	{
		int index = (x-1)*a_s + y; 
		a_rep[index-1]=val; 
	}
	int get_s(int x, int y)
	{
	        int index = (x-1)*a_s + y; 
		return a_rep[index-1]; 	
	}
	double get_en(double J)
	{
		double E =0; 
		for(int ii=1; ii<=a_s; ii++)
		{
			for(int jj=1; jj<=a_s; jj++)
			{
				int im = ii-1; 
				if(im == 0){im = a_s; }
				int ip = ii+1; 
				if(ip > a_s){ip = 1;}
				int jm = jj -1; 
				if(jm==0){jm=a_s;}
				int jp = jj+1; 
				if(jp > a_s){jp=1;}
				E = E - J*(get_s(im,jj)*get_s(ii,jj)*1.0); 
				E = E - J*(get_s(ii,jj)*get_s(ip,jj)*1.0); 
				E = E - J*(get_s(ii,jm)*get_s(ii,jj)*1.0); 
				E = E - J*(get_s(ii,jj)*get_s(ii,jp)*1.0); 
			}
		}
             return E; 
	}
    private:
	vector<int> a_rep; 
	int  a_s; 
};

ising2d::ising2d()
{
a_rep.push_back(0); 
a_s=1; 
}

ising2d::ising2d(int n)
{
	for(int x=1; x<=n; x++)
	{
		for(int y=1; y<=n; y++)
		{
			a_rep.push_back(0); 
		}
	}
	a_s = n; 
}
ising2d::~ising2d()
{}
