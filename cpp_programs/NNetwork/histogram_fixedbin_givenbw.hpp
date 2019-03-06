#include <algorithm>
#include <math.h>
using namespace std; 
class hist
{
	public: 
		hist();
		hist(const vector<double> & ens, const vector<double> & cnts,const vector<double> & bwidths);
		hist(const hist  & H1,  const hist & H2);
		~hist(); 
		void make_file(string filename)
		{
			file outfile; 
			for(unsigned int x=1; x<=cents.size()+1; x++)
			{
				if(x<=cents.size()){
				stringstream ss; string outline; string holder; 
				ss << cents[x-1]; ss >> outline; ss.clear(); ss.str(""); 
				ss << GE[x-1]; ss >> holder; outline = outline + "\t" + holder; 
				outfile.add_line(outline);}else{
				 stringstream ss; string outline; string holder;
                                ss << cents[cents.size()-1]+bw; ss >> outline; ss.clear(); ss.str("");
                                ss << GE[x-1]; ss >> holder; outline = outline + "\t" + holder;
                                outfile.add_line(outline);
				}	
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
			for(unsigned int x=1; x<=cents.size()+1; x++)
			{
				if(x<=cents.size()){
				stringstream ss; string outline; string holder; 
				ss << cents[x-1]/(val*1.0); ss >> outline; ss.clear(); ss.str(""); 
				ss << GE[x-1]; ss >> holder; outline = outline + "\t" + holder; 
				outfile.add_line(outline);}else{
				       stringstream ss; string outline; string holder;
                                ss << (cents[x-1]+bw)/(val*1.0); ss >> outline; ss.clear(); ss.str("");
                                ss << GE[x-1]; ss >> holder; outline = outline + "\t" + holder;
                                outfile.add_line(outline);}	
			}
			outfile.make_file(filename); 
			}
		
		}
		
		void combine(const hist & H); 
		void set_count(int x,double val){GE[x-1]=val;}
		unsigned int num_bins() const {return GE.size();}
		unsigned int get_bin(double en) const 
		{
		 	unsigned int bin=0; 
			for(unsigned int x=1; x<=cents.size(); x++)
			{
			   double lwr = cents[x-1]-bw/2.0; 
		           double uppr= cents[x-1]+bw/2.0; 	   
			if(en>=lwr&&en<uppr){bin=x;}
			}
			if(bin==0){bin=cents.size()+1;}
			return bin; 
		}
		double   get_en(int x) const { double eng=0; 
			if(x<=cents.size()){eng= cents[x-1];}
			if(x>cents.size()){eng= cents[x-1]+bw*2.0;}
			return eng; 
			}
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
        vector<double> bw; 	
	


};

hist :: hist()
{
GE.push_back(0);
cents.push_back(0); 
}


hist::hist(const vector<double> & ens, const vector<double> & cnts,const vector<double> & bwidths)
{
	bw = bwidths;
	cents = cnts;
	for(unsigned int x=1; x<=cnts.size()+1; x++){GE.push_back(0);}
	for(unsigned int x=1; x<= ens.size(); x++)
        {
		int fb =0; 
		int count =1; 
		while(fb==0&&count <= cnts.size())
		{
			double lwr = cnts[count-1]-bw[count-1]/2.0; 
			double upr = cnts[count-1]+bw[count-1]/2.0; 
			if(ens[x-1]>=lwr && ens[x-1]<upr)
			{
				fb=1; GE[count-1]=GE[count-1]+1; 
			}
			count++;
		}
		if(fb==0){GE[cnts.size()]=GE[cnts.size()]+1;}
	}	
	
		
}


hist::hist(const hist  & H1,  const hist & H2, const vector<double> & bwidths)
{
	for(int x=1; x<=(H1.num_bins()-1); x++)
	{
		cents.push_back(H1.get_en(x));
	}
	bw = bwidths;
	for(int x=1; x<=H1.num_bins(); x++)
	{
		GE.push_back(H1.get_count(x)+H2.get_count(x)); 
	}
	
}

void hist::combine(const hist & H)
{
	
	for(unsigned int x=1; x<=GE.size(); x++)
	{
		//if(x==GE.size()){
		//cout << "\n" << GE[x-1] << "\t" << H.get_count(x); }
		GE[x-1]=GE[x-1]+H.get_count(x); 
	}
	
}

hist::~hist()
{}
