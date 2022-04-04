/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------

Namespace
    Foam::viscosityModels

Description
    A namespace for various incompressible viscosityModel implementations.

Class
    Foam::viscosityModel

Description
    An abstract base class for incompressible viscosityModels.

    The strain rate is defined by:

        mag(symm(grad(U)))


SourceFiles
    viscosityModel.C
    viscosityModelNew.C

\*---------------------------------------------------------------------------*/

#ifndef viscosityModel_H
#define viscosityModel_H

#include "dictionary.H"
#include "volFieldsFwd.H"
#include "surfaceFieldsFwd.H"
#include "dimensionedScalar.H"
#include "runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                Class viscosityModel Declaration
\*---------------------------------------------------------------------------*/

class viscosityModel
{

protected:

    // Protected data

        word name_;
        dictionary viscosityProperties_;

        const volVectorField& U_;
        const surfaceScalarField& phi_;


    // Private Member Functions

        //- No copy construct
        viscosityModel(const viscosityModel&) = delete;

        //- No copy assignment
        void operator=(const viscosityModel&) = delete;


public:

    //- Runtime type information
    TypeName("viscosityModel");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            viscosityModel,
            dictionary,
            (
                const word& name,
                const dictionary& viscosityProperties,
                const volVectorField& U,
                const surfaceScalarField& phi
            ),
            (name, viscosityProperties, U, phi)
        );


    // Selectors

        //- Return a reference to the selected viscosity model
        static autoPtr<viscosityModel> New
        (
            const word& name,
            const dictionary& viscosityProperties,
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    // Constructors

        //- Construct from components
        viscosityModel
        (
            const word& name,
            const dictionary& viscosityProperties,
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    //- Destructor
    virtual ~viscosityModel()
    {}


    // Member Functions

        //- Return the phase transport properties dictionary
        const dictionary& viscosityProperties() const
        {
            return viscosityProperties_;
        }

        //- Return the strain rate
        tmp<volScalarField> strainRate() const;

        //- Return the laminar viscosity
        virtual tmp<volScalarField> nu() const = 0;

        //- Return the laminar viscosity for patch
        virtual tmp<scalarField> nu(const label patchi) const = 0;

        //- Correct the laminar viscosity
        virtual void correct() = 0;

        //- Read transportProperties dictionary
        virtual bool read(const dictionary& viscosityProperties) = 0;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
