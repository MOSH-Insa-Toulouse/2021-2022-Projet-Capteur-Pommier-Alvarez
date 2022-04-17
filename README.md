# 2021-2022-Projet-Capteur-Pommier-Alvarez
 
## Description Générale

Dans le cadre de l’unité de formation « Du capteur et banc de test » de l’année scolaire 2021-2022 en quatrième année de Génie Physique à l’INSA Toulouse, nous devions réaliser une jauge de contrainte à base de graphite.

Afin de mener ce projet à bien tout en respectant l’esprit de autour de ce capteur (Low tech, low cost et transportable), nous avons utilisé une carte Arduino Uno, un PCB, et différents composants détaillés par la suite.

## Table des matières
* [Livrables](#livrables)
* [Composants](#comp)
* [PCB Shield](#pcb)
* [Application](#apk)
* [Arduino](#ard)
* [Banc de test](#banc)
* [Datasheet](#data)
* [Améliorations](#ameliorations)


<div id='livrables'/>

## Livrables

Les livrables à l’issu de ce projet sont:
* Un rapport sur le circuit analogique à l'aide du logiciel LTSpice
* Un PCB Shield
* Un code Arduino permettant de collecter et transférer les données du capteur soit
sur un oled soit à un module bluetooth connecté à un Android.
* Une application APK
* Un banc de test
* Une datasheet

<div id='comp'/>

## Composants

Les composants pour la réalisation du circuit analogique sont les suivants :
* Arduino Uno
* LTC1050
* Module Bluetooth HC05
* OLED 128x64
* Encodeur rotatif GT055
* R4 : Capteur papier
* Résistances: 100kOhms (x2), 1kOhms(x2), 10kOhms
* Capacités: 100nF(x3), 1uF

<div id='pcb'/>

## PCB Shield

La première étape dans la création du PCB a été la création du Schematic sur le logiciel KiCAD. Nous devions créer chacun des composants et déterminer à quels pin de l'Arduino étaient connectés chacun ds pins des composants.

![Shematic](https://github.com/MOSH-Insa-Toulouse/2021-2022-Projet-Capteur-Pommier-Alvarez/blob/main/Kicad/Sch%C3%A9matique.png)

L'étape suivante a été le placement des composants sur le PCB et la connexion entre chaque pin et finalement, la représentation 3D des composants pour s'assurer qu'aucun ne se chevauchaient.

![routage](https://github.com/MOSH-Insa-Toulouse/2021-2022-Projet-Capteur-Pommier-Alvarez/blob/main/Kicad/routage.png)

Après l'étape de réalisation du PCB avec le logiciel KiCAD est venue l'étape de réalisation physique de celui-ci. C'est avec l'aide de Madame Crouzet que cela a été possible.

Enfin, le PCB a été percé avec des trous de 1mm de diamètre pour les pins de
l'Arduino et 0,8mm de diamètre pour les autres.

Les détails du PCB et du Schematic se trouvent dans le dossier [KiCAD](https://github.com/MOSH-Insa-Toulouse/2021-2022-Projet-Capteur-Pommier-Alvarez/tree/main/Kicad) 

<div id='apk'/>

## Application

Les informations envoyées par le module bluetooth sont récupérées sur une application Android faite grâce au site [MIT App Inventor](https://appinventor.mit.edu/).

Notre application se compose de trois écrans différents. Le premier est une page de garde qui permet d'accéder aux deux autres écrans, soit un écran d'informations générales sur le fonctionnement du capteur soit un écran qui permet la connexion bluetooth et la visualisation des données reçues.
Sur ce dernier la valeur de la résistance est affichée dans une zone texte et tracée au et à mesure sur un graphique.

Voici l'ecran avec le graphique:

![graph](https://github.com/MOSH-Insa-Toulouse/2021-2022-Projet-Capteur-Pommier-Alvarez/blob/main/APK/page_graphique.png)


Les photos et le code de l'application se trouvent dans le dossier [APK](https://github.com/MOSH-Insa-Toulouse/2021-2022-Projet-Capteur-Pommier-Alvarez/tree/main/APK)

<div id='ard'/>

## Code Arduino

Afin que tout cela soit possible et fonctionnel nous devions écrire un code Arduino. Celui-ci permet de récupérer les valeurs de la résistances, se connecter au module bluetooth avec un téléphone et les envoyer par la suite. Il permet également de visualiser ces valeur sur un écran OLED constitué de trois menus différents pilotés par l'encodeur rotatif. Ces trois menus sont une page de présentation, une page d'informations et une page avec les valeurs.
Un autre code fut nécéssaire pour pouvoir gérer notre banc de test, celui-ci sera expliqué dans la partie suivante.

Les informations relatives au code se trouvent dans le dossier Arduino

<div id='banc'/>

## Banc de test

Afin de pouvoir rédiger notre datasheet mais également de pouvoir connaître la répétabilité de la mesure avec un seul capteur nous avions besoin d'un banc de test. Celui-ci fut réalisé en collaboration avec le groupe de Louis-Maxence Hotton et Thalia Lamy.
Notre banc de test est composé d'un servo-moteur et de pièces recyclées (papier et carton recyclés). Un code Arduino permet de piloter celui-ci et de faire une rotation de 0° à 90°. Afin d'avoir les valeurs en compression et dilatation nous avons retourné le capteur.

![banc de test](https://github.com/MOSH-Insa-Toulouse/2021-2022-Projet-Capteur-Pommier-Alvarez/blob/main/Banc_de_test/banc_de_test4.JPG)

Les photos du banc de test sont dans le dossier [banc de test](https://github.com/MOSH-Insa-Toulouse/2021-2022-Projet-Capteur-Pommier-Alvarez/tree/main/Banc_de_test) et le code associé dans le dossier Arduino

<div id='data'/>

## Datasheet

Les données de la datasheet ont été mesurées à l'aide du banc de test décrit ci- dessus. Nous avons fait les mesures avec des crayons HB et 2B. Pour les mesures nous avons fait cinq séries en compression, effectué la moyenne de ces séries et répété l'opération avec la dilatation pour chacun des crayons.
Nous avons testé avec un crayon 6B mais notre programme nous annonçait un overload.

Nous avons estimé la répétabilité de l'expérience à 10 mesures par capteur (papier) soit 5 en compression suivies de 5 en dilatation car après cela les valeurs nous semblaient moins cohérentes avec les premières séries.

La datasheet se trouve dans le dossier [datasheet](https://github.com/MOSH-Insa-Toulouse/2021-2022-Projet-Capteur-Pommier-Alvarez/blob/main/Datasheet%20jauge%20de%20contrainte%20graphite.pdf).

<div id='ameliorations'/>

## Améliorations

L'utilisation du banc de test a nécessité deux cartes Arduino Uno. Il aurait fallu intégrer le servo moteur sur le KiCAD pour pouvoir le mettre sur le PCB et ainsi le faire fonctionner avec une seule carte et un seul programme.

Comme améliorations pour les valeurs de la datasheet, peut être faudrait-il utiliser plusieurs capteurs avec le même crayon (par exemple HB), faire les 10 séries de mesures et faire la moyenne sur toutes les séries des différents capteurs.

On peut également penser pour l'application à l'affichage d'un message pour signaler que la connexion bluetooth s'est effectuée.
