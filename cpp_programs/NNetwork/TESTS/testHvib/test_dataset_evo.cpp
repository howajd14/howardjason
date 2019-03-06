#include "../NN_fixed_hist.hpp"
//#include "/home/howard/cpp_programs/classes/histogram.hpp"
#include "../random.hpp"
using namespace std; 

double xscore(const vector<double> calc,  const dataset & mydata, int wds); 
void   mutate( NN & nntwk); 
void   breed( vector<NN>  & nnP, vector<NN> & nnO,  vector<double> & scores); 
int main()
{
   dataset   myds("Dataset",458,5,3); 
   vector<NN>     myNN; 
   srand(time(NULL)); 
   int S = 1; for(int x=1; x<=S; x++){myNN.push_back(NN(1,20,1,5));}
   double del = 0.001;
   int num_its = 1000000;  
   double val = 0.0001; 
   double bw =1; int nbins = 200; 
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
		myNN[z-1].set_oW(x,val*pm*100,y);
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
}

double max = tempscores[S-1];
hist GE(tempscores,bins); 

for(int x=1; x<=num_its; x++)
{
	if(x%1000==0){cout << "\n" << x << "\t" << tempscores[0];} 
	vector<NN>  nnP; 
	vector<double> scoresP;
	for(int y=1; y<=S; y++)
	{
		
		double scrh=0; 
		for(int dd=1; dd<=myds.get_nsets(); dd++)
		{
		vector<double> out; nnP[y-1].get_O(out, myds , dd);
		scrh = scrh +  xscore(out,myds,dd); //if(x%1000==0&&y==1){cout << "\n" << out[0] << "\t" << myds.get_od(dd, 1) << "\t" << xscore(out,myds,dd);} 
		} 
		scoresP.push_back(scrh/(myds.get_nsets()*1.0)); 
		tempscoresP.push_back(scoresP[y-1]); 
	}

        GE.combine(Hp);


}

GE.make_file("file_Hist.dat"); 
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
	if( calc[x-1]*mydata.get_od(wds,x) < 0 ){Sc=Sc+Sc;}
	return Sc; 
}
void mutate_hW( NN & nntwk, double p)
{
         int rl = rand()% nntwk.get_nlyer();
	 int rn = rand()% nntwk.get_nnpl(); 
	 int rw = rand()% nntwk.get_nhw(rl); 
	 nntwk.set_hW(rl, rn, nntwk.get_hW(rl,rn,rw)+p, rw); 
         
}
void mutate_oW(NN & nntwk, double p)
{
         int rn = rand()% nntwk.get_non();
         int rw = rand()% nntwk.get_now(rl);
         nntwk.set_oW( rn, nntwk.get_oW(rn,rw)+p, rw);
}
void   breed( vector<NN>  & nnP, vector<NN> & nnO,  vector<double> & scores)
{
	NN	nnNew(nnO[0].get_nlyer(),nnO[0].get_nnpl(),nnO[0].get_non(), nnO[0].get_nhw(1));
		
}
