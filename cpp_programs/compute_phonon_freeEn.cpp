#include "../classes/file_class/file.hpp"
#include <math.h>
using namespace std;

int main()
{

string filename; 
cout << "\nWhat is the name of your file with dos?  \n"; cin >> filename;
file dos(filename);


vector<double> freq;
vector<double> N; 
double   conv_ev = 100*2.99792458e8*4.1356677e-15;
//double   conv_J  = 100*2.99792458e8*6.626176e-34; 
//double   Z = 0;
double  T =0;
double intergal =0;
double kb_ev  = 8.61733e-5;
//double kb_J   = 1.3806485e-23; 
//double  J_ev = 1.0/(1.60217657e-19);

cout << "\nWhat is the maximum temperature ?\n";
cin >> T; 
string enfile; 
cout << "\nWhat is the name of the file with the DFT energy"; 
cin >> enfile;
file enFile(enfile);
string linehere = enFile.get_line(1);
stringstream hh; hh << linehere; 
double DFT_en;  hh >> DFT_en; DFT_en = DFT_en*13.605693;  


//double   avg_freq = 0; 



for(int x =1 ; x<=dos.num_lines(); x++)
{
	string line = dos.get_line(x);
	stringstream ss;
	ss << line;
	double holder;
	ss >> holder; freq.push_back(holder); ss>> holder; N.push_back(holder);
}

double dw = (freq[1]-freq[0]);

/*
for(int x =1 ; x<=dos.num_lines()-1; x++)
{
	double en = (freq[x-1]+freq[x])*0.5*100*3e8*4.13567e-15;
	Z = Z + (freq[x]-freq[x-1])*((N[x-1]+N[x])/2)*exp(-(en)/(T*8.617e-5));
}
*/
file outfile; 

for(int ii =1; ii<= T; ii++)
{
	//double avg_w = 0;
	double  F = 0;
	for(int x =1; x<=(dos.num_lines()); x++)
	{      
	//	if(x>1){dw = freq[x-1]-freq[x-2];}
	//	if(freq[x-1]<0){freq[x-1]=1e-3;}
	//	if(freq[x-1]==0){freq[x-1]=1e-5;}
	//
	 double sh =0;
	if(freq[x-1]>0)
	{
		double  xx = conv_ev*freq[x-1]/(2*kb_ev*ii); 
		//double sh =0;
		//double frq = freq[x-1]*100*2.99792458e8;
	
			if(xx<=100)
			{
			sh = kb_ev*ii*log(2*sinh(xx))*dw*N[x-1]; if(isnan(sh)){cout << "\n" << xx;} //cout << "\n" << en<< "\t" << (2*kb_ev*ii); 
			}
			if(xx>100)
			{
			sh = kb_ev*ii*xx*dw*N[x-1]; 
			}
	}
	/*
		if(xx<=50)
		{
		sh = 0.5*4.1356677e-15*frq*(cosh(xx)/sinh(xx))*N[x-1]*dw; 
		}
		if(xx>50)
		{
		sh = 0.5*4.1356677e-15*frq*N[x-1]*dw;
		}
	*/
		F = F + sh;
	
		
	}

	string outline, holder; 
	double outen = F+DFT_en; //cout << "\n" << F; 
	stringstream ss; ss << ii; ss >> outline; 
	ss.clear();ss.str("");
	outen = outen;// + DFT_en;
	ss.width(11);ss.precision(11);
	ss << outen; ss >> holder; 
	outline = outline + "      " + holder; 
	outfile.add_line(outline);

}

for(int x =1; x<=(dos.num_lines()); x++)
{
		intergal = intergal + dw*N[x-1];
}
cout << "\n" << intergal << "\n";

outfile.make_file("Free_energy");

return 0;
}
