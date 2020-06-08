fl = open('avgOPus','r')
of = open('avgOP_stddev.dat','w');

ls = []
for line in fl:
    ls.append(line)

mn = float(ls[0].split()[0])
for x in range(len(ls)):
    sp = ls[x].split()
    of.write(str(float(sp[0])-mn) + "\t" + sp[1] + "\t" + sp[2] + "\n")

fl.close()
of.close()
