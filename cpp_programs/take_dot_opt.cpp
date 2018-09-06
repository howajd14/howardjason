#include "../../../../../cpp_programs/classes/file_class/file.hpp"
using namespace std;

int main()
{
int num_files;
cout << "\nhow many files?\n";
cin >> num_files;
file outfile;
int  vectors [num_files][24]; 

for(int x=1; x<=num_files; x++)
{
	stringstream ss; ss << x; string holdit; ss >> holdit;
        string file1 = "vec" + holdit;  file  vec1(file1);
	for (int y=1; y<=vec1.num_lines(); y++)
	{
		ss.clear();ss.str(""); ss << vec1.get_line(y); 
		int holdint; ss >> holdint; vectors[x-1][y-1]=holdint; 
	}
}

for(int x = 1; x<=num_files; x++)
{
cout << "\n" << x << "\n";
        

       vector<int> data; data.push_back(0);
        for (int y=1; y<=num_files; y++)
        {
                
                int dot =0;
                for(int ii=1; ii<=vec1.num_lines(); ii++)
                {
                        
                        dot = dot + vectors[x-1][ii-1]*vectors[y-1][ii-1];
                        
                }
                if(dot==16){data[0]=data[0]+1; data.push_back(y);}
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
