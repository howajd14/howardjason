#include "../../../../../../cpp_programs/classes/file_class/file.hpp"
using namespace std; 

int main()
{
int num_files=0; 
string outname=""; 
cout << "\nHow many files?\n"; 
cin >> num_files; 
cout << "\nWhat is the out file name?\n";
cin >> outname; 
file outfile1; file outfile2; 

for(int x=1; x<=num_files; x++)
{
	stringstream ss; ss << x; string holder; ss >> holder; 
	string filename = "run" + holder + "/" + outname; 
	ss.clear();ss.str(""); 
	file  datafile(filename); 
	double force =0; 
	for(int y=1; y<= datafile.num_lines(); y++)
	{
		string  lne = datafile.get_line(y); 
		ss << lne;  string holdline; ss >> holdline; 
		if(holdline == "Total")
		{
			string burner; ss >> burner; ss >> burner; 
			ss >> force; 
		}
	}
	if(force > 0.00005)
	{
		ss.clear();ss.str(""); 
		ss << force; string hold2; ss >> hold2;
		string outline1 = holder + "\t" + hold2;  
		outfile1.add_line(outline1); 
	}
	ss.clear();ss.str(""); 
	string outline2; ss << force; ss >> outline2; 
	outfile2.add_line(outline2); 
}
if(outfile1.num_lines()>0)
{
	outfile1.make_file("Forces_to_high"); 
}
outfile2.make_file("All_Forces"); 
return 0; 
}
