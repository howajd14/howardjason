#include "../../../../../cpp_programs/classes/file_class/file.hpp"
using namespace std;

int main()
{
int num_files;
cout << "\nhow many files?\n";
cin >> num_files;
file outfile;
int  vectors1 [num_files][24]; 
int  vectors2 [num_files][24];
int num_e=0;
for(int x=1; x<=num_files; x++)
{
	stringstream ss; ss << x; string holdit; ss >> holdit;
        string file1 = "Vecs1/vec" + holdit;  file  vec1(file1); num_e=vec1.num_lines();
	for (int y=1; y<=vec1.num_lines(); y++)
	{
		ss.clear();ss.str(""); ss << vec1.get_line(y); 
		int holdint; ss >> holdint; vectors1[x-1][y-1]=holdint; 
	}
	ss.clear();ss.str("");
	string file2 = "Vecs2/vec" + holdit;  file  vec2(file2);
	for (int y=1; y<=vec2.num_lines(); y++)
	{
		ss.clear();ss.str(""); ss << vec2.get_line(y); 
		int holdint; ss >> holdint; vectors2[x-1][y-1]=holdint; 
	}
	
}
int count_sm =0; 
for(int x = 1; x<=num_files; x++)
{

       
                
                int dot =0;
                for(int ii=1; ii<=num_e; ii++)
                {
                        
                        dot = dot + vectors1[x-1][ii-1]*vectors2[y-1][ii-1];
                        
                }
		int  eqneq = 0; 
                if(dot==16){count_sm = count_sm+1; eqneq =1; }
		string outline; stringstream ss; ss << eqneq; ss >> outline; 
		ss.clear();ss.str(""); ss << x; string holdnow; ss >> holdnow; 
		outlin=outline+"\t"+holdnow;
    	        outfile.add_line(outline);
}
cout << "\n\n" << count_sm << "\n\n" ; 
outfile.make_file("same_not_same"); 
return 0; 
}
