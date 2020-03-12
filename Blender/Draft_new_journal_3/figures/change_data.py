import math
myfile = open('10X10_S10_I1e6_vary_Co.dat','r',encoding='utf-8')
outfile = open('10X10_S10_I1e6_vary_Co.dat_changed','w',encoding='utf-8')
for line in myfile:
    mylist = line.split()
    outline = mylist[0]+'\t'+mylist[1]+'\t'+str(float(mylist[2])/math.sqrt(36))+'\n'
    outfile.write(outline)

myfile.close()
outfile.close()
