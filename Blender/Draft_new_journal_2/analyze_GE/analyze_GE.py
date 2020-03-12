import math 

GE     =     open('GEp_3000.dat','r',encoding='utf-8')
out300 = open('300.dat','w',encoding='utf-8')
out500 = open('500.dat','w',encoding='utf-8')
out800 = open('800.dat','w',encoding='utf-8')
out1000 = open('1500.dat','w',encoding='utf-8')
kb = 8.617e-5; 
GEdat = []
ens = []
for x in GE:
	vals = x.split()
	ens.append(float(vals[0]))
	GEdat.append(float(vals[1]))

count =0; 
eo = ens[0]
for x in ens: 
	line = str(ens[count]-eo) + '\t' +  str(math.exp(-(ens[count]-eo)/(kb*300))*GEdat[count])
	out300.write(line+'\n')  
	line = str(ens[count]-eo) + '\t' +  str(math.exp(-(ens[count]-eo)/(kb*500))*GEdat[count])
	out500.write(line+'\n')
	line = str(ens[count]-eo) + '\t' +  str(math.exp(-(ens[count]-eo)/(kb*800))*GEdat[count])
	out800.write(line+'\n')
	line = str(ens[count]-eo) + '\t' + str(math.exp(-(ens[count]-eo)/(kb*1500))*GEdat[count])
	out1000.write(line+'\n')
	count=count+1


GE.close()
out300.close()
out500.close()
out800.close()
out1000.close()
