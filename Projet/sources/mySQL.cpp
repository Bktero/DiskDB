/*********************************************************************
****** GNU GPL *******************************************************
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



#include "mySQL.h"


/*
Lu dans la doc :

If you iterate through a result set only using next() and seek()
with positive values, you can call QSqlQuery::setForwardOnly(true)
before calling exec(). This is an easy optimization
that will speed up the query significantly
when operating on large result sets.

*/


/*
MySQL_execQueryModel :
- execute la requete SQL via le modele (passés en parametre)
- la base de donnes est supposee deja ouverte (on utilise la connexion par defaut)
- contrairement à MySQL_execQuery, on peut utiliser les resultats grace au modele

Parametres :
- IN : QString maRequete = la requete SQL
- OUT : QSqlQueryModel *monModele = pointeur sur le modele a modifier
- return : TRUE si tout s'est bien passe ; FALSE en cas d'erreur
*/
bool MySQL_execQueryModel(QString maRequete, QSqlQueryModel *monModele)
{
    qDebug() << "\n-----MySQL_execQueryModel : debut";
    qDebug() << maRequete;

    // Execution de la requete
    monModele->setQuery(maRequete);

    // Verification de la bonne execution de la requete
    bool validErr = monModele->lastError().isValid();
    if (validErr == true)
    {
        qDebug() << monModele->lastError();
    }
    else
    {
        qDebug() << "La requete avec le modele s'est bien executee";
    }

    qDebug() << "-----MySQL_execQueryModel : fin\n";
    return (!validErr); // S'il y a une erreur valide, alors ca s'est mal execute
} // MySQL_execQueryModel



/*
MySQL_execQuery :
- execute la requete SQL passee en parametre
- la base de donnes est supposee deja ouverte (on utilise la connexion par defaut)
- ne permet pas de récupérer des résultats : uniquement adaptee pour des requetes
du type "INSERT INTO...."

Parametres :
- IN : QString maRequete = la requete SQL
- OUT : void
- return : TRUE si tout s'est bien passe ; FALSE en cas d'erreur
*/
bool MySQL_execQuery(QString maRequete)
{
    qDebug() << "\n-----MySQL_execQuery : debut";
    qDebug() << maRequete;

    QSqlQuery query;
    QSqlError err;

    // Requete sur elements
    if( false == query.exec(maRequete) )
    {
        // Generation d'une erreur
        err = query.lastError();

        qDebug() << "La requete a echoue";
        qDebug() << err.text();
        qDebug() << "\n-----MySQL_execQuery : fin";

        return false;
    }
    else
    {
        qDebug() << "La requete s'est bien passee";
        qDebug() << "-----MySQL_execQuery : fin\n";

        return true;
    }
}// MySQL_execQuery



