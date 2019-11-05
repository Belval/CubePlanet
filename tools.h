template <class T>
static bool EqualWithEpsilon(const T& v1, const T& v2, T epsilon = T(0.0001))
{
return (fabs(v2 - v1) < epsilon);
}

template <class T>
static bool InRangeWithEpsilon(const T& v, const T& vinf, const T& vsup, T epsilon = T(0.0001))
{
return (v >= vinf - epsilon && v <= vsup + epsilon);
}
