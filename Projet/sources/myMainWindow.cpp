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
#include "myMainWindow.h"


// Constructeur par defaut (sans parametre)
MyMainWindow::MyMainWindow() : QWidget()
{
    // Parametrage de la fenetre
    //setFixedSize(350, 500);
    this->setWindowTitle("DiskDB : ma collection de disques !");

    // Creation du ableau d'onglets
    ongletsPrincipaux = new QTabWidget(this);
    //ongletsPrincipaux->setGeometry(10,10,100,100);
    //ongletsPrincipaux->move(500,500);
    QWidget *onglet1 = new MyWelcomeTab;
    ongletsPrincipaux->addTab(onglet1, tr("Accueil"));
    QWidget *onglet2 = new MyAddTab;
    ongletsPrincipaux->addTab(onglet2, tr("Ajouter"));
    QWidget *onglet3 = new MySearchTab;
    ongletsPrincipaux->addTab(onglet3, tr("Rechercher"));
    QWidget *onglet4 = new MyAboutTab;
    ongletsPrincipaux->addTab(onglet4, tr("A propos"));

    // Connexion du signal indiquant un changement d'onglet
    QObject::connect(ongletsPrincipaux, SIGNAL(currentChanged(int)), onglet1, SLOT(majLCDNombreDisques(int)));

    // Creation du bouton Quitter
    boutonQuitter = new QPushButton(tr("Quitter"),this);
    //boutonQuitter->move(400,20);
    QObject::connect(boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));

    // Creation d'un layout
    QVBoxLayout *layoutFenetrePrincipale = new QVBoxLayout;
    layoutFenetrePrincipale->addWidget(ongletsPrincipaux);
    layoutFenetrePrincipale->addWidget(boutonQuitter);
    this->setLayout(layoutFenetrePrincipale);

    this->move(450,50);

}//MyMainWindow()
