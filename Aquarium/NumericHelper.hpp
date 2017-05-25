template<typename NumericType> inline Min (NumericType a, NumericType b)
{
  return a < b ? a : b;
};

template<typename NumericType> inline Max (NumericType a, NumericType b)
{
  return a > b ? a : b;
};

template<typename NumericType> inline NumericType Constrain (NumericType value, NumericType min, NumericType max)
{
    return Min(max, Max(value, min));
};

long inline long Map (long value, long inMin, long inMax, long outMin, long outMax)
  {
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
  };
