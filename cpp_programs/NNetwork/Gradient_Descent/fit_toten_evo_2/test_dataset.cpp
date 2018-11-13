#include "../../NN_fixed_hist.hpp"
//#include "/home/howard/cpp_programs/classes/histogram.hpp"
#include "../../random.hpp"
using namespace std; 

double xscore(const vector<double> calc,  const dataset & mydata, int wds); 
void grad( NN &  gradNN,   NN & myNN,  const dataset & mydata, double p);
void gradSD( NN &  gradNN,   NN & myNN,  const dataset & mydata, double p, int wds);
void gradD( NN & gradNN,   NN & myNN, double p); 
void gradMP( NN &  gradNN,   NN & myNN,  const dataset & mydata, double p);
void   mutate_hW( NN & nnwk, double p);
void   mutate_oW( NN & nnwk, double p);
void   mutate_hb( NN & nnwk, double p);
int main()
{
   dataset   myds1("Dataset1",990,8,1); 
   dataset   myds2("Dataset2",932,8,1); 
   NN  myNN(1,20,1,5);
  myNN.load_NN("FinalNN");  
   srand(time(NULL)); 
  

   double del = 0.0000001;
   double del2 =0.0000001; 
   int num_its = 10000000;  
   double val = 0.000001;  
	
/*
for(int nl=1; nl<=myNN.get_nlyer(); nl++)
{ 
for(int x=1; x<=myNN.get_nnpl(); x++)
{
	 for(int y=1; y<=myNN.get_nhw(nl); y++)
	 {
		 double rn = rand()%10+1;
		int  pm = (rand()%2+1)*2 -3;  
		myNN.set_hW(nl,x,val*pm*rn, y); 
	 }
}
}
for(int nl=1; nl<=myNN.get_nlyer(); nl++)
{
for(int x=1; x<=myNN.get_nnpl(); x++)
{
		double rn = rand()%10+1; 
         
                int  pm = (rand()%2+1)*2 -3;
                myNN.set_hnb(nl,x,val*rn*pm);
         
}
}




for(int x=1; x<=myNN.get_non(); x++)
{
	for(int y=1; y<=myNN.get_now(); y++)
	{
		double rn = rand()%10+1; 
		 int  pm = (rand()%2+1)*2 -3;
		myNN.set_oW(x,val*pm*rn,y);
	} 
}
*/

	  


NN   gradNN(myNN.get_nlyer(),myNN.get_nnpl(),myNN.get_non(),myNN.get_nhw(1));
for(int x=1; x<=num_its; x++)
{
	if(x%1==0){
     double scr =0; 
     for(int ii=1; ii<=myds1.get_nsets(); ii++)
     {
	 vector<double> calc_val;
         myNN.get_O(calc_val,myds1,ii);  
         scr = scr + xscore(calc_val, myds1, ii);
     }
     for(int ii=1; ii<=myds2.get_nsets(); ii++)
     {
         vector<double> calc_val;
         myNN.get_O(calc_val,myds2,ii);
         scr = scr + xscore(calc_val, myds2, ii);
     }

     scr = scr/(myds1.get_nsets()+myds2.get_nsets()); 
     cout << "\n" << x << "\t" << scr; 
       //mutate_hW( myNN, val);
       //mutate_oW( myNN, val);
       //mutate_hb( myNN, val);

	
	}/*
         if(x%20000==0)
	{	
		 mutate_hW( myNN, val);
       mutate_oW( myNN, val);
       mutate_hb( myNN, val);

	}
	*/	
     int rn = rand()%2+1;
    if(rn==1)
    {
    //int rds = rand()%myds1.get_nsets()+1;  
     gradMP(gradNN, myNN, myds1,del); 
    }
    if(rn==2)
    { 
     //int rds = rand()%myds2.get_nsets()+1;
     gradMP(gradNN, myNN, myds2,del);
    }
     gradD(gradNN,myNN,del2);  
     if(x%1000==0)
     {
	     string cfilename = "CurrentNN";
	     myNN.make_NN(cfilename);
     }

}


 string cfilename = "FinalNN"; 
myNN.make_NN(cfilename);
     


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
                                 myNN.set_oW(x,myNN.get_oW(x,y)+p,y);
                                 for(int ii=1; ii<=mydata.get_nsets(); ii++)
                                 {
                                         vector<double> calc_val;
                                         myNN.get_O(calc_val,mydata,ii);
                                         score2 = score2 + xscore(calc_val, mydata, ii);
                                 }
                                 score2 = score2/mydata.get_nsets();
                                 myNN.set_oW(x,myNN.get_oW(x,y)-p,y);
                                 gradNN.set_oW(x, (score2-score1)/p,y);

                 }
         }


}
void gradMP( NN &  gradNN,   NN & myNN,  const dataset & mydata, double p)
{


         for(int x=1; x<=myNN.get_nlyer(); x++)
         {
                 for(int y=1; y<=myNN.get_nnpl(); y++)
                 {
                         for(int z=1; z<=myNN.get_nhw(x); z++)
                         {
                                double score1 =0;
                                double P = myNN.get_hW(x,y,z)-p;
                                 myNN.set_hW(x,y,P,z);
                                for(int ii=1; ii<=mydata.get_nsets(); ii++)
                                {
                                vector<double> calc_val;
                                myNN.get_O(calc_val,mydata,ii);
                                score1 = score1 + xscore(calc_val, mydata, ii);
                                }
                                score1 = score1/mydata.get_nsets();
                                 double score2 = 0;
                                 P = myNN.get_hW(x,y,z)+2*p;
                                 myNN.set_hW(x,y,P,z);
                                 for(int ii=1; ii<=mydata.get_nsets(); ii++)
                                 {
                                         vector<double> calc_val;
                                         myNN.get_O(calc_val,mydata,ii);
                                         score2 = score2 + xscore(calc_val, mydata, ii);
                                 }
                                 score2 = score2/mydata.get_nsets();
                                 P = myNN.get_hW(x,y,z)-p;
                                 myNN.set_hW(x,y,P,z);
                                 gradNN.set_hW(x,y, (score2-score1)/(2*p),z);
                         }
                 }
         }
  for(int x=1; x<=myNN.get_nlyer(); x++)
         {
                 for(int y=1; y<=myNN.get_nnpl(); y++)
                 {
                                double score1 =0;
                                double P = myNN.get_hnb(x,y)-p;
                                 myNN.set_hnb(x,y,P);
                                for(int ii=1; ii<=mydata.get_nsets(); ii++)
                                {
                                vector<double> calc_val;
                                myNN.get_O(calc_val,mydata,ii);
                                score1 = score1 + xscore(calc_val, mydata, ii);
                                }
                                score1 = score1/mydata.get_nsets();

                                 double score2 = 0;
                                  P = myNN.get_hnb(x,y)+2*p;
                                 myNN.set_hnb(x,y,P);
                                 for(int ii=1; ii<=mydata.get_nsets(); ii++)
                                 {
                                         vector<double> calc_val;
                                         myNN.get_O(calc_val,mydata,ii);
                                         score2 = score2 + xscore(calc_val, mydata, ii);
                                 }
                                 score2 = score2/mydata.get_nsets();
                                 P = myNN.get_hnb(x,y)-p;
                                 myNN.set_hnb(x,y,P);
                                 gradNN.set_hnb(x,y, (score2-score1)/(2*p));

                 }
         }
  for(int x=1; x<=myNN.get_non(); x++)
         {
                 for(int y=1; y<=myNN.get_now(); y++)
                 {
                                double score1 =0;
                                double P = myNN.get_oW(x,y)-p;
                                 myNN.set_oW(x,P,y);
                                for(int ii=1; ii<=mydata.get_nsets(); ii++)
                                {
                                vector<double> calc_val;
                                myNN.get_O(calc_val,mydata,ii);
                                score1 = score1 + xscore(calc_val, mydata, ii);
                                }
                                score1 = score1/mydata.get_nsets();
                                 double score2 = 0;
                                 P = myNN.get_oW(x,y)+2*p;
                                 myNN.set_oW(x,P,y);
                                 for(int ii=1; ii<=mydata.get_nsets(); ii++)
                                 {
                                         vector<double> calc_val;
                                         myNN.get_O(calc_val,mydata,ii);
                                         score2 = score2 + xscore(calc_val, mydata, ii);
                                 }
                                 score2 = score2/mydata.get_nsets();
                                 P = myNN.get_oW(x,y)-p;
                                 myNN.set_oW(x,P,y);
                                 gradNN.set_oW(x, (score2-score1)/(2*p),y); //cout << "\n" << score2 << "\t" << score1;

                 }
         }


}

