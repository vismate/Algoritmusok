// Jegyzet: vismate.github.io/Algoritmusok/MergeSort

#include <iostream>
#include <vector>

#include "PrintVector.hpp" // Vektor kiíratás

// Egy névtér, ami tartalmazza a segédfüggvényeket.
// Ez csak arra való, hogy "elrejtsük" a nem implementálónak szánt dolgokat.
namespace _impl
{
    // A merge függvény két önmagában már rendezett alvektort fésül össze
    template <typename T>
    auto merge(std::vector<T> &vec, size_t begin, size_t mid, size_t end) -> void
    {
        // A bal alvektor hossza
        const size_t d = mid - begin;

        // Ez a temp vektorunk (egyszerűség kedvéért marad vektor)
        std::vector<T> Z(d);
        // Átmásoljuk a vec bal felét
        for (size_t n = 0; n < d; n++)
        {
            Z[n] = vec[begin + n];
        }

        // Most vec[begin .. end] intervallumba összefésüljük a bal alvektor másolatát (Z) és a jobb alvektort.

        // Az i index a jobb alvektoron halad végig
        // A j index a bal alvektoron (az átmásolt)
        // A k index pedig az egész alvektoron, és a jelenlegi feltöltendő helyre mutat
        size_t i = mid, j = 0, k = begin;

        while (i < end && j < d)
        {
            if (vec[i] < Z[j])
            {
                // A jobb oldali elem kisebb, mint a baloldali.
                vec[k] = vec[i];
                i++;
            }
            else
            {
                // A bal oldali elem kisebb, tegyük be a helyére
                vec[k] = Z[j];
                j++;
            }

            k++;
        }

        // Másoljuk át a bal oldali alvektor elemeit, ha még maradtak. (Ezek már biztosan a legnagyobbak)
        // Itt azért nem kell a jobb oldali alvektorral foglalkozni, mert ha abból maradtak elemek
        // azok már biztosan a jó helyen vannak
        while (j < d)
        {
            vec[k] = Z[j];
            j++;
            k++;
        }
    }

    // Ez a fő függvény, ami már rekurzívan hívható indexekkel (egyszerűség kedvéért, hagyjuk az iteratorokat).
    template <typename T>
    auto merge_sort(std::vector<T> &vec, size_t begin, size_t end) -> void
    {
        if (begin >= end - 1)
            return; // Egy elemű részt már nem kell rendezni

        size_t mid = begin + (end - begin) / 2;

        // Rendezzük a vektor bal felét
        merge_sort(vec, begin, mid);

        // Most a jobb felét
        merge_sort(vec, mid, end);

        // Most pedig fésüljük össze a két felet
        merge(vec, begin, mid, end);
    }
}

// Most vektorokra implementáljuk a merge_sortot, mert miért ne!
// Úgy is azt használjuk sok helyen...
// A template megengedi, hogy ne csak pl. int vektorokra működjön.
template <typename T>
auto merge_sort(std::vector<T> &vec) -> void
{
    _impl::merge_sort(vec, 0, vec.size());
}

#ifdef MERGE_SORT
int main()
{
    std::vector<int> vec = {4, 2, 5, 8, 9, 3, 5, 3, 5, 2, 6, 1, 0};

    std::cout << vec << std::endl;
    merge_sort(vec);
    std::cout << vec << std::endl;

    std::vector<std::string> vec2 = {"Citrom", "Barack", "Alma"};

    // Látszik hogy pl. string-ek vektorára is működik.
    std::cout << vec2 << std::endl;
    merge_sort(vec2);
    std::cout << vec2 << std::endl;
}
#endif