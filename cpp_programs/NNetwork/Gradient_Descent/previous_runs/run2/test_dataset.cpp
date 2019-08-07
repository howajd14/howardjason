#include "../../NN_fixed_hist.hpp"
//#include "/home/howard/cpp_programs/classes/histogram.hpp"
#include "../../random.hpp"
using namespace std; 

double xscore(const vector<double> calc,  const dataset & mydata, int wds); 
void grad( NN &  gradNN,   NN & myNN,  const dataset & mydata, double p);
void gradD( NN & gradNN,   NN & myNN, double p); 
void   mutate_hW( NN & nnwk, double p);
void   mutate_oW( NN & nnwk, double p);
void   mutate_hb( NN & nnwk, double p);
int main()
{
   dataset   myds("Dataset",458,5,3); 
   NN  myNN(2,4,1,5); 
   srand(time(NULL)); 
  

   double del = 0.001;
   int num_its = 10000;  
   double val = 0.01;  
	

for(int nl=1; nl<=myNN.get_nlyer(); nl++)
{ 
for(int x=1; x<=myNN.get_nnpl(); x++)
{
	 for(int y=1; y<=myNN.get_nhw(nl); y++)
	 {
		int  pm = (rand()%2+1)*2 -3;  
		myNN.set_hW(nl,x,val*pm, y); 
	 }
}
}
for(int nl=1; nl<=myNN.get_nlyer(); nl++)
{
for(int x=1; x<=myNN.get_nnpl(); x++)
{
         
                int  pm = (rand()%2+1)*2 -3;
                myNN.set_hnb(nl,x,val*pm);
         
}
}




for(int x=1; x<=myNN.get_non(); x++)
{
	for(int y=1; y<=myNN.get_now(); y++)
	{
		 int  pm = (rand()%2+1)*2 -3;
		myNN.set_oW(x,val*pm,y);
	} 
}


	  


NN   gradNN(myNN.get_nlyer(),myNN.get_nnpl(),myNN.get_non(),myNN.get_nhw(1));
for(int x=1; x<=num_its; x++)
{
     double scr =0; 
     for(int ii=1; ii<=myds.get_nsets(); ii++)
     {
	 vector<double> calc_val;
         myNN.get_O(calc_val,myds,ii); //cout << "\n" << calc_val[0] << "\t" << myds.get_od(ii,1); 
         scr = scr + xscore(calc_val, myds, ii);
     }
     scr = scr/myds.get_nsets(); 
     if(x%10==0){cout << "\n" << x << "\t" << scr; }
                                 

     	     
     grad(gradNN, myNN, myds, del); 
     gradD(gradNN,myNN,del);  
     
}


 string cfilename = "FinalNN"; 
myNN.make_NN(cfilename);
     


return 0; 
   
}
double xscore(const vector<double> calc,  const dataset & mydata, int wds)
{
	double Sc = 0; 
	int x=1; 
	double  diff = calc[x-1]-mydata.get_od(wds,x);
	double mag_diff = diff*diff/sqrt(diff*diff); 
	double mag_data = mydata.get_od(wds,x)*mydata.get_od(wds,x)/(sqrt(mydata.get_od(wds,x)*mydata.get_od(wds,x)));
	Sc = Sc+ mag_diff/mag_data; 
	if(!isnan(Sc)&&!isinf(Sc))
	{
	   return Sc; ;
	}
	else{return 100;}
}
void grad( NN &  gradNN,   NN & myNN,  const dataset & mydata, double p)
{
	double score1 =0; 
	for(int ii=1; ii<=mydata.get_nsets(); ii++)
        { 
              vector<double> calc_val;
              myNN.get_O(calc_val,mydata,ii);
              score1 = score1 + xscore(calc_val, mydata, ii);
        }
	score1 = score1/mydata.get_nsets(); 
	 for(int x=1; x<=myNN.get_nlyer(); x++)
	 {
		 for(int y=1; y<=myNN.get_nnpl(); y++)
		 {
			 for(int z=1; z<=myNN.get_nhw(x); z++)
		         {
				 
				 double score2 = 0; 
				 myNN.set_hW(x,y,myNN.get_hW(x,y,z)+p,z); 
				 for(int ii=1; ii<=mydata.get_nsets(); ii++)
                                 {
                                         vector<double> calc_val;
                                         myNN.get_O(calc_val,mydata,ii);
                                         score2 = score2 + xscore(calc_val, mydata, ii);
                                 }
				 score2 = score2/mydata.get_nsets(); 
				 myNN.set_hW(x,y,myNN.get_hW(x,y,z)-p,z);		 
				 gradNN.set_hW(x,y, (score2-score1)/p,z); 
			 }
		 }
         }
	 for(int x=1; x<=myNN.get_nlyer(); x++)
         {
                 for(int y=1; y<=myNN.get_nnpl(); y++)
                 {
                         
                                 double score2 = 0;
                                 myNN.set_hnb(x,y,myNN.get_hnb(x,y)+p);
                                 for(int ii=1; ii<=mydata.get_nsets(); ii++)
                                 {
                                         vector<double> calc_val;
                                         myNN.get_O(calc_val,mydata,ii);
                                         score2 = score2 + xscore(calc_val, mydata, ii);
                                 }
                                 score2 = score2/mydata.get_nsets();
                                 myNN.set_hnb(x,y,myNN.get_hnb(x,y)-p);
                                 gradNN.set_hnb(x,y, (score2-score1)/p);
                         
                 }
         }
	 for(int x=1; x<=myNN.get_non(); x++)
         {
                 for(int y=1; y<=myNN.get_now(); y++)
                 {
                                 double score2 = 0;
                                 myNN.set_oW(x,y,myNN.get_oW(x,y)+p);
                                 for(int ii=1; ii<=mydata.get_nsets(); ii++)
                                 {
                                         vector<double> calc_val;
                                         myNN.get_O(calc_val,mydata,ii);
                                         score2 = score2 + xscore(calc_val, mydata, ii);
                                 }
                                 score2 = score2/mydata.get_nsets();
                                 myNN.set_oW(x,y,myNN.get_oW(x,y)-p);
                                 gradNN.set_oW(x,y, (score2-score1)/p);

                 }
         }


}
void gradD( NN & gradNN,   NN & myNN, double p)
{
	 for(int x=1; x<=myNN.get_nlyer(); x++)
         {
                 for(int y=1; y<=myNN.get_nnpl(); y++)
                 {
                         for(int z=1; z<=myNN.get_nhw(x); z++)
                         {

                                 myNN.set_hW(x,y,myNN.get_hW(x,y,z)-p*gradNN.get_hW(x,y,z),z);
                           
                         }
                 }
         }
	  for(int x=1; x<=myNN.get_nlyer(); x++)
         {
                 for(int y=1; y<=myNN.get_nnpl(); y++)
                 {
                       
                                 myNN.set_hnb(x,y,myNN.get_hnb(x,y)-p*gradNN.get_hnb(x,y));
  
                 }
         }
	   for(int x=1; x<=myNN.get_non(); x++)
         {
                 for(int y=1; y<=myNN.get_now(); y++)
                 {

                                 myNN.set_oW(x,y,myNN.get_oW(x,y)-p*gradNN.get_oW(x,y));

                 }
         }



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

