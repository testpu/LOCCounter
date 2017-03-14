@if exist "%VS140COMNTOOLS%"vsvars32.bat goto begin
@echo Error: "%VS140COMNTOOLS%"vsvars32.bat is not found!
@echo        Do you have VS140 installed?
@goto error

:begin

:setup

@setlocal
@rem --------------------set VS vars:
@call "%VS140COMNTOOLS%"vsvars32.bat

@rem --------------------set paths, etc.:

@set BOOST_PATH=U:\3rdParty\boost_1_63_0
@set CPP_UNIT_PATH=U:\3rdParty\cppunit_1.12.1

@set INCLUDE=^
\LOCCounter\include;^
$(SolutionDir)\include;^
%BOOST_PATH%;^
%CPP_UNIT_PATH%\include;^
%INCLUDE%

@set LIB=^
$(SolutionDir)\lib;^
%BOOST_PATH%\stage\win32\lib;^
%CPP_UNIT_PATH%\lib;^
%LIB%

@goto run

:error
@echo Error  : input path is invalid!
@pause
@goto end

:run
@start devenv /useenv /nosplash LOCCounter.sln
@goto end

:ide
@start devenv /useenv /nosplash

:end
