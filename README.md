# Résumé: Détection de markers ArUco

L’objet de mon projet d’étude et réalisation porte sur la conception d’un programme en langage C++ permettant d’éviter les collisions entre deux robots autonomes ainsi que d’optimiser ses déplacements et ses prises de décisions.  
En vue de d’effectuer la détection et la caractérisation dans l’espace de tag ArUco, j’utilise la bibliothèque graphique OpenCV qui me permet de détecter des objets dans l’espace à l’aide de leur forme. Un programme en C++ sera développé pour permettre une analyse temps réel de notre système.  
Pour se faire, je possède une webcam Spedal 920 Pro, disposé sur un mat à une hauteur de 1m et ayant un visuel sur l’ensemble du plateau sur lequel le robot autonome doit évoluer.  
Afin de répondre à la problématique de vitesse de calcul j’ai opté pour un nano ordinateur Raspberry PI permettant d’héberger le programme servant aux calculs des postions des tags ArUco dans l’espace ainsi que de la communication entre le robot et le Raspberry PI.

