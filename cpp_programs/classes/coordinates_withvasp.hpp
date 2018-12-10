/*
the coordinates class abbreviated as coord
this class is being designed to streamline some of the basic coordinate file manipulations needed for writing programs
for dealing with coordinates. Its assumes a simple from for the input file of the coordinates as

particle name 1  x-coordinate y-coordinate z-coordinate
particle name 2  x-coordinate y-coordinate z-coordinate
......

*/



#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


class coord
{
public:
	//constructors
	coord();
	coord(string filename);
        coord(string  filename, string vasp); 
	~coord();
	//manipulator functions
		// these functions allow adding atoms to the coordinates
		void add_atom_name(string atom_name){atom_lbl.push_back(atom_name);}
		void add_atom_xcoord(double set_coord){x_coord.push_back(set_coord);}
		void add_atom_ycoord(double set_coord){y_coord.push_back(set_coord);}
		void add_atom_zcoord(double set_coord){z_coord.push_back(set_coord);}
		void  make_file(string file_name)
		{
		ofstream  out_file(file_name.c_str());
		if(out_file.is_open())
		{
			for(unsigned int x=1; x<=atom_lbl.size();x++)
			{
			
				
				out_file << atom_lbl[x-1] << "\t" << x_coord[x-1]<<"\t"<< y_coord[x-1 ]<< "\t" << z_coord[x-1];
				if(x <=atom_lbl.size())
				{out_file<< "\n";}
				
			}
			out_file.close();
		}
		else {cout << "\n" << "The file you tried to make named:  " << file_name << "  did not open properly\n";}
		}
		void make_file(string file_name, string vasp)
		{
			 ofstream  out_file(file_name.c_str());
                if(out_file.is_open()&&vasp=="vasp")
                {
                        for(unsigned int x=1; x<=atom_lbl.size();x++)
                        {


                                out_file  << x_coord[x-1]<<"\t"<< y_coord[x-1 ]<< "\t" << z_coord[x-1] << "\t" << atom_lbl[x-1];
                                if(x <=atom_lbl.size())
                                {out_file<< "\n";}

                        }
                        out_file.close();
                }
                else {cout << "\n" << "The file you tried to make named:  " << file_name << "  did not open properly\n";}

		}
		// these functions allow replacing a current coordinate with a new one
		void set_atom_name(int atm_num, string atom_name){ atom_lbl[atm_num-1]=atom_name;}
		void set_xcoord(int atm_num, double set_coord){ x_coord[atm_num-1]= set_coord;}
		void set_ycoord(int atm_num, double set_coord){ y_coord[atm_num-1]=set_coord;}
		void set_zcoord(int atm_num, double set_coord){ z_coord[atm_num-1]=set_coord;}
	//accessor functions
		// accessors that get # of coordinates along with access to name and value of specified coordinates
		int get_num_atoms() const { return atom_lbl.size();}
		string get_name(int atom_num) {return atom_lbl[atom_num-1];}
		double get_xcoord(int atom_num){return x_coord[atom_num-1];}
		double get_ycoord(int atom_num){return y_coord[atom_num-1];}
		double get_zcoord(int atom_num){return z_coord[atom_num-1];}

private:
	vector<string> atom_lbl;
	vector<double> x_coord;
	vector<double> y_coord;
	vector<double> z_coord;
};
coord::coord()
{
//	atom_lbl.push_back("");
//	x_coord.push_back(0);
//	y_coord.push_back(0);
//	z_coord.push_back(0);
/*
		cout << "\n default constructor called\n";
		cout << "atom label: " << atom_lbl[0]<<"\n";
		cout << "x_coord: " << x_coord[0] << "\n";
		cout << "y_coord: " << y_coord[0] << "\n";
		cout << "z_coord: " << z_coord[0] << "\n";
*/
}


coord::coord(string filename)
{
	string name;
	string line;
	double n;
	ifstream c_file(filename.c_str());
if (c_file.is_open())
{
	while ( getline (c_file,line))              
		{ 
			istringstream iss(line);             
			for(int x=0; x<4 ; x++)            
			{
				if(x==0)
				{iss>>name; atom_lbl.push_back(name);}               

				if (x==1)
				{iss>>n;  x_coord.push_back(n);}  
	
				if (x==2)
				{iss>>n;  y_coord.push_back(n);}
			
				if (x==3)
				{iss>>n; z_coord.push_back(n);}
			}	
		} 
c_file.close();
}
else{ cout << "\n\nThe file containing your coordinates failed to open\n";}
}
// constructor for vasp coordinates
coord::coord(string filename,string vasp)
{
        string name;
        string line;
        double n;
        ifstream c_file(filename.c_str());
if (c_file.is_open())
{
        while ( getline (c_file,line))
                {
                        istringstream iss(line);
			if(vasp == "vasp"){
                        for(int x=0; x<4 ; x++)
                        {
                            

                                if (x==0)
                                {iss>>n;  x_coord.push_back(n);}

                                if (x==1)
                                {iss>>n;  y_coord.push_back(n);}

                                if (x==2)
                                {iss>>n; z_coord.push_back(n);}
				if(x==3)
                                {iss>>name; atom_lbl.push_back(name);}

                        }
			}
                }
c_file.close();
}
else{ cout << "\n\nThe file containing your coordinates failed to open\n";}
}

coord::~coord()
{
	// cout << "\ndefault destructor called\n";
}


