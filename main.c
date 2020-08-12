
/*
I)	initialisation du programme
	1) 	vérification du paramètre en entrée
		a) si le fichier n'existe pas ou qu'il y a plusieurs ou pas de fichier en paramètre, on ferme le programme
	2) 	création de la structure
		a) allocation de la structure
		b) initialisation des éléments de la structure

II)	traitement du fichier envoyé en paramètre
** récupérer les sources de fdf
	1)	on ouvre le fichier
		a)	on vérifie qu'il n'y ait pas de boucle infinie**
	2)	on lit le fichier
		a)	on vérifie que la map est bien conforme**
	3)	on stocke la taille de la map
		a)	protection des maps trop petites / trop grandes
	4)	le 'X' placé dans la map est le point d'origine du personnage
		a)	si X n'est pas présent on remplace le premier '1' disponible en 'X'
		b)	s'il y a plusieurs X, on envoie une erreur et on ferme le programme
		c)	on stocke la position du X dans la map
	Note:	les 0 équivalent à des zones vides, les 1 seront équivalents à du sol et le reste à des objets
	5)	on range le tableau de points dans la structure

III) transformation du tableau en zones spatiales
	1)	si une zone est traitée comme un sol, on applique des murs autour, si il y a un autre sol on enlève le mur en contact
		a)	on considère 2^4 états pour un type de sol
			- 0 pas de mur
			- NSEW avec comme état possible 0 ou 1 pour N,S,E et W en fonction de si il y a un sol voisin (1) ou non (0)
		b)	on stocke l'état de chaque sol dans la structure
	2)	on applique une taille aux sols, murs et objets
		a)	on convertit les variables vers des types compatibles avec les flottants (pour permettre de se déplacer fluidement et de calculer le Raycast)
		b)
	3)	on définit un type de texture en fonction de la position NSEW du mur

IV)	calcul de la position du personnage dans l'espace
	1)	on crée 2 vecteurs : le vecteur de direction et le vecteur caméra.
		a)	le vecteur de direction correspond à la direction et le sens vers lequel le personnage se dirige.
		b)	le vecteur caméra correspond à l'orthogonale du vecteur de direction. Il a pour origine le point d'arrivée du vecteur de direction, et pour points d'arrivées 2 points a égale distance
		c)	le FOV correspond au rapport de ces deux vecteurs. (possibilité de modifier ce paramètre)
	2)	on initie la hauteur du personnage a 70% de la hauteur des murs (axe Z), on le déplacera dans l'axe du vecteur de direction
	3)	le personnage ne peut se déplacer que si le point en dessous de lui est un sol et qu'il n'est pas trop proche d'un mur
		a)	on prend la position d'origine du point, et on ajoute la valeur de l'offset créé par les mouvements du joueur
	4)	on calcule le rendu de l'image a raycast
		a)	Pour chaque rayon à caster
			- on envoie le rayon depuis la position du personnage vers la position des points dessinés par la caméra.
			- a chaque fois qu'on entre dans une nouvelle zone, on vérifie que le point ne touche pas un mur.
			- si on touche un mur on calcule la distance entre l'origine et l'arrivée, on connait l'angle, ce qui nous donne la valeur de couleur position finale sur l'écran.
		b)	on passe au rayon suivant


V)	affichage du rendu et gestion des events
	1)	lancer l'ouverture de la fenetre
	2)	ESC ou croix = sortie du programme
	3)	les fleches UP/DOWN font avancer/reculer le personnage
	4)	les flèches LEFT/RIGHT font tourner le personnage
*/

int	main(int argc, char **argv)
{


	return (0);
}
