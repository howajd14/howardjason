Program getMSDfromPWscf
!  Prepares MSD
!   From PWscf MD run
!   Keeps only one type of atom
  Implicit none

  CHARACTER(256) :: filename,readline
  INTEGER :: i,j,k,l,m,n,ok, natom,skip,ntime,nstep,actatm,acttime,mult
  REAL(8) :: basis(3,3),x,y,z,scale,v(3),dt
  CHARACTER(2) :: sym, keepsym
  REAL(8), allocatable :: rr(:,:,:),msd(:,:),howmanyt(:)
  REAL(8), PARAMETER :: autime=0.048378d0     !in 10^-15 s units (for QE)

  write(6,*) 'Enter file name for PWscf output'
  read(5,*) filename
  write(6,*) 'Enter number of concenated output files -- overestimate'
  read(5,*) mult
  open(7,file=TRIM(filename),form='formatted')
  open(8,file='msd.dat', form='formatted')

  basis=0   
  do    
    read(7,'((a))',iostat=OK) readline
     if (OK/=0) exit
       j=INDEX(readline,'number of atoms/cell      =')
       if (j>0) then
               write(6,*) readline; call flush(6)
          read(unit=readline(j+28:80),fmt=*) natom     
               write(6,*) 'natom', natom; call flush(6)
          cycle
       endif   
       k=INDEX(readline,'nstep')
       if (k>0) then
           read(unit=readline(k+28:80),fmt=*) nstep    
              write(6,*) 'nstep', nstep; call flush(6)
           cycle
       endif    
       i=INDEX(readline,'celldm')
       if (i>0) then
          read(unit=readline(i+10:80),fmt=*) x
          write(6,*) 'celldm(1) = ', x
          read(7,*)
          read(7,*)
          read(7,*)
          read(7,'(23x,3f11.6)')basis(:,1)
          read(7,'(23x,3f11.6)')basis(:,2)
          read(7,'(23x,3f11.6)')basis(:,3)
          basis=basis*x*0.52917721068d0
          write(6,*) 'basis vectors'
          write(6,'(3f16.7)') basis(:,1)
          write(6,'(3f16.7)') basis(:,2)
          write(6,'(3f16.7)') basis(:,3)
          cycle
      endif
      l=INDEX(readline,'Time step')
      if (l>0) then
         read(unit=readline(30:37),fmt=*) dt
         write(6,*) 'dt = ', dt, dt*autime   
         exit
      endif   
 enddo    

 dt=dt*autime

 write(6,*) 'enter the number of time units to skip'
 read(5,*) skip
 write(6,*) 'number of time units to skip = ', skip

 k=0
  do    
    read(7,'((a))',iostat=OK) readline
     if (OK/=0) exit
       i=INDEX(readline,'ATOMIC_POSITIONS')
       if (i>0) k=k+1
       if (k.ge.skip) exit  
  enddo

 write(6,*) 'enter the symbol for the atom for MSD'
 read(5,*) keepsym
 write(6,*) ' MSD calculated for ', keepsym
 
 allocate(rr(3,nstep*mult,natom))
 rr=0
 acttime=0; actatm=0

  do    
    read(7,'((a))',iostat=OK) readline
     if (OK/=0) exit
       i=INDEX(readline,'ATOMIC_POSITIONS')
       if (i>0) then
         acttime=acttime+1
         actatm=0
         do j=1,natom
            read(7,*) sym,x,y,z
            if (sym==keepsym) then
               actatm=actatm+1     
               v=x*basis(:,1)+y*basis(:,2)+z*basis(:,3)
               rr(:,acttime,actatm)=v
            endif
         enddo
         write(6,*) 'For time ', acttime,'  accumulated ',actatm
         call flush(6)
       else
         cycle
       endif  
  enddo   

  write(6,*) 'Completed rr '
  allocate(msd(3,acttime-1),howmanyt(acttime-1))

  msd=0;howmanyt=0
     do i=1,acttime-1
        do j=i+1,acttime
           k=j-i
             x=0;y=0;z=0
             do l=1,actatm
                x=x+(rr(1,j,l)-rr(1,i,l))**2
                y=y+(rr(2,j,l)-rr(2,i,l))**2
                z=z+(rr(3,j,l)-rr(3,i,l))**2
             enddo   
           howmanyt(k)=howmanyt(k)+1
           msd(1,k)=msd(1,k)+x/actatm    
           msd(2,k)=msd(2,k)+y/actatm    
           msd(3,k)=msd(3,k)+z/actatm    
         enddo  
      enddo    


    write(8,'(" #                  time (fs)       x**2          y**2           z**2")')
 do k=1,acttime-1
    write(8,'(i10,1p4e16.7)') k,k*dt,msd(:,k)/howmanyt(k)
    write(6,*) 'for time step ', k, howmanyt(k)
 enddo   

 close(7)
 close(8)


  END PROGRAM  
