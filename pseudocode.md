# I)	initialisation du programme
#	A)	vérification du paramètre en entrée
#		1) si le fichier n'existe pas ou qu'il y a plusieurs ou pas de fichier en paramètre, on ferme le programme
#	B)	création de la structure
#		1)  allocation de la structure wolf qui regroupe tous les parametres du wolf
		2)  initialisation des éléments de la structure
			- X ?
			- Y ?
			- Z ?
#		3)  ajout d'un pointeur map qui va récupérer la structure t_token_t:{unsigned:1 type(bloc/sprite), unsigned:1 crossable(oui/non), unsigned:1 origin(), unsigned:1 pickable, unsigned:3 texture (pragma packed), '\0'}

# II)	traitement du fichier envoyé en paramètre
#	A)	on ouvre le fichier
#		1)	on vérifie qu'il n'y ait pas de boucle infinie
#	B)	on lit le fichier
#		1)	on vérifie que la map est bien conforme
#	C)	on stocke la taille de la map
#		1)	protection des maps trop grandes ou pleines
#		2)  caster directement le contenu du token dans t_token_t
#	D)	le bit position actif seul placé dans la map est le point d'origine du personnage, si il est actif avec d'autres bits, il devient le point déteminant du vecteur de direction
#		1)	si bit position n'est pas présent on considère le dernier crossable disponible
#		2)  si le vecteur position n'est pas défini, on le place vers la face nord.
#		3)	s'il y a plusieurs position joueur ou vecteur direction, on récupère la dernière position connue
#		4)	on stocke les positions et rotation (angle vecteur direction et horizontale) du joueur dans la structure wolf3d
#		5)  on décale de +0,5 bloc pour mettre au centre l'origine

# III)	calcul de la position du personnage dans l'espace
#	A)	on définit le FOV
#		1)  on alloue un tableau de la taille du nombre de pixels sur la fenêtre (en float llf)
#		2)  on calcule les angles des rayons de raycasting
#            a)  on utilise le nombre de pixels de l'image et le FOV pour définir l'angle de chaque rayon
	B)	on initie la hauteur du personnage a 70% de la hauteur des murs (axe Z), on le déplacera dans l'axe du vecteur de direction

# IV)	lancer l'ouverture de la fenetre
	A)	initialisation de la sdl
		1)	creation du pointeur de fenetre
		2)	création du pointeur de rendu
		
	B)	création d'une image SDL
	C)	création de la fenêtre

# V)	affichage du rendu
    A)	on calcule le rendu de l'image a raycast
		1)	Pour chaque rayon à caster
			- on envoie le rayon depuis la position du personnage dans la direction de rotation du joueur + valeur de l'angle du rayon
			- pour chaque rayon, on calcule une distance
		2)	on passe au rayon suivant
    B) put image to window

# VI)     Gestion des events
	A)	ESC ou croix = sortie du programme
	B)	les fleches UP/DOWN et W/S font avancer/reculer le personnage
        1)  le personnage ne peut se déplacer que si le point de destination est valide et qu'il n'est pas trop proche d'un mur
	C)	les flèches LEFT/RIGHT A/D font tourner le personnage
