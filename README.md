## Prérequis

Cette application nécessite :
- Un compilateur compatible C++20
- Un ordinateur compatible avec OpenGL 4.3

## Comment installer les dépendances pour utiliser le projet ?

Pour installer les dépendances, lancer les commandes suivantes :
- "sudo apt-get install libglfw3-dev"
- "sudo apt-get install libglew-dev"
- "sudo apt-get install libstb-dev"
- "sudo apt-get install libassimp-dev"
- "sudo apt-get install libglm-dev"

## Comment compiler le programme

Il suffit de lancer la commande "make" à la racine du dossier pour compiler l'application

## Comment lancer le programme

Si vous êtes sur ordinateur de bureau ou sur ordinateur portable sans puce graphique dédiée :

"./bin/app.out"

Si vous êtes sur ordinateur portable avec une puce graphique dédié :

NVIDIA : "make run" ou alors "__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia ./bin/app.out"
AMD : "DRI_PRIME=1 ./bin/app.out"