# (Fordított) Lengyel jelölés - aka.: postfix

A lengyel jelölés lényege, hogy az általában binért operátorok az operandusai után vannak jelölve.
    
    a + b = a b +
    a + b * c = a b c * +
    (a + b) * c = a b + c *

## A kiértékelési folyamatot így lehetne röviden leírni: 

Balról jobbra haladunk a kifejezésen
 
 - Ha egy operandus jön velünk szembe, egy verembe tesszük
 - Ha egy operátor jön velünk szembe, akkor 2 értéket kiszedünk a veremből, elvégezzük az műveletet, majd az eredmény ismét a verembe tesszük

### Ezek alapján egy példa:
  
    input := 2 3 + 5 * // (2 + 3) * 5

Első karakter: 2  
'2' egy operandus, tehát megy a stack-re.

    stack = [2]

Második karakter: 3  
'3' egy operandus, tehát ő is megy a stack-re.

    stack = [2, 3]

Harmadik karakter: +  
'+' egy operátor, tehát kiszedünk két operandust a veremből, elvégezzük a megfelelő műveletet, végül az eredményt tesszük a verembe.

    stack = [5]

Negyedik karakter: 5  
'5' egy operandus, tehát ő is megy a stack-re.

    stack = [5, 5]

Ötödik karakter: *  
'*' egy operátor, tehát kiszedünk két operandust a veremből, elvégezzük a megfelelő műveletet, végül az eredményt tesszük a verembe.

    stack = [25]

Ha minden jól ment, akkor csak a végeredmény marandt a veremben.

    eredmény := stack.top()

## Infix jelölés átalakítása postfix jelöléssé

A folyamat hasonlít a feljebb tárgyalt kiértékeléshez, annyi különbséggel, hogy most az operátorokat fogjuk egy veremben tárolni feldolgozásig.

### Struktogramm
Előzetesen itt egy struktogramm, ha valaki pont ezt keresné.

![infix2postfix struki](/assets/LengyelStruki.png)

### Az algoritmus logikai lépései

Balról jobbra haladunk a kifejezésen

 - Ha egy operandus jön velünk szembe, akkor azt hozzáadjuk a kimenethez.
 - Ha egy nyitott zárójel jön velünk szembe, akkor a verembe tesszük
 - Ha egy csukott zárójellel találkozunk, akkor addig szedjük ki és adjuk a kimenethez a verem elemeit, míg nyitott zárójellel nem találkozunk. Végül azt is kivesszük.
 - Ha operátorral ralálkozunk, akkor mindaddig szedjük és írjük ki a verem elemeit, míg magasabb precedenciájú elemmel, vagy zárójellel nem találkozunk. Végül betesszük a kurrens operátort a verembe.
 - Utolsó lépésként kiírjuk az összes veremben maradt operátort.

 ### Ezek alapján egy példa:

    input := (2 + 3) * 5
Első karakter: '(', tehát a verembe helyezzük.
    
    stack = [ ( ]

A következő karakter: '2', tehát hozzáadjuk a kimenethez.

    stack = [ ( ]
    output = 2

A következő karakter: '+', és mivel csak egy nyitó zárójel van a verem tetején, ezért csak a verem tetejére kell tennünk.

    stack = [ (, + ]
    output = 2

A következő karakter: '3', tehát hozzáadjuk a kimenethez.

    stack = [ (, + ]
    output = 2 3

A következő karakter: ')', tehát addig addjuk a stack felső elemeit a kimenethez, míg '(' karaktert nem találunk. Végül azt is eltávolítjuk.

    stack = [  ]
    output = 2 3 +

A következő karakter a '*'. Nem tudunk mást tenni, csak a verembe helyezni.

    stack = [ * ]
    output = 2 3 +

Az utolsó karakter az '5', ezt az eredményhez adjuk.

    stack = [ * ]
    output = 2 3 + 5

Mivel minden karakterünk elfogyott, ezért az összes stack-ben maradt elemet az eredményhez adunk.

    stack = [  ]
    output = 2 3 + 5 *
