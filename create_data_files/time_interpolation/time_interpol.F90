program timeloop
  ! JCH 10/8/18
  ! this file will serve to generate the cycles of potential vtk files in a given sequence
  ! and their respective time occurrances. This is inteded to be a reference for use in 
  ! the code so that the code can use the actual time to interpolate to the exact distacne 
  ! function which will be used by the solver. This was generated when we were testing the 
  ! vtk interpolator using some circles moving back and forth.
  ! 
  implicit none
  !
  real*8            :: reeltime,time_per_slice,periodTime
  integer           :: ninLoop,fileNum,i,j,jj,total_loop_steps,downAndBack,straightSeries,startingFileNum
  character*120     :: filename
  !
  downAndBack = 0                             ! based on how files are organized
  straightSeries =1                           ! based on how files are organized
  startingFileNum = 0
  fileNum = startingFileNum                   ! starting file index, probably 0 or 1.
  reeltime = 0.0                              ! time should probably always start at 0.
  ninloop = 59                                ! total number of files in the loop
  periodTime = 1.8                            ! time for one cycle of the loop.
  time_per_slice = periodTime/(ninloop)
  total_loop_steps = 1000
  filename = "heart2d_step_loop.dat"
  open(656,file=filename)
  !this is the setup for down and back, where the set goes down and then back.
  if (downAndBack.eq.1) then
     do i = 1, total_loop_steps
        !if (fileNum.gt.ninloop-1) then
        !   fileNum = 1
        !endif
        do j = 1, ninloop/2
           if ((fileNum.eq.1).and.(i.ne.1)) then
              !!nothing    
           else
              write(656,'(i2.2,E20.10)') fileNum,reeltime
              reeltime = reeltime + time_per_slice
           endif
           if (fileNum.eq.ninloop/2) then
              fileNum = fileNum
           else
              fileNum = 1 + fileNum
           endif
        enddo
        do j = 1, ninloop/2 -1
           !!     do j = 1, ninloop/2 -2
           fileNum = fileNum - 1
           write(656,'(i2.2,E20.10)') fileNum,reeltime
           reeltime = reeltime + time_per_slice
           !if (fileNum.gt.ninloop) then
           !   fileNum = 1
           !endif
        enddo
     enddo
  endif
  if (straightSeries.eq.1) then
     !if only in a straight series, just down
     do i = 1, total_loop_steps
        do j = 1, ninloop
           write(656,'(i4.4,E15.5)') fileNum,reeltime
           reeltime = reeltime + time_per_slice
           fileNum = 1 + fileNum
           if (fileNum.gt.ninloop) then
              fileNum = startingFileNum
           endif
        enddo
     enddo
  endif
  close(656)
end program timeloop
