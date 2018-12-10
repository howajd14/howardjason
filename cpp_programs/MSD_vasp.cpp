#include "classes/file.hpp"
#include "classes/coordinates.hpp"
#include<math.h>
using namespace std;

int main()
{


string lat_vec_file;
cout << "\nwhat is your lattice vectors file name\n";
cin >> lat_vec_file; 
file lat_vecs(lat_vec_file); 

double v1 [3];  
double v2 [3];  
double v3 [3]; 
double AA=0; 

for(int x=1 ; x<=lat_vecs.num_lines() ; x++)
{
	if(x==1)
	{
		string lineHH = lat_vecs.get_line(x); 
		stringstream jll; jll << lineHH; jll>>AA; 
	}
	if(x==2)
	{
		string linell = lat_vecs.get_line(x);
		stringstream kjj; kjj << linell; 
		double holder; 
		kjj >> holder; v1[0]=holder*AA; 
		kjj >> holder; v1[1]=holder*AA; 
		kjj >> holder; v1[2]=holder*AA; 
	}
	if(x==3)
	{
		string linell = lat_vecs.get_line(x);
		stringstream kjjj; kjjj << linell; 
		double holder; 
		kjjj >> holder; v2[0]=holder*AA; 
		kjjj >> holder; v2[1]=holder*AA; 
		kjjj >> holder; v2[2]=holder*AA; 
	}
	if(x==4)
	{
		string linell = lat_vecs.get_line(x);
		stringstream kjjjj; kjjjj << linell; 
		double holder; 
		kjjjj >> holder; v3[0]=holder*AA; 
		kjjjj >> holder; v3[1]=holder*AA; 
		kjjjj >> holder; v3[2]=holder*AA; 
	}
} 


string file_name;
cout << "\nWhat is the name of you atomic positions file?";
cin >> file_name;

file Li_positions(file_name);

int num_atoms;
cout << "\nHow many atoms?";
cin >> num_atoms;

int num_ensembles;
cout << "\nHow many ensembles?";
cin >> num_ensembles;
double dt ;
cout << "\nWhat is your dt?";
cin >> dt; 
dt = dt*0.048;

int num_iterations = Li_positions.num_lines()/(num_atoms+2);
cout << "\nnum_iterations:   " << num_iterations;

double MSD[num_iterations-num_ensembles]; for(int y=0; y<num_iterations-num_ensembles; y++){MSD[y]=0;}
double MSD_vec[num_iterations-num_ensembles][3];  for(int y=0; y<num_iterations-num_ensembles; y++){MSD_vec[y][0]=0;MSD_vec[y][1]=0;MSD_vec[y][2]=0;}

int countt = 0 ; 
for(int x =1 ; x<= num_ensembles; x++)
{
		coord first_coords;
		for(int vv = 1; vv<=num_atoms; vv++)
		{
			string line1;
			line1 = Li_positions.get_line(vv+1+(x-1)*(num_atoms+2)); //cout << "\n" << line1;
			stringstream  hh;
			hh << line1; string name; double crds1;
			hh >> name;  first_coords.add_atom_name(name);
			hh >> crds1; first_coords.add_atom_xcoord(crds1);
			hh >> crds1; first_coords.add_atom_ycoord(crds1);
			hh >> crds1; first_coords.add_atom_zcoord(crds1);
		
		}
		  
		for(int y=1; y <= num_iterations - num_ensembles;y++)
		{
			coord second_coords;
			double MSD_coords_avg=0;
			double MSD_coords_avg_vec[3];MSD_coords_avg_vec[0]=0;MSD_coords_avg_vec[1]=0;MSD_coords_avg_vec[2]=0;
			for(int ll = 1; ll <= num_atoms; ll++)
			{
				string line2;
				int line_num2 = ll + 1 + (x-1)*(num_atoms+2) + y*(num_atoms+2); 
				line2 = Li_positions.get_line(line_num2); //cout << "\n" << line2;
				stringstream ii;
				ii << line2; string name; double crds2;
				ii >> name; second_coords.add_atom_name(name); 
				if(name!="#Li"&&countt==0){cout << "\n" << name << "\t" << ll<<"\t"<<line_num2 <<"\t" << y+1; countt++;}
				ii >> crds2; second_coords.add_atom_xcoord(crds2);
				ii >> crds2; second_coords.add_atom_ycoord(crds2);
				ii >> crds2; second_coords.add_atom_zcoord(crds2);

			}

			for(int h=1; h<=first_coords.get_num_atoms();h++)
			{
				
				double first [3];
				double second [3];
				first[0] = first_coords.get_xcoord(h)*v1[0] + first_coords.get_ycoord(h)*v2[0] + first_coords.get_zcoord(h)*v3[0];
				first[1] = first_coords.get_xcoord(h)*v1[1] + first_coords.get_ycoord(h)*v2[1] + first_coords.get_zcoord(h)*v3[1];
		                first[2] = first_coords.get_xcoord(h)*v1[2] + first_coords.get_ycoord(h)*v2[2] + first_coords.get_zcoord(h)*v3[2];
			
				second[0] = second_coords.get_xcoord(h)*v1[0] + second_coords.get_ycoord(h)*v2[0] + second_coords.get_zcoord(h)*v3[0];
				second[1] = second_coords.get_xcoord(h)*v1[1] + second_coords.get_ycoord(h)*v2[1] + second_coords.get_zcoord(h)*v3[1];
		                second[2] = second_coords.get_xcoord(h)*v1[2] + second_coords.get_ycoord(h)*v2[2] + second_coords.get_zcoord(h)*v3[2];
				//cout << "\n" << second[0] << "\t" << second[1] << "\t" << second[2];
	MSD_coords_avg = MSD_coords_avg+ (second[0]-first[0])*(second[0]-first[0]) + (second[1]-first[1])*(second[1]-first[1])+(second[2]-first[2])*(second[2]-first[2]);
//	if((second[0]-first[0])*(second[0]-first[0]) + (second[1]-first[1])*(second[1]-first[1])+(second[2]-first[2])*(second[2]-first[2])>75)
//	{
//		cout << "\n:second  " << h << "\t" << second_coords.get_xcoord(h) << "\t" << second_coords.get_ycoord(h) << "\t" << second_coords.get_zcoord(h); 
//		
//	}
			MSD_coords_avg_vec[0]=MSD_coords_avg_vec[0]+(second[0]-first[0])*(second[0]-first[0]);
			MSD_coords_avg_vec[1]=MSD_coords_avg_vec[1]+(second[1]-first[1])*(second[1]-first[1]);
			MSD_coords_avg_vec[2]=MSD_coords_avg_vec[2]+(second[2]-first[2])*(second[2]-first[2]);
			
			}
			MSD_coords_avg = MSD_coords_avg/num_atoms;
			MSD[y-1]=MSD[y-1]+MSD_coords_avg;
			MSD_vec[y-1][0]=MSD_vec[y-1][0]+MSD_coords_avg_vec[0]/num_atoms;
			MSD_vec[y-1][1]=MSD_vec[y-1][1]+MSD_coords_avg_vec[1]/num_atoms;
			MSD_vec[y-1][2]=MSD_vec[y-1][2]+MSD_coords_avg_vec[2]/num_atoms;
					
		}

		cout << "\nensemble:  " << x;

}
	file out_file;
	file out_file2;
	for(int y=0; y<num_iterations-num_ensembles; y++)
	{
		MSD[y]=MSD[y]/(num_ensembles);
		stringstream ss;
		string holder; string line4;
		ss << (y+1)*dt; ss >> holder; line4 = holder;
		ss.clear();ss.str(""); 
		ss << MSD[y]; ss >> holder; line4 = line4 + "\t" + holder;
		out_file.add_line(line4);

		ss.clear();ss.str(""); string line5;
		ss << (y+1)*dt; ss >> holder; line5 = holder;
		ss.clear(); ss.str("");
		ss << MSD_vec[y][0]/num_ensembles; ss >> holder; line5 = line5 + "\t" + holder;
		ss.clear(); ss.str("");
		ss << MSD_vec[y][1]/num_ensembles; ss >> holder; line5 = line5 + "\t" + holder;
		ss.clear(); ss.str("");
		ss << MSD_vec[y][2]/num_ensembles; ss >> holder; line5 = line5 + "\t" + holder;
		out_file2.add_line(line5);
	}

	out_file.make_file("MSD_unop.dat");
	out_file2.make_file("MSD_xyz_unop.dat");


return 0; 
}
