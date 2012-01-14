/--------------------------------------------------------------/
Copyright 2011 Pierre Gradot

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
/--------------------------------------------------------------/

	
-------	DiskDB : a propos


DiskDB est un logiciel permettant de contrôler une base de données SQLite via une interface graphique réalisée avec Qt. Il vous permet la gestion de sa collection de disques, par l'ajout de nouveaux objets dans la base de données et par la consultation des disques enregistrés dans celle-ci.

Ce logiciel n'a pas la prétention d'être d'un niveau professionnel. Il se veut ludique, puisqu'il a été développé à la maison avec pour seuls objectifs de m'amuser et de découvrir Qt.

Ce logiciel ainsi que son code source sont placés sous licence GNU GPL. Vous pouvez consulter le fichier LICENCE.txt accompagnant le programme pour lire le texte de la licence.

Si vous souhaitez me contacter, écrivez-moi à l'adresse suivante :  plgbasura@gmail.com

Si vous souhaitez avoir plus d'informations sur Qt, allez sur le site :
http://qt.nokia.com/title-fr?set_language=fr&cl=fr

Si vous souhaitez avoir plus d'informations sur SQLite, allez sur le site : http://www.sqlite.org/




--------DiskDB : utilisation

Pour lancer DiskDB sous Windows, il suffit de double-cliquer sur fichier exécutable : DiskDB.exe.

Les nombreux fichiers DLL sont nécessaires à l'exécution du programme. Elles contiennent les fonctions offertes par Qt. Il ne faut pas les supprimer.

Quand vous lancerez le programme pour la première fois, il créera un fichier ma_base.db. C'est le fichier SQLite, c'est la base de données. Ce fichier stocke l'ensemble de vos disques. Ne le supprimer sauf si vous souhaitez commencer une nouvelle base. Vous pouvez aussi le sauvegarder de temps en temps, par exemple en vous l'envoyant par email.

