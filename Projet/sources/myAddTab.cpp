/***********************************************************************/
/****** GNU GPL ********************************************************/
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
/***********************************************************************/

/********************
* Bibliotheques perso
********************/
#include "myAddTab.h"

#include "messagesUtilisateur.h"
#include "mySQL.h"

/* Fonction convertTypeToQString
* Cette fonction permet de transformer les valeurs du type enumere typeDisque,
* défini dans le fichier MyAddTab.h.
* Ainsi, on obtient une QString qu'on peut mettre dans la requete d'insertion en base
*
* Paramètre :
* - aConvertir : objet de type typeDisque
* Return :
* - resultatConvertion : objet de type QString donnant la valeur correspondante
*                        en cas d'erreur, le retour est une chaine vide ("")
*/
QString convertTypeToQString(typeDisque aConvertir)
{
    QString resultatConvertion = "";
    if(aConvertir = Aucun)
    {
        resultatConvertion = "Aucun";
    }
    else if(aConvertir = CD)
    {
        resultatConvertion = "CD";
    }
    else if(aConvertir = Vinyle)
    {
        resultatConvertion = "Vinyle";
    }
    else
    {
        // rien
    }
    return resultatConvertion;
}//convertTypeToQString


/* Constructeur MyAddTab
* Construit l'onglet et mettant en place tous les objets de l'interface graphique et en connectant les signaux.
*/
MyAddTab::MyAddTab(void) : QWidget()
{
    //----------------------------------------------------------------------------------------------------------
    // Premier groupe : les details sur le disque
    // Creation des differents champs de texte
    champTitre = new QLineEdit;
    champSortie = new QSpinBox;
    champSortie->setRange(1900,QDate::currentDate().year());
    champSortie->setValue(QDate::currentDate().year());
    champMaison = new QLineEdit;

    // Menu deroulant avec la liste des artistes connus
    // Creation et execution de la requete SQL pour obtenir la listes des artistes
    //QString requeteListeArtistes = "SELECT DISTINCT id_artiste, nom FROM artistes";
    QString requeteListeArtistes = "SELECT DISTINCT nom FROM artistes ORDER BY 1";
    QSqlQueryModel *modeleArtistes = new QSqlQueryModel;
    if( false == MySQL_execQueryModel(requeteListeArtistes, modeleArtistes) )
    {
        QMessageBox::critical(\
            this,\
            MESSAGE_ERREUR_SQL,\
            "Impossible de recuperer la liste des artistes et on ne peut pas initialiser le programme. L'application va se terminer.");
        // On termine le programme en erreur
        exit(1);
    }
    // Combo box pour l'affichage de la liste
    champNom = new QComboBox;
    // Edition autorise
    champNom->setEditable(true);
    // Un champ vide pour entrer son texte
    champNom->insertItem(0,"");
    // Remplissage de la combo box
    for (int i = 0; i < modeleArtistes->rowCount(); i++)
    {
        QString nom = modeleArtistes->record(i).value("nom").toString();
        //int id_artiste = modeleArtistes->record(i).value("id_artiste").toInt();
        //champNom->insertItem(id_artiste+1,nom);
        champNom->insertItem(i+1,nom);
    }

    // Radiobuttons pour le type de disque
    QRadioButton *radioCD = new QRadioButton("CD");
    radioCD->setChecked(true);
    QRadioButton *radioVinyle = new QRadioButton("Vinyle");
    // Mise en forme dans un layout
    QHBoxLayout *layoutTypeDisque = new QHBoxLayout;
    layoutTypeDisque->addWidget(radioCD);
    layoutTypeDisque->addWidget(radioVinyle);
    // Groupe non visible pour savoir lequel est coche
    groupeTypeDisque = new QButtonGroup();
    groupeTypeDisque->addButton(radioCD,1);
    groupeTypeDisque->addButton(radioVinyle,2);

    // Mise en forme dans un layout
    QFormLayout *layoutDetailsDisque = new QFormLayout;
    layoutDetailsDisque->addRow(tr("&Artiste"),champNom);
    layoutDetailsDisque->addRow(tr("&Titre"),champTitre);
    layoutDetailsDisque->addRow(tr("C'est un"),layoutTypeDisque);
    layoutDetailsDisque->addRow(tr("Annee de &sortie"),champSortie);
    layoutDetailsDisque->addRow(tr("Maison de &disque"),champMaison);

    // Insertion dans un QGroupBox
    QGroupBox *blocDetailsDisque = new QGroupBox(tr("C'est quoi ce disque ?"));
    blocDetailsDisque->setLayout(layoutDetailsDisque);



    //----------------------------------------------------------------------------------------------------------
    // Second groupe : les details sur l'obtention
    // Creation des differents champs
    champVille = new QLineEdit;
    champMagasin = new QLineEdit;
    champOffreur = new QLineEdit;
    champPrix = new QDoubleSpinBox;
    champPrix->setRange(0,1000);
    champDate = new QDateEdit;
    champDate->setCalendarPopup(true);
    champDate->setDisplayFormat("dd/MM/yyyy");
    champDate->setDate( QDate::currentDate() );
    champDate->setMaximumDate( QDate::currentDate() );

    // Radiobuttons pour savoir s'il est neuf ou d'occasion
    QRadioButton *radioNeuf = new QRadioButton("Neuf");
    radioNeuf->setChecked(true);
    QRadioButton *radioOccasion = new QRadioButton("D'occasion");
    // Mise en forme dans un layout
    QHBoxLayout *layoutNeufOccasion = new QHBoxLayout;
    layoutNeufOccasion->addWidget(radioNeuf);
    layoutNeufOccasion->addWidget(radioOccasion);
    // Groupe non visible pour savoir lequel est coche
    groupeNeuf = new QButtonGroup();
    groupeNeuf->addButton(radioNeuf,1);
    groupeNeuf->addButton(radioOccasion,2);

    // Mise en forme dans un layout
    QFormLayout *layoutObtention = new QFormLayout;
    layoutObtention->addRow(tr("Il est"),layoutNeufOccasion);
    layoutObtention->addRow(tr("&Magasin"),champMagasin);
    layoutObtention->addRow(tr("&Ville"),champVille);
    layoutObtention->addRow(tr("&Date d'obtention"),champDate);
    layoutObtention->addRow(tr("&Offert par"),champOffreur);
    layoutObtention->addRow(tr("&Prix"),champPrix);

    // Insertion dans un QGroupBox
    QGroupBox *blocObtention = new QGroupBox(tr("Et il sort d'ou ?"));
    blocObtention->setLayout(layoutObtention);

    //----------------------------------------------------------------------------------------------------------
    // Assemblage des blocs
    // Ajout d'un bouton pour valider et ajouter cette nouvelle entree
    boutonAjouter = new QPushButton(tr("Valider"));
    QObject::connect(boutonAjouter, SIGNAL(clicked()), this, SLOT(slotAjouter()));
    // Ajout d'un bouton pour nettoyer tous les champs et ainsi faire une nouvelle entree
    boutonNettoyer = new QPushButton(tr("Effacer"));
    QObject::connect(boutonNettoyer, SIGNAL(clicked()), this, SLOT(slotNettoyer()));
    // Mise en forme dans un layout
    QHBoxLayout *layoutBoutons = new QHBoxLayout;
    layoutBoutons->addWidget(boutonNettoyer);
    layoutBoutons->addWidget(boutonAjouter);

    // Placement dans le layout superieur (avec les 2 blocs et le layout des boutons)
    QVBoxLayout *layoutAddTab = new QVBoxLayout;
    layoutAddTab->addWidget(blocDetailsDisque);
    layoutAddTab->addWidget(blocObtention);
    layoutAddTab->addLayout(layoutBoutons);
    this->setLayout(layoutAddTab);

}//MyAddTab()








