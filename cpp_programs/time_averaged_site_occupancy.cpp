#include "../classes/file_class/file.hpp"
#include "../cpp_programs/classes/coordinates_class/coordinates.hpp"
#include<math.h>
using namespace std;

int main()
{

// first read a file with the lattice vectors with the first line having the multiplier for the vectors
string lattice_vecs;
cout << "\nWhat is the name of your file with the lattice vectors, first line whould have multiplier. Make sure the multiplier is in angstroms    ";
cin >> lattice_vecs;
file  lat_vecs(lattice_vecs);  
double V_base[3][3],multiplier;

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

//next a file is needed for the possible Li sites; 
string  Li_site_types;
cout << "\nWhat is the name of your ion positions file name?    " ;
cin >> Li_site_types;
coord  Li_sites(Li_site_types);

//convert the possible Li sites from fractional to real space coordinates;
for(int x=1; x<=Li_sites.get_num_atoms(); x++)
{
		if(Li_sites.get_xcoord(x)>1||Li_sites.get_xcoord(x)<0){Li_sites.set_xcoord(x,Li_sites.get_xcoord(x)-floor(Li_sites.get_xcoord(x)));}
		if(Li_sites.get_ycoord(x)>1||Li_sites.get_ycoord(x)<0){Li_sites.set_ycoord(x,Li_sites.get_ycoord(x)-floor(Li_sites.get_ycoord(x)));}
		if(Li_sites.get_zcoord(x)>1||Li_sites.get_zcoord(x)<0){Li_sites.set_zcoord(x,Li_sites.get_zcoord(x)-floor(Li_sites.get_zcoord(x)));}
		
		double x_p, y, z;
		x_p = Li_sites.get_xcoord(x)*V_base[0][0] + Li_sites.get_ycoord(x)*V_base[1][0] + Li_sites.get_zcoord(x)*V_base[2][0];
		y = Li_sites.get_xcoord(x)*V_base[0][1] + Li_sites.get_ycoord(x)*V_base[1][1] + Li_sites.get_zcoord(x)*V_base[2][1];
		z = Li_sites.get_xcoord(x)*V_base[0][2] + Li_sites.get_ycoord(x)*V_base[1][2] + Li_sites.get_zcoord(x)*V_base[2][2];
		Li_sites.set_xcoord(x,x_p);Li_sites.set_ycoord(x,y);Li_sites.set_zcoord(x,z);
}

//next a file is needed for the Li site labels make a vector string with the site labels
string Li_site_labels;
cout << "\nWhat is the name of the file with your ion site labels for the ion site pos list?   ";
cin >> Li_site_labels;
file   Li_labels(Li_site_labels);
vector<string> ion_site_labels;
for(int t = 1; t <=Li_labels.num_lines(); t++)
{
	string line_here = Li_labels.get_line(t);
	ion_site_labels.push_back(line_here);
}

//next a file is needed just for the site label types;
string site_label_types;
cout << "\nWhat is the name of the file with your site label types?    ";
cin >> site_label_types;
file  site_labels_file(site_label_types);
vector<string> site_labels_vec;
for(int l =1; l<=site_labels_file.num_lines(); l++)
{
		string line = site_labels_file.get_line(l);
		site_labels_vec.push_back(line);
}
int num_site_labels = site_labels_file.num_lines();

//ask for the number of atoms in the simulation
int num_atoms;
cout << "\nHow many atoms?  "; 
cin  >> num_atoms; 

//next a file is needed for the Li_positions over time
string Li_positions_ovr_time;
cout << "\nWhat is the name of the file with your ion positions over time?   ";
cin >> Li_positions_ovr_time;
file   Li_positions(Li_positions_ovr_time);

int num_iterations = Li_positions.num_lines()/(num_atoms+2);

//get the cut off radius for determining site types 
double cut_r;
cout << "\nWhat is your desired cut-off radius for determining site type?  ";
cin >> cut_r;


for(int y=1; y<=num_atoms;y++)	//loop over each atom and a time and track its progress
{
	cout << "\natom num:  " << y; 
	int  temp_site_num[num_iterations];
	string  temp_site_label[num_iterations];
	for (int x=1; x<=num_iterations; x++)//track the atomes progress over the iterations
	{
			int site_num=0; string site_type="u"; double R_min = 100;
			
			for(int k=1; k<=Li_sites.get_num_atoms();k++) // find out which site is occupied
			{
				string  lineH;
				lineH = Li_positions.get_line((num_atoms+2)*(x-1)+y+1);
				double v1frac,v2frac,v3frac,v1,v2,v3;
				stringstream jj; string burner;
				jj << lineH; jj >> burner; jj>>v1frac;jj>>v2frac;jj>>v3frac;
				if(v1frac > 1){v1frac = v1frac - floor(v1frac/1);}
				if(v1frac < 0){v1frac = v1frac - floor(v1frac/1);}
				if(v2frac > 1){v2frac = v2frac - floor(v2frac/1);}
				if(v2frac < 0){v2frac  = v2frac - floor(v2frac/1);}
				if(v3frac >1){v3frac = v3frac -floor(v3frac/1);}
				if(v3frac< 0){v3frac = v3frac -floor(v3frac/1);}
				v1 = v1frac*V_base[0][0] + v2frac*V_base[1][0] + v3frac*V_base[2][0];
				v2 = v1frac*V_base[0][1] + v2frac*V_base[1][1] + v3frac*V_base[2][1];
				v3 = v1frac*V_base[0][2] + v2frac*V_base[1][2] + v3frac*V_base[2][2];

				
				double R=1000;
				double  Li_x, Li_y, Li_z; 
				Li_x = Li_sites.get_xcoord(k);  Li_y = Li_sites.get_ycoord(k);  Li_z = Li_sites.get_zcoord(k);
			        for(int ww=1; ww<=27; ww++)
				{
				int a,b,c;
				if(ww==1){a=0;b=0;c=0;}
				if(ww==2){a=1;b=0;c=0;}
				if(ww==3){a=0;b=1;c=0;}
				if(ww==4){a=0;b=0;c=1;}
				if(ww==5){a=1;b=1;c=0;}
				if(ww==6){a=0;b=1;c=1;}
				if(ww==7){a=1;b=0;c=1;}
				if(ww==8){a=-1;b=0;c=0;}
				if(ww==9){a=0;b=-1;c=0;}
				if(ww==10){a=0;b=0;c=-1;}
				if(ww==11){a=-1;b=-1;c=0;}
				if(ww==12){a=-1;b=0;c=-1;}
				if(ww==13){a=0;b=-1;c=-1;}
				if(ww==14){a=-1;b=-1;c=-1;}
				if(ww==15){a=1;b=-1;c=0;}
				if(ww==16){a=-1;b=1;c=0;}
				if(ww==17){a=0;b=-1;c=1;}
				if(ww==18){a=0;b=1;c=-1;}
				if(ww==19){a=-1;b=0;c=1;}
				if(ww==20){a=1;b=0;c=-1;}
				if(ww==21){a=-1;b=1;c=1;}
				if(ww==22){a=1;b=-1;c=1;}
				if(ww==23){a=1;b=1;c=-1;}
				if(ww==24){a=-1;b=-1;c=1;}
				if(ww==25){a=-1;b=1;c=-1;}
				if(ww==26){a=1;b=-1;c=-1;}
				if(ww==27){a=1;b=1;c=1;}
				
				v1 = (v1frac+a)*V_base[0][0] + (v2frac+b)*V_base[1][0] + (v3frac+c)*V_base[2][0];
				v2 = (v1frac+a)*V_base[0][1] + (v2frac+b)*V_base[1][1] + (v3frac+c)*V_base[2][1];
				v3 = (v1frac+a)*V_base[0][2] + (v2frac+b)*V_base[1][2] + (v3frac+c)*V_base[2][2];
				R=sqrt((v1-Li_x)*(v1-Li_x)+(v2-Li_y)*(v2-Li_y)+(v3-Li_z)*(v3-Li_z));
					if(R<cut_r&&R<R_min)
					{
					    site_num = k; 
					    site_type = ion_site_labels[k-1];
					    R_min = R; 
					   
					}
				}
				
				
			}// end find out which site is occupied 
		
		temp_site_num[x-1]=site_num; 
		temp_site_label[x-1]=site_type;
		
				
	}  //end looping over the iterations 	


	file instant_occupancy; // file for storing frac occupancy of a atom
	
	//loop to make lines for where the atom is time to time
	for(int uu =1 ; uu <= num_iterations ; uu++)
	{		
			
			double instant_label[num_site_labels]; for(int llk = 0; llk <num_site_labels; llk++){instant_label[llk]=0;}
			for(int uui =1; uui<=num_site_labels; uui++)
			{
				if(site_labels_vec[uui-1]==temp_site_label[uu-1]){instant_label[uui-1]=1;}
			}
					
			string line98; 
			string holder98; 
			for(int er=0; er<=num_site_labels; er++)
			{
				stringstream ht; 
				if(er==0){ht << uu; ht >> line98;}
				if(er>0)
				{
					ht << instant_label[er-1]; 
					ht >> holder98; line98 = line98 + "\t" + holder98;
					 
				}
			}
			instant_occupancy.add_line(line98);
		
	}// end loop to make line for where atom is time to time
	
	stringstream ui;  ui << y; string holder87; ui >> holder87; 
	string line6_filename = "atom" + holder87 + "instant_occ"; 
	
        instant_occupancy.make_file(line6_filename);

}//end looping over the number of atoms 




file  frac_occ_t;
file time_avg_frac_occ;

// loop to compute the frac occupancy as function of time and place in file 
// also makes a file for the integrated time average frac occ
double int_frac_occ_t[num_site_labels];for(int rt=1; rt<=num_site_labels; rt++){int_frac_occ_t[rt-1]=0;}
for(int ip = 1; ip <= num_iterations; ip++)
{
	double  frac_ovr_time[num_site_labels];for(int pol=1; pol<=num_site_labels; pol++){frac_ovr_time[pol-1]=0;}
	
	//
	for(int yt =1; yt <=num_atoms; yt++)
	{
		stringstream ry; string holder82; ry << yt; ry >> holder82;
		string file_name90 = "atom" + holder82 + "instant_occ";
		file  temp4_instant_occupancy(file_name90);
		string line77 = temp4_instant_occupancy.get_line(ip);
		string burner53;  ry.clear(); ry.str(""); 
		ry << line77; 
		ry >>  burner53; 
		for(int vx =1 ; vx <= num_site_labels; vx++)
		{
			double holder891; ry >>  holder891; frac_ovr_time[vx-1]=frac_ovr_time[vx-1]+holder891;
			int_frac_occ_t[vx-1]=int_frac_occ_t[vx-1] + holder891;
		}


	}
	string line_tot_frac, line_time_avg_frac_occ;
	for(int jlk=0; jlk<=num_site_labels; jlk++)
	{
		string holder834, holder786;
		stringstream kli; 
		if(jlk==0){kli << ip; kli>>holder834;  line_tot_frac = holder834; line_time_avg_frac_occ=holder834;}
		if(jlk>0)
		{
			kli << frac_ovr_time[jlk-1]/num_atoms; kli >> holder834; line_tot_frac = line_tot_frac + "\t" + holder834; 
			kli.clear(); kli.str("");
			if(ip>1)
			{
				kli << int_frac_occ_t[jlk-1]/(num_atoms*(ip)); kli >> holder786; line_time_avg_frac_occ = line_time_avg_frac_occ + "\t" + holder786; 
			}
		}
	}
		frac_occ_t.add_line(line_tot_frac);
		if(ip>1){time_avg_frac_occ.add_line(line_time_avg_frac_occ);}
		

}// end loop for making file object of frac occ of t

frac_occ_t.make_file("frac_occupancy_over_time");
time_avg_frac_occ.make_file("time_avg_frac_occupancy");




return 0;
}
