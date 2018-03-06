# OrdonancementArchOS

On désire simuler un ordonnancement de plusieurs processus. Ecrivez un programme à qui l’on
transmet, en ligne de commande, un entier, un nom de fichier d’origine et un nom de fichier de
destination. Le processus principal (père) va lire le fichier qu’on lui a transmis et le séparer en groupes
de n lignes, n’étant l’entier fourni. Pour chacun de ces groupes de lignes, il va, avec fork(), créer un
processus fils, en lui fournissant son groupe de ligne et le nom du fichier de destination. Lorsque tous
les fils sont créés, il crée un fichier dont vous choisirez le nom - par exemple toto - dans lequel il place
le PID du premier fils. Puis il attend la terminaison de ses fils. Chaque fois que l’un d’eux est terminé, il
modifie toto pour y mettre le PID du prochain fils. Quand tous sont arrêtés, il s’arrête à son tour.
Chaque fils fonctionne ainsi: il vérifie l’existence du fichier toto et, le cas échéant, lit l’identifiant qui s’y
trouve. Si le fichier n’existe pas ou si l’identifiant n’est pas le sien, il s’endort pendant une seconde à
l’aide de la primitive sleep(int). Sinon, il affiche à l’écran son groupe de lignes et le concatène également
au fichier destination, le créant le cas échéant. Lorsque ceci est fait, il s’arrête.

