#include "skaiciavimai.h"

/// @private
uniform_int_distribution<int> dist(0, 10);
/// @private
mt19937 mt(static_cast<long unsigned int>(high_resolution_clock::now().time_since_epoch().count()));

/// Generuoja pažymį nuo 0 iki 10.
int GeneruotiPazymi()
{
    return dist(mt);
}

/// Apskaičiuoja vektoriaus elementų vidurkį.
double VidurkioApskaiciavimas(Vector<int> m)
{
    return std::accumulate(m.begin(), m.end(), 0) / m.size();
}

/// Apskaičiuoja medianos elementų vidurkį.
double MedianosApskaiciavimas(Vector<int> m)
{
    std::sort(m.begin(), m.end());
    if (m.size() % 2 == 0)
        return (m[m.size() / 2] + m[m.size() / 2 - 1]) / 2.0;
    else
        return m[m.size() / 2];
}