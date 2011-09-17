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
#include "myWelcomeTab.h"

#include "messagesUtilisateur.h"
#include "mySQL.h"



MyWelcomeTab::MyWelcomeTab() : QWidget()
{
    // Comptage du nbr de disques
    int nbrDisques = MySQL_elementsCount("elements");
    if(nbrDisques < 0)
    {
        QMessageBox::critical(\
            this,\
            MESSAGE_ERREUR_SQL,\
            tr("Il a ete impossible de compter le nombre d'element dans la base de donnees. Le fonctionnement pourrait s'en trouver corrompu.\nL'application va se terminer."));
            // On termine le programme en erreur
            exit(1);

    }

    // Creation des objets
    LCDNombreDisques = new QLCDNumber;
    LCDNombreDisques->setSegmentStyle(QLCDNumber::Flat);
    LCDNombreDisques->display(nbrDisques);
    QLabel *texteNombreDisques = new QLabel;
    texteNombreDisques->setText(tr("Nombre de disques dans la base :"));

    // Positionnement dans un layout
    QGridLayout *layoutWelcomeTab = new QGridLayout;
    layoutWelcomeTab->addWidget(LCDNombreDisques,0,1);
    layoutWelcomeTab->addWidget(texteNombreDisques,0,0);
    this->setLayout(layoutWelcomeTab);

}//MyWelcomeTab()


void MyWelcomeTab::majLCDNombreDisques(int currentTabIndex)
{
    qDebug() << "\n-----majLCDNombreDisques (index = " << currentTabIndex << ") : debut";

    // Si l'onglet courant est l'onglet d'accueil (le premier de la liste)
    if(currentTabIndex == 0)
    {
        // Comptage du nbr de disques
        int nbrDisques = MySQL_elementsCount("elements");
        if(nbrDisques < 0)
        {
            // Erreur lors de la requete sur la base
            QMessageBox::critical(\
                this,\
                MESSAGE_ERREUR_SQL,\
                tr("Il a ete impossible de compter le nombre d'element dans la base de donnees. Le fonctionnement pourrait s'en trouver corrompu.\nL'application va se terminer."));
            // On termine l'application Qt en erreur
            qApp->exit(1);
        }
        // Mise a jour de l'afficheur LCD
        this->LCDNombreDisques->display(nbrDisques);
    }
    // else : rien

    qDebug() << "-----majLCDNombreDisques : fin\n";
}//majLCDNombreDisques
