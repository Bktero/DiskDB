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
#include "mySQL.h"
#include "messagesUtilisateur.h"
#include "myMainWindow.h"
#include "myWelcomeTab.h"
#include "myAddTab.h"

/********************
* Bibliotheques Qt
********************/
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    int resultatExecution = 0;
    // ouverture de la base de donnees
    int connexionBDD = MySQL_openDatabase("ma_base.db");

    // verification du retour
    // selon la valeur, on lance l'application
    // ou on affiche un message d'erreur et on termine l'application
    if( 0 == connexionBDD )
    {
        // Interface utilisateur
        MyMainWindow fenetrePrincipale;
        //MyWelcomeTab fenetrePrincipale;
        //MyAddTab fenetrePrincipale;
        fenetrePrincipale.show();

        //resultatExecution = app.exec();
        return app.exec();

    }
    else if( 1 == connexionBDD )
    {
        resultatExecution = -1;
        QMessageBox::information(\
            0,\
            MESSAGE_ERREUR_CONNEXION,\
            "Votre base de donnees n'est pas accessible. Une autre instance du logiciel est-elle en cours ?\nL'application va se terminer.");
    }
    else if( 2 == connexionBDD || 3  == connexionBDD || 4 == connexionBDD )
    {
        resultatExecution = -234;
        QMessageBox::information(\
            0,\
            MESSAGE_ERREUR_CREATION_BDD,\
            "Une erreur est survenue lors de la creation de la base de données.\nVerifier que le dossier de l'application n'est pas en lecture seule et relancer l'application.");
    }
    else if( 5 == connexionBDD )
    {
        resultatExecution = -5;
        QMessageBox::information(\
            0,\
            MESSAGE_ERREUR_CONNEXION,\
            "Une erreur est survenue lors de la creation de la base de données.\nSupprimer le fichier ma_base.db et relancer l'application.");
    }
    // On termine le programme en erreur
    qDebug() << "Fin de l'application avec le code : "  << resultatExecution;
    return resultatExecution;

}//main

    // Creation du ableau d'onglets

/*
    QTabWidget *ongletsPrincipaux;
    ongletsPrincipaux = new QTabWidget;
    ongletsPrincipaux->setGeometry(10,10,100,100);

    QWidget *onglet1 = new QWidget;
    ongletsPrincipaux->addTab(onglet1, "Accueil");
    QWidget *onglet2 = new QWidget;
    ongletsPrincipaux->addTab(onglet2, "Ajouter");
    QWidget *onglet3 = new QWidget;
    ongletsPrincipaux->addTab(onglet3, "Rechercher");

    ongletsPrincipaux->show();
*/



