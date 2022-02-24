// Jegyzet: vismate.github.io/Algoritmusok/Lengyel

#include <stack>
#include <iostream>
#include <exception>
#include <sstream>

namespace _impl
{
    auto precedence(const char op) -> size_t
    {
        switch (op)
        {
        case '(':
        case '=':
            return 0; // Ezek itt összevonhatóak a switch műkodése miatt. (lefele "esik")
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            throw std::runtime_error("Invalid operator givent to function \"precedence\"");
        }
    }

    inline auto is_variable(const char ch) -> bool
    {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }

    inline auto is_operator(const char ch) -> bool
    {
        switch (ch)
        {
        case '=':
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return true;
        default:
            return false;
        }
    }
}

auto infix2postfix(const std::string &str) -> std::string
{
    using _impl::is_operator;
    using _impl::is_variable;
    using _impl::precedence;

    // A standard kimenet helyett egy ostringstream-be írunk, így visszatudunk adni egy stringet.
    std::ostringstream output_stream;

    std::stack<char> ops;
    for (const char ch : str)
    {
        // Skippeljük a space karakter kezelését, csak hogy lehessen az inputba space-t rakni
        if (ch == ' ')
            continue;

        // Egy változó (most nem foglalkozunk knkrét számokkal az egyszerűség kedvéért)
        if (is_variable(ch))
        {
            // Ha ez egy változó, akkor nem kell mást tenni, csak kiírni rögtön.
            output_stream << ch << ' ';
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
                output_stream << ops.top() << ' ';
                ops.pop();
            }
            // Végül eltüntetjük magát a nyitott zárójelet
            ops.pop();
        }
        else if (is_operator(ch))
        {
            // Amíg van nagyobb precedenciájú művelet a stacken, addig azokat sorban kiírjuk és eltávolítjuk
            //(Itt most kihagytam a bal-jobb operator check-et, mert az összes az.)
            //(A '(' check-et is kihagytam, mert a "precedence" függvényben kezelve van.))
            while (not ops.empty() && precedence(ch) <= precedence(ops.top()))
            {
                output_stream << ops.top() << ' ';
                ops.pop();
            }
            // Na most már ez is mehet a stack tetejére
            ops.push(ch);
        }
        else
        {
            //Váratlan karakter a kifelyezésben. Ooops...
            throw std::runtime_error("Invalid character found in expression.");
        }
    }
    // Itt a végén, ha még esetleg maradt volna operátor, azt kiírjuk.
    while (not ops.empty())
    {
        output_stream << ops.top() << ' ';
        ops.pop();
    }

    return output_stream.str();
}
auto postfix2infix(const std::string &str) -> std::string
{
    using _impl::is_variable;
    using _impl::is_operator;

    std::stack<std::string> stack;
    for (const char ch : str)
    {
        // Skippeljük a space karakter kezelését, csak hogy lehessen az inputba space-t rakni
        if (ch == ' ')
            continue;

        if (is_variable(ch))
        {
            // Ha változóról van szó, akkor (stringként) a stackre helyezzük.
            stack.push(std::string{ch});
        }
        else if (is_operator(ch))
        {
            // Ha operátor jön velünk szembe, akkor lepattintunk 2 operandust a stack-ről,
            // és a belőlük konstruált eredményt a verembe visszatesszük.

            if (stack.size() < 2)
                throw std::runtime_error("Invalid expression given to function.");

            // A balról jobbra sorrend megőrzése végett előbb a 'b' operandust vesszük ki a veremből.
            //(Az alábbi string építés nem a leghatékonyabb, de legalább egyszerű.)
            const std::string b = stack.top();
            stack.pop();

            const std::string a = stack.top();
            stack.pop();

            stack.push("(" + a + ' ' + ch + ' ' + b + ")");
        }
        else
        {
             throw std::runtime_error("Invalid character found in expression.");
        }
    }

    // Ha több (vagy éppen kevesebb) kifelyezés maradt a stack-ben, mint az egyetlen végeredmény,
    // akkor érvénytelen kifelyezést kaptunk argumentumként.
    if (stack.size() != 1)
        throw std::runtime_error("Invalid expression given to function.");

    return stack.top();
}

#ifdef LENGYEL
int main()
{
    try
    {
        const auto postfix = infix2postfix("(a + b) * c");
        const auto infix = postfix2infix(postfix);

        std::cout << "Postfix: " << postfix << std::endl;
        std::cout << "Infix: " << infix << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
#endif