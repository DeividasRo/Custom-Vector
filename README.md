# Eksperimentiniai Vector klasės tyrimai
## Spartos tyrimai
Naudojant push_back() funkciją, palyginta, kuris konteineris užsipildo greičiau. Matoma, jog sukurta Vector klasė yra truputį lėtesnė.
|Įrašų kiekis|My Vector|std::vector|
|------------|---------|-----------|
|10000|0.0001418 s|0.0001336 s|
|100000|0.0010581 s|0.0009965 s|
|1000000|0.0113836 s|0.009906 s|
|10000000|0.111952 s|0.0951455 s|
|100000000|1.0516 s|0.964288 s|

Patikrinta kiek kartų atliekamas atminties perskirstymas (size() == capacity()) pasinaudojant push_back() funkcija užpildant vektorius su 100000000 elementų,
|Konteineris|Perskirstymų kiekis|
|-----------|-------------------|
|std::vector|27|
|My Vector|27|

Palyginti StudentoDB programos veikimo laikai analizuojant failus su 100.000 ir 1.000.000 studentų įrašų.

|Įrašų kiekis|My Vector|std::vector|
|------------|---------|-----------|
|100000|0.503757 s|0.526834 s|
|1000000|4.96879 s|5.20269 s|

## Funkcijų aprašymai

### 1. Uncreate()
Funkcija sunaikina priskirtus elementus po 1 elementą iš eilės, pradėdama nuo *avail-1* iteratoriaus pozicijos, kuri rodo į paskutinį elementą. Iteratorius yra mažinamas, kol pasiekia iteratoriaus *data* adresą, kuri rodo į pirmąjį elementą. Tuomet atlaisvinama visa užrezervuota vieta nuo *data* iki *limit*, bei visi iteratoriai nunulinami.
```
template <typename T>
void Vector<T>::Uncreate()
{
    if (data)
    {
        while (avail != data)
            alloc.destroy(--avail);
        alloc.deallocate(data, limit - data);
    }
    data = limit = avail = nullptr;
}
```
### 2. Grow()
Gauna dydį naujos rezervuotos vietos padvigubinus buvusią rezervuotą vietą. Priskiria naują užrezervuotą vietą nuo naujo pradžios iteratoriaus. Seni elementai nukopijuojami į naują vietą. Visi seni elementai panaikinami Uncreate() funkcijos pagalba ir priskiriamos atitinkamos naujos reikšmės iteratoriams *data*, *avail* ir *limit*.
```
template <typename T>
void Vector<T>::Grow()
{
    size_t new_size = std::max(2 * (limit - data), ptrdiff_t(1));
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    Uncreate();
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}
```
### 3. clear()
Sunaikinami visi priskirti elementai.
```
template <typename T>
void Vector<T>::clear()
{
    while (avail != data)
    {
        alloc.destroy(--avail);
    }
}
```
### 4. shrink_to_fit()
Sumažina užrezervuota vietą iki vietos po paskutinio elemento pozicijos, jeigu užrezervuota vieta yra didesnė, nei naudojama.
```
template <typename T>
void Vector<T>::shrink_to_fit()
{
    if (avail < limit)
        limit = avail;
}
```

### 5. operator==(const Vector<T> &v) 
Tikrina ar abiejų pusių vektorių elementai sutampa. Jeigu vektorių dydžiai nesutampa, gražinama klaida. Kitu atveju, lyginamas kiekvienas elementas iš eilės. Jeigu bent vienas yra nelygus, grąžinama klaida. Jei visi elementai lygūs, grąžinama tiesa.
```
template <typename T>
bool Vector<T>::operator==(const Vector<T> &v) const
{
    if (v.size() != this->size())
        return false;
    else
    {
        for (size_t i = 0; i < v.size(); i++)
        {
            if (data[i] != v.data[i])
                return false;
        }
        return true;
    }
}
```
