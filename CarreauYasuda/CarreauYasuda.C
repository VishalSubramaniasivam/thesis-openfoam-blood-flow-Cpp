/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2017 OpenFOAM Foundation
     \\/     M anipulation  | Copyright (C) 2017 OpenCFD Ltd.

\*---------------------------------------------------------------------------*/

#include "CarreauYasuda.H"
#include "addToRunTimeSelectionTable.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{
    defineTypeNameAndDebug(CarreauYasuda, 0);
    addToRunTimeSelectionTable
    (
        viscosityModel,
        CarreauYasuda,
        dictionary
    );
}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField>
Foam::viscosityModels::CarreauYasuda::calcNu() const
{
    return
        nuInf_
      + (nu0_ - nuInf_)
      * pow(scalar(1) + pow(k_*strainRate(), a_), (n_ - 1.0)/a_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::viscosityModels::CarreauYasuda::CarreauYasuda
(
    const word& name,
    const dictionary& viscosityProperties,
    const volVectorField& U,
    const surfaceScalarField& phi
)
:
    viscosityModel(name, viscosityProperties, U, phi),
    CarreauYasudaCoeffs_
    (
        viscosityProperties.optionalSubDict(typeName + "Coeffs")
    ),
    nu0_("nu0", dimViscosity, CarreauYasudaCoeffs_),
    nuInf_("nuInf", dimViscosity, CarreauYasudaCoeffs_),
    k_("k", dimTime, CarreauYasudaCoeffs_),
    n_("n", dimless, CarreauYasudaCoeffs_),
    a_
    (
        CarreauYasudaCoeffs_.lookupOrDefault
        (
            "a",
            dimensionedScalar("a", dimless, 2)
        )
    ),
    nu_
    (
        IOobject
        (
            name,
            U_.time().timeName(),
            U_.db(),
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        calcNu()
    )
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::viscosityModels::CarreauYasuda::read
(
    const dictionary& viscosityProperties
)
{
    viscosityModel::read(viscosityProperties);

    CarreauYasudaCoeffs_ =
        viscosityProperties.optionalSubDict(typeName + "Coeffs");

    CarreauYasudaCoeffs_.readEntry("nu0", nu0_);
    CarreauYasudaCoeffs_.readEntry("nuInf", nuInf_);
    CarreauYasudaCoeffs_.readEntry("k", k_);
    CarreauYasudaCoeffs_.readEntry("n", n_);
    a_ = CarreauYasudaCoeffs_.lookupOrDefault
    (
        "a",
        dimensionedScalar("a", dimless, 2)
    );

    return true;
}


// ************************************************************************* //
