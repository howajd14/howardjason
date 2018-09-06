#include "../classes/file_class/file.hpp"
#include "../classes/coordinates_class/coordinates.hpp"
#include<math.h>
using namespace std;

int main()
{

// first read a file with the lattice vectors with the first line having the multiplier for the vectors
//string lattice_vecs;
//cout << "\nWhat is the name of your file with the lattice vectors, first line whould have multiplier. Make sure the multiplier is in angstroms    ";
//cin >> lattice_vecs;
file  lat_vecs("lattice_vector");  
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
//string  Li_site_types;
//cout << "\nWhat is the name of your ion positions file name?    " ;
//cin >> Li_site_types;
coord  Li_sites("sites");

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
//string Li_site_labels;
//cout << "\nWhat is the name of the file with your ion site labels for the ion site pos list?   ";
//cin >> Li_site_labels;
file   Li_labels("site_labels");
vector<string> ion_site_labels;
for(int t = 1; t <=Li_labels.num_lines(); t++)
{
	string line_here = Li_labels.get_line(t);
	ion_site_labels.push_back(line_here);
}

//next a file is needed just for the site label types;
//string site_label_types;
//cout << "\nWhat is the name of the file with your site label types?    ";
//cin >> site_label_types;
file  site_labels_file("site_label_types");
vector<string> site_labels_vec;
for(int l =1; l<=site_labels_file.num_lines(); l++)
{
		string line = site_labels_file.get_line(l);
		site_labels_vec.push_back(line);
}
int num_site_labels = site_labels_file.num_lines();

//ask for the number of atoms in the simulation
int num_atoms=54;
//cout << "\nHow many atoms?  "; 
//cin  >> num_atoms; 

//next a file is needed for the Li_positions over time
//string Li_positions_ovr_time;
//cout << "\nWhat is the name of the file with your ion positions over time?   ";
//cin >> Li_positions_ovr_time;
file   Li_positions("Lipos");

int num_iterations = (Li_positions.num_lines()+1)/(num_atoms+2);

//get the cut off radius for determining site types 
double cut_r=50;
//cout << "\nWhat is your desired cut-off radius for determining site type?  ";
//cin >> cut_r;


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
	
	//loop to make lines for which specific site the the atom is time to time
	for(int uu =1 ; uu <= num_iterations ; uu++)
	{		
			
			stringstream ht ; ht << temp_site_num[uu-1];string line908; ht >> line908; 
			instant_occupancy.add_line(line908);
		
	}// end loop to make line for where atom is time to time
	
	stringstream ui;  ui << y; string holder87; ui >> holder87; 
	string line6_filename = "atom" + holder87 + "instant_occ"; 
	
        instant_occupancy.make_file(line6_filename);

}//end looping over the number of atoms 




//file  frac_occ_t;
file time_avg_order_parameter;

// loop to compute the frac occupancy as function of time and place in file 
// also makes a file for the integrated time average frac occ
//double site_count[Li_sites.get_num_atoms()];for(int rt=1; rt<=Li_sites.get_num_atoms(); rt++){site_count[rt-1]=0;}

	//double  frac_ovr_time[num_site_labels];for(int pol=1; pol<=num_site_labels; pol++){frac_ovr_time[pol-1]=0;}


	
