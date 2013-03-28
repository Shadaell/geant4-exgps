#
# example of Geant4.9.5 configuration
# change these variables so that they correspond to your paths
#
export G4WORKDIR=$HOME/G4WORK
export DATADIR=$HOME/geant4-install/geant4.9.5
export G4ABLADATA=$DATADIR/data/G4ABLA3.0
export G4LEDATA=$DATADIR/data/G4EMLOW6.23
export G4LEVELGAMMADATA=$DATADIR/data/PhotonEvaporation2.2
export G4NEUTRONHPDATA=$DATADIR/data/G4NDL4.0
export G4NEUTRONXSDATA=$DATADIR/data/G4NEUTRONXS1.1
export G4PIIDATA=$DATADIR/data/G4PII1.3
export G4RADIOACTIVEDATA=$DATADIR/data/RadioactiveDecay3.4
export G4REALSURFACEDATA=$DATADIR/data/RealSurface1.0

#call geant4.9.5 configuration script:
. /usr/local/share/Geant4-9.5.0/geant4make/geant4make.sh

