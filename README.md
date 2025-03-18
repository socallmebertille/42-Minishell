# Minishell

As beautiful as a shell

## Testers

```
https://docs.google.com/spreadsheets/d/1BPW7k81LJPhGv2fbi35NIIoOC_mGZXQQJDnV0SjulFs/edit?gid=0#gid=0
```

## Step 1 : Git guide

### Step 1.1 : some useful commands

| command | action |
|---|---|
| git branch | -> affiche les differentes branches existantes |
| git pull | -> toujours avant de commencer des modif pour mettre a jour et eviter les conflits |
| git checkout development | -> rentrer dans la branche development |
| git checkout branche_a_copie dossier/fichier_a_copie | -> ajoute ou modifie le fichier_a_copie provenant de la branche_a_copie sur la branche actuelle |

### Step 1.2 : learn how to create a great organization

Generalement, et particulierement dans le developpement informatique il est courant d'utiliser plusieurs branches qui vont suivre une certaine arborescence.

On retrouve ces branches de maniere a observer (ex : sur un projet commun ou il y a 3 developpeurs):

                                main

                                 |

                            development

                        /        |        \

                   user_1      user_2      user_3

De maniere usuelle, chaque user travaille sur sa branche. Ainsi lorsqu'il a termine sa partie du code et qu'elle est fonctionnelle, il met a jour la branche `development` afin de d'avoir la derniere version dans le cas ou un autre user l'aurait mis a jour. Puis il merge la branche `develpment` sur la sienne, pour ensuite merge la sienne sur `development`.

La branche `main` est mise a jour uniquement lorsque chaque user a finit sa partie perso, l'a merge sur `development` et donc que celle-ci est la version final et fonctionnelle du projet. 

### Step 1.3 : learn how to merge your work on a common repo 

De `my_branch` sur `common_branch` (= `development`) :

```
git:(my_branch)$ git pull
git:(my_branch)$ git add .
git:(my_branch)$ git commit -m "comment of your advanced"
git:(my_branch)$ git push
git:(my_branch)$ git merge common_branch
git:(my_branch)$ git push
git:(my_branch)$ git checkout common_branch
git:(common_branch)$ git pull
git:(common_branch)$ git merge my_branch
git:(common_branch)$ git push
```

## Step 2 : where to begin ?

Au depart, on cherche a afficher un prompt et ouvrir l'entree clavier. Ces fonctionnalites sont disponibles avec la fonction `readline()`. A noter que c'est une fonction qui creee des leaks visualisables par valgrind. Pour pallier a cette lecture assez indigeste on peut creer un fichier `readline.supp` contenant :

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

Ensuite, on peut lancer la commande suivante pour lire valgrind sans les leaks lier a `readline()` : 

```
valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell
```

## Step 3 : how to turn your own shell into a real shell

Dans l'entree standard, `readline()` nous renvoie une string avec laquelle il va falloir interagir pour renvoyer un resultat au plus proche d'un shell.

### Step 3.1 : signals

Les signaux sont des actions recu par une interaction de l'utilisateur avec le clavier comme par exemple `CTRL + C` ou `CTRL + D` notamment.