/*
MySQL_openDatabase :
- ouvre une connexion vers la base de donnes dont le nom de fichier est donne en parametre
- teste si le fichier doit etre cree ou s'il avait ete cree par une precedente execution du programme
- si le fichier doit etre cree, il construit les tables vides a l'interieur

Parametres:
- IN : QString du nom de fichier
- return : un INT avec comme valeur possible
            - 0 : l'execution s'est passee sans erreur
            - 1 : le fichier BDD existe mais on n'arrive pas a s'y connecter
            - 2 : erreur lors de la creation de la table "artistes"
            - 3 : erreur lors de la creation de la table "albums"
            - 4 : erreur lors de la creation de la table "elements"
            - 5 : erreur lors de la suppression du fichier (induit un des cas 2 à 4)
*/
bool MySQL_openDatabase(QString nomFichier)
{
    qDebug() << "\n-----MySQL_openDatabase : debut";

    // Test de l'existence du fichier de la BDD
    QFile dbFile(nomFichier);
    bool existait = dbFile.exists();

    // Initialisation de la connexion avec le fichier QSQLite
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("Local");
    db.setDatabaseName(nomFichier);
    db.setUserName("root");
    db.setPassword("");

    // Verification de la bonne ouverture de connexion
    bool ouverture = db.open();
    if (ouverture == false)
    {
        return 1;
    }

    // Si le fichier n'existe pas, il faut creer les tables
    if(existait)
    {
        qDebug() << "Le fichier existait deja";
    }
    else
    {
        qDebug() << "Le fichier n'existe pas\nOn le remplit";
        // Creation des tables
        QSqlQuery maRequete;

        // Objet pour obtenir des informations sur les erreurs des requetes
        QSqlError errCreation;

        if ( false == maRequete.exec("CREATE TABLE artistes\
                        (id_artiste integer primary key,\
                        nom varchar(40))") )
        {
            errCreation = maRequete.lastError();
            qDebug() << "Message d'erreur associe : " + errCreation.text();
            // On supprime le fichier nouvellement creer et on sort de la fonction
            if( false == dbFile.remove())
            {
                return 5;
            }
            else
            {
                return 2;
            }
        }//Creation de "artistes"

        if ( false == maRequete.exec("CREATE TABLE albums\
                        (id_album integer primary key,\
                        titre varchar(100),\
                        sortie integer,\
                        maison varchar(50))") )
        {
            errCreation = maRequete.lastError();
            qDebug() << "Message d'erreur associe : " + errCreation.text();
            // On supprime le fichier nouvellement creer et on sort de la fonction
            if( false == dbFile.remove())
            {
                return 5;
            }
            else
            {
                return 3;
            }
        }//Creation de "albums"

        if ( false == maRequete.exec("CREATE TABLE elements\
                       (id_element interger primary key,\
                       id_artiste integer,\
                       id_album integer,\
                       magasin varchar(50),\
                       ville varchar(50),\
                       offreur varchar(50),\
                       prix float,\
                       dateObtention date,\
                       neuf boolean,\
                       typeDisque varchar(10))") )
        {
            errCreation = maRequete.lastError();
            qDebug() << "Message d'erreur associe : " + errCreation.text();
            // On supprime le fichier nouvellement creer et on sort de la fonction
            if( false == dbFile.remove())
            {
                return 5;
            }
            else
            {
                return 4;
            }
        }//Creation de "elements"

    #warning Les cles etrangeres doivent etre implementees

   }
    // Fin en succes
    qDebug() << "Le fonctionnement s'est bien deroule";
    qDebug() << "-----MySQL_openDatabase : fin\n";
    return 0;

}//MySQL_openDatabase






/*
MySQL_elementsCount :
- calcule d'elements distinct d'une des tables possibles de la base de donnees
en se basant sur les id de la table.
- la base de donnees est supposee deja ouverte (on utilise la connexion par defaut)

Parametres :
- IN : QString : nom de la table (elements, artistes, albums)
- OUT : void
- return : un int contenant le nombre d'elements.
Ce nombre est negatif en cas d'erreur.
-1 = mauvais parametre (la table n'existe pas)
-2 = execution de la requete SQL en erreur
-3 = impossibilite d'extraire le nbr d'elements  de la requete
*/
int MySQL_elementsCount(QString nomTable)
{
    qDebug() << "\n-----MySQL_elementsCount sur " << nomTable << " : debut";

    QString maRequete = NULL;
    if(nomTable == "elements")
    {
        maRequete = "SELECT COUNT (DISTINCT id_element) FROM elements";
    }
    else if(nomTable == "artistes")
    {
        maRequete = "SELECT COUNT (DISTINCT id_artiste) FROM artistes";
    }
    else if(nomTable == "albums")
    {
        maRequete = "SELECT COUNT (DISTINCT id_album) FROM albums";
    }
    else
    {
        qDebug() << "Mauvais parametre !";
        qDebug() << "-----MySQL_elementsCount " << nomTable << " : fin\n";
        return -1;
    }


    // Le parametre est reconnu, on peut executer la fonction
    QSqlQuery query;
    // Execution de la requete
    if( false == query.exec(maRequete) )
    {
        // Generation d'une erreur
        qDebug() << "Erreur sur la table " << nomTable << " pour compter";
        QSqlError err1 = query.lastError();
        qDebug() << "Message d'erreur associe : " + err1.text();
        qDebug() << "-----MySQL_elementsCount " << nomTable << " : fin\n";
        return -2;
    }
    else
    {
        // Recuperation du resultat : il y en a un seul donc un seul next() suffit.
        int nbrElements = 0;
        if(query.next() == true)
        {
            nbrElements = query.value(0).toInt();
        }
        else
        {
            qDebug() << "On n'a pas reussi a compter le nombre d'element dans la table";
            QSqlError err2 = query.lastError();
            qDebug() << "Message d'erreur associe : " + err2.text();
            return -3;
        }

        qDebug() << "Nombre d'elements trouves : " + QString::number(nbrElements);
        qDebug() << "-----MySQL_elementsCount " << nomTable << " : fin\n";

        return nbrElements;
    }
}//MySQL_elementsCount






