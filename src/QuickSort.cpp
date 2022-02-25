// Jegyzet: vismate.github.io/Algoritmusok/QuickSort

#include <vector>
#include "PrintVector.hpp" // Vektor kiíratás

// Egy namespace, hogy elrejtsük valamelyest az implementáció részfüggvényeit.
namespace _impl
{
    template <typename T>
    auto partition(std::vector<T> &vec, size_t begin, size_t end) -> size_t
    {
        // Okos matematikusok azt mondták, hogy a random indexen jó esélyünk van találni kedvező tengelyt.
        size_t i = begin + rand() % (end - begin);

        // A tengelyt külön változóban tároljuk, helyére az alvektor utolsó elemét tesszük.
        const T pivot = vec[i];
        vec[i] = vec[end];

        // Megkeressük az első olyan elemet, amely nagyobb a tengelynél.
        i = begin;
        while (i < end && vec[i] <= pivot)
        {
            i++;
        }

        // Ha nincs ilyen, a tengelyt az alvektor végére tesszük.
        if (i >= end)
        {
            vec[end] = pivot;
        }
        else
        {
            // Az első tengelytől nagyobb elem utáni indextől j segítségével végigiterálunk az alvektoron.
            for (size_t j = i + 1; j < end; j++)
            {
                // Ha egy adott elem kisebb, mint a tengely, megcseréljük az i. elemmel.
                // Majd növeljük az i-t egyel.
                if (vec[j] < pivot)
                {
                    std::swap(vec[i], vec[j]);
                    i++;
                }
            }

            // Végül a tengelyt a helyére tesszük. (Az utolsó csere utáni index)
            // Az utolsó helyre pedig az i. elem kerül.
            // (Ez ugye biztosan nagyobb mint a pivot, mert itt nem volt csere.)
            vec[end] = vec[i];
            vec[i] = pivot;
        }

        // Visszaadjuk a tengely helyét.
        return i;
    }

    // A valódi rekurzív függvény.
    template <typename T>
    auto quick_sort(std::vector<T> &vec, size_t begin, size_t end) -> void
    {
        // Ha még szükséges, felparticionáljuk az alvektort, majd rekurzívan rendezzük őket.
        if (begin < end)
        {
            // Megkapjuk a kiválasztott tengely indexét.
            const size_t mid = partition(vec, begin, end);

            // A tengelyt már kihagyhatjuk a rendezésből, az már biztosan helyen van,
            // mert előtte a kisebb, mögötte pedig a nála nagyobb értékek vannak.
            if (mid > 1)
            {
                // Csak akkor próbáljuk meg rendezni a bal felét, ha van olyan.
                // (mivel C++ konvenciók miatt unsigned típust használunk indexnek,
                // a 0-ból való kivonás miatt overflow-t és segfault-ot kapnánk)
                quick_sort(vec, begin, mid - 1);
            }
            quick_sort(vec, mid + 1, end);
        }
    }
}

// Az egyszerűség kedvéért tetszőleges típus vektorára implementáljuk az algoritmust.
template <typename T>
auto quick_sort(std::vector<T> &vec) -> void
{
    _impl::quick_sort(vec, 0, vec.size() - 1);
}

#ifdef QUICK_SORT
int main()
{
    std::vector<int> vec = {4, 2, 5, 8, 9, 3, 5, 3, 5, 2, 6, 1, 0};

    std::cout << vec << std::endl;
    quick_sort(vec);
    std::cout << vec << std::endl;

    std::vector<std::string> vec2 = {"Citrom", "Barack", "Alma"};

    // Látszik hogy pl. string-ek vektorára is működik.
    std::cout << vec2 << std::endl;
    quick_sort(vec2);
    std::cout << vec2 << std::endl;
}
#endif