
/*
I)	initialisation du programme
	1) 	vérification du paramètre en entrée
		a) si le fichier n'existe pas ou qu'il y a plusieurs fichiers ou pas de fichier en paramètre, on ferme le programme
	2) 	création de la structure
		a) allocation de la structure
		b) initialisation des éléments de la structure

II)	traitement du fichier envoyé en paramètre
	1)	on ouvre le fichier
	2)	on lit le fichier
	3)	on stocke la taille de la map
		a)	protection des maps trop petites / trop grandes
	4)	le 'X' placé dans la map est le point d'origine du personnage
		a)	si X n'est pas présent on remplace le premier '1' disponible
		b)	s'il y a plusieurs X, on envoie une erreur et on ferme le programme
		c)	les 0 équivalent à des zones vides, les 1 seront équivalents à du sol et le reste à des objets
		d)	on stocke la position du X dans la map
	5)	on range le tableau de points dans la structure

III)transformation du fichier en zones spatiales
	1)	si une zone est traitée comme un sol, on applique des murs autour, si il y a un autre sol on enlève le mur en contact
		a)	on considère 2^4 états pour un type de sol
			- 0 pas de mur
			- NSEW avec comme état possible 0 ou 1 pour N,S,E et W en fonction de si il y a un sol voisin (1) ou non (0)
		b) on stocke l'état de chaque sol dans la structure
	2)	on applique une taille aux sols, murs et objets
	3)	on applique un type de texture en fonction de la position NSEW du mur

IV)	calcul de la position du personnage dans l'espace
	1)	on initie la hauteur du personnage, on le déplacera dans l'axe des X et Y de la map
	2)	le personnage ne peut se déplacer que si le point en dessous de lui est un sol et qu'il n'est pas trop proche d'un mur
	3)	la position du personnage permet de calculer l'éclairage et donc le rendu a afficher

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
