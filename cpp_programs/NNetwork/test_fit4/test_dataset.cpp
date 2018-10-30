#include "../NN_fixed_hist.hpp"
//#include "/home/howard/cpp_programs/classes/histogram.hpp"
#include "../random.hpp"
using namespace std; 

double xscore(const vector<double> calc,  const dataset & mydata, int wds); 

int main()
{
   dataset   myds("Dataset",624,49,3); 
   vector<NN>     myNN; 
   srand(time(NULL)); 
   int S = 10; for(int x=1; x<=S; x++){myNN.push_back(NN(1,4,1,52));} 
  // cout << "\ngot here\n";
   double del = 0.001;
   int num_its = 1000000;  
   double val = 0.001; 
   int bw =10; int nbins = 200; 
   vector<double> bins; for(int x=1; x<=nbins; x++){bins.push_back(bw/2.0 + bw*(x-1));} 
for(int z=1; z<=S; z++)
{	
for(int x=1; x<=myNN[0].get_nnpl(); x++)
{
	 //cout << "\n" << myNN[2].get_nhw(1);
	 for(int y=1; y<=myNN[0].get_nhw(1); y++)
	 {
		//cout << "\n    " << z  << "\t" << x << "\t" << y;
		int  pm = (rand()%2+1)*2 -3; 
		 val = 0.01; // (rand()%RAND_MAX*1.0+1)/RAND_MAX*1.0;
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
                 val = 0.01;
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
double max = tempscores[S-1];
hist GE(tempscores,bins); 

for(int x=1; x<=num_its; x++)
{
	if(x%1000==0){cout << "\n" << x << "\t" << tempscores[0] << "\t" << tempscores[S-1];} 
	 if(x%10000==0)
        {
                max = tempscores[S-1];
                bw =  floor(max/200);
                for(int nnb =1; nnb <=nbins; nnb++){bins[nnb-1]=bw/2.0 + bw*(nnb-1);}
                hist GEP(tempscores,bins);
                GE = GEP;
        }

	vector<NN>  nnP; for(int y=1; y<=S; y++){nnP.push_back(myNN[y-1]);}
	vector<double> scoresP, tempscoresP; 
	for(int y=1; y<=S; y++)
	{
		double rnmb = (rand()%520 + 10 +1); 
		
		if(rnmb <=520)
		{
		int rnn = rand()%myNN[0].get_nnpl()+1;
		int rw  = rand()%myNN[0].get_nhw(1)+1;  
		int pm = (rand()%2+1)*2 -3;
		double chng = nnP[y-1].get_hW(1,rnn,rw) + del*pm; 
		//if(chng<=val*1 && chng >=-1*val)
		//{
			nnP[y-1].set_hW(1,rnn,chng,rw); 
		//}
		}
		if(rnmb >520)
		{
		// int rnn = rand()%myNN[0].get_non()+1;
                int rw  = rand()%myNN[0].get_now()+1;
                int pm = (rand()%2+1)*2 -3;
                double chng = nnP[y-1].get_oW(1,rw) + del*pm;
                //if(chng<=val*1 && chng >=-1*val)
                //{
                        nnP[y-1].set_oW(1,chng,rw);
                //}
                //}

		}
		double scrh=0; 
		for(int dd=1; dd<=myds.get_nsets(); dd++)
		{
		vector<double> out; nnP[y-1].get_O(out, myds , dd);
		scrh = scrh +  xscore(out,myds,dd); //if(x%1000==0&&y==1){cout << "\n" << out[0] << "\t" << myds.get_od(dd, 1) << "\t" << xscore(out,myds,dd);} 
		} 
		scoresP.push_back(scrh/(myds.get_nsets()*1.0)); 
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



return 0; 
   
}
double xscore(const vector<double> calc,  const dataset & mydata, int wds)
{
	double Sc = 0; 
	int x=1; 
	double  diff = calc[x-1]-mydata.get_od(wds,x);
	Sc = Sc+ diff*diff/(mydata.get_od(wds,x)*mydata.get_od(wds,x));
	if( calc[x-1]*mydata.get_od(wds,x) < 0 ){Sc=Sc+100*Sc;}
	return Sc; 
}

