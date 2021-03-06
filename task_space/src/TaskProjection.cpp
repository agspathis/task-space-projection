#include "TaskProjection.h"
#include <simmath/LinearAlgebra.h>

using namespace SimTK;

Matrix calcJpT(const Matrix& NT, const Matrix& JT) {
    return NT * JT;
}

Matrix calcLambda(const Matrix& J, const Matrix& MInv, const Matrix& JT) {
    Matrix Lambda;
    auto LambdaInv = J * MInv * JT;
    FactorSVD svd(LambdaInv);
    svd.inverse(Lambda);
    return Lambda;
}

Matrix calcJBarT(const Matrix& Lambda, const Matrix& J, const Matrix& MInv) {
    return Lambda * J * MInv;
}

Matrix calcNT(const Matrix& JT, const Matrix& JBarT) {
    return 1 - JT * JBarT;
}

Matrix calcNpT(const Matrix& NtT, const Matrix& NT) {
    return NtT * NT;
}

Vector calcFt(const Vector& xddot, const Matrix& Lambdap, const Vector& bt,
	      const Matrix& JBarpT, const Vector& taup) {
    return Lambdap * (xddot + bt) + JBarpT * taup;
}

Vector calcTau(const Matrix& JT, const Vector& f) {
    return JT * f;
}
