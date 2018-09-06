#include "../classes/file_class/file.hpp"
//#include "../classes/coordinates_class/coordinates.hpp"
#include<math.h>
using namespace std;

int main()
{

file Opos("Opos"); file Hpos("Hpos");
file  lat_vecs("lattice_vectors");  
double V_base[3][3],multiplier;
int numO  = 0;
int numH  = 0;
cout << "\nHow many O and H atoms?  " ; 
cin >> numO; numH=numO;
int num_its = (Hpos.num_lines()+1)/(numH+2);
for(int x=1; x<=lat_vecs.num_lines();x++)
{
	if(x==1)
	{
		string mult_line; mult_line = lat_vecs.get_line(x);
		stringstream ss1; ss1 << mult_line; ss1 >> multiplier;
	}
	if(x>1)
	{
		string vec_line; vec_line = lat_vecs.get_line(x);
		stringstream ss2; ss2 << vec_line;
		double holder;  ss2 >> holder; V_base[x-2][0]=holder*multiplier; ss2>>holder; V_base[x-2][1]=holder*multiplier; ss2>>holder; V_base[x-2][2]=holder*multiplier;
	}
}




vector<double> ox,oy,oz,hx,hy,hz;


//store positions of Oxygen in vectors
for(int y=1; y<=Opos.num_lines(); y++){ox.push_back(0); oy.push_back(0); oz.push_back(0); }
for(int x = 1; x<=Opos.num_lines(); x++)
{
	string line43 = Opos.get_line(x);
	stringstream ppp; ppp << line43; 
	string holder;  ppp >> holder; 
	if(holder == "O")
	{
	double av, bv, cv; ppp >> av; ppp >> bv; ppp>>cv;
	ox[x-1]=av*V_base[0][0]+bv*V_base[1][0]+cv*V_base[2][0]; 
	oy[x-1]=av*V_base[0][1]+bv*V_base[1][1]+cv*V_base[2][1]; 
	oz[x-1]=av*V_base[0][2]+bv*V_base[1][2]+cv*V_base[2][2];
	}
	
}

//store hydrogen positions in vectors and make vector of oh group at each time step 
vector<double> Theta;
vector<double> Phi; 
for(int y=1; y<=Hpos.num_lines(); y++){hx.push_back(0); hy.push_back(0); hz.push_back(0);}
for(int x = 1; x<=Opos.num_lines(); x++)
{
	string line43 = Hpos.get_line(x);
	stringstream ppp; ppp << line43; 
	string holder;  ppp >> holder; 
	if(holder == "H")
	{
	double av, bv, cv; ppp >> av; ppp >> bv; ppp>>cv;
	hx[x-1]=av*V_base[0][0]+bv*V_base[1][0]+cv*V_base[2][0]; 
	hy[x-1]=av*V_base[0][1]+bv*V_base[1][1]+cv*V_base[2][1]; 
	hz[x-1]=av*V_base[0][2]+bv*V_base[1][2]+cv*V_base[2][2];
	

	}	
}



// create oh vectors and angles	
for( int x =1; x<=num_its; x++)
{
	for(int ii =1; ii <=numO; ii++)
	{
		int hi = ii + (x - 1)*(numO+2); 
		
		double  rmin = 10000; 
		double ohx, ohy, ohz; 
		int Oindex=0; 
			for(int oo =1; oo<=numO; oo++)
			{
			int oi = oo  + (x-1)*(numO+2);
				for(int i =1; i<=3; i++)
				{
				for(int j=1; j<=3; j++)
				{
				for(int k=1; k<=3; k++)
				{
						int ip, jj, kk; ip=i-2; jj=j-2; kk=k-2;
						double ohxt, ohyt, ohzt;
						ohxt= hx[hi] -  (ox[oi]+ip*V_base[0][0]);
						ohyt= hy[hi] - (oy[oi]+jj*V_base[1][1]);
						ohzt= hz[hi]- (oz[oi]+kk*V_base[2][2]); 
						double rt = sqrt(ohxt*ohxt + ohyt*ohyt + ohzt*ohzt);
						
						if(rt<rmin)
						{
							rmin=rt; ohx = ohxt; ohy=ohyt; ohz=ohzt;
							Oindex = oo; 
								
						}					
				}
				}
				}
			}
			
		if(ii<38&&x<2){cout << "\n" << Oindex << "\t" << rmin;}
			
		

		double mag = sqrt(ohx*ohx+ohy*ohy+ohz*ohz);
		ohx=ohx/mag;
		ohy=ohy/mag;
		ohz=ohz/mag;
		double h1 = 0;
		double xx = ohx;double yy = ohy;
		//double avg_theta, avg_phi; 
		if(xx==0||yy==0){cout << "\n" << hx[hi];}
		if(xx<=0&&yy>=0){h1=atan(yy/xx) + 3.1416;}
		if(xx<=0&&yy<=0){h1=atan(yy/xx) + 3.1416;}
		if(xx>=0&&yy<=0){h1=atan(yy/xx)+ 2*3.1416;}
		if(xx>=0&&yy>=0){h1=atan(yy/xx);}
	
		double h2 = acos(ohz);
		//if(ohz[x-1]<0){cout << "\n" <<ohz[x-1];}
		Theta.push_back(h1);
		Phi.push_back(h2);
	}

}

//end create OH and angles

double tmax,tmin,pmax,pmin; tmax=-1000;tmin=1000;pmax=-100; pmin=1000;
for(unsigned int x =1; x<=Theta.size(); x++)
{
	if(Theta[x-1]<tmin){tmin=Theta[x-1];}
	if(Theta[x-1]>tmax){tmax=Theta[x-1];}
	if(Phi[x-1]<pmin){pmin=Phi[x-1];}
	if(Phi[x-1]>pmax){pmax=Phi[x-1];}
}
int bn = 400;
double hist_theta[bn],bin_center_theta[bn];
double hist_phi[bn],bin_center_phi[bn];
double bin_width_theta = (tmax-tmin)/bn;
double bin_width_phi = (pmax-pmin)/bn;

for(int x =1; x<=bn; x++)
{
	hist_theta[x-1]=0;hist_phi[x-1]=0;
	bin_center_theta[x-1]=0.5*bin_width_theta + (x-1)*bin_width_theta+tmin;
	bin_center_phi[x-1]=0.5*bin_width_phi + (x-1)*bin_width_phi+pmin;
}

for(unsigned int x =1; x<=Theta.size(); x++)
{
	int b1,b2; 
	b1 = floor((Theta[x-1]-tmin)/bin_width_theta);
	b2 = floor((Phi[x-1]-pmin)/bin_width_phi);	
	hist_theta[b1]=hist_theta[b1]+1;
	hist_phi[b2]=hist_phi[b2]+1;
}

file hist_OH; 
double sz = Theta.size();
for(int x =1; x<=bn; x++)
{
	string holdern; string lineoutn;
	stringstream jh; 
	jh <<(180/3.1416)*bin_center_theta[x-1]; jh >> lineoutn;
	jh.clear();jh.str("");
	jh << hist_theta[x-1]/sz; jh >> holdern; lineoutn = lineoutn + "\t" + holdern; 
	jh.clear();jh.str("");
	jh << (180/3.1416)*bin_center_phi[x-1]; jh >> holdern; lineoutn = lineoutn + "\t" + holdern;
	jh.clear();jh.str("");
	jh << hist_phi[x-1]/sz; jh >> holdern; lineoutn = lineoutn + "\t" + holdern; 
	hist_OH.add_line(lineoutn);
	
}
hist_OH.make_file("OH_angles_hist");




return 0;
}
