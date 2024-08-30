/*

1.  Introduction dans la programmation C

1.7 Mise en pratique : d�couverte du compilateur

Exercice 1
Installer un compilateur, Code::Blocks ou Visual Studio. Une recherche Google vous
indique o� ces compilateurs sont t�l�chargeables sur Internet :
Pour codeblocks http://www.codeblocks.org/
et pour Visual Studio Express http://www.microsoft.com/fr-fr/download/details.aspx?id=40787

Une fois l'installation du compilateur termin�e, rep�rer sur le disque l'emplacement
des dossiers include et lib du compilateur. Attention � ne rien modifier. Lancer le compilateur
que vous avez install�, Code::Blocks ou Visual Studio.
Rep�rer les �tapes de la cr�ation d'un projet, cr�er un projet vide ou un projet "console
application". Attention � bien nommer votre projet et bien le positionner sur votre
disque dur. Pour Visual Studio, bien faire la distinction entre la solution, qui est un
ensemble de projets, et le projet qui est un �l�ment d'une solution.

Exercice 2
Si le projet est vide, ajouter une page de code et �crire votre main(), puis afficher "ce
que vous voulez" avec la fonction printf(). Cette fonction s'obtient avec un include,
au-dessus du main(), de la librairie stdio.h.
Une fois le programme termin�, le compiler et l�ex�cuter. Si la fen�tre console s'ouvre
et se referme imm�diatement, ajouter l'instruction suivante juste avant le return
final :
system("PAUSE");
Recompiler, relancer.
Recommencer en modifiant quelque chose � chaque fois, par exemple :
� Ajouter \n � la fin du message, des accents �, �, �, �, �, etc.
� Supprimer le point-virgule, un ou deux guillemets, une parenth�se...
Dans quels cas y a-t-il un message d'erreur et quel est-il ?

Exercice 3
Faire un dessin en utilisant plusieurs fois de suite la fonction printf() et plusieurs affichages
successifs de cha�nes de caract�res.

*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Ces questions supposent de la manipulation et il n'y a pas de corrige � faire!\n");
    return 0;
}
