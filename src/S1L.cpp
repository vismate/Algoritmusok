// Fejelem nélküli egyszeresen csatolt lista egyszerű, procedurális implementációja
// Az egyes függvények, bár megtehetnék, nem használják egymást. Külön-külön működőképesek.

#include <iostream>

// Egy nódus egy T típusú adattagot, illetve a következő nódusra mutató pointert tartalmazza.
template <typename T>
struct ListNode
{
    T data;
    ListNode<T> *next = nullptr;
};

// Operátor overload kiíratáshoz.
template <typename T>
std::ostream &operator<<(std::ostream &stream, const ListNode<T> *p)
{
    stream << "[ ";
    while (p != nullptr)
    {
        stream << p->data << " ";
        p = p->next;
    }

    stream << "]";
    return stream;
}

// Egy std::initializer_list-ből állítunk elő egy új listát.
template <typename T>
auto create(std::initializer_list<T> init_list) -> ListNode<T> *
{
    if (init_list.size() == 0)
        return nullptr;

    // Lefoglaljuk és inicializáljuk az első nódust, majd a 2. elemtől kezdve hozzáfűzögetjük az elemeket.
    ListNode<T> *p = new ListNode<T>{*init_list.begin()}, *q = p;
    for (auto itr = init_list.begin() + 1; itr != init_list.end(); itr++)
    {
        q->next = new ListNode<T>{*itr};
        q = q->next;
    }

    // Visszaadjuk az elmentett első nódusra mutató pointert.
    return p;
}

template <typename T>
auto length(ListNode<T> *p) -> size_t
{
    size_t n = 0;
    while (p != nullptr)
    {
        n++;
        p = p->next;
    }
    return n;
}

// Itt elkezdünk pointer-referenciákat alkalmazni,
// mivel a paraméterül kapott első nódusra mutató pointer
// a függvény során megváltozhat.

// Ez itt látszik a legtisztábban.
template <typename T>
auto push_front(ListNode<T> *&p, T item) -> void
{
    p = new ListNode<T>{item, p};
}

template <typename T>
auto push_back(ListNode<T> *&p, T item) -> void
{
    // Ha a listánk üres, mutasson 'p' az új elemre.
    if (p == nullptr)
        p = new ListNode<T>{item, nullptr};
    else
    {
        // Eliterálunk az utolsó nódusig.
        ListNode<T> *q = p; // Lemásoljuk 'p'-t, mert nem akarjuk megváltoztatni.

        while (q->next != nullptr)
        {
            q = q->next;
        }

        // Az utolsó nódus 'next' mezője mutasson az úl elemre.
        q->next = new ListNode<T>{item, nullptr};
    }
}

template <typename T>
auto pop_front(ListNode<T> *&p) -> void
{
    if (p != nullptr)
    {
        ListNode<T> *next = p->next;
        delete p;
        p = next;
    }
}

template <typename T>
auto pop_back(ListNode<T> *&p) -> void
{
    if (p == nullptr)
        return;

    // Iterálunk a lista utolsó nódusáig, de számon tartjuk az azt megelőző nódust is.
    ListNode<T> *prev = nullptr, *q = p;
    while (q->next != nullptr)
    {
        prev = q;
        q = q->next;
    }

    // Töröljük az utolsó nódust, és ha volt azt megelőző elem, akkor annak a 'next' mezőjét,
    // ellenkező esetben a 'p'-t állítjuk nullptr-re.
    delete q;
    (prev ? prev->next : p) = nullptr;
}

template <typename T>
auto reverse(ListNode<T> *&p) -> void
{
    ListNode<T> *prev = nullptr, *next = nullptr;
    while (p != nullptr)
    {
        next = p->next;
        p->next = prev;
        prev = p;
        p = next;
    }

    p = prev;
}

template <typename T>
auto purge(ListNode<T> *p) -> void
{
    while (p != nullptr)
    {
        ListNode<T> *tmp = p->next;
        delete p;
        p = tmp;
    }
}

template <typename T>
auto find(ListNode<T> *p, const T &item) -> ListNode<T> *
{
    while (p != nullptr)
    {
        if (p->data == item)
            return p;
        p = p->next;
    }

    return nullptr;
}

template <typename T>
auto at(ListNode<T> *p, size_t ind) -> ListNode<T> *
{
    while (p != nullptr && ind > 0)
    {
        ind--;
        p = p->next;
    }

    return p;
}

template <typename T>
auto append(ListNode<T> *&p1, ListNode<T> *p2) -> void
{
    // Ha az első lista üres, legyen a lista első nódusa a második lista első nódusa.
    if (p1 == nullptr)
        p1 = p2;

    // Megkeressük az első lista utolsó nódusát, majd annak a 'next' mezőjét p2-re állítjuk.
    ListNode<T> *q = p1;

    while (q->next != nullptr)
    {
        q = q->next;
    }

    q->next = p2;
}

template <typename T>
auto remove(ListNode<T> *&p, ListNode<T> *item) -> void
{
    if (p == nullptr || item == nullptr)
        return;

    // Ha az első elemet kell törölnünk, a p-t a lista második elemére állítjuk.
    if (p == item)
    {
        p = item->next;
        delete item;
        return;
    }

    // Megkeressük a törlendő elem előtti nódust, majd ha megtaláltuk kifűzzük az elemet és töröljük.
    ListNode<T> *q = p;
    while (q != nullptr && q->next != item)
    {
        q = q->next;
    }

    if (q)
    {
        q->next = item->next;
        delete item;
    }
}

template <typename T>
auto insert(ListNode<T> *p, ListNode<T> *q) -> void
{
    if (p == nullptr || q == nullptr)
        return;

    q->next = p->next;
    p->next = q;
}

#ifdef S1L
int main()
{
    auto int_list = create({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

    push_front(int_list, 6);
    push_back(int_list, 11);
    std::cout << "Lista: " << int_list << std::endl;

    reverse(int_list);
    std::cout << "Megfordítva: " << int_list << std::endl;

    pop_back(int_list);
    pop_front(int_list);
    std::cout << "Se eleje, se vége: " << int_list << std::endl;

    std::cout << "Hossz: " << length(int_list) << std::endl;


    auto string_list = create({"list.", "a", "I\'m"});

    append(string_list, create({"World!", "Hello"}));
    reverse(string_list);
    std::cout << string_list << std::endl;

    remove(string_list, string_list);
    std::cout << "Eleje nélkül: " << string_list << std::endl;

    std::cout << "World utáni szó: " << find(string_list, (const char *)"World!")->next->data << std::endl;

    std::cout << "Negyedik szó: " << at(string_list, 3)->data << std::endl;

    purge(int_list);
    purge(string_list);
}
#endif