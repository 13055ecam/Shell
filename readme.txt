1) Télécharger le fichier zip et l'extraire. 
2) Se rendre à l'emplacemement du fichier via le terminal ("cd...")
3)  Ecrire la commande ./compile.sh pour créer le fichier exécutable "test".

4) option AIDE des commandes
 Ecrire la commande ./test -h stats pour lancer lancer l'aide pour stats 
 Ecrire la commande ./test -h shrink pour lancer lancer l'aide pour shrink 
 Ecrire la commande ./test -h clnup pour lancer lancer l'aide pour clnup 
 Ecrire la commande ./test -h sort pour lancer lancer l'aide pour sort

5) Ecrire la commande ./test -r pour lancer le programme 

Les commandes de notre programme sont les suivantes :

- stats : affiche les infos (taille, nom, date de la dernière modifification) de chaque fichier d'un dossier 
- shrink: compresse les fichiers d'un dossier qui dépassent 500MiB   
- clnup: trie les fichiers d'un dossier dans différents dossiers selon leur type                                                            - sortn: trie les fichiers d'un dossier par nom (Si il y a des doublons, on les met dans un dossier commun)
- quit : quitter le programme
