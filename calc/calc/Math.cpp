#include <boost/math/special_functions/round.hpp>
#include "Math.h"

Math::Math() {
}

Math::~Math() {
}

double Math::round(const double valor, const unsigned int precision) {
    double aux = pow(10.0, (double) precision);
    double result = boost::math::lround(valor * aux);
    result /= aux;
    return result;
}

