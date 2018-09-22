Program getTEMPfromPWscf
!  Prepares average temperature
!   From PWscf MD run
  Implicit none

  CHARACTER(256) :: filename,readline
  INTEGER :: i,j,k,l,m,n,ok, natom,skip,ntime,nstep,actatm,acttime
  REAL(8) :: basis(3,3),x,y,z,scale,v(3),dt
  CHARACTER(2) :: sym, keepsym
  REAL(8), PARAMETER :: autime=0.048378d0     !in 10^-15 s units (for QE)

  write(6,*) 'Enter file name for PWscf output'
  read(5,*) filename
  open(7,file=TRIM(filename),form='formatted')
  
 write(6,*) 'enter the number of time units to skip'
 read(5,*) skip
 write(6,*) 'number of time units to skip = ', skip

 k=0
  do    
    read(7,'((a))',iostat=OK) readline
     if (OK/=0) exit
       i=INDEX(readline,'temperature')
       if (i>0) k=k+1
       if (k.ge.skip+2) exit  
  enddo

 acttime=0; x=0;z=0

  do    
    read(7,'((a))',iostat=OK) readline
     if (OK/=0) exit
       i=INDEX(readline,'temperature')
       if (i>0) then
         acttime=acttime+1
         read(unit=readline(29:43),fmt=*) y
         x=x+y
         z=z+y*y
       else
         cycle
       endif  
  enddo   

  write(6,*) 'temperature averaged over ', acttime,'  steps'
  write(6,*) 'T = ', x/acttime, sqrt((z-x*x/acttime)/acttime)

  close(7)
  
  END PROGRAM

