from pymatgen.analysis.diffraction.xrd import  XRDCalculator
from pymatgen.analysis.diffraction.core import AbstractDiffractionPatternCalculator
import pymatgen as mg
struct = mg.Structure.from_file("CONTCAR.vasp")  
xrd = XRDCalculator()#wavelength='CuKa', symprec=0, debye_waller_factors=None) 
pattern = xrd.get_pattern(struct,scaled=True,two_theta_range=(0,90)) 
print(pattern)
