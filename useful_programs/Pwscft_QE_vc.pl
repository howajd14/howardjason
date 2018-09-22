#!/usr/bin/perl
##############################
# program originally written by Xiao Xu;
#    modified by Yaojun Du and NAWH
#    Version with Variable Cell 
##############################
@args=@ARGV;
@args==2 || die "usage: PWscf2Axsf <input> <output>";
open(outputHANDLE,"> $ARGV[1]");
select(outputHANDLE);

#########################################
########to get the lattice parameter#####
#########################################
$au=0.52917720859;
open(scfHANDLE,"$ARGV[0]");
while (<scfHANDLE>){
        if ($_=~/lattice parameter /)
                {
                  @fields=split(" ",$_);
                  $LatticeParameter=$fields[4];
                  #print $LatticeParameter;
                        };
        } ;
$Factor=$au*$LatticeParameter;
#print $factor;

##############################################################
########to get the atom number ###############################
######## for practice,number of iter is got with other method#
##############################################################
seek(scfHANDLE,0,0) or die;
while (<scfHANDLE>){
        if ($_=~/number of atoms/)
                {
                  @fields=split(" ",$_);
                   $AtomNumber=$fields[4];

                };
        } ;
#print $AtomNumber;
#########################################
######the number of iterations########
#########################################

seek(scfHANDLE,0,0) or die;
@Lines=<scfHANDLE>;
$NumberOFIterations=grep(/ATOMIC/,@Lines);
$NumberOFIterations=$NumberOFIterations;
#print $NumberOFIterations,"\n";;
$CountInitial=$NumberOFIterations;

print "ANIMSTEPS $CountInitial\n";
print "CRYSTAL\n";

#############################################
#########Big loop ###########################
#############################################

for($AnimSteps=1;$AnimSteps<$NumberOFIterations+1;$AnimSteps++){

        $temp=$AnimSteps;
        print "PRIMVEC $temp\n";
   
seek(scfHANDLE,0,0) or die;
$count=$AnimSteps;
while (<scfHANDLE>){
        if($_=~/CELL_PARAMETERS/) {$count--;};
        last if $count==0;
    }
$count=1;

while (<scfHANDLE>){
     $count++;
     push(@LatticeLine,$_);
     last if $count>3;
     }

for($index=0;$index<3;$index++){
        ($NumberX,$NumberY,$NumberZ)=split(" ",$LatticeLine[$index]);
        
        printf ( "%15.9f ", $NumberX*$Factor);
        printf ( "%15.9f ", $NumberY*$Factor);
        printf ( "%15.9f ", $NumberZ*$Factor);
        print "\n";

        $LatticeConstant[$index][1]=$NumberX*$Factor;
        $LatticeConstant[$index][2]=$NumberY*$Factor;
        $LatticeConstant[$index][3]=$NumberZ*$Factor;

                }
        undef @LatticeLine;
   

   print "PRIMCOORD $temp\n";
   print "$AtomNumber 1\n";     

seek(scfHANDLE,0,0) or die;
$count=$AnimSteps;

while (<scfHANDLE>){
        if($_=~/ATOMIC_POSITIONS/) {$count--;};
        last if $count==0;
    }
$count=1;

while (<scfHANDLE>){
        $count++;
        push(@CoordLines,$_);
        last if $count>$AtomNumber;
        }

for($index=0;$index<$AtomNumber;$index++){
        ($AtomSym,$CoordX,$CoordY,$CoordZ)=split(" ",$CoordLines[$index]);
        printf ("%s", $AtomSym);
        printf "  ";       
        printf ( "%12.8f ", $CoordX*$LatticeConstant[0][1]+
           $CoordY*$LatticeConstant[1][1]+
           $CoordZ*$LatticeConstant[2][1],);
        printf ( "%12.8f ", $CoordX*$LatticeConstant[0][2]+
           $CoordY*$LatticeConstant[1][2]+
           $CoordZ*$LatticeConstant[2][2],);
        printf ( "%12.8f ", $CoordX*$LatticeConstant[0][3]+
           $CoordY*$LatticeConstant[1][3]+
           $CoordZ*$LatticeConstant[2][3],);

        print "\n";
                }

undef @CoordLines;

   }
