#include <algorithm>
#include <math.h>
using namespace std; 
class hist
{
	public: 
		hist();
		hist(const vector<double> & ens);
		hist(const hist  & H1,  const hist & H2);
		~hist(); 
		void make_file(string filename)
		{
			file outfile; 
			for(unsigned int x=1; x<=cents.size(); x++)
			{
				stringstream ss; string outline; string holder; 
				ss << cents[x-1]; ss >> outline; ss.clear(); ss.str(""); 
				ss << GE[x-1]; ss >> holder; outline = outline + "\t" + holder; 
				outfile.add_line(outline);  
			}
			outfile.make_file(filename); 
		}
		void make_file(string filename, int val)
		{
			if(val ==0)
			{
			file outfile; 
			for(unsigned int x=1; x<=cents.size(); x++)
			{
				stringstream ss; string outline; string holder; 
				ss << x; ss >> outline; ss.clear(); ss.str(""); 
				ss << GE[x-1]; ss >> holder; outline = outline + "\t" + holder; 
				outfile.add_line(outline);  
			}
			outfile.make_file(filename); 
			}
		
		}
		void make_file(string filename, double val)
		{
			if(val >0)
			{
			file outfile; 
			for(unsigned int x=1; x<=cents.size(); x++)
			{
				stringstream ss; string outline; string holder; 
				ss << cents[x-1]/(val*1.0); ss >> outline; ss.clear(); ss.str(""); 
				ss << GE[x-1]; ss >> holder; outline = outline + "\t" + holder; 
				outfile.add_line(outline);  
			}
			outfile.make_file(filename); 
			}
		
		}
		
		void combine(const hist & H); 
		void set_count(int x,double val){GE[x-1]=val;}
		unsigned int num_bins() const {return cents.size();}
		unsigned int get_bin(double en) const 
		{
		 	unsigned int bin=0; 
			for(unsigned int x=1; x<=cents.size(); x++)
			{ 
			if((cents[x-1]-en)*(cents[x-1]-en)<1e-20){bin=x;}
			}
			return bin; 
		}
		double   get_en(int x) const {return cents[x-1];}
		double   get_count(int x) const {return GE[x-1];}
		double   get_sum() const 
		{ 
			double sum =0 ; 
			for(unsigned int x=1; x<=GE.size(); x++){sum=sum+GE[x-1];}
			return sum; 
		}
		
		 


	private:
	vector<double> GE; 
	vector<double> cents; 
	


};

hist :: hist()
{
GE.push_back(0);
cents.push_back(0); 
}


hist::hist(const vector<double> & ens)
{
	cents.push_back(ens[0]);
	double en = ens[0];
	GE.push_back(0); 
	for(unsigned int x = 2; x <= ens.size(); x++)
	{
		
		if((ens[x-1]- en)*(ens[x-1]- en)>1e-20){cents.push_back(ens[x-1]);  en = ens[x-1];  GE.push_back(0); }
	}
	for(unsigned int x=1; x<=cents.size(); x++)
	{
		for(unsigned int y=1; y<=ens.size(); y++)
		{
			if((ens[y-1]-cents[x-1])*(ens[y-1]-cents[x-1])<1e-20){GE[x-1] = GE[x-1]+1; }
		}
	}
		
}


hist::hist(const hist  & H1,  const hist & H2)
{
	vector<double> centso; 
         for(unsigned int x=1; x<= H1.num_bins(); x++)
	 {
		centso.push_back(H1.get_en(x)); 
	 }
	for(unsigned int  x=1; x<= H2.num_bins(); x++)
	{
		centso.push_back(H2.get_en(x)); 
	}
	sort(centso.begin(),centso.end()); 
	cents.push_back(centso[0]);
	double en = centso[0];
	GE.push_back(0); 
	for(unsigned int x = 2; x <= centso.size(); x++)
	{
		if((centso[x-1]-en)*(centso[x-1]-en)>1e-20){cents.push_back(centso[x-1]); en = centso[x-1];  GE.push_back(0);}
	}
	for(unsigned int x =1; x<= cents.size(); x++)
	{
		for(unsigned int y=1; y<= H1.num_bins(); y++)
		{
			if((H1.get_en(y)-cents[x-1])*(H1.get_en(y)-cents[x-1])<1e-20){GE[x-1]=GE[x-1]+H1.get_count(y);}
		}
		for(unsigned int y=1; y<=H2.num_bins(); y++)
		{
			if((H2.get_en(y)-cents[x-1])*(H2.get_en(y)-cents[x-1]) <1e-20){GE[x-1]=GE[x-1]+H2.get_count(y);}
		}
	}
	
}

void hist::combine(const hist & H)
{
	
	vector<double> centsp; 
	for(unsigned int x=1; x<=cents.size(); x++){centsp.push_back(cents[x-1]);}
	for(unsigned int x=1; x<=H.num_bins(); x++){centsp.push_back(H.get_en(x));}
	sort(centsp.begin(),centsp.end()); 
	vector<double> centsnew; centsnew.push_back(centsp[0]); 
	double en = centsp[0];
	vector<double> GEnew; GEnew.push_back(0);  
	
	for(unsigned int x = 2; x <= centsp.size(); x++)
	{
		if(((centsp[x-1]-en)*(centsp[x-1]-en))>1e-20){centsnew.push_back(centsp[x-1]); en = centsp[x-1];  GEnew.push_back(0);}
	}
        
	for(unsigned int x =1; x<= centsnew.size(); x++)
	{
		for(unsigned int y=1; y<= GE.size(); y++)
		{
			if((cents[y-1]-centsnew[x-1])*(cents[y-1]-centsnew[x-1])<1e-20){GEnew[x-1]=GEnew[x-1]+GE[y-1];}
		}
		
		for(unsigned int y=1; y<=H.num_bins(); y++)
		{
			if((H.get_en(y)-centsnew[x-1])*(H.get_en(y)-centsnew[x-1])<1e-20){GEnew[x-1]=GEnew[x-1]+H.get_count(y);}
		}
		
	}
	
	unsigned int sz = cents.size(); 
	for(unsigned int x=1; x<=sz; x++){ GE.pop_back(); cents.pop_back(); }
	
	for(unsigned int x=1; x<=centsnew.size(); x++)
	{
		GE.push_back(GEnew[x-1]); cents.push_back(centsnew[x-1]); 
	}
	
	
}

hist::~hist()
{}
