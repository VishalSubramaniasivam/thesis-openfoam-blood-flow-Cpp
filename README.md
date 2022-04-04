# thesis-openfoam-blood-flow-Cpp
This repository contains the classes and dictionaries defined during my master thesis that simulated blood flow on a c++ based CFD solver called openFOAM. The thesis is titled "Blood flow in dissected aortas after Thoracic Endovascular Aortic Repair (TEVAR)"

## Table of contents
* [General information](#General-information)
* [Carreau-Yasuda model - implementation into openFOAM source code](#Carreau-Yasuda-model-implementation-into-openFOAM-source-code)
* [Newtonian model - implementation into openFOAM source code](#Newtonian-model-implementation-into-openFOAM-source-code)
* [Abstract base class for viscosity - implementation into openFOAM source code](#Abstract-base-class-for-viscosity-implementation-into-openFOAM-source-code)
* [Defining dictionary file for constants in the Carreau-Yasuda model](#Defining-dictionary-file-for-constants-in-the-Carreau-Yasuda-model)
* [Other dictionary files](#Other-dictionary-files)
* [Contact](#Contact)

## General information
The class defined in this repository can be used in openFOAM, a c++ based CFD opensource software. Visit https://www.openfoam.com/ for installation files and support.

## Carreau-Yasuda model - implementation into openFOAM source code
CarreauYasuda.C<br />
CarreauYasuda.H<br /><br />
This class defines the newly implemented Carreau-Yasuda shear-thinning model.<br /><br /> Both these files must be copied to the location:<br /> $FOAM_SRC/transportModels/incompressible/viscosityModels 

## Newtonian model - implementation into openFOAM source code
Newtonian.C<br />
Newtonian.H<br /><br />
This class defines a linear viscosity model .<br /><br /> Both these files must be copied to the location:<br /> $FOAM_SRC/transportModels/incompressible/viscosityModels 

## Abstract base class for viscosity - implementation into openFOAM source code
viscosityModel.C<br />
viscosityModel.H<br /><br />
This is an abstract base class gets inherited by both CarreauYasuda and Newtonian. The class defines the shear rate on any cell in the computational grid.<br /><br /> Both these files must be copied to the location:<br /> $FOAM_SRC/transportModels/incompressible/viscosityModels

## Defining dictionary file for constants in the Carreau-Yasuda model
transportProperties<br /><br />
This dictionary file like all other dictionary files must be must be present in the constants folder from where the simulation is run. 

## Other Dictionary Files
All other dictionary files must be must be present in the constants folder from where the simulation is run. They control important parameters such as boundary conditions, solver methods, descretization schemes, meshing method, simulation time and parallel computing.

## Contact
Created by Vishal Subramaniasivam - feel free to contact me (vishal.subramaniasivam.95@gmail.com).
