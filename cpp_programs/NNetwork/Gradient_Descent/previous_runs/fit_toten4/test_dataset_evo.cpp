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
   dataset   myds1("Dataset1",990,8,1);
   dataset   myds2("Dataset2",932,8,1);
   double  tns = myds1.get_nsets()+myds2.get_nsets(); 
   vector<NN>     myNN; 
   srand(time(NULL)); 
   int S = 100; for(int x=1; x<=S; x++){myNN.push_back(NN(1,60,1,5));} 
   double hw_del = 0.0001;
   double  bias_del = 0.0001; 
   double ow_del = 0.00001;
   int num_its = 1000000;  
   double val = 0.001;  
for(int z=1; z<=S; z++)
{	
for(int nl=1; nl<=myNN[0].get_nlyer(); nl++){
for(int x=1; x<=myNN[0].get_nnpl(); x++)
{
	 for(int y=1; y<=myNN[0].get_nhw(nl); y++)
	 {
		int  pm = (rand()%2+1)*2 -3;  
		int rn = rand()%10+1; 
		myNN[z-1].set_hW(nl,x,val*pm*1.0*rn, y); 
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
		  int rn = rand()%10+1;
		myNN[z-1].set_oW(x,val*pm*1.0*rn,y);
	} 
}
}

for(int z=1; z<=S; z++){
for(int nl=1; nl<=myNN[z-1].get_nlyer(); nl++)
{
for(int x=1; x<=myNN[z-1].get_nnpl(); x++)
{
                double rn = rand()%10+1;

                int  pm = (rand()%2+1)*2 -3;
                myNN[x-1].set_hnb(nl,x,val*rn*pm);

}
}
}

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

		scores.push_back(scr/(tns));
	        tempscores.push_back(scores[x-1]); 	
}
sort(tempscores.begin(),tempscores.end()); 

for(int x=1; x<=num_its; x++)
{
	if(x%1==0){cout << "\n" << x << "\t" << tempscores[0]; }
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
        for(int y=1; y<=myds1.get_nsets(); y++)
        {
                vector<double>  out;  myNN[xx-1].get_O(out, myds1, y );
                scr = scr + xscore(out,myds1,y);
        }
	for(int y=1; y<=myds2.get_nsets(); y++)
        {
                vector<double>  out;  myNN[xx-1].get_O(out, myds2, y );
                scr = scr + xscore(out,myds2,y);
        }

                scores[xx-1]=(scr/(tns));
                tempscores[xx-1]=(scores[xx-1]);
	}
	sort(tempscores.begin(),tempscores.end()); 
	
        
       if(x%1000==0)
       {
             string cfilename = "CurrentNN";
             myNN[0].make_NN(cfilename);
       }

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

