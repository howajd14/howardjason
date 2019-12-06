from ase import Atoms 
from ase.io.vasp import *
import sys
from ase.lattice import bulk
from ase.io import *
from ase.utils.xrdebye import wavelengths
import numpy 

myatoms = ase.io.read('CONTCAR326',format='vasp')
#xrd = XrDebye(atoms=myatoms,wavelength=0.5406)
#xrd.calc_pattern(x=np.arange(10,120,0.1,mode='XRD')
#xrd.write_pattern('XRD.out')
