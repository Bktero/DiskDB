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


#ifndef MY_SEARCH_TAB_H
#define MY_SEARCH_TAB_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QString>

class MySearchTab : public QWidget
{
    // Necessaire pour faire des "public slots" personnalises
    Q_OBJECT


    public:
        MySearchTab();

    public slots:
        void slotRechercher(void);

    private:
        // Table "artistes"
        QLineEdit *champNom;

        // Table "albums"
        QLineEdit *champTitre;
        QSpinBox *champSortie;
        QLineEdit *champMaison;

        // typeDisque type;
        // QButtonGroup *groupeTypeDisque;
        // pour mettre les radiobuttons
        // bool neuf;
        // true = neuf et false = occassion
        // QButtonGroup *groupeNeuf;

        //QLineEdit *champVille;
        //QLineEdit *champMagasin;
        // ??? *champDate;
        //QLineEdit *champOffreur;

        // Autres
        QPushButton *boutonRechercher;

        // Pour afficher les resultats des recherches
        QTableView *vueResultats;

};

#endif // MY_SEARCH_TAB_H
