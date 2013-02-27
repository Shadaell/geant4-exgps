---------------------------------------------------------------------------
Copying/modifying conditions:
See LICENSE for copying conditions.
The project is mostly licensed under GEANT4 license,
see http://geant4.web.cern.ch/geant4/ for details.

  Some of the code files are written without dependence on GEANT4 toolit
and they're licensed under GNU GPL License see http://www.gnu.org/
for details.
  In few words, copy and modify as you wish, but with no patenting,
commercial use etc. Any modification of GEANT4-licensed files should
contain notice of GEANT4 license(I guess).

Author: Bogdan V.Maslovskiy, 04 March 2012.
e-mail1: blinkenlichten{##doggy##}yandex{##antispam-dot##}ua
e-mail2: blinkofnight{##doggy##}gmail{##antispam-dot##}com
IRC chat:
        server: tfsoft.org.ua
	port: 6667
	channel: #main
	chan. encoding UTF-8
	my nick there is Viper
Ukrainian, Russian or English languages can be spoken at that IRC-channel.

----------------------------------------------------------
Program name: egamma
Synopsis:
        egamma [OPTION1] [OPTIONN] FILE

The directory called "e-gamma-ta-al" contains the files you may want
to use or modify.

  This is GEANT4 simulation of such process:
  Electrons with energy ~44MeV hits the 1.0mm thick plate made of Tl,
newly generated gamma along with electrons quants going thru Al 10cm
material and then they hit 1mm thick Indium-made target, if it's present.
  The result of simulation is a spectra of deposited in target energy
(if enabled) and a spectra of particles that get into any of detectors,
(only registers kinetic energy at the moment of contact, no losses).
  By default the Indium target is present -- it's mass: 0.200gramm,
diameter: 0.5cm, cylindrical shape(thickness is calculated automatically).
  The particles are being registered by 2 pseudo-detectors called "void0_DetectorSD"
and "void_DetectorSD". These detectors does not interact with particle,
they do not slow downthe particles or proccess the hits inside detector's body
[because made of almost vacuum], they only record particle's kinetic energy and then
dump it to the output files. If Indium target is enabled, then it will register
deposited by incoming particles energy, it will also registed it's kinetic
energy at the moment of contact with the surface(without losses) and write all that
into the files.

The simulation program should be compiled and used  this way:

# --- go to project directory ---:
cd egamma-ta-al-in/

# --- setup you GEANT4 variables ---:
. g4conf.sh   #for v4.9.4 of geant
#or
. g5conf.sh   #for v4.9.5 of geant

# --- compile ---:
make  #4.9.4 and 4.9.5
#or
mkdir build && cd build && cmake .. #only 4.9.5

# --- run it ---:
./e-gamma filename.mac   # +many options available(see below)


filename.mac -- is a name of the mac file for GEANT4.

There are 2 mac-files in the project's directory:
vis.mac -- only few simulations being run, it will generate g4_00.wrl file
           of standard VRML97 which shows geometry and particles trajectories.
           You can view it with Blender http://blender.org -- it's a great
	   open source 3D modelling/animating program.

run.mac -- makes a simulation, generates output files with spectas.
	   If you're simulating ~100e06 events it will take 3Gb of the disk space!

OPTIONS;
--tathick
         Thickness of the plate made from Ta-material,
         default value is: 0.105cm.
--tadiam 
         Diameter of the plate made from Ta-material,
         default value is: 10cm.

--althick
         Thickness of the aluminium-made cylindrical block,
         default value is: 10cm.

--aldiam 
         Diameter of the aluminium cylindrical block,
         default value is: 10cm.

--tgdiam
         Diameter of the pseudo-detectors and Indium-target
         default value is: 0.5cm.

--tgmass
          mass of the Indium-target, may be 0, the target 
          will be removed from the simulation in that case;
	  default value: 0.200.
	  Measure units: gramms

--tgthick
         Thickness of the indium-made cylindrical block,
         default value is: 0cm.

All values except tgmass are measured in centimeters (cm),
.

#USAGE example:
./e-gamma run.mac --tgmass 0.237 --tgdiam 0.357 --tathick 0.1057

 -------- Processing the program's OUTPUT: -------

There is another small program written in Python:   binner.py
It can make histograms with any binning from *.raw files.

The "e-gamma" executable may produce these kinds of files:

*.raw -- a file that has records of some kinds particles that been
         registered by one of the DetectorSD objects in code, the prefix
         of file name indicates which one detector has generated the
	 output. The file name's root suffix indicates what kind of particles
	 has been recorded to the file.  

One can make extract a spectra from the raw file using a script called "binner.py"
which is located at sub-directory "sripts"
or by using a C++ program called "cpp-histogrammer"(it works 10 times faster than script),
it is located at the same repository:
svn checkout svn://svn.code.sf.net/p/g4schiff/code/trunk/cpp-histogrammer cpp-histogrammer

