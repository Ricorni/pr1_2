#include "helpers.hpp"


long long normalizeModulo(
    long long value,
    long long modulo
) {
    value %= modulo;

    if (value < 0) {
        value += modulo;
    }

    return value;
}

long long extendedEuclidean(
    long long a,
    long long b,
    long long& u,
    long long& v
) {
    if (b == 0) {
        u = 1;
        v = 0;

        return a;
    }

    long long previousU;
    long long previousV;

    long long gcdValue = extendedEuclidean(
        b,
        a % b,
        previousU,
        previousV
    );

    u = previousV;
    v = previousU - (a / b) * previousV;

    return gcdValue;
}