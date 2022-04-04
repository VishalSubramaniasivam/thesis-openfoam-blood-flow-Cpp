/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
     \\/     M anipulation  | Copyright (C) 2017 OpenCFD Ltd
-------------------------------------------------------------------------------

Class
    Foam::viscosityModels::CarreauYasuda

Description
    An incompressible CarreauYasuda non-Newtonian viscosity model.

SourceFiles
    CarreauYasuda.C

\*---------------------------------------------------------------------------*/

#ifndef CarreauYasuda_H
#define CarreauYasuda_H

#include "viscosityModel.H"
#include "dimensionedScalar.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{

/*---------------------------------------------------------------------------*\
                           Class CarreauYasuda Declaration
\*---------------------------------------------------------------------------*/

class CarreauYasuda
:
    public viscosityModel
{
    // Private data

        dictionary CarreauYasudaCoeffs_;

        dimensionedScalar nu0_;
        dimensionedScalar nuInf_;
        dimensionedScalar k_;
        dimensionedScalar n_;
        dimensionedScalar a_;


protected:

    // Protected Data

        volScalarField nu_;

    // Protected Member Functions

        //- Calculate and return the laminar viscosity
        tmp<volScalarField> calcNu() const;


public:

    //- Runtime type information
    TypeName("CarreauYasuda");


    // Constructors

        //- Construct from components
        CarreauYasuda
        (
            const word& name,
            const dictionary& viscosityProperties,
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    //- Destructor
    virtual ~CarreauYasuda()
    {}


    // Member Functions

        //- Return the laminar viscosity
        virtual tmp<volScalarField> nu() const
        {
            return nu_;
        }

        //- Return the laminar viscosity for patch
        virtual tmp<scalarField> nu(const label patchi) const
        {
            return nu_.boundaryField()[patchi];
        }

        //- Correct the laminar viscosity
        virtual void correct()
        {
            nu_ = calcNu();
        }

        //- Read transportProperties dictionary
        virtual bool read(const dictionary& viscosityProperties);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace viscosityModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
