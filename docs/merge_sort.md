# Összefésülő rendezés (merge sort)
<sup>[C++ implementáció](https://github.com/vismate/Algoritmusok/blob/main/src/Sort/merge_sort.cpp)</sup>

Ez az algoritmus az "oszd meg és uralkodj" elven működik. Ha feltételezzük hogy a tömbünk bal és jobb része rendezett, már csak annyi maradt hátra, hogy összefésüljök őket.  

Mint minden rekurzív függvény, az összefésülő rendezés is visszavezethető egy alapesetre. Az alapesetünk egy már rendezett résztömb. Azon résztömbről, amely egyetlen elemet tartalmaz, biztosan tudjuk, hogy rendezett.

## A rekurzív függvény műkodése
Ha a (rész) tömbünk legalább két elemű:

 - Megfelezzük a tömbünket
 - Rendezzük a bal résztömböt (rekurzív hívás)
 - Rendezzük a jobb résztömböt (rekurzív hívás)
 - Összefésüljük őket

## Az összefésülés menete

  - A bal altömböt átmásoljuk egy temporális tömbbe.
  - Létrehozunk 2 változót: 'i' és ''j'. Az 'i' a jobb altömb elejére mutat, a 'j' a bal elejére.
  - Létrehozunk egy 'k' változót is, amely a résztömb jelenleg feltöltendő helyét jelöli (kezdetben bal eleje).
  - Egy while-ciklussal haladunk mindaddig, míg 'i' kisebb mint a jobb altömb utolsó indexe, és 'j' kisebb mint a bal altömb utolsó indexe.
  - Amennyiben a résztömb i. eleme kisebb mint a temporális tömb j. eleme, a résztömb k. elemét a résztömb i. elemével tesszük egyenlővé, ellenkező esetbe a temporális tömb j. elemével. Majd inkrementáljuk a megfelelő indexet.
  - Inkrementáljuk a k-t
  - Ha kiléptünk a while-ciklusból, átmásoljuk a bal altömb hátramaradt elemeit a jobb altömb végére.

  ![merge animation](/Algoritmusok/assets/merge_sort_animation.gif)

### Struktogramm
  ![merge struki](/Algoritmusok/assets/merge_struki.png)

### Rövidített C++ kód
  ```c++
  auto merge(std::vector<T> &vec, size_t begin, size_t mid, size_t end) -> void
{
        const size_t d = mid - begin;
        std::vector<T> Z(d);

        for (size_t n = 0; n < d; n++) Z[n] = vec[begin + n];

        size_t i = mid, j = 0, k = begin;

        while (i < end && j < d)
        {
            if (vec[i] < Z[j]) vec[k++] = vec[i++];
            else vec[k++] = Z[j++];
        }

        while (j < d) vec[k++] = Z[j++];        
}
  ```
## Egy diagram az algoritmus működéséről
  ![merge sort diagram](/Algoritmusok/assets/merge_sort_diagram.png)

## Az algoritmus tulajdonságai

 - Stabil, tehát az egyenlő elemek relatív sorrendje nem változik meg a rendezés közben.
 - Nem helyben rendező, tehát extra memóriára van szüksége futás közben.
 - Komplexitás: <strong>O(n * log n)</strong>
    - A feljebb látott diagramon látszik, hogy a kirajzolt bináris fa <strong>log n </strong> szintel rendelkezik.
    - Minden egyes szinten összefésülünk, az összefésülés komplexitása pedig lineáris.
- Nincs sok különbség a minimális és maximális műveletigény között, mindig a feljebb tárgyalt komplexitás érvényes.