for(int yt =1; yt <=num_atoms; yt++)
{
	file site_count; for(int x =1 ; x<= num_iterations; x++)
		{
			string linezeros="0"; 
			for(int kj = 1; kj<=Li_sites.get_num_atoms()-1; kj++)
			{
				linezeros = linezeros + " 0";
			}
	
			site_count.add_line(linezeros);
		}

	cout << "\natom#" << yt ; 
	stringstream ry; string holder82; ry << yt; ry >> holder82;
	string file_name90 = "atom" + holder82 + "instant_occ";
	file  temp4_instant_occupancy(file_name90);
		for(int ip = 1; ip <= num_iterations; ip++)
		{
			
			vector<int> temp_site_counts;
			if(ip==1)
			{
				string site_counts = site_count.get_line(ip);
				stringstream peel_sites; peel_sites << site_counts; 
				for(int ll =1; ll<=Li_sites.get_num_atoms();ll++)
				{
					int holdernow;  peel_sites >> holdernow; 
					temp_site_counts.push_back(holdernow);
				}
		
				string line77 = temp4_instant_occupancy.get_line(ip);
				stringstream ity; ity << line77; int holdertty; 
				ity >> holdertty; 
				temp_site_counts[holdertty-1] = temp_site_counts[holdertty-1] + 1; 
			}
			if(ip>1)
			{
				 
				string site_counts = site_count.get_line(ip-1);
				stringstream peel_sites; peel_sites << site_counts; 
				for(int ll =1; ll<=Li_sites.get_num_atoms();ll++)
				{
					int holdernow;  peel_sites >> holdernow; 
					temp_site_counts.push_back(holdernow);
				}
				
			
				
				string line77 = temp4_instant_occupancy.get_line(ip);
				stringstream ity; ity << line77; int holdertty; 
				ity >> holdertty; 
				temp_site_counts[holdertty-1] = temp_site_counts[holdertty-1] + 1; 
			}

			string new_site_counts = "";
			for(int re =1; re <=Li_sites.get_num_atoms();re++)
			{
				stringstream nws; nws << temp_site_counts[re-1]; string holdnw; 
				nws >> holdnw; 
				if(re!=Li_sites.get_num_atoms()){new_site_counts=new_site_counts + holdnw +" ";}
				if(re==Li_sites.get_num_atoms()){new_site_counts=new_site_counts + holdnw;}
			}
		
			site_count.set_line(ip,new_site_counts);
		}
	ry.clear();ry.str("");
	string  site_count_file_name = "site_count_atom#"; 
	string dss;  ry << yt; ry >> dss;  site_count_file_name = site_count_file_name + dss; 
	site_count.make_file(site_count_file_name);

}

file total_site_count; for(int x =1 ; x<= num_iterations; x++)
		{
			string linezeros="0"; 
			for(int kj = 1; kj<=Li_sites.get_num_atoms()-1; kj++)
			{
				linezeros = linezeros + " 0";
			}
	
			total_site_count.add_line(linezeros);
		}

for(int x =1; x<=num_atoms; x++)
{
	string flnme = "site_count_atom#"; stringstream qw; qw << x; string hlder7; qw >> hlder7; flnme = flnme + hlder7; 
	file  site_count_atom(flnme);
	for(int yy =1 ; yy<=num_iterations; yy++)
	{
		string total_counts, atom_counts;
		total_counts = total_site_count.get_line(yy); atom_counts = site_count_atom.get_line(yy);
		string new_total=""; 
		stringstream peel1; stringstream peel2; 
		peel1 << total_counts; peel2 << atom_counts; 
		for(int op =1; op <= Li_sites.get_num_atoms(); op++)
		{
			int tt1, at1;  peel1 >> tt1; peel2 >> at1; 
			int new_t = at1 + tt1; 
			stringstream yut; yut << new_t ; string otnw; yut >> otnw; 
			if(op!=Li_sites.get_num_atoms()){new_total=new_total + otnw + " ";}
			if(op==Li_sites.get_num_atoms()){new_total=new_total + otnw;}
		}
		total_site_count.set_line(yy,new_total);
	}
}

for(int oo =1 ; oo <= num_iterations; oo++)
{
	double order_parameter = 0; 
	string  site_counts = total_site_count.get_line(oo);
	vector<int> site_count_vec;
	stringstream  hgf;  hgf << site_counts; 
	for(int ew =1 ; ew <= Li_sites.get_num_atoms(); ew++)
	{
		int temp; hgf >> temp;  site_count_vec.push_back(temp);
	}
	
	for(int hgy =1; hgy <= Li_sites.get_num_atoms(); hgy++)
	{
		order_parameter = order_parameter + sqrt(((2.0/3.0)- 1.0*site_count_vec[hgy-1]/(1.0*oo))*((2.0/3.0)- 1.0*site_count_vec[hgy-1]/(1.0*oo)));
	}
	order_parameter = order_parameter/(Li_sites.get_num_atoms()*1.0);
	stringstream nbv; nbv << oo; string outlinefinal; string holderfinal; nbv >> outlinefinal; 
	nbv.clear();nbv.str(""); nbv << order_parameter;  nbv >> holderfinal; outlinefinal = outlinefinal + "\t" + holderfinal; 
	time_avg_order_parameter.add_line(outlinefinal);
	

}	
		

// end loop for making file object of frac occ of t


time_avg_order_parameter.make_file("time_avg_order_parameter");




return 0;
}
