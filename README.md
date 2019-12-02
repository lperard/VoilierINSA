
# Projet Voilier 4IR INSA TOULOUSE

Réalisé par Lucas Pérard, Clément Géhin, Ruben Gres et Phillipe Saade

## Fonctionnalités développées :

* Girouette : un codeur incrémental permet de renvoyer l'angle de la girouette en degré, le degré 0 correspond à l'avant du bateau.
ATTENTION : Avant de mettre le bateau à l'eau, il est necessaire de faire un tour de girouette afin de trouver l'origine.
	
* Servo moteur : permet de contrôler le déplacement de la voile en fonction de l'angle transmit par la girouette. La voile se déplace entre un angle de 30 et 100 degrés.
* La voile est positionnée en fonction de la girouette selon une plage d'angles. Celà permet d'éviter de prendre en compter les vibrations de la girouette.
	Note : l'angle minimal correspond à la plus grande pulsation (2 ms) pour la PWM en output

* Contrôle du plateau : permet de contrôler le sens et la vitesse de rotation du plateau. La vitesse est donnée entre 0% et 100% de la vitesse max et le sens est déterminé comme suit : 1 pour droite et -1 pour gauche
	
* Télécommande : il est possible de contrôler le plateau en sens et en vitesse à l'aide d'une télécommande.
	
## Organisation du projet :

* Chaque module possède une implémentation dans le dossier "MyDrivers"
* Le dossier "PeriphServices" comprend les fichiers de configuration des GPIO
* Le dossier "src" comprend le main ainsi que la bibliothèque du stm32
* Le fichier projet pour uVision se trouve dans le dossier "MDK-ARM"