#include "../../../../../cpp_programs/classes/file_class/file.hpp"
using namespace std; 

int main()
{
int num_files; 
cout << "\nhow many files?\n";
cin >> num_files; 
file outfile;

for(int x = 1; x<=num_files; x++)
{

	stringstream ss; ss << x; string holdit; ss >> holdit; 
	string file1 = "vec" + holdit;  file  vec1(file1); 
       vector<int> data; data.push_back(0);
	for (int y=1; y<=num_files; y++)
	{
		ss.clear();ss.str(""); ss << y; ss >> holdit; 
		ss.clear();ss.str(""); 
		string file2 = "vec" + holdit; file vec2(file2);
		int dot =0; 
		for(int ii=1; ii<=vec1.num_lines(); ii++)
		{
			int a,b;  ss << vec1.get_line(ii); ss >> a; 
			ss.clear(); ss.str("");  ss << vec2.get_line(ii); ss >> b; 
			dot = dot + a*b; 
			ss.clear(); ss.str(""); 
		}
		if(dot==16){data[0]=data[0]+1; data.push_back(y); 
	}
	ss.clear();ss.str(""); string outline = ""; 
	for(unsigned int kk=1; kk<=data.size(); kk++)
	{
	 string holder;  ss << data[kk-1]; 
	 ss >> holder; outline = outline + holder + "\t"; 
	ss.clear(); ss.str(""); 
	}
	outfile.add_line(outline); 
}

outfile.make_file("vec_dot_info"); 
return 0; 
}
