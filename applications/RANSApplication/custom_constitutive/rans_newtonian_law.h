//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:         BSD License
//                   Kratos default license: kratos/license.txt
//
//  Main authors:    Suneth Warnakulasuriya
//

#if !defined(KRATOS_RANS_NEWTONIAN_LAW_H_INCLUDED)
#define KRATOS_RANS_NEWTONIAN_LAW_H_INCLUDED

// System includes

// External includes

// Project includes
#include "geometries/geometry.h"
#include "includes/node.h"
#include "includes/constitutive_law.h"

// Application includes
#include "custom_constitutive/fluid_adjoint_constitutive_law.h"

namespace Kratos
{
/**
 * @brief This class is extending Newtonian2DLaw in FluidDynamicsApplication
 *
 * This class is used to extend Newtonian2DLaw in FluidDynamicsApplication
 * to include turbulent viscosity from Bossinesq Hypothesis.
 *
 */
template<class TPrimalBaseType, class TAdjointBaseType>
class KRATOS_API(RANS_APPLICATION) RansNewtonianLaw : public TPrimalBaseType
{
public:
    ///@name Type Definitions
    ///@{

    using BaseType = TPrimalBaseType;

    using NodeType = Node<3>;

    using GeometryType = Geometry<NodeType>;

    ///@}
    ///@name Life Cycle
    ///@{

    /**
     * Counted pointer of Newtonian3DLaw
     */

    KRATOS_CLASS_POINTER_DEFINITION(RansNewtonianLaw);

    /**
     * Life Cycle
     */

    /**
     * Default constructor.
     */
    RansNewtonianLaw();

    /**
     * Clone function (has to be implemented by any derived class)
     * @return a pointer to a new instance of this constitutive law
     */
    ConstitutiveLaw::Pointer Clone() const override;

    /**
     * Copy constructor.
     */
    RansNewtonianLaw(const RansNewtonianLaw& rOther);

    /**
     * Destructor.
     */
    ~RansNewtonianLaw();

    /**
     * Operations needed by the base class:
     */

    ///@}
    ///@name Operations
    ///@{

    /**
     * This function is designed to be called once to perform all the checks
     * needed on the input provided. Checks can be "expensive" as the function
     * is designed to catch user's errors.
     * @param rMaterialProperties
     * @param rElementGeometry
     * @param rCurrentProcessInfo
     * @return
     */
    int Check(
        const Properties& rMaterialProperties,
        const GeometryType& rElementGeometry,
        const ProcessInfo& rCurrentProcessInfo) override;

    FluidAdjointConstitutiveLaw::Pointer GetAdjointConstitutiveLaw() override;

    ///@}
    ///@name Access
    ///@{

    /**
     * Input and output
     */
    /**
     * Turn back information as a string.
     */
    std::string Info() const override;

    ///@}

protected:
    ///@name Protected Operations
    ///@{

    /// Get the effective viscosity (in dynamic units -- Pa s) for the fluid.
    double GetEffectiveViscosity(ConstitutiveLaw::Parameters& rParameters) const override;

    ///@}
private:
    ///@name Serialization
    ///@{

    friend class Serializer;

    void save(Serializer& rSerializer) const override;

    void load(Serializer& rSerializer) override;

    ///@}
}; // Class RansNewtonianLaw
} // namespace Kratos.
#endif // KRATOS_RANS_NEWTONIAN_LAW_H_INCLUDED  defined