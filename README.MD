# Labirynt

Gra polega na dotarciu graczami do mety. Plansza jest podzielona na kwadratowe pola, każde o określonym typie (mur, trawa, drzwi, bramka, przycisk, meta). Na planszy znajdują się także gracze, przeciwnicy, pudełka (które gracz może przesuwać), monety i klucze (które można zbierać) oraz ziemia (którą gracz może przekopać). W momencie spotkania z przeciwnikiem gracz traci jedno życie - jeśli straci wszystkie, gra kończy się porażką. Ukończenie poziomu może wymagać zebrania określonej liczby monet. Aby przechodzić przez drzwi, trzeba posiadać klucz określonego koloru. Aby otworzyć bramkę, należy nacisnąć odpowiadający jej przycisk. Gra jest wyposażona także w edytor umożliwiający tworzenie własnych poziomów.

Zrzut ekranu prototypu:

![](https://i.imgur.com/2YHxI2k.png)


Schemat UML:

![](https://i.imgur.com/Xfxkx5A.png)

Aby skompilować, należy pobrać archiwum z biblioteką SFML (https://www.sfml-dev.org/download/sfml/2.5.1/) i wypakować w tym samym folderze, w którym są pliki źródłowe.
Można użyć komend:
`g++ -c src/*.cpp -ISFML-2.5.1/include -std=c++17`
`g++ *.o -o main -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system`
