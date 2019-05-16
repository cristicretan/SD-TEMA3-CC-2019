* 311CC Cretan Gheorghe-Cristian
** Tema 3 Structuri de date, Seria CC 2019

# Overview of the homework
* Problem 1
The first problem's difficulties are found in building the graph in
such a manner that you would be able to easily operate with it and perform
operations on it.My idea was that rather than brutally storing all the
actor's names in the graph directly we could make use of a coding, a 1 to 1
correspondance between an actor's name and a number identificator.

The approach was easy to follow, the data structures that needs to be used
came to the mind pretty easily.A binary search tree based on every actor's
name, we would first add all the unique actors name in this binary search tree
and the number identificator were easy to find, just a simple enumerating from
1 to (the number of all unique actor names).This would solve some problems:

** 1.When starting to read the input we can't know how many unique actors
I have, thus don't know with how many nodes we should initialise the graph.
Otherwise would have to reallocate the number of nodes pretty often on tests
with a lot of actors. This reduced a lot of operations.
** 2.A sorting problem when we had to sort all the cut vertices found in
lexicographical order. This would be solved with just an inorder printing
of the constructed binary tree.
** 3.Reduced the number of reallocations to 1.

Now I've constructed my graph with only integers and it's a lot easier to
operate on such a graph.

* Problem 2
On the second problem there were no real difficulties, the problem's statement
was pretty straigh-forward. I had to find the minimum time that Wall-e has to
spend to escape the maze with some conditions on the guardians.

My approach was to implement Dijkstra's shortest path algorithm.Thus for the
beginning we had to build a graph with costs. The costs in this were the time
Wall-e has to spend to teleport from one room of the maze to another.
At first I was naive and thought I should also create a binary tree here for
the time momemnts given for each guardian in each room, but then I realized
rather than creating a binary tree with sorted elements that would result
into just a singly-linked list (giving me a complexity of O(n) searching time)
I can just create arrays for each room with the times that each guardian
will appear at. Thus, I can easily do a binary search on it and easily 
search for the wanted time (giving me a complexity of searching of O(logN)).

For Dijkstra's algorithm to be implemented I would need a heap but then
I thought that I might have duplicates of the costs, thus I created an ordered
multiset that would behave just like a heap.

# Taking each task individually
* Problem 1
** Task 1
For this task I had to determine the number of different productions from each
graph created. Fairly easy to see what this wants me to do is to find the
number of connected components. To do this, we start a depth-first search(DFS)
from each non-visited node, and everytime we start another DFS we add 1 to the
answer.
** Task 2
For this task I had to determine the degree of kinship between 2 actors, which
is nothing more than the shortest path in a unweighted, undirected graph, I
could use other algorithms too, but I chose to use breadth-first search since
it is enought for this task, starting from any of the actors id's, we could
find the minimum distance to the other actor and return it.
** Task3
This tasks asks me straight-forward to determine the cut vertices of the graph.
This can be accomplished easily with a fairly modified depth-first search, at
each point in time, to keep the discovery time of the node and it's low time.
It's low time represents the lowers on the DFS-tree a vertex is without
having a back-edge. Like this we determine the cut vertices and we insert them
in a new binary tree and thus we can easily sort the output lexicographically.
** Bonus
For the bonus task, I used the Bron-Kerbosch algorithm to determine the
maximal clique which is nothing but a complete subgraph of the given graph, it
just has to be maximal. I used binary trees in this task, too, again for fast
sorting at the output.
* Problem 2
For this problem there is almost everything said above, I implemented
Dijkstra's algorithm, using a multiset and some binary search optimizations for
the guardians timestamps.

# Prezentare generala a temei
* Problema 1
Dificultatile prime probleme sunt gasite in construirea grafului in asa fel
incat sa pot opera destul de usor cu acesta. Ideea mea a fost, mai bine decat
sa stochez brutal toate numele actorilor in fiecare nod din graf, am putea
folosi o codificare si o corespondenta 1 la 1 intre aceasta si numele actorului

