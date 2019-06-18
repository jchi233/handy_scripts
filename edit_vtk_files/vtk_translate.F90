program reorg
  ! JCH 6/15/19
  ! The code has the capability to translate and rotate VTK files, but for visualization
  ! purposes, I built an external resource that can also do more specific data modifications.
  ! I really built this to swap the x and z coordinates. This code can be edited in several
  ! was and has not been extensively tested. The first part reads the data that you want to
  ! have, then the second part writes that data in the normal VTK format into a new file.
  ! Depending on the numbering format, you may have to edit the filename setup. As of right
  ! now, the numbering is set to work for only 4 digit(s) i.e. 0001, 0002, 0003 ....
  !=====================      EDIT HISTORY     =======================
  !      Created 6/15/19 JCH
  !
  implicit none
  !
  integer           :: fileNum,i,j,jj,total_loop_steps,no_geom_pts,numIDsPerLine,numPtsPerLine,check,check2,ind
  integer           :: index,kk,no_geom_lines,pts,connectivity_const,startingIndex
  character*120     :: filename,newfilename,endFilename,dir,basefilename,new_basefilename
  character*4       :: stFileNum
  logical           :: directory
  ! from bitcart
  integer,allocatable,dimension(:,:) :: geom_con
  real*8,allocatable,dimension(:,:)  :: geom_pts_tmp
  integer,allocatable,dimension(:)   :: newPntNo,siftindex,geom_compID
  logical, allocatable,dimension(:)  :: removePnt,removeLine
  character*10                      :: dummyA1,dummyA2
  !
  directory        = .false.
  startingIndex    = 0                   ! set to the number of the first file. This currently works for 1 or 0.
  fileNum          = 58                  ! The number of files in the set. If only one file, set to 1.
  numPtsPerLine    = 3                   ! number of points per line in the crap vtk(1 is a normal VTK)
  numIDsPerLine    = 9                   ! number of component IDs per line is the original vtk(1 is a normal VTK)
  endFilename      = ".vtk"             
  basefilename     = "heart2d_fixed2-"       ! crap basefile name, with numbers following the "-"
  new_basefilename = "heart2d_fixed3-"   ! new basefile name, with numbers to follow the "-"
  dir              = "fixed/"            ! the directory with the file(s). If you are in the same directory, just set it empty.
  !
  !
  do index = 1,fileNum
     !deallocate if allocated
     if(allocated(geom_pts_tmp)) then
        deallocate(geom_pts_tmp)
        deallocate(geom_compID)
        deallocate(geom_con)
     endif
     ! determine the current file and read the data from it
     if (startingIndex.eq.0) then
        write(stFileNum,'(I4.4)') index-1
     elseif (startingIndex.eq.1) then
        write(stFileNum,'(I4.4)') index
     else
        write(*,*) "EEEEEEEEERRRRRRRRRRRRRRRRRRRRROOOOOOOORRRRRRRRRR WITH STARTING INDEX"
     endif
     write(*,*) "fileNum, stFileNum = ",fileNum,stFileNum
     filename = trim(dir) // trim(basefilename) // trim(stFileNum) // trim(endFilename)  
     write(*,*) "filename = ",filename
     open(656,file=filename)
     !read lines until the first six characters in the line is POINTS. then backs up one line.              
     dummyA1='abcdef'                                                                                       
     do while (dummyA1(1:6).ne."POINTS")
        read(656,*) dummyA1                                                                                 
     end do
     Backspace(656)                                                                                         
     !                                                                                                      
     !read the points line and the second word is the number of points.                                     
     read(656,*) dummyA1,no_geom_pts,dummyA2                                                                
     !write(*,'(A,I8,A)') '[I] VTK-file contains ',no_geom_pts,' nodes'                                   
     allocate(geom_pts_tmp(0:no_geom_pts+1,3))                                                                                                                                     
     !                                                                                                      
     geom_pts_tmp=0.d0                                                                                                   
     ! this loops over all points, to get x,y,z coordinates    
     do pts=1, no_geom_pts
        ind = numPtsPerLine*(pts-1)
        read(656,*) geom_pts_tmp(pts,1:3)                                          
     end do
     ! read connectivity                                                                                    
     ! read lines until the first five characters in the line is LINES. then backs up one line.              
     dummyA1='abcdef'                                                                                       
     do while (dummyA1(1:5).ne."LINES")                                                                     
        read(656,*) dummyA1                                                                                 
     end do
     backspace(656)
     !                                                                                                      
     ! reads the number of lines to be generated                                                            
     read(656,*) dummyA1,dummyA1,no_geom_lines                                                               
     !                                                                                                      
     ! calculates the number of points                                                                       
     no_geom_lines=no_geom_lines/3                                                                          
     !write(*,'(A,I8,A)') '[I] 2D VTK-file contain ',no_geom_lines,' segments'                               
     ! assuming that lines are closed                                                                       
     !                                                                                                      
     allocate(geom_con(1:no_geom_lines,2))                                                                  
     !                                                                                                      
     do kk=1,no_geom_lines                                                                                 
        ! reads the line segment connectivity between points.                                               
        read(656,*) connectivity_const,geom_con(kk,1:2)                                                                
     end do
     ! reading component data                                                                               
     allocate(geom_compID(0:no_geom_lines))                                                                 
     ! read lines til the first six characters in line=LOOKUP. proceeds to find comp ID's.                  
     dummyA1='abcdef'                                                                                       
     do while (dummyA1(1:6).ne."LOOKUP")                                                                    
        read(656,*) dummyA1                                                                                 
     end do
     !                                                                                                      
     do pts=1,no_geom_lines
        read(656,*) geom_compID(pts)                                          
     end do
     close(656)
     !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     ! Now write everything to a new vtk file.
     filename = trim(dir) // trim(new_basefilename) // trim(stFileNum) // trim(endFilename)  
     open(656,file=filename)
     write(656,'(A)') "# vtk DataFile Version 3.0"
     write(656,'(A)') "vtk output"
     write(656,'(A)') "ASCII"
     write(656,'(A)') "DATASET POLYDATA"
     write(656,'(A,I0,A)') "POINTS ",no_geom_pts," float"
     do pts=1, no_geom_pts
        ! right now, I am swapping x,y,z, and setting the new z location to 0.00
        write(656,'(3F12.5)') -geom_pts_tmp(pts,2),-geom_pts_tmp(pts,3),0.00                                          
     end do
     write(656,'(A,I0,A,I0)') "LINES ",no_geom_pts," ",no_geom_pts*3
     do kk=1,no_geom_lines                                                                                  
        write(656,'(I0,A,I0,A,I0)') 2," ",geom_con(kk,1)," ",geom_con(kk,2)                                                                
     end do
     write(656,'(A,I0)') "CELL_DATA ",no_geom_pts
     write(656,'(A)') "SCALARS Components float"
     write(656,'(A)') "LOOKUP_TABLE default"
     !                                                                                                      
     do pts=1,no_geom_pts
        write(656,'(I0)') geom_compID(pts)                                          
     end do
     close(656)    
  end do
end program reorg
   
