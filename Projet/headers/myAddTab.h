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


#ifndef MY_ADD_TAB_H
#define MY_ADD_TAB_H

#include <QApplication>
#include <QButtonGroup>
#include <QComboBox>
#include <QDateEdit>
#include <QGroupBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QWidget>


typedef enum{Aucun,CD,Vinyle} typeDisque;
QString convertTypeToQString(typeDisque);


class MyAddTab : public QWidget
{
    Q_OBJECT // pour le slot personnalise "slotAjouter"

    public:
        MyAddTab();
    public slots:
        void slotAjouter(void);
        void slotNettoyer(void);

    private:
        // En rapport avec la table "artistes"
        QComboBox *champNom;

        // En rapport avec la table "albums"
        QLineEdit *champTitre;
        QSpinBox *champSortie; //annee de sortie
        QLineEdit *champMaison; //maison de disque
        // typeDisque champType
        // --> pas de champ spécifique mais un groupe de radiobuttons
        QButtonGroup *groupeTypeDisque;
        // bool neuf;
        // true = neuf et false = occassion
        // --> pas de champ spécifique mais un groupe de radiobuttons
        QButtonGroup *groupeNeuf;

        // En rapport avec la table "elements"
        QLineEdit *champVille;
        QLineEdit *champMagasin;
        QLineEdit *champOffreur;
        QDateEdit *champDate;
        QDoubleSpinBox *champPrix;

        // Autres
        QPushButton *boutonAjouter;
        QPushButton *boutonNettoyer;

};


#endif // MY_ADD_TAB_H