void gradSD( NN &  gradNN,   NN & myNN,  const dataset & mydata, double p, int wds)
{
        double score1 =0;
              vector<double> calc_val;
              myNN.get_O(calc_val,mydata,wds);
              score1 = score1 + xscore(calc_val, mydata, wds);
         for(int x=1; x<=myNN.get_nlyer(); x++)
         {
                 for(int y=1; y<=myNN.get_nnpl(); y++)
                 {
                         for(int z=1; z<=myNN.get_nhw(x); z++)
                         {
                                 double score2 = 0;
                                 myNN.set_hW(x,y,myNN.get_hW(x,y,z)+p,z);      
                                 vector<double> calc_val;
                                 myNN.get_O(calc_val,mydata,wds);
                                 score2 = score2 + xscore(calc_val, mydata, wds);
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
                                 
                                         vector<double> calc_val;
                                         myNN.get_O(calc_val,mydata,wds);
                                         score2 = score2 + xscore(calc_val, mydata,wds);
                                 myNN.set_hnb(x,y,myNN.get_hnb(x,y)-p);
                                 gradNN.set_hnb(x,y, (score2-score1)/p); //cout << "\n" <<  (score2-score1)/p;


                 }
         }
 for(int x=1; x<=myNN.get_non(); x++)
         {
                 for(int y=1; y<=myNN.get_now(); y++)
                 {
                                 double score2 = 0;
                                 myNN.set_oW(x,myNN.get_oW(x,y)+p,y);
                                 
                                         vector<double> calc_val;
                                         myNN.get_O(calc_val,mydata,wds);
                                         score2 = score2 + xscore(calc_val, mydata, wds);
                                 myNN.set_oW(x,myNN.get_oW(x,y)-p,y);
                                 gradNN.set_oW(x, (score2-score1)/p,y);

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

                                 myNN.set_oW(x,myNN.get_oW(x,y)-p*gradNN.get_oW(x,y),y);

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

