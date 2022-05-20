#ifndef SKAICIAVIMAI_H
#define SKAICIAVIMAI_H

#include <random>
#include <chrono>
#include <numeric>
#include <vector>
#include <algorithm>
#include "myvector.h"

using namespace ::std::chrono;
using std::mt19937;
using std::uniform_int_distribution;
using std::vector;

int GeneruotiPazymi();
double VidurkioApskaiciavimas(Vector<int>);
double MedianosApskaiciavimas(Vector<int>);

#endif