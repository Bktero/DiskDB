/**********************************************************************
****** GNU GPL ********************************************************
Copyright 2011 Pierre Gradot

This file is part of DiskDB.

DiskDB is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/


/********************
* Bibliotheques perso
********************/
#include "mySearchTab.h"
#include "mySQL.h"
#include "messagesUtilisateur.h"



MySearchTab::MySearchTab(void) : QWidget()
{

    // Creation des champs de recherche
    champNom = new QLineEdit;
    champTitre = new QLineEdit;
    champSortie = new QSpinBox;
    champMaison = new QLineEdit;

    // Assemblage dans un layout de formulaire
    QFormLayout *layoutChampsRecherche = new QFormLayout;
    layoutChampsRecherche->addRow(tr("Artiste"),champNom);
    layoutChampsRecherche->addRow(tr("Titre"),champTitre);
    layoutChampsRecherche->addRow(tr("Annee de sortie"),champSortie);
    layoutChampsRecherche->addRow(tr("Maison de disque"),champMaison);

    // Ajout d'un bouton Recherche
    boutonRechercher = new QPushButton(tr("Rechercher"));
    layoutChampsRecherche->addWidget(boutonRechercher);
    // Associer une action au bouton "Rechercher"
    QObject::connect(boutonRechercher, SIGNAL(clicked()), this, SLOT(slotRechercher()));


    // Ajout d'une visualisation de table pour afficher les resultats
    vueResultats = new QTableView();
    layoutChampsRecherche->addWidget(vueResultats);

    // Application du layout au widget formant l'onglet
    this->setLayout(layoutChampsRecherche);
}


void MySearchTab::slotRechercher(void)
{
    // Recuperation des valeurs des champs
    QString nom = champNom->text();
    QString titre = champTitre->text();
    int sortie = champSortie->value();
    QString maison = champMaison->text();

    // Construction de la requete SQL
    QString requeteSQL = \
"SELECT nom, titre, sortie, maison, ville, magasin, prix, offreur, dateObtention, typeDisque \
FROM elements INNER JOIN artistes ON elements.id_artiste = artistes.id_artiste \
INNER JOIN albums ON elements.id_album = albums.id_album \
WHERE elements.id_artiste IS NOT NULL";

    // Rajout des differents criteres";
    if(nom.isEmpty() == false)
    {
        requeteSQL += " AND nom LIKE '%"+nom+"%'";
    }
    if((titre.isEmpty() == false))
    {
        requeteSQL += " AND titre LIKE '%"+titre+"%'";
    }
    if((sortie != 0))
    {
        requeteSQL += " AND sortie='"+QString::number(sortie)+"'";
    }
    if((maison.isEmpty() == false))
    {
        requeteSQL += " AND maison LIKE '%"+maison+"%'";
    }

/*  Pour ajouter une nouvelle clause :
    if((.isEmpty() == false))
    {
        requeteSQL += "AND ='"++"'";
    }
*/

    // Execution de la requete avec des classes de plus haut niveau
    QSqlQueryModel *model = new QSqlQueryModel;
    if( false == MySQL_execQueryModel(requeteSQL, model) )
    {
        QMessageBox::critical(\
            this,\
            MESSAGE_ERREUR_SQL,\
            "Impossible d'acceder aux resultats de la recherche. Essayez a nouveau.");
    }
    // Affichage
    vueResultats->setModel(model);
    vueResultats->resizeColumnsToContents();
    //vueResultats->show();

}// slotRechercher

