#
# example of Geant4.9.4 configuration
# change these variables so that they correspond to your paths
#
export G4SYSTEM=Linux-g++
export G4INSTALL=$HOME/geant4-install/geant4.9.4.p01/
#export G4LIB=$HOME/lib4.9.3.p01
export G4WORKDIR=$HOME/G4WORK
export CLHEP_BASE_DIR==$G4INSTALL/clhep-install
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CLHEP_BASE_DIR}/lib
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${G4LIB}/${G4SYSTEM}
#export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${G4LIB}/
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${G4INSTALL}/lib/${G4SYSTEM}
export G4UI_USE_TERMINAL=1
#export G4VIS_USE_OPENGLX=1
#export G4VIS_USE_OPENGLXM=1
export G4LIB_BUILD_STATIC=1

source $G4INSTALL/.config/bin/${G4SYSTEM}/env.sh
