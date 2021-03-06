#include "studentas.h"

int Studentas::pazymiu_kiekis = 0;

bool YraSveikasisSkaicius(string x) // tikrina ar visi eilutes simboliai yra skaitmenys
{
    if (!isdigit(x[0]) && x[0] != '-')
        return false;
    for (int i = 1; i < x.length(); i++)
    {
        if (!isdigit(x[i]))
            return false;
    }
    return true;
}

int TinkamoSveikojoSkaiciausIvedimas()
{
    string s;
    cin >> s;
    while (!YraSveikasisSkaicius(s))
    {
        cout << "Netinkama ivestis. Prasome ivesti sveikaji skaiciu: ";
        cin >> s;
    }
    return stoi(s);
}

void RusiuotiPagalPavardeDidejanciai(Vector<Studentas> &studentai)
{
    std::sort(studentai.begin(), studentai.end(), [](const Studentas &a, const Studentas &b)
              { return a.Pavarde() < b.Pavarde(); });
}

void RusiuotiPagalVidurkiDidejanciai(Vector<Studentas> &studentai)
{
    std::sort(studentai.begin(), studentai.end(), [](const Studentas &a, const Studentas &b)
              { return a.GalutinisVid() > b.GalutinisVid(); });
}

void RusiuotiPagalVidurkiMazejanciai(Vector<Studentas> &studentai)
{
    std::sort(studentai.begin(), studentai.end(), [](const Studentas &a, const Studentas &b)
              { return a.GalutinisVid() < b.GalutinisVid(); });
}

void StudentoIvedimas(Studentas &s)
{
    string zodis;
    cout << "Iveskite varda: ";
    cin >> zodis;
    s.SetVardas(zodis);
    cout << "Iveskite pavarde: ";
    cin >> zodis;
    s.SetPavarde(zodis);

    int x = -1;
    cout << "Pasirinkite pazymiu ivedimo buda: " << endl;
    cout << "1 - automatinis pazymiu ivedimas" << endl;
    cout << "2 - rankinis pazymiu ivedimas" << endl;
    x = TinkamoSveikojoSkaiciausIvedimas();
    while (x != 1 && x != 2)
    {
        cout << "Nera tokio pasirinkimo. Iveskite teisinga skaiciu." << endl;
        cin >> x;
    }
    if (x == 2) // pazymiu ivedimas rankiniu budu
    {
        cout << "\nSuveskite namu darbu pazymius. (Noredami nutraukti ivedima, iveskite neigiama arba didesni uz 10 skaiciu)" << endl;
        while (true)
        {
            cout << "Iveskite " << s.ND().size() + 1 << " pazymi: ";
            x = TinkamoSveikojoSkaiciausIvedimas();
            if (x >= 0 && x <= 10)
                s.PushToND(x);
            else if (s.ND().size() != 0)
                break;
        }
        cout << "Iveskite gauta egzamino rezultata: ";
        while (true)
        {
            x = TinkamoSveikojoSkaiciausIvedimas();
            if (x < 0)
                cout << "Egzamino rezultatas turi buti teigiamas: ";
            else if (x > 10)
                cout << "Egzamino rezultatas turi buti nuo 0 iki 10: ";
            else
                break;
        }
        s.SetEgzaminas(x);
    }
    else // pazymiu generavimas
    {
        cout << "Iveskite norimu sugeneruoti pazymiu kieki: ";
        x = TinkamoSveikojoSkaiciausIvedimas();
        while (x <= 0)
        {
            x = TinkamoSveikojoSkaiciausIvedimas();
            if (x <= 0)
                cout << "Netinkama ivestis. Iveskite teigiama sveikaji skaiciu: ";
        }
        cout << "Pazymiai: ";
        for (int i = 0; i < x; i++)
        {
            s.PushToND(GeneruotiPazymi());
            cout << s.ND(i) << " ";
        }
        s.SetEgzaminas(GeneruotiPazymi());
        cout << "\nEgzaminas: " << s.Egzaminas() << endl;
    }
}

void IsvedimasIKonsole(Vector<Studentas> studentai, string galutinis_budas)
{
    stringstream my_buffer;
    if (galutinis_budas == "v")
    {
        my_buffer << "\n"
                  << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15)
                  << "Galutinis (Vid.)" << endl;
        my_buffer << string(45, '-') << endl;
        for (auto studentas : studentai)
        {
            my_buffer << left << setw(15) << studentas.Pavarde() << setw(15) << studentas.Vardas() << fixed
                      << setprecision(2) << studentas.GalutinisVid() << endl;
        }
        cout << my_buffer.str();
    }
    else if (galutinis_budas == "m")
    {
        my_buffer << "\n"
                  << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15)
                  << "Galutinis (Med.)" << endl;
        my_buffer << string(45, '-') << endl;

        for (auto studentas : studentai)
        {
            my_buffer << left << setw(15) << studentas.Pavarde() << setw(15) << studentas.Vardas() << fixed
                      << setprecision(2) << studentas.GalutinisMed() << endl;
        }

        cout << my_buffer.str();
    }
    my_buffer.clear();
}

