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




