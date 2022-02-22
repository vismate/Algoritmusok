#include <stack>
#include <iostream>
#include <exception>

auto precedence(const char op) -> size_t
{
    switch (op)
    {
    case '(':
    case '=': return 0; // Ezek itt összevonhatóak a switch műkodése miatt. (lefele "esik")
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    case '^': return 3;
    default:
        throw std::runtime_error("Invalid operator givent to function \"precedence\"");
    }
}

auto infix2postfix(const std::string &str) -> void
{
    std::stack<char> ops;
    for (const char &ch : str)
    {
        //Skippeljük a space karakter kezelését, csak hogy lehessen az inputba space-t rakni
        if(ch == ' ') continue;

        // Egy változó (most nem foglalkozunk knkrét számokkal az egyszerűség kedvéért)
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            // Ha ez egy változó, akkor nem kell mást tenni, csak kiírni rögtön.
            std::cout << ch << ' ';
        }
        else if (ch == '(')
        {
            // Egy nyitottzárójel: csak a stack-re nyomjuk
            ops.push(ch);
        }
        else if (ch == ')')
        {
            // Egy csukott zárójelnél mindent fel kell dolgozni a nyitóig.
            //
            while (ops.top() != '(')
            {
                std::cout << ops.top() << ' ';
                ops.pop();
            }
            // Végül eltüntetjük magát a nyitott zárójelet
            ops.pop();
        }
        else
        {
            // Itt, ha helyes az input, már feltételezhetjük hogy operátorról van szó.
            // Lehetne tesztelni, de az egyszerűség kedvéért hagyjuk.
            // A "precedence" függvény úgy is dob egy kivételt, ha nem.

            // Amíg van nagyobb precedenciájú művelet a stacken, addig azokat sorban kiírjuk és eltávolítjuk
            //(Itt most kihagytam a bal-jobb operator check-et, mert az összes az.)
            //(A '(' check-et is kihagytam, mert a "precedence" függvényben kezelve van.))
            while (not ops.empty() && precedence(ch) <= precedence(ops.top()))
            {
                std::cout << ops.top() << ' ';
                ops.pop();
            }
            // Na most már ez is mehet a stack tetejére
            ops.push(ch);
        }
    }
    // Itt a végén, ha még esetleg maradt volna operátor, azt kiírjuk.
    while (not ops.empty()) 
    {
        std::cout << ops.top() << ' ';
        ops.pop();
    }
    std::cout << std::endl;
}

#ifdef LENGYEL
int main()
{
    try
    {
        infix2postfix("a + b * c");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
#endif