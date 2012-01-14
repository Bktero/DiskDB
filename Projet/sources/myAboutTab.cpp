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
#include "myAboutTab.h"

MyAboutTab::MyAboutTab(void) : QWidget()
{
    // Creation des elements
    QLabel *imageQt = new QLabel;
    imageQt->setPixmap(QPixmap("imageQt.png"));
    QLabel *blabla = new QLabel;

    QString texteBlabla = "Ce logiciel est realise en C++ et il utilise Qt.\n";
    texteBlabla += "Il vous permet de lister tous vos disques dans une base de donnees. ";
    texteBlabla += "Pour chaque disque, un ensemble de donn�es peut �tre renseign�, comme l'artiste, le magasin o� il a �t� achet�, la personne qui vous l'a offert...\n";
    texteBlabla += "Qt est un framework, particuli�rement utilis� pour cr�er des interface graphiques. ";
    texteBlabla += "C'est le cas pour ce logiciel. Qt poss�de �galement bien d'autres fonctionnalit�s. ";
    texteBlabla += "C'est par exemple avec les outils Qt que la base de donn�es SQLite dans laquelle sont enregistr�es les informations sur vos disques est g�r�e.";

    blabla->setText(texteBlabla);
    blabla->setMargin(10);
    blabla->setWordWrap(true);


    // Assemblage dans un layout
    QVBoxLayout *layoutAboutTab = new QVBoxLayout;
    layoutAboutTab->addWidget(imageQt);
    layoutAboutTab->addWidget(blabla);
    this->setLayout(layoutAboutTab);

}//MyAboutTab()
