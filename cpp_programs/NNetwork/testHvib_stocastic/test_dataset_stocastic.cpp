#include "../NN_fixed_hist.hpp"
//#include "/home/howard/cpp_programs/classes/histogram.hpp"
#include "../random.hpp"
using namespace std; 

double xscore(const vector<double> calc,  const dataset & mydata, int wds); 

int main()
{
   dataset   myds("Dataset",458,5,3); 
   vector<NN>     myNN; 
   srand(time(NULL)); 
   int S = 1; for(int x=1; x<=S; x++){myNN.push_back(NN(1,10,1,5));} 
   int tnhw=0; 
for(int x=1; x<=myNN[0].get_nlyer(); x++)
{
	tnhw = tnhw + myNN[0].get_nnpl()*myNN[0].get_nhw(x); 
}
   double del = 0.001;
   int num_its = 10;  
   double val = 0.001;
   double mult = 1;
   int epochs =10000;   
   double bw =0.005; int nbins = 400; 
   double avgS  = 0; 
   double avgSp = 0; 
   vector<double> bins; for(int x=1; x<=nbins; x++){bins.push_back(bw/2.0 + bw*(x-1));} 
for(int z=1; z<=S; z++)
{	
for(int ioo=1; ioo<=myNN[0].get_nlyer(); ioo++)
{
for(int x=1; x<=myNN[0].get_nnpl(); x++)
{
	 for(int y=1; y<=myNN[0].get_nhw(1); y++)
	 {
		int  pm = (rand()%2+1)*2 -3;  
		myNN[z-1].set_hW(ioo,x,val*pm, y); 
	 }
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

for(int dds=1; dds <=epochs*myds.get_nsets(); dds++){  
int ods = rand()%myds.get_nsets()+1; 
int ods2 = rand()%myds.get_nsets()+1;
int ods3 = rand()%myds.get_nsets()+1;
vector<int>  rds; rds.push_back(ods); rds.push_back(ods2); rds.push_back(ods3); 
vector<double> scores,tempscores; 
for(int x=1; x<=S; x++)
{
	        double  scr =0; 
                for(int yt=1; yt<=3; yt++)
		{
		vector<double>  out;  myNN[x-1].get_O(out, myds, rds[yt-1]);
		scr = scr + xscore(out,myds,rds[yt-1]);
		}
		scores.push_back(scr/3); 
	        tempscores.push_back(scores[x-1]);
		if(dds%10==0)
		{
	        scr =0; 
		for(int y=1; y<=myds.get_nsets(); y++)
		{
			vector<double> outn; myNN[x-1].get_O(outn, myds, y);
			scr = scr + xscore(outn,myds,y); 
		}	
               avgS = avgS + scr/myds.get_nsets(); 
		}
}
if(dds%100==0){cout << "\n" << dds << "\t" << ods << "\t" <<  "\t" << avgS/(dds/10) << "\t" << avgSp/(dds/10);}
sort(tempscores.begin(),tempscores.end()); 
double max = tempscores[S-1];
hist GE(tempscores,bins); 
for(int x=1; x<=num_its; x++)
{
	//if(x%1000==0){cout << "\n" << dds << "\t" << ods << "\t" << x << "\t" << tempscores[0];} 
        if(x%2==0){max = tempscores[0];}
	vector<NN>  nnP; for(int y=1; y<=S; y++){nnP.push_back(myNN[y-1]);}
	vector<double> scoresP, tempscoresP; 
	for(int y=1; y<=S; y++)
	{
		double rnmb = (rand()%(tnhw  +  myNN[0].get_non()*myNN[0].get_now()) +1); 
		
		if(rnmb <= tnhw)
		{
		int rly = rand()%myNN[0].get_nlyer()+1;  
		int rnn = rand()%myNN[0].get_nnpl()+1;
		int rw  = rand()%myNN[0].get_nhw(rly)+1;  
		int pm = (rand()%2+1)*2 -3;
		double chng = nnP[y-1].get_hW(rly,rnn,rw) + del*pm; 
			nnP[y-1].set_hW(rly,rnn,chng,rw); 
		}
		if(rnmb >  tnhw)
		{
                int rw  = rand()%myNN[0].get_now()+1;
                int pm = (rand()%2+1)*2 -3;
                double chng = nnP[y-1].get_oW(1,rw) + del*pm;
                nnP[y-1].set_oW(1,chng,rw);
		}
		double scrh=0; 
		for(int yt=1;yt <=3; yt++)
		{
		vector<double> out; nnP[y-1].get_O(out, myds , rds[yt-1]);
		scrh = scrh +  xscore(out,myds,rds[yt-1]);
	         }	
		scoresP.push_back(scrh/3); 
		tempscoresP.push_back(scoresP[y-1]);
	       if(x==num_its&&dds%10==0)
	       {	       
		 scrh =0;
                for(int yp=1; yp<=myds.get_nsets(); yp++)
                {
                        vector<double> outn; nnP[y-1].get_O(outn, myds, yp);
                        scrh = scrh + xscore(outn,myds,yp);
                }
               avgSp = avgSp + scrh/myds.get_nsets();
		}
	}
      //  if(dds%100==0){cout << "\t" << avgSp/dds; }
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

			
                        myNN[y-1] = nnP[y-1];
		

                        scores[y-1]=scoresP[y-1];
                }
                
        }

        for(int z=1; z<=S; z++){tempscores[z-1]=scores[z-1];}
        sort(tempscores.begin(),tempscores.end());
        hist Hp(tempscores,bins);
        double term = mult/GEI.get_sum();
        for(unsigned int kk=1; kk<=Hp.num_bins(); kk++)
        {
                int  wb =  GEI.get_bin(Hp.get_en(kk));
                Hp.set_count(kk,term*Hp.get_count(kk)*GEI.get_count(wb));
        }
        GE.combine(Hp);


}
}

//GE.make_file("file_Hist.dat"); 
for(int sk =1;sk<=S; sk++){ string cfilename = "FinalNN"; stringstream ui; ui << sk;
string cnnhold; ui >> cnnhold;  cfilename = cfilename + cnnhold;
myNN[sk-1].make_NN(cfilename);}
     


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

