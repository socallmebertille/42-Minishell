# Minishell
As beautiful as a shell

## Git guide

| command | action |
|---|---|
| git branch | -> affiche les differentes branches existantes |
| git pull | -> toujours avant de commencer des modif pour mettre a jour et eviter les conflits |
| git checkout development | -> rentrer dans la branche development |
| git checkout branche_a_copie dossier/fichier_a_copie | -> ajoute ou modifie le fichier_a_copie provenant de la branche_a_copie sur la branche actuelle |

## Testeurs

```
https://docs.google.com/spreadsheets/d/1BPW7k81LJPhGv2fbi35NIIoOC_mGZXQQJDnV0SjulFs/edit?gid=0#gid=0
```

## Step 1 : where to begin ?

Au depart, on cherche a afficher un prompt et ouvrir l'entree clavier. Ces fonctionnalites sont disponibles avec la fonction readline. A noter que c'est une fonction qui creee des leaks visualisables par valgrind. Pour pallier a cette lecture assez indigeste on peut creer un fichier "readline.supp" contenant :
```
{
    readline_leak
    Memcheck:Leak
    match-leak-kinds: reachable
    ...
    fun:readline
    ...
}
```
Ensuite, on peut lancer la commande suivante pour lire valgrind sans les leaks lier a readline : 
```
valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell
```