Pour cela, nous devrons creer une variable globale, recuperable a tout endroit dans le code, a laquelle on pourra assigner une certaine valeur (afin de realiser une certaine action en fonction du moment auquel l'utilisateur aura realise ce signal) des la reception d'un certain signal :

```
#include <signal.h>
void (*signal(int sig, void (*func)(int)))(int);
```

Par exemple, si je veux qu'a l'envoie du signal `CTRL + C` (= `SIGINT`) le programme se ferme, je peux ecrire :

```
signal(SIGINT, function_who_kills_prog);
```

### Step 3.2 : remove quotation marks, then expand

Un shell possede un environnement `char **` dans lequel on y trouve une serie de type `char *` assigne a des valeurs `char *`. On y trouve par exemple le `HOME` sous forme `HOME=/home/user`. Et si l'on ecrit `env | grep HOME` le resultat precedemment cite apparaira. Or, il est egalemet possible de recuperer la valeur de `HOME` en ecrivant `echo $HOME`. C'est ca un expand. C'est la valeur `char *` lie a une autre string `char *` presente dans l'environnement `env`.

Il est donc necessaire de realiser ce travail de "transformation" a ce stade de reproduction d'un shell, cad, fouille dans l'environnement si la valeur `char *` qui suit le signe dollar "$" existe dans l'`env` pour ensuite les interchanger.

C'est notamment a ce moment qu'on verifiera si les guillemets (simples ou doubles) ont bien ete fermees, si ce n'est pas le cas, on peut dors et deja renvoyer une erreur. Dans le cas ou les guillemets sont correctement fermees, on peut le retirer de maniere strategique, puis qu'en effet si des guillemets simples se trouve en extremite d'un expand, ce dernier ne doit pas etre expand.

### Step 3.3 : tokens

L'idee de "tokenise" revient a assigner un type a chaque arguments de la string recu dans `readline()`. Il est possible de creer une structure de type `enum` qui permet d'associer une macro liee a un `int` mais plus digeste en terme de lecture. On peut aisement imaginer quelque chose comme :
```
typedef enum e_enum
{
	CMD,
	FLAG,
}					t_enum;
```
Ici, la structure d'`enum` va assigne a `CMD` la valeur "0", puis a `FLAG` la valeur "1".

Le travail a realise ici est d'identifie (= de categoriser) chaque argument qui construit la string de `readline()`, afin de pouvoir manier la ligne de commande. On peut donc creer une liste chainee (ex : `typedef struct t_token`) dans laquelle chaque noeud sera relie a un contenu (= `char *`) et un type (= `t_enum`) ainsi qu'evidemment (et pour faciliter notre travail) un next et un previous (= tous deux de type `t_token`).

### Step 3.4 : parsing

Une fois que la ligne de commande tokenisee il faut proceder au parsing. C'est-a-dire verifier l'ordre des arguments (= tokens) en fonction de leur type. On sait par exemple que le premier arguments est obligatoirement une commande, de meme pour ce qui suit un pipe, etc. C'est ce travail qui doit etre realise en premier. 

On va poursuivre ce meme travail comcernant les redirections, qui doivent etre suivi par un argument :

| redirection | followed by which type | action |
|---|---|---|
| `<` | outfile | cree le fichier s'il n'existe pas, remplace/cree le contenu par le resultat de la commande auquel il est relie |
| `<<` | outfile | cree le fichier s'il n'existe pas, ajoute/cree le contenu par le resultat de la commande auquel il est relie |
| `>` | infile | applique la commande auquel il est relie a partir de la lecture du infile et l'affich dans le terminal |
| `>>` | delimiter | cree un nouveau prompte dans lequel l'utilisateur ecrit jusqu'a ce qu'il rentre de delimiteur et affiche le resultat de la commande auquel il est relie a partir de la lecture du heredoc |

Ensuite, et avant de passer a l'execution des commenades, on peut verifier si chaque commande existe en testant avec les chemins presents dans la variable d'environnement `env` : `PATH=...`.

### Step 3.5 : execution, built-in or not

Le sujet de l'ecole 42 nous impose la construction de certaines commandes appelees "built-in". Il va donc etre necessaire de recoder le fonctionnement de ces commandes. Et, il sera interessant de re-categoriser le type de token des built-in via le systeme d'`enum` par exemple.

Etant donne, que le reste des commandes seront passes a :

```
#include <unistd.h>
int execve(const char *path, char *const argv[], char *const envp[]);
```

et que cette fonction quitte le programme dans lequel elle execute le groupe de commande recue en parametre, il est necessaire de faire un `fork()` en amont, cad, de dupliquer le programme pour qu'`execve()` quitte seulemnt ce duplicata sans mettre fin au programme.

Or, l'execution des built-in ne doit pas etre preceder de ce duplicata. 

On va donc devoir distinguer built-in et commande avant de choisir vers quel type d'execution on envoie chaque groupe de commande (la commande et ses flags). 
Il va sans dire que pour chaque groupe de commande, il est necessaire de verifier s'il est precede ou suivi de redirections pour que le resultat de la commande soit envoye au bon endroit.
