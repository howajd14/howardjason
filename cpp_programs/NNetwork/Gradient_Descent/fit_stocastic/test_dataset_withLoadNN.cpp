#include "../../NN_fixed_hist.hpp"
//#include "/home/howard/cpp_programs/classes/histogram.hpp"
#include "../../random.hpp"
using namespace std; 

double xscore(const vector<double> calc,  const dataset & mydata, int wds); 
void   mutate_hW( NN & nnwk, double p);
void   mutate_oW( NN & nnwk, double p);
void   mutate_hb( NN & nnwk, double p);

int main()
{
    dataset   myds1("Dataset1",990,8,1);
   dataset   myds2("Dataset2",932,8,1);
//   NN  myNN(1,20,1,5);
 
   vector<NN>     myNN; 
   srand(time(NULL)); 
   int S = 10; for(int x=1; x<=S; x++)
   {myNN.push_back(NN(1,40,1,5)); myNN[x-1].load_NN("FinalNN"); } 
    
   int tnhw=0; 
for(int x=1; x<=myNN[0].get_nlyer(); x++)
{
	tnhw = tnhw + myNN[0].get_nnpl()*myNN[0].get_nhw(x); 
}
   double del = 0.000005;
   int num_its = 1000000;  
   double val = 0.0001; 
   double bw =1e-11; int nbins = 1000; 
   vector<double> bins; for(int x=1; x<=nbins; x++){bins.push_back(bw/2.0 + bw*(x-1));} 
/*
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
*/
vector<double> scores,tempscores; 
for(int x=1; x<=S; x++)
{
	double  scr =0; 
	for(int y=1; y<=myds1.get_nsets(); y++)
	{
		vector<double>  out;  myNN[x-1].get_O(out, myds1, y );
		scr = scr + xscore(out,myds1,y);
	}
	for(int y=1; y<=myds2.get_nsets(); y++)
        {
                vector<double>  out;  myNN[x-1].get_O(out, myds2, y );
                scr = scr + xscore(out,myds2,y);
        }

		scores.push_back(scr/(myds1.get_nsets()*1.0+myds2.get_nsets()*1.0)); 
	 tempscores.push_back(scores[x-1]); 
}

sort(tempscores.begin(),tempscores.end()); 
double max = tempscores[S-1];
hist GE(tempscores,bins); 

for(int x=1; x<=num_its; x++)
{
	if(x%10==0){cout << "\n" << x << "\t" << tempscores[0];} 
        if(x%1000==0){max = tempscores[S-1];}


	vector<NN>  nnP; for(int y=1; y<=S; y++){nnP.push_back(myNN[y-1]);}
	vector<double> scoresP, tempscoresP; 
	for(int y=1; y<=S; y++)
	{
	       mutate_hW( nnP[y-1], del);
               mutate_oW( nnP[y-1], del);
               mutate_hb( nnP[y-1], del);

		double scrh=0; 
		for(int yy=1; yy<=myds1.get_nsets(); yy++)
        {
                vector<double>  out;  nnP[y-1].get_O(out, myds1, yy );
                scrh = scrh + xscore(out,myds1,yy);  
        }
        for(int yy=1; yy<=myds2.get_nsets(); yy++)
       {
                vector<double>  out;  nnP[y-1].get_O(out, myds2, yy );
                scrh = scrh + xscore(out,myds2,yy);
       }

                scoresP.push_back(scrh/(myds1.get_nsets()*1.0+1.0*myds2.get_nsets()));
	
		tempscoresP.push_back(scoresP[y-1]); 
	}
   
	sort(tempscoresP.begin(),tempscoresP.end()); 
	hist HE(tempscoresP,bins); 
	hist GEI(GE,HE); 
	for(int y=1; y<=S; y++)
        {
                int b1 = GEI.get_bin(scores[y-1]);
                int b2 = GEI.get_bin(scoresP[y-1]);
                double p  = (rand()%RAND_MAX + 1)/(RAND_MAX*1.0);
                if(p <  GEI.get_count(b1)/GEI.get_count(b2) && scoresP[y-1]<max)
                {

                         myNN[y-1]=nnP[y-1];

                        scores[y-1]=scoresP[y-1];
                }
                
        }

        for(int z=1; z<=S; z++){tempscores[z-1]=scores[z-1];}
        sort(tempscores.begin(),tempscores.end());
        hist Hp(tempscores,bins);
        double term = 1.0/GEI.get_sum();
        for(unsigned int kk=1; kk<=Hp.num_bins(); kk++)
        {
                int  wb =  GEI.get_bin(Hp.get_en(kk));
                Hp.set_count(kk,term*Hp.get_count(kk)*GEI.get_count(wb));
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
        double  diff = calc[x-1]-mydata.get_od(wds,x)/10.0;
        Sc = diff*diff ;
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

