# Devoir 1

Julien De Loor (julien.de-loor1@uqac.ca)

Le projet est codé en C++ avec Visual Studio 2013 la solution devoir1.sln contient les 3 exercices, Strassen, Tri et Karatsuba
Tous les executables sont dans le dossier *bin*

## Strassen

*strassen.exe* permet de tester le fonctionnement de Strassen et de comparer les résultats avec une multiplication naïve
``` 
strassen.exe <taille de la matrice> <nombre de d'essais pour le benchmark>
```
Si vous lancez avec Visual Studio la taille de la matrice est de 8 et le nombre d'essai est de 100.

 * Note: en mode Debug l'algorithme est bien plus lent qu'en Release à cause des nombreux *assert*

Dans mes tests il apparait que strassen est toujours beaucoup plus lent que la multiplication naïve à cause (certainement) des nombreuses allocations. 

## Tri

tri.exe permet de tester les algos de tri en spécifiant n (par defaut n = 100)
``` 
tri.exe <n> 
```
tri.exe exporte le résultat dans le fichier 'output.csv'. Les tableaux, courbes et conclusions 
sont dans le pdf 'resultats tri.pdf'

##Karatsuba

karastuba.exe est une mini calculatrice qui supporte les additions et multiplications de 2
nombres entiers positifs.

``` 
karatsuba.exe <a> <'+' or '*'> <b>
```

Note: il faut un espace entre le '+' ou le '*' et les nombres.