/*
MySQL_searchElementId :
- cherche si un element existe dans la table desiree de la base de donnees
- renvoie l'identifiant de cet element de la table si trouve ; un code d'erreur sinon

Probleme : SENSIBILITE A LA CASSE DU NOM DE L'ELEMENT

Parametres :
- IN :
    QString nomTable = nom de la table (elements, artistes, albums)
    QString nomChamp= nom de la colonne de la table
    QString valeurChamp = valeur qu'on souhaite trouvee
- OUT : int = id de l'element ou code d'erreur
    -1 = erreur du nom de table en parametre
    -2 = echec de la requete SQL (potentiellement, le nom de colonne indique est incorrect)
    -3 = succes d'execution mais pas de resultat (aucune entree ne possede cette valeur...)
    -4 = on a plusieurs resultats possible. C'est une potentielle corruption de la base (artiste en double) !
    >=0 = l'identifiant de l'element
*/
int MySQL_searchElementId(QString nomTable, QString nomChamp, QString valeurChamp)
{
    qDebug() << "-----MySQL_searchElementId : debut";

    // En fonction de la table, l'ID a retourne est different
    QString ID="";

    // Verification du nom de table
    if(nomTable == "elements")
    {
        ID="id_element";
    }
    else if(nomTable == "artistes")
    {
        ID="id_artiste";
    }
    else if(nomTable == "albums")
    {
        ID="id_album";
    }
    else
    {
        qDebug() << "Mauvais parametre !";

        // Fin
        qDebug() << "-----MySQL_searchElementId : fin";
        return -1;
    }

    // Construction de la requete
    QSqlQueryModel *monModele = new QSqlQueryModel;
    QString maRequete = "SELECT "+ID+","+nomChamp+" FROM "+nomTable+" WHERE "+nomChamp+"="+"'"+valeurChamp+"'";

#warning La requete est sensible a la casse de "valeurChamp"

    // Execution de la requete
    if(false == MySQL_execQueryModel(maRequete, monModele))
    {
        // Requete echouee : sortie en erreur
        qDebug() << "L'execution de la requete a echoue";

        // Fin
        qDebug() << "-----MySQL_searchElementId : fin\n";
        return -2;
    }
    else
    {
        // Requete en succes : analyse des resultats
        int nbResultats = monModele->rowCount();
        if(0 == nbResultats)
        {
            // Aucun resultat
            qDebug() << "La requete n'a donne aucun resultat : l'element demande n'est pas present dans la table";

            // Fin
            qDebug() << "-----MySQL_searchElementId : fin\n";
            return -3;

        }
        else if(1 == nbResultats)
        {
            // Une entree trouve, on renvoit l'identifiant
            int idTrouve = monModele->record(0).value(ID).toInt();
            qDebug() << "Identifiant de l'element recherche : " << idTrouve;

            // Fin
            qDebug() << "-----MySQL_searchElementId : fin\n";
            return idTrouve;
        }
        else
        {
            // On a trouve plusieurs elements : la base a un probleme !
            qDebug() << "On a trouve plusieurs entrees correspondantes !!!";
            qDebug() << "Voici les resultats.";
            for (int i = 0; i < nbResultats; i++)
            {
                QString nom = monModele->record(i).value(nomChamp).toString();
                int id = monModele->record(i).value(ID).toInt();
                qDebug() << "Identifiant = "<< id << " et valeur = " << nom;
            }

            // Fin
            qDebug() << "-----MySQL_searchElementId : fin\n";
            return -4;
        }//else nbResultats
    }//else requete


}//MySQL_searchElementId