Aceasta abordare a fost usor de urmarit, structurile de date care trebui a fi
folosite au venit destul de usor in minte.Un arbore binar de cautare bazat pe
numele fiecarui actor, la inceput am adaugat fiecare nume de actor unic in 
acest arbore binar de cautare si codificarea a fost usor de gasit, o simpla
enumerare de la 1 pana la numarul de actori unici. 
Asta ar rezolva niste probleme:
** 1.Cand incep sa citesc inputul nu pot stii cati actori unici exista, astfel
nu stiu cate noduri sa aloc pentru graf. Altfel ar fi trebui sa alocam numarul
de noduri destul de des pe teste cu multi actori. Asta a redus destule operatii.
** 2.O problema de sortare cand aveam nevoie de numele actorilor sortati in
ordine lexicografica. Folosind un arbore binar reducem asta la o simpla afisare
in inordine.
** 3.Am redus numarul de realocari la 1.

Acum am construid graful doar cu intregi si e mult mai usor sa operam pe un
astfel de graf.

* Problema 2
Pentru a 2a problema nu au fost dificultati de genul acesta, input-ul si cerinta
problemei a fost direct. Trebuia sa aflu timpul minim pe care Wall-e trebuie
sa il parcurga astfel incat sa scape din labirint cu unele conditii cu gardienii.

Ideea mea a fost sa implementez algoritmul lui Dijkstra de cea mai scurta cale.
Asadar pentru inceput a trebui sa construim graful cu costurile aferente.
Costurile in acest graf erau reprezentate de timpul de teleportare al lui Wall-e
dintr-o camera a labirintului la alta. La inceput am fost naiv si m-am gandit ca
ar trebui sa creez si aici un arbore binar de cautare pentru fiecare gardian si
timpii acestuia de aparitii in camera respectiva, dar apoi am realizat ca mai bine
decat a crea un arbore binar de cautare dintr-o lista ordonata de numere, as putea
sa fac un vector pentru fiecare camera si timpii aparitiei gardienilor in camera
respectiva, deoarece pe acestia putem aplica cautare binara fiind un vector deja
sortat. Dandu-ne o complexitate mult mai buna decat cautarea intr-un arbore binar
doar cu elemente ordonate (O(n)), am obtinut (O(logn)).

Pentru algoritmul lui Dijkstra am fi avut nevoie de un heap, dar apoi m-am
gandit ca e posibil sa am si costuri duplicate asa ca am implementat un multiset
ordonat care ar actiona exact ca un heap.

# Luand fiecare cerinta in parte
* Problema 1
** Cerinta 1
Pentru aceasta cerinta, a trebuit sa determin numarul de distributii diferite
de actori in graful creat. Ne dam usor seama ca intrebarea este de fapt sa
determinam numarul de componente conexe din graf. Putem obtina asta pornind un
dfs din fiecare nod nevizitat si la fiecare pornire sa adaugam 1 la un contor.
** Cerinta 2
Pentru aceasta cerinta a trebuit sa determin gradul de inrudire dintre 2 actori
ceea ce nu e nimic altceva decat cel mai scurt drum intre 2 noduri intr-un graf
neorientat si fara costuri. Pentru obtinerea acestui rezultat putem aplica o
parcugere in latime pornind din oricare id corespondent cu numele actorilor si
afisand distanta obtinuta.
** Cerinta 3
Aceasta cerinta, ne spune direct sa aflam cate puncte de articulatie exista in
graful creat si care sunt acestea si sa le afisam in ordine lexicografica.
Utilizand arborii binari de cautare pe numele actorilor si un dfs schimbat unde
sa retinem timpul de descoperire al unui nod si "low"-ul acesta, adica cel mai jos
nivel la care poate ajunge un nod (in arborele DFS) fara ca acesta sa aiba 
muchie de intoarcere, putem afla cu usurinta punctele de articulatie.
** Bonus
Pentru cerinta bonus, am folosit algoritmul Bron-Kerbosch pentru a determina
clica maximala, ceea ce nu este altceva decat un subgraf complet maximal in
graful initial. De asemenea, si aici am folosit arbori binari de cautare pentru
a ma ajuta de ei la afisarea rezultatului.
* Problema 2
Pentru aceasta problema am zis cam tot ce era de espus mai sus, am implementat
Dijkstra, folosind un multiset si niste cautari binare pentru optimizari.

# Feedback pentru tema si note:
Tema a fost foarte bine structurata si bine gandita. De asemenea, o aplicare
foarte buna a grafurilor in viata reala. Teoria din spatele celor 6 grade de
separatie este foarte interesanta si mi-a placut.
Faptul ca nu am avut checker local a fost un impediment pentru inceput, dar am
inteles motivele din spate pentru ca nu am primit, a fost un exercitiu bun oricum
sa imi fac propriul checker macar pentru cerintele 1, 2, 3.