#include "../../NN_fixed_hist.hpp"
//#include "/home/howard/cpp_programs/classes/histogram.hpp"
#include "../../random.hpp"
using namespace std; 

double xscore(const vector<double> calc,  const dataset & mydata, int wds); 
void   mate( NN & stud,  NN & breeder );
void   mutate_hW( NN & nnwk, double p);
void   mutate_oW( NN & nnwk, double p); 
void   mutate_hb( NN & nnwk, double p);
int main()
{
   dataset   myds("Dataset",458,5,3); 
   vector<NN>     myNN; 
   srand(time(NULL)); 
   int S = 100; for(int x=1; x<=S; x++){myNN.push_back(NN(1,80,1,5));} 
   double hw_del = 0.001;
   double  bias_del = 0.01; 
   double ow_del = 0.001;
   int num_its = 1000000;  
   double val = 0.0001; 
   int bw =0.5; int nbins = 200; 
   vector<double> bins; for(int x=1; x<=nbins; x++){bins.push_back(bw/2.0 + bw*(x-1));} 
for(int z=1; z<=S; z++)
{	
for(int x=1; x<=myNN[0].get_nnpl(); x++)
{
	 for(int y=1; y<=myNN[0].get_nhw(1); y++)
	 {
		int  pm = (rand()%2+1)*2 -3;  
		myNN[z-1].set_hW(1,x,val*pm, y); 
	 }
}
}

for(int z=1; z<=S; z++)
{
for(int x=1; x<=myNN[0].get_non(); x++)
{
	for(int y=1; y<=myNN[0].get_now(); y++)
	{
		 int  pm = (rand()%2+1)*2 -3;
		myNN[z-1].set_oW(x,val*pm,y);
	} 
}
}
vector<double> scores,tempscores; 
for(int x=1; x<=S; x++)
{
	
	double  scr =0; 
	for(int y=1; y<=myds.get_nsets(); y++)
	{
		vector<double>  out;  myNN[x-1].get_O(out, myds, y );
		scr = scr + xscore(out,myds,y);
	}
		scores.push_back(scr/(myds.get_nsets()*1.0));
	        tempscores.push_back(scores[x-1]); 	
}
sort(tempscores.begin(),tempscores.end()); 

for(int x=1; x<=num_its; x++)
{
	if(x%100==0){cout << "\n" << x << "\t" << tempscores[0]; }
	vector<int> most_fit; 
	for(int y=1; y<=10;y++)
	{
		for(unsigned int z=1; z<=tempscores.size(); z++)
		{
			if(tempscores[y-1]==scores[z-1])
		        {
				most_fit.push_back(z); 
			}
		}
	}
	
	vector<NN>  nnP;
	for(int y=1; y<=10; y++){for(int z=1; z<=10; z++){nnP.push_back(myNN[most_fit[z-1]-1]);}}
	
	for(int y=1; y<100; y++)
	{
		int  rn =rand()%S +1; mate(nnP[rn-1],nnP[y-1]);
		mutate_hW(nnP[y-1],hw_del);
	        mutate_oW(nnP[y-1],ow_del); 
		mutate_hb(nnP[y-1],bias_del);
	        myNN[y-1]=nnP[y-1]; 	
	}
	
        for(int xx=1; xx<=S; xx++)
	{
        double  scr =0;
        for(int y=1; y<=myds.get_nsets(); y++)
        {
                vector<double>  out;  myNN[xx-1].get_O(out, myds, y );
                scr = scr + xscore(out,myds,y);
        }
                scores[xx-1]=(scr/(myds.get_nsets()*1.0));
                tempscores[xx-1]=(scores[xx-1]);
	}
	sort(tempscores.begin(),tempscores.end()); 
	

}


for(int sk =1;sk<=S; sk++){ string cfilename = "FinalNN"; stringstream ui; ui << sk;
string cnnhold; ui >> cnnhold;  cfilename = cfilename + cnnhold;
myNN[sk-1].make_NN(cfilename);
}     


return 0; 
   
}

double xscore(const vector<double> calc,  const dataset & mydata, int wds)
{
	double Sc = 0; 
	int x=1; 
	double  diff = calc[x-1]-mydata.get_od(wds,x);
	Sc = Sc+ diff*diff/(mydata.get_od(wds,x)*mydata.get_od(wds,x));
	if( calc[x-1]*mydata.get_od(wds,x) < 0 ){Sc=Sc+100;}
	return Sc; 
}

void  mutate_hW(NN & nn,double p)
{
	int pm = (rand()%2+1)*2 - 3; 
	int rl = rand()%nn.get_nlyer()+1; 
	int rn = rand()%nn.get_nnpl()+1; 
	int rw = rand()%nn.get_nhw(rl)+1; 
	nn.set_hW(rl,rn,nn.get_hW(rl,rn,rw)+pm*p,rw); 
}
void  mutate_hb(NN & nn,double p)
{
        int pm = (rand()%2+1)*2 - 3;
        int rl = rand()%nn.get_nlyer()+1;
        int rn = rand()%nn.get_nnpl()+1;
        nn.set_hnb(rl,rn,nn.get_hnb(rl,rn)+pm*p);
}

void  mutate_oW(NN & nn,double p)
{
        int pm = (rand()%2+1)*2 - 3;
        int rn = rand()%nn.get_non()+1;
        int rw = rand()%nn.get_now()+1;
        nn.set_oW(rn,nn.get_oW(rn,rw)+pm*p,rw);
}

	

void   mate( NN & stud,  NN & breeder )
{
	//cout << "\n" << stud.get_nhw(1); 
	
	for(int x=1; x<=stud.get_nlyer(); x++)
	{ 
		
		for(int y=1; y<=stud.get_nnpl(); y++)
		{
			
			for(int z=1; z<=stud.get_nhw(x); z++)
			{
				int rn = rand()%2+1; 
				if(rn==2)
				{
				breeder.set_hW(x,y,stud.get_hW(x,y,z),z); 
				}
			}
			
		}
		
	}
	
	for(int x=1; x<=stud.get_non(); x++)
	{
		for(int y=1; y<=stud.get_now(); y++)
		{
			int rn = rand()%2 +1; 
			if(rn==2)
			{
				breeder.set_oW(x,stud.get_oW(x,y),y); 
			}
		}
	}
	
}

