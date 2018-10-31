#include "nueron.hpp"
using namespace std; 

class  NN
{
	public:
	NN();
	NN( int nlayers, int nneruons_lyer, int nout_nuerons, int ninputs);
	~NN(); 
	void set_hW(int lyr, int n, double val, int nindex)
	{int index = (lyr-1)*nnpl + n; hnuerons[index-1].set_W(nindex,val);}        
	void set_oW(int n, double val, int nindex)
	{onuerons[n-1].set_W(nindex,val);}
	 void make_NN(string filename);
	 void load_NN(string NNfilename); 
	double get_hW(int lyr, int n, int nindex) 
	{int index = (lyr-1)*nnpl + n; return hnuerons[index-1].get_W(nindex);}
        int   get_non() const {return non;}
	int   get_nnpl()const {return nnpl;}
	int  get_nhw(int wl){int index = 1 + (wl-1)*get_nnpl(); return hnuerons[index-1].get_nw();}
	int get_now(){return onuerons[0].get_nw();}
	int get_nlyer(){return nly; }
	unsigned int get_tnhn(){return hnuerons.size();}
	double get_oW(int n,int index) {return onuerons[n-1].get_W(index);}
	void get_O(vector<double> &  output, const dataset & D, int wds);
	private: 
	int nly; 
	int nnpl; 
	int non; 
        int nind;
        vector<nueron> hnuerons; 
        vector<nueron> onuerons;
	

};
//default constructor
NN::NN()
{
	nly=1; nnpl=1; non=1;nind=1; hnuerons.push_back(nueron(1)); 
	onuerons.push_back(nueron(1));  
}
//basic constructor
NN::NN(int nlayers, int nnuerons_lyer, int nout_nuerons, int nindata)
{
	for(int x=1; x<=nlayers; x++)
	{
		for(int y=1; y<=nnuerons_lyer; y++)
		{
		if(x==1)
		{
		hnuerons.push_back(nueron(nindata)); 
		}
		if(x>1)
		{
		hnuerons.push_back(nueron(nnuerons_lyer)); 
		//cout << "\n" << hnuerons[(x-1)*nnuerons_lyer + y -1].get_nw();
		}
		}
	}
	for(int x=1; x<=nout_nuerons; x++)
	{
		onuerons.push_back(nueron(nnuerons_lyer)); nind=nindata;
	}
	
	nly = nlayers; nnpl = nnuerons_lyer; non = nout_nuerons; 
}
//make a nueral network file
void NN::make_NN(string filename)
{
                file  NNtw;
                for(int x=1;x<= nly; x++)
                {
                        string line = "HL"; stringstream ss; ss << x; string hold; ss >> hold;
                        line = line  + hold;
                        NNtw.add_line(line);
                        for(int y=1; y<=get_nnpl(); y++)
                        {
                                line = "n" ;  ss.clear(); ss.str(""); ss << y;
                                ss >> hold; line = line + hold; ss.clear(); ss.str("");
                                for(int z=1; z<=get_nhw(x); z++)
                                {
                                        ss << get_hW(x,y,z); ss >> hold;
                                        line = line + "\t" + hold;
                                        ss.clear(); ss.str("");
                                }
                                NNtw.add_line(line);
                        }
                }
                string line = "OL"; NNtw.add_line(line);
                for(int x=1; x<=get_non(); x++)
                {
                        line = "n" ; string hold; stringstream ss;
                        ss << x; ss >> hold; line = line + hold;
                        ss.clear(); ss.str("");
                        for(int y=1; y<=get_now(); y++)
                        {
                                ss << get_oW(x,y); ss >> hold;
                                line = line + "\t" + hold;
                                ss.clear(); ss.str("");
                        }
                        NNtw.add_line(line);
                }
                NNtw.make_file(filename);
}
//load  NN from file
void NN::load_NN(string NNfilename)
{
	file  NNfile(NNfilename);
       	
	for(int x=1; x<=nly; x++)
	{
		stringstream ss; ss <<x; string hold; ss >> hold; 
		string line = "HL" + hold; 
		for(int y=1; y<=NNfile.num_lines(); y++)
		{
			if(NNfile.get_line(y)==line)
			{
				for(int z=1; z<=nnpl; z++)
				{
					ss.clear(); ss.str(""); 
					ss << NNfile.get_line(y+z);  
					string burner; ss >> burner; 
					for(int ko =1; ko<=get_nhw(x); ko++)
					{
						double holder; ss >> holder;
					        cout << "\n" << x << "\t" << z << "\t" << holder << "\t" << ko << "\t" << get_nhw(x); 	
						set_hW(x, z, holder, ko);
					}
				}
			}
		}
	}
	
	for(int y=1; y<=NNfile.num_lines(); y++)
        {
              if(NNfile.get_line(y)=="OL")
              {
                   for(int z=1; z<=non; z++)
                   {
                          stringstream ss; 
		          ss << NNfile.get_line(y+z); 
                          string burner; ss >> burner;
                          for(int ko =1; ko<=get_now(); ko++)
                          {
                               double holder; ss >> holder;
                               set_oW( z, holder, ko);
                          }
                   }
             }
       }
       

}	
// get the output from a data 
 void NN::get_O(vector<double> &  output, const dataset & D, int wds) 
{
	vector<double> Y; for(int x=1; x<=nnpl; x++){Y.push_back(0);}
	for(int x=1; x<=nly; x++)
	{
		if(x==1)
		{
		for(int y=1; y<=nnpl; y++)
		{
			double bias =0; 
			
				for(int z=1; z<=D.get_szin(); z++)
				{
		           	bias = bias + D.get_ind(wds,z)*get_hW(x,y,z); 		
				}
			
			Y[y-1]=tanh(bias); 
		}
		}
		if(x>1)
		{
			vector<double> newY; 
	         for(int y=1; y<=nnpl; y++)
	          {
                                double bias =0;
                        	for(int z=1; z<=nnpl; z++)
                        	{
                           	bias = bias + Y[z-1]*get_hW(x,y,z);
                        	}
			
                        newY.push_back(tanh(bias));
                  }
                 for(int y=1; y<=nnpl; y++){Y[y-1]=newY[y-1];}
		}
	}
	 
	for(int x=1; x<=non; x++)
	{
		double bias = 0; 
		
		for(int y=1; y<=nnpl; y++)
		{
			bias = bias + Y[y-1]*get_oW(x,y); 
		}
		//cout << "\n" << bias; 
		output.push_back(bias); 
	}
	
}
NN::~NN()
{}
