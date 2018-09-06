/*
This is the File class meant to stream line file operations

The basic premise of this class are methods designed to alter and retrieve information
from a vector<string> that contains the information about a users desired file. The entire file
will be in-effect stored line by line in the vector. 
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class file
{
public:
	//constructors
	file();
	file(string file_name);
	~file();
	//manipulator functions
	void add_line(string line)
	{ 
		file_vector.push_back(line); line_num = file_vector.size(); 
		//ofstream  new_file("untitled.txt")
	}
	void set_line(int line_num , string line)
	{
		//cout << "\n" << line_num;
		if(line_num<=num_lines())
		{
		file_vector[line_num-1]=line;
		}
		else{cout << "\nyour file has less lines than requested\n";}
	}
	void set_line_num(int line_number){line_num=line_number;}
	void insert_line(unsigned int line_number, string line)
	{
		string holder1;
		string holder2;
		unsigned int file_length = file_vector.size();
		for(unsigned int x= line_number; x<=file_length+1; x++)
		{
			if(x==line_number)
			{
				holder1=file_vector[x-1]; 
				file_vector[x-1]=line;
			}
			if(x<file_vector.size())
			{
				holder2=file_vector[x];
				file_vector[x]=holder1;
				holder1=holder2;
			}
			if(x==file_vector.size()+1)
			{
				file_vector.push_back(holder1);
			}
		}
	}
	void  make_file(string file_name)
	{
		ofstream  out_file(file_name.c_str());
		if(out_file.is_open())
		{
			for(unsigned int x=1; x<=file_vector.size();x++)
			{
			
				
				out_file << file_vector[x-1];
				if(x <=file_vector.size())
				{out_file<< "\n";}
				
			}
			out_file.close();
		}
		
		else {cout << "\n" << "The file you tried to make named:  " << file_name << "  did not open properly\n";}
	}
	//accessor functions
	string current_line(){return file_vector[line_num];}
	string next_line(){return file_vector[++line_num];}
	string get_line(unsigned int line_number)
		{
			if(line_number <= file_vector.size())
				{line_num=line_number; return file_vector[line_number-1];} 
			else {cout << "\n\nfile has less lines then line # requested\n\n" << line_number << "\n" ; return "0";}
		}
	int    current_line_num(){return line_num;}
	int    num_lines(){return file_vector.size();}
private:	
	int    line_num;
	vector<string> file_vector;
};
//****** default constructor *****************
file::file()
{
//file_vector.push_back("0");
line_num=0;
}

//****** overloaded constructor ****************
file::file(string file_name)
{
	string line;
	line_num = 0;
	ifstream my_file(file_name.c_str());
	

	if(my_file.is_open())
	{
		while(getline(my_file,line)){file_vector.push_back(line);}
		my_file.close();

	}
	else{cout << "\n\nYour file failed to open\n\n";}

}
file::~file()
{}
