# Set up some imports that we will need
from pymatgen import Lattice, Structure
import numpy
import xrayutilities as xru
from xrayutilities.materials.cif import CIFFile
from xrayutilities.materials.material import Crystal
#from IPython.display import Image, display
from tempfile import NamedTemporaryFile
#import matplotlib
#import matplotlib.pyplot as plt
#import matplotlib.ticker as ticker
#%matplotlib inline


for y in range(16864,16865):
    print(y,end='\n')
    num = str(y)
    infilename = '../CONTCAR_files/CONTCAR' + num + '.vasp'
    structure = Structure.from_file(infilename)
    temp_cif = NamedTemporaryFile(delete=False)
    structure.to("cif", temp_cif.name)
    xu_cif = CIFFile(temp_cif.name)
    xu_crystal = Crystal(name="LLTO", lat=xu_cif.SGLattice())
    temp_cif.close()
    two_theta = numpy.arange(10, 120, 0.025)
    powd = xru.simpack.Powder(xu_crystal,1)
    wlen = xru.wavelength('CuKa1')
    pm = xru.simpack.PowderModel(powd,wl=wlen)
    intensities = pm.simulate(two_theta)
    fend = str(y)
    filename = 'file' + fend
    outfile = open(filename,'w')
    for x in range(1,len(intensities)):
        #v1  = (x-1)*0.05 + 10 
        #v2  = intensities[x]
        #strv1 = str(v1)
        #strv2 = str(v2)
        #outline = strv1 + "  " + strv2 + '\n'
        outfile.write(str((x-1)*0.025 + 10) + "  " + str(intensities[x]) + "\n")
    outfile.close()
    pm.close()