/* Slot slotNettoyer
* C'est la fonction qui s'execute quand on clique sur le bouton "Nettoyer".
* Elle efface les valeurs renseignées dans les champs de texte.
* Comme il n'est pas forcément utile de remettre à leur valeur initiale certains champs, on les laisse tels quels.
* On peut ainsi plus facilement entrer les valeurs pour une nouvelle insertion.
*/
void MyAddTab::slotNettoyer(void)
{
    qDebug() << "\n-----slotNettoyer : debut";

    champNom->setCurrentIndex(0);

    champTitre->clear();
    champMaison->clear();
    champVille->clear();
    champMagasin->clear();
    champOffreur->clear();

    champPrix->setValue(0.00);

    qDebug() << "-----slotNettoyer : fin\n";
}








/* Slot slotAjouter
* C'est la fonction qui s'execute quand on clique sur le bouton "Ajouter".
* Elle récupère les valeurs des différents de la GUI, les analyse, et fait les insertions en base qui vont bien.
*/
void MyAddTab::slotAjouter(void)
{
    //----------------------------------------------------------------------------------------------------------
    // Recuperation des parametres principaux : l'artiste et le titre de l'album
    QString nom = champNom->lineEdit()->text();
    QString titre = champTitre->text();

    // Le nom de l'artiste et le titre de l'album doivent etre non vides, pour avoir du sens dans la base
    if(nom.isEmpty() == true || titre.isEmpty() == true)
    {
        if(nom.isEmpty() == true)
        {
            QMessageBox::information(\
                this,\
                MESSAGE_SAISIE_INCORRECTE,\
                "Le champ 'Nom' est vide. Entrez-en un !");
        }
        else //(titre.isEmpty() == true)
        {
            QMessageBox::information(\
                this,\
                MESSAGE_SAISIE_INCORRECTE,\
                "Le champ 'Titre' est vide. Entrez-en un !");
        }

        // Comme l'un (au moins) des 2 champs indispensables est vide,
        // on interrompt la fonction ici
        return;
    }
    else
    {
        // Recuperation et traitement des parametres
        /***********************************************
        * Determination de l'ID de l'artiste
        ***********************************************/

        // Execution de la fonction recuperant l'ID de l'artiste renseigne
        int idTrouve = MySQL_searchElementId("artistes", "nom", nom);

        // Verification du retour de la recherche d'ID et actions adaptees
        // Note : les cas les plus probables sont places en premier
        if( -3 == idTrouve)
        {
            // Nouvel artiste : on demande quoi faire l'utilisateur
            // Texte pour l'utilisateur
            QString texte="L'artiste que vous avez indique n'est pas present dans la base.\n\n";
            texte+="Si vous cliquer sur Oui, vous ajouterez :\n\t"+nom+"\na la base.\n\n";
            texte+="Vous pouvez cliquer sur Non pour modifier le nom de cet artiste.";

            // On demande de confirmer le nom de l'artiste
            int reponse = QMessageBox::question(\
                    this,\
                    MESSAGE_ARTISTE_INCONNU,\
                    texte,\
                    QMessageBox::Yes | QMessageBox::No);

            if(QMessageBox::No == reponse)
            {
                // On arrete les traitement et on revient a l'ecran d'ajout
                return;
            }
            // else : l'utilisateur a valide le nom de l'artiste et on poursuit les traitements
        }
        else if( (-1 == idTrouve) || (-2 == idTrouve) )
        {
            // Erreur de programmation ou SQL. Causes possibles :
            // - la table passee en parametre de la fonction MySQL_searchElementId n'est pas reconnue
            // - le champ passe en parametre de cette fonction n'existe pas et fait planter la requete
            // - la requete SQL plante pour une autre raison
            // - ?...
            QMessageBox::critical(\
                    this,\
                    MESSAGE_ERREUR_PROGRAMMATION,\
                    tr("Erreur critique : impossible de rechercher l'identifiant de l'artiste dans la base. L'application va se terminer."));
            // On termine l'application Qt en erreur
            qApp->exit(1);
        }
        else if( -4 == idTrouve)
        {
            QMessageBox::critical(\
                    this,\
                    MESSAGE_ERREUR_BASE,\
            // On termine l'application Qt en erreur
                    tr("Il y a un probleme dans la base de donnees !\nIl y a plusieurs entrees pour le meme artiste."));
            qApp->exit(1);
        }
        else // (0 <= idTrouve)
        {
            // L'artiste a été trouvé dans la base et on continue les traitements
        }//fin des tests


        /***********************************************
        * Determination de l'ID de l'album
        *
        * Sur le même principe que l'artiste
        * Il faudra modifier le layout de l'onglet
        ***********************************************/

        #warning Il faut implementer un champ ARTISTE similaire au champ ARTISTE

        /***********************************************
        * Recuperation des parametres secondaires
        ***********************************************/
        // Parametres secondaires qui peuvent etre vides.
        QString maison = champMaison->text();
        QString ville = champVille->text();
        QString magasin = champMagasin->text();
        QString offreur = champOffreur->text();
        int sortie = champSortie->value();
        double prix = champPrix->value();

        // Recuperation de la date d'obtention
        QString date = champDate->date().toString("dd/MM/yyyy");

        // Analyse des groupes de radiobuttons
        // Type de disque
        typeDisque type = Aucun;
        int idRadio = groupeTypeDisque->checkedId();
        switch(idRadio)
        {
            case 1:
                type = CD;
                break;
            case 2:
                type = Vinyle;
                break;
            default:
                type = Aucun;
        }
        // Neuf ou occassion
        bool neuf = true;
        idRadio = groupeNeuf->checkedId();
        if(idRadio == 1)
        {
            neuf = true;
        }
        else if(idRadio == 2)
        {
            neuf = false;
        }
        else
        {
            QMessageBox::critical(\
                this,\
                MESSAGE_ERREUR_PROGRAMMATION,\
                "Probleme avec les boutons 'neuf / occassion'. L'application va se terminer.");
            // On termine le programme en erreur
            qApp->exit(1);
        }




        /**************************************************
        * On ajoute les informations necessaires a la base
        **************************************************/
        //---------------------------------------------------------------------------------------------------
        // Table 'artistes' : ajout conditionnel a idTrouve
        int id_artiste = 0;
        if(-3 == idTrouve)
        {
            // Nouvel artiste donc nouvel identifiant : a la fin de la base
            id_artiste = MySQL_elementsCount("artistes");
            #warning Si on offre la possibilite de supprimer des entrees dans la base, cette technique ne sera plus valide

            // Ajout a la base
            QString requeteArtistes = "INSERT INTO artistes VALUES ("\
                                       +QString::number(id_artiste)+","\
                                       +"'"+nom+"'"\
                                       +")";
            MySQL_execQuery(requeteArtistes);

            // On rafraichit le menu deroulant des artistes pour integrer le nouvel artiste
            // Requete de la liste des artistes
            QString requeteListeArtistes = "SELECT DISTINCT nom FROM artistes ORDER BY 1";
            QSqlQueryModel *modeleArtistes = new QSqlQueryModel;
            if( false == MySQL_execQueryModel(requeteListeArtistes, modeleArtistes) )
            {
                QMessageBox::critical(\
                this,\
                MESSAGE_ERREUR_SQL,\
                "Impossible de recuperer la liste des artistes pour mettre a jour la fenetre. L'application va se terminer.");
            // On termine le programme en erreur
            qApp->exit(1);
            }
            // On vide le combo box des artistes qu'il contient deja
            champNom->clear();
            // Remplissage de la combo box
            for (int i = 0; i < modeleArtistes->rowCount(); i++)
            {
                QString nom = modeleArtistes->record(i).value("nom").toString();
                //int id_artiste = modeleArtistes->record(i).value("id_artiste").toInt();
                champNom->insertItem(i+1,nom);
            }
        }
        else
        {
            // idTrouve est superieur ou egal a zero et correspond a un artiste existant
            id_artiste=idTrouve;
            // Pas d'ajout a faire.
        }
        //---------------------------------------------------------------------------------------------------
        // Table "albums"
        int id_album = MySQL_elementsCount("albums");
        QString requeteAlbums = "INSERT INTO albums VALUES ("\
                                        +QString::number(id_album)+","\
                                        +"'"+titre+"'"+","\
                                        +QString::number(sortie)+","\
                                        +"'"+maison+"'"
                                        +")";
        MySQL_execQuery(requeteAlbums);

        //---------------------------------------------------------------------------------------------------
        // Table "element" : ajout systematique
        int id_element = MySQL_elementsCount("elements");
        QString requeteElements = "INSERT INTO elements VALUES ("\
                                       +QString::number(id_element)+","\
                                       +QString::number(id_artiste)+","\
                                       +QString::number(id_album)+","\
                                       +"'"+magasin+"'"+","\
                                       +"'"+ville+"'"+","\
                                       +"'"+offreur+"'"+","\
                                       +QString::number(prix)+","\
                                       +"'"+date+"'"+","\
                                       +QString::number(neuf?1:0)+","\
                                       +"'"+convertTypeToQString(type)+"'"
                                       +")";
        MySQL_execQuery(requeteElements);

        //------------------------------------------------------------------------------------------------------
        // On averti l'utilisateur que l'ajout de ce disque s'est bien passee
        QMessageBox::information(\
                this,\
                MESSAGE_INSERTION_SUCCES,\
                "Le "+convertTypeToQString(type)+" de "+titre+" par "+nom+" a ete ajoute a votre base de donnes.");

    }// ELSE pour "Recuperation et traitement des parametres"
        /***********************************************
        * Fin de la fonction
        ***********************************************/
}//slotAjouter