void IsvedimasIFaila(Vector<Studentas> &studentai, string rez_failas)
{
    stringstream my_buffer;
    ofstream fo(rez_failas);
    // RusiuotiPagalPavardeDidejanciai(studentai);
    my_buffer << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15)
              << "Galutinis (Vid.)" << endl;
    my_buffer << string(63, '-') << endl;
    for (auto s : studentai)
    {
        my_buffer << s;
    }
    fo << my_buffer.str();
    // cout << "Duomenys isvesti i " << rez_failas << " faila." << endl;
    fo.close();
    my_buffer.clear();
    studentai.clear();
    studentai.shrink_to_fit();
}

void SkaitymasIsFailo(Vector<Studentas> &studentai, string ivesties_failas)
{
    int paz_kiek = -3;

    stringstream my_buffer;
    ifstream fi(ivesties_failas);

    my_buffer << fi.rdbuf();
    fi.close();

    string zodis;
    while (zodis != "Egz.")
    {
        my_buffer >> zodis;
        paz_kiek++;
    }
    if (paz_kiek < 1)
        return;

    Studentas::pazymiu_kiekis = paz_kiek;

    while (!my_buffer.eof())
    {
        Studentas s = Studentas();
        my_buffer >> s;
        studentai.push_back(s);
    }

    my_buffer.clear();
}

void RankinisIvedimas(Vector<Studentas> &studentai)
{
    string skaiciavimo_budas = "v";
    string testi_ivedima = "t";
    while (testi_ivedima == "t")
    {
        Studentas s;
        StudentoIvedimas(s);
        studentai.push_back(s);
        cout << "\nJei norite prideti dar viena studenta, irasykite 't': ";
        cin >> testi_ivedima;
    }
    RusiuotiPagalPavardeDidejanciai(studentai);

    cout << "\nKokiu budu apskaiciuoti galutini bala?" << endl;
    cout << "v - Vidurkis" << endl;
    cout << "m - Mediana" << endl;
    cout << "Irasykite atitinkama trumpini: ";
    cin >> skaiciavimo_budas;
    while (skaiciavimo_budas != "v" && skaiciavimo_budas != "m")
    {
        cout << "Iveskite tinkama trumpini: ";
        cin >> skaiciavimo_budas;
    }

    if (skaiciavimo_budas == "m")
    {
        for (auto &s : studentai)
        {
            s.SetGalutinisMed(MedianosApskaiciavimas(s.ND()) * 0.4 + s.Egzaminas() * 0.6);
        }
        IsvedimasIKonsole(studentai, "m");
    }
    else
    {
        for (auto &s : studentai)
        {
            s.SetGalutinisMed(VidurkioApskaiciavimas(s.ND()) * 0.4 + s.Egzaminas() * 0.6);
        }
        IsvedimasIKonsole(studentai, "v");
    }
}

void PadalintiStudentusKategorijomis(Vector<Studentas> &studentai, Vector<Studentas> &vargsiukai, Vector<Studentas> &moksliukai)
{
    // STRATEGIJA1:
    /*
        for (auto &s : studentai)
        {
            if (s.galutinis_vid < 5.00)
                vargsiukai.push_back(s);
            else
                moksliukai.push_back(s);
        }
    */
    // STRATEGIJA2:
    /*
        for (auto it = studentai.begin(); it != studentai.end();)
        {
            if ((*it).galutinis_vid < 5.00)
            {
                vargsiukai.push_back(*it);
                iter_swap(it, next(studentai.end(), -1));
                studentai.pop_back();
            }
            else
                it++;
        }
    */
    // MANO:

    // RusiuotiPagalVidurkiMazejanciai(studentai);
    std::partition(studentai.begin(), studentai.end(), [](const Studentas &s)
                   { return s.GalutinisVid() < 5.00; });
    auto it_u = std::upper_bound(studentai.begin(), studentai.end(), 5.00, [](double val, const Studentas &s)
                                 { return s.GalutinisVid() >= val; });
    moksliukai = Vector<Studentas>(it_u, studentai.end());

    studentai.resize(studentai.size() - moksliukai.size());

    vargsiukai = studentai;

    studentai.clear();
    studentai.shrink_to_fit();
}

void GeneruotiDuomenuFaila(int studentu_kiekis, int nd_kiekis)
{
    stringstream my_buffer;
    ofstream fo("st" + to_string(studentu_kiekis) + ".txt");
    int (*genPaz)() = &GeneruotiPazymi;

    my_buffer << "Vardas" << setw(12) << "Pavarde ";
    for (int i = 0; i < nd_kiekis; i++)
        my_buffer << setw(9) << "ND" << i + 1;
    my_buffer << setw(10) << "Egz."
              << "\n";

    for (int i = 0; i < studentu_kiekis; i++)
    {
        my_buffer << "Vardas" << i + 1 << setw(10) << "Pavarde" << i + 1;
        for (int j = 0; j < nd_kiekis + 1; j++)
            my_buffer << setw(10) << genPaz();
        if (i != studentu_kiekis - 1)
            my_buffer << "\n";
    }
    fo << my_buffer.str();
    my_buffer.clear();
    fo.close();
}