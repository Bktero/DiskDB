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


#ifndef MY_MAIN_WINDOW_H
#define MY_MAIN_WINDOW_H

#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QWidget>

/********************
* Bibliotheques perso
********************/

#include "myWelcomeTab.h"
#include "myAddTab.h"
#include "mySearchTab.h"
#include "myAboutTab.h"


class MyMainWindow : public QWidget
{
    public:
    // constructeur par defaut
    MyMainWindow();

    private:
    // bouton Quitter
    QPushButton *boutonQuitter;
    // tableau d'onglets
    QTabWidget *ongletsPrincipaux;

};

#endif
