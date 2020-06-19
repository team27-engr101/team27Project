# team27Project
plan and code for engr101 project 3
Engr 101 AVC Plan:
Team number : 27
Team members:
Thomas 
Nathika 
Logan
Oliver
As discussed prior on discord the workload will be spread as evenly as possible with changing roles. For example two people code for core and two people check the functionality and layout for core, these roles will then reverse when we move onto completion and challenge.
Key dates: 
The project is due on the 19th of June.(conflicts with this date may be comp , engr and cybr assignments).
The plan needs to be submitted before the 4th of June.
The timeline fore each phase is about 5 days until the due date.
Core (5 days) – due date 8th of June
Completion(5 days) – due date 13th of June
Challenge (5 days) – due date 18th of June
The timeline for Team logs will be caught up every second day of each phase where each member will submit a short sentence discussing milestones reached from the following days and any other key points to address to other members.
Roles per phase:
Core: Oliver and Nathika will work together to code the program, Thomas and Logan will check functionality and overall execution they, may also be able to give advice on the code itself.
Completion: Thomas and Logan work together to code the program, Oliver and Nathika will check functionality and overall execution, they may also be able to give advice on code itself.
Challenge: All four team members (if able) will do a rough draft on how they think the challenge can work. Then will test each other’s code for functionality and overall execution giving advice on code itself. From there the team will agree on a piece on code and add that to the final project code.
Primary source of communication will be discord, and to share team logs Google doc.

Install
For Windows -

If you do not have a program to run and compile C++ programs you will need to install Geany and MinGW. If SFML isn't working (MinGW version may be outdated), you will need to install MinGW again. To install MinGW again, you must first delete the existing version. 


Deleting MinGW

To delete MinGW, you can open the uninstall.exe in the location you installed it, or you can simply delete the files and remove the system environment variable. To remove the system environment variable you must look up system environment variables on your computer, press the button under System Properties - Advanced , click on PATH and then edit (whether user or system variables depends on how you previously set it up) if you are unable to locate your MinGW file location you will be able to see it here. Delete the path to the MinGW bin and you are ready to install it again.


Installing MinGW

To install MinGW, get the online installer from https://sourceforge.net/projects/mingw-w64/files/, if you have a 64 bit operating system it is recommended you install 64 bit MinGW but 32 bit will still work (though 64 bit will not work on 32 bit machines, to find out which your computer is search "About your PC" and under device specifications, system type it should say 32 or 64 bit operating system). If you want 32 bit MinGW, in the installer you want to select i686 architecture and dwarf for the exception, if you want 64 bit, the architecture should be x86_64 and the exception seh. Once this is done installing, go to the location you installed MinGW and find the folder called bin, copy the directory by left clicking to the right of /bin in the bar up the top and pressing CTRL+C or right click and copy, this should look something like C:\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin for 64 bit or C:\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin for 32 bit. You will now need to add the bin of MinGW to your system environment variables under PATH. How to access this is described in the paragraph on uninstalling MinGW above and once there press new and paste in the directory then press ok in all the windows to save and exit, add this under system variables if you want to use MinGW on multiple local users or user variables if you just want it on your user.


Installing Geany

To install Geany, download the installer executable from https://www.geany.org/download/releases/ , run it and follow the displayed instructions.


Installing SFML

The first step of installing SFML is to check whether your C++ compiler is 32 or 64 bit, this is important as you must match the version with that of SFML. If you are using MinGW, this can be done by opening command prompt and entering gcc --version or looking at the file names in the directory where you installed MinGW (if it is 64 bit you will likely see mingw64 or mingw-w64 and vice versa for 32 bit). For other C++ compilers, please refer to relevant file names or search up online how to find the version. If you are unable to find the location where you installed your C++ compiler, you can open the system environment variables as described in the paragraph on uninstalling MinGW and you should be able to see the directory here. Once you have the version of your C++ compiler, you will need to download SFML from the website https://www.sfml-dev.org/download/sfml/2.5.1/ , the version you download depends on your C++ compiler and the version (32 or 64 bit)
of it you found previously. Using this information download the relevant matching version of SFML (latest release). Once this has finished downloading, extract to any location you like and browse to find a file named “SFML-2.5.1”.  In this file should be the files “include” and “lib”. If you can see these, left click to the right of SFML-2.5.1 in the bar above the window and then do CTRL+C or right click and copy to copy this directory. In both the Robot and Server files you downloaded previously (unzip if zipped), you will find a “makefile”, open these with any text editor (eg notepad or you could use Geany if you have it). In the makefiles, you will find up the top it says DIR=... or some other variable name with a directory after it, delete anything on the line after the = and then paste in the SFML directory you copied earlier. Save this by pressing control + S or doing it manually, this will need to be done for both the server and robot makefiles. In the server and robot files you will see files ending in .o and .exe, delete these (server.o,server.exe,robot.o,robot.exe - was told about this in a lab). Once you have done that, open up the program you are using to build and compile C++ programs and navigate to the build commands (build - build commands up the top for geany or you can use the drop down menu for build). Under independent commands it should say “make”, anywhere it says make, add mingw32- in front of it eg make-> mingw32-make, make %e.o -> mingw32-make %e.o. The final step to getting the program working is to go back to the location you installed SFML in and locate the bin, in there should be a bunch of dll files. You will need to select all of these, copy, and paste into both the robot and server folders. When you do this, it will ask if you want to replace the files in the destination or skip, you should replace all the files in each folder.


Making and running the programs

If you have C++ compiling and SFML working, you should now be able to run the programs. To do so, open the server.cpp and robot.cpp files in the C++ program and on each one, select make all from the build menu. Once both have been made they are ready to execute using the button up the top, the server.cpp must be executed first followed by the robot.cpp for it to work correctly. To change to core, completion and challenge, edit the line in config.txt. You will not need to delete the .o and .exe when making the files in the future but they will need to be made each time they are changed. If you are getting the code from github, replace the code in robot.cpp with the code from the github page.



