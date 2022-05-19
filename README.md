# Custom Vector Class
## Spartos tyrimai
Naudojant push_back() funkciją, palyginta, kuris konteineris užsipildo greičiau. Matoma, jog sukurta Vector klasė yra truputį lėtesnė.
|Įrašų kiekis|My Vector|std::vector|
|------------|---------|-----------|
|10000|0.0001418|0.0001336|
|100000|0.0010581|0.0009965|
|1000000|0.0113836|0.009906|
|10000000|0.111952|0.0951455|
|100000000|1.0516|0.964288|

Patikrinta kiek kartų atliekamas atminties perskirstymas (size() == capacity()) pasinaudojant push_back() funkcija užpildant vektorius su 100000000 elementų,
|Konteineris|Perskirstymų kiekis|
|-----------|-------------------|
|std::vector|27|
|My Vector|27|

## Funkcijų aprašymai
