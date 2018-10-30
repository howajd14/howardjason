#include "file.hpp"
#include "histogram_fixedbin.hpp"
using namespace std; 

class dataset
{
	public:
	dataset(); 
	dataset(int ns, int insz, int osz);
	dataset(string datafile, int nsets, int insz, int osz); 
        ~dataset();  
	void  set_ind(int sn, int dn, double val)
	{int index= (sn-1)*szin + dn; indata[index-1]=val;}
	void  set_od(int sn, int  dn, double val)
	{int index= (sn-1)*szo + dn; outdata[index-1]=val;}
	double get_ind(int sn, int dn) const
	{int index = (sn-1)*szin + dn; return indata[index-1];}
	double get_od(int sn, int dn) const 
	{int index = (sn-1)*szo + dn; return outdata[index-1];}
        int  get_nsets()const {return nsets; }
	int  get_szin()const {return  szin;}
	int  get_szo()const {return  szo;}	

	private:
	vector<double> indata; 
	vector<double> outdata;
	int  nsets; 
	int  szin; 
	int  szo; 
 

};
//default  constructor
dataset::dataset()
{
indata.push_back(0); outdata.push_back(0); 
nsets=1; szin =1; szo =1; 
}
//basic constructor
dataset::dataset(int ns,int insz, int osz) 
{
 nsets = ns;  szin = insz;  szo = osz; 
for(int x=1; x<= ns*insz; x++)
{
	indata.push_back(0); 
}
for(int x=1; x<=ns*szo; x++)
{
	outdata.push_back(0); 
}
}

//Construct from file
//basic constructor
dataset::dataset(string datafile, int ns,int insz, int osz)
{
//cout << "\ngot here\n"; 
        nsets = ns;  szin = insz;  szo = osz;
        file data_set; int count =1;
	ifstream my_file(datafile.c_str()); string hhll; while(getline(my_file,hhll)){data_set.add_line(hhll);}
	my_file.close(); 
	//cout << "\ngot here\n";
	for(int x=1; x<=data_set.num_lines(); x++)
	{
		
		stringstream gobolygook; gobolygook << count; 
		string linehold; gobolygook >> linehold; 
		string dsn = "ds" + linehold;
		gobolygook.clear(); gobolygook.str(""); 
		gobolygook << data_set.get_line(x); string llhld; gobolygook >> llhld; 
		gobolygook.clear(); gobolygook.str("");  
		if(llhld==dsn)
		{
		//	cout << "\ngot here\n";
  			gobolygook.clear(); gobolygook.str(""); 
			gobolygook  << data_set.get_line(x); 
			string burner; gobolygook >> burner; 
			for(int jk=1; jk<=osz; jk++)
			{
			// cout << "\ngot here\n" << jk;
			 double holdie; gobolygook >> holdie; outdata.push_back(holdie); 
			} 
			gobolygook.clear(); gobolygook.str(""); 
			for(int jk=1; jk<=insz; jk++)
			{
		//	cout << "\ngot here    " << count << "\t";
				gobolygook << data_set.get_line(x+jk); 
				double holdie; gobolygook >> holdie; 
				indata.push_back(holdie); 
				gobolygook.clear(); gobolygook.str(""); 
			}
		
		count++;
		}
	}



}
dataset::~dataset()
{}
