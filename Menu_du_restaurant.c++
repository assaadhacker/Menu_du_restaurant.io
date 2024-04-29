#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Plat
{
private:
    string nom;
    string description;
    float prix;

public:
    Plat(string n, string desc, float p) : nom(n), description(desc), prix(p) {}

    void afficherDetails() const
    {
        cout << " " << endl;
        cout << "*************************************************" << endl;
        cout << "Nom : " << nom << endl;
        cout << "Description : " << description << endl;
        cout << "Prix : " << prix << " $" << endl;
        cout << "*************************************************" << endl;
        cout << " " << endl;
    }

    float getPrix() const
    {
        return prix;
    }
};

class Boisson
{
private:
    string nom;
    string description;
    float prix;

public:
    Boisson(string n, string desc, float p) : nom(n), description(desc), prix(p) {}

    void afficherDetails() const
    {
        cout << " " << endl;
        cout << "*************************************************" << endl;
        cout << "Nom : " << nom << endl;
        cout << "Description : " << description << endl;
        cout << "Prix : " << prix << " $" << endl;
        cout << "*************************************************" << endl;
        cout << " " << endl;
    }

    float getPrix() const
    {
        return prix;
    }
};

class Commande
{
private:
    vector<Plat> platsCommandes;
    vector<Boisson> boissonsCommandees;

public:
    const vector<Plat> &getPlatsCommandes() const
    {
        return platsCommandes;
    }
    const vector<Boisson> &getBoissonsCommandes() const
    {
        return boissonsCommandees;
    }
    void ajouterPlat(Plat plat)
    {
        platsCommandes.push_back(plat);
    }

    void ajouterBoisson(Boisson boisson)
    {
        boissonsCommandees.push_back(boisson);
    }

    void afficherDetails() const
    {
        cout << " " << endl;
        cout << "*************************************************" << endl;
        cout << "Commande :" << endl;
        cout << " " << endl;
        cout << "Plats :" << endl;
        for (vector<Plat>::const_iterator it = platsCommandes.begin(); it != platsCommandes.end(); ++it)
        {
            it->afficherDetails();
            cout << endl;
        }
        cout << " " << endl;
        cout << "Boissons :" << endl;
        for (vector<Boisson>::const_iterator it = boissonsCommandees.begin(); it != boissonsCommandees.end(); ++it)
        {
            it->afficherDetails();
            cout << endl;
            cout << " " << endl;
            cout << "*************************************************" << endl;
        }
    }

    int nombrePlats() const
    {
        return platsCommandes.size();
    }

    int nombreBoissons() const
    {
        return boissonsCommandees.size();
    }

    float calculerTotal() const
    {
        float total = 0;
        for (vector<Plat>::const_iterator it = platsCommandes.begin(); it != platsCommandes.end(); ++it)
        {
            total += it->getPrix();
        }
        for (vector<Boisson>::const_iterator it = boissonsCommandees.begin(); it != boissonsCommandees.end(); ++it)
        {
            total += it->getPrix();
        }
        return total;
    }
};

class Reservation
{
private:
    string dateHeure;
    int nombrePersonnes;
    string statut;

public:
    Reservation(string date, int nbPersonnes) : dateHeure(date), nombrePersonnes(nbPersonnes), statut("en attente") {}

    void confirmer()
    {
        statut = "confirmée";
    }

    void annuler()
    {
        statut = "annulée";
    }

    void afficherDetails() const
    {
        cout << " " << endl;
        cout << "*************************************************" << endl;
        cout << "Date et heure : " << dateHeure << endl;
        cout << "Nombre de personnes : " << nombrePersonnes << endl;
        cout << "Statut : " << statut << endl;
        cout << "*************************************************" << endl;
        cout << " " << endl;
    }

    bool operator==(const Reservation &other) const
    {
        return (dateHeure == other.dateHeure && nombrePersonnes == other.nombrePersonnes && statut == other.statut);
    }
};

class Menu
{
private:
    vector<Plat> plats;
    vector<Boisson> boissons;
    vector<Commande> commandes;
    vector<Reservation> reservations;
    int tablesDisponibles;
    int tablesReservees;

public:
    Menu(int tables) : tablesDisponibles(tables), tablesReservees(0) {}

    void ajouterPlat(Plat plat)
    {
        plats.push_back(plat);
    }

    void ajouterBoisson(Boisson boisson)
    {
        boissons.push_back(boisson);
    }

    void ajouterCommande(Commande commande)
    {
        commandes.push_back(commande);
    }

    void ajouterCommande()
    {
        Commande commande;
        string input;
        int choix;

        do
        {
            afficherPlats();
            cout << " " << endl;
            cout << "Entrez le numéro du plat à ajouter (ou 0 pour terminer) : ";
            cin >> input;
            if (input == "0")
            {
                break;
            }
            stringstream ss(input);
            ss >> choix;
            if (!ss.fail() && choix >= 1 && choix <= plats.size())
            {
                Plat plat = plats[choix - 1];
                commande.ajouterPlat(plat);
            }
            else if (input != "0")
            {
                cout << " " << endl;
                cout << "Numéro de plat invalide." << endl;
            }
        } while (input != "0");

        do
        {
            afficherBoissons();

            cout << " " << endl;
            cout << "Entrez le numéro de la boisson à ajouter (ou 0 pour terminer) : ";
            cin >> input;
            if (input == "0")
            {
                break;
            }
            stringstream ss(input);
            ss >> choix;
            if (!ss.fail() && choix >= 1 && choix <= boissons.size())
            {
                Boisson boisson = boissons[choix - 1];
                commande.ajouterBoisson(boisson);
            }
            else if (input != "0")
            {
                cout << "Numéro de boisson invalide." << endl;
            }
        } while (input != "0");

        commandes.push_back(commande);
    }

    void reserverTable(Reservation reservation)
    {
        if (tablesDisponibles > 0)
        {
            reservations.push_back(reservation);
            tablesDisponibles--;
            tablesReservees++;
            cout << "Table réservée avec succès." << endl;
        }
        else
        {
            cout << "Désolé, toutes les tables sont déjà réservées." << endl;
        }
    }

    void afficherPlats() const
    {
        cout << " " << endl;
        cout << "Plats :" << endl;
        for (vector<Plat>::const_iterator it = plats.begin(); it != plats.end(); ++it)
        {
            it->afficherDetails();
            cout << endl;
        }
    }

    void afficherBoissons() const
    {
        cout << " " << endl;
        cout << "Boissons :" << endl;
        for (vector<Boisson>::const_iterator it = boissons.begin(); it != boissons.end(); ++it)
        {
            it->afficherDetails();
            cout << endl;
        }
    }

    void supprimerPlat(int index)
    {
        if (index >= 0 && index < plats.size())
        {
            plats.erase(plats.begin() + index);
            cout << " " << endl;
            cout << "Plat supprimé avec succès." << endl;
        }
        else
        {
            cout << " " << endl;
            cout << "Indice de plat invalide." << endl;
        }
    }

    void supprimerBoisson(int index)
    {
        if (index >= 0 && index < boissons.size())
        {
            boissons.erase(boissons.begin() + index);
            cout << " " << endl;
            cout << "Boisson supprimée avec succès." << endl;
        }
        else
        {
            cout << " " << endl;
            cout << "Indice de boisson invalide." << endl;
        }
    }

    void afficherCommandes() const
    {
        for (vector<Commande>::const_iterator it = commandes.begin(); it != commandes.end(); ++it)
        {
            cout << " " << endl;
            cout << "*************************************************" << endl;
            cout << "Commande :" << endl;
            cout << " " << endl;
            cout << "Nombre de plats : " << it->getPlatsCommandes().size() << endl;
            cout << "Nombre de boissons : " << it->getBoissonsCommandes().size() << endl;
            cout << " " << endl;
            cout << "*************************************************" << endl;
            cout << "Plats :" << endl;
            const vector<Plat> &plats = it->getPlatsCommandes();
            for (vector<Plat>::const_iterator plat_it = plats.begin(); plat_it != plats.end(); ++plat_it)
            {
                plat_it->afficherDetails();
                cout << endl;
            }
            cout << " " << endl;
            cout << "*************************************************" << endl;
            cout << "Boissons :" << endl;
            const vector<Boisson> &boissons = it->getBoissonsCommandes();
            for (vector<Boisson>::const_iterator boisson_it = boissons.begin(); boisson_it != boissons.end(); ++boisson_it)
            {
                boisson_it->afficherDetails();
                cout << endl;
            }
            cout << " " << endl;
            cout << "*************************************************" << endl;
            cout << "Total : " << it->calculerTotal() << " DH" << endl;
            cout << "*************************************************" << endl;
            cout << " " << endl;
        }
    }
    void supprimerCommande(int index)
    {
        if (index >= 0 && index < commandes.size())
        {
            commandes.erase(commandes.begin() + index);
            cout << "Commande supprimée avec succès." << endl;
        }
        else
        {
            cout << "Indice de commande invalide." << endl;
        }
    }

    void afficherReservations() const
    {
        cout << " " << endl;
        cout << "Réservations :" << endl;
        for (vector<Reservation>::const_iterator it = reservations.begin(); it != reservations.end(); ++it)
        {
            it->afficherDetails();
            cout << endl;
        }
    }

    void afficherTables() const
    {
        cout << " " << endl;
        cout << "Tables disponibles : " << tablesDisponibles << endl;
        cout << "Tables réservées : " << tablesReservees << endl;
    }

    int nombreCommandes() const
    {
        return commandes.size();
    }

    float totalPrixCommandes() const
    {
        float total = 0;
        for (vector<Commande>::const_iterator it = commandes.begin(); it != commandes.end(); ++it)
        {
            total += it->calculerTotal();
        }
        return total;
    }

    void updateStock()
    {
        int totalPlats = 0;
        int totalBoissons = 0;
        for (vector<Commande>::const_iterator it = commandes.begin(); it != commandes.end(); ++it)
        {
            totalPlats += it->nombrePlats();
            totalBoissons += it->nombreBoissons();
        }
        cout << "Total plats restants : " << plats.size() - totalPlats << endl;
        cout << "Total boissons restantes : " << boissons.size() - totalBoissons << endl;
    }
    void supprimerReservation(int index)
    {
        if (index >= 0 && index < reservations.size())
        {
            reservations.erase(reservations.begin() + index);
            tablesDisponibles++;
            tablesReservees--;
            cout << "Réservation supprimée avec succès." << endl;
        }
        else
        {
            cout << "Indice de réservation invalide." << endl;
        }
    }
};

int main()
{
    Menu menu(10);

    int userType;
    cout << "Etes-vous un client (1) ou un serveur (2) ? ";
    cin >> userType;

    if (userType == 1)
    {
        int choix;
        do
        {
            cout << " " << endl;
            cout << "___________________________________________________ " << endl;
            cout << "|*************************************************|" << endl;
            cout << "|**                                             **|" << endl;
            cout << "|**             Menu du restaurant              **|" << endl;
            cout << "|**                                             **|" << endl;
            cout << "|**     Que souhaitez-vous faire ?              **|" << endl;
            cout << "|**     1. Afficher les plats                   **|" << endl;
            cout << "|**     2. Afficher les boissons                **|" << endl;
            cout << "|**     3. Reservations de table                **|" << endl;
            cout << "|**     4. Ajouter des commandes                **|" << endl;
            cout << "|**     5. Quitter                              **|" << endl;
            cout << "|**                                             **|" << endl;
            cout << "|*************************************************|" << endl;
            cout << "|________________________________By Asaad AZAROUAL| " << endl;
            cout << " " << endl;
            cout << "votre choix : ";
            cin >> choix;

            switch (choix)
            {
            case 1:
                menu.afficherPlats();
                break;
            case 2:
                menu.afficherBoissons();
                break;
            case 3:
            {
                string date;
                int nbPersonnes;
                cout << " " << endl;
                cout << "Entrez la date et l'heure de la réservation : ";
                cin >> date;
                cout << "Entrez le nombre de personnes : ";
                cin >> nbPersonnes;
                Reservation reservation(date, nbPersonnes);
                menu.reserverTable(reservation);
                break;
            }
            case 4:
                menu.ajouterCommande();
                break;
            case 5:
                cout << "Au revoir !" << endl;
                break;
            default:
                cout << "Choix invalide. Veuillez réessayer." << endl;
            }
        } while (choix != 5);

        return 0;
    }
    else if (userType == 2)
    {
        int choix;
        do
        {
            cout << " " << endl;
            cout << "___________________________________________________ " << endl;
            cout << "|*************************************************|" << endl;
            cout << "|**                                             **|" << endl;
            cout << "|**             Menu du restaurant              **|" << endl;
            cout << "|**                                             **|" << endl;
            cout << "|**     Que souhaitez-vous faire ?              **|" << endl;
            cout << "|**     1. Ajouter des plats                    **|" << endl;
            cout << "|**     2. Afficher les plats                   **|" << endl;
            cout << "|**     3. Supprimer des plats                  **|" << endl;
            cout << "|**     4. Ajouter des boissons                 **|" << endl;
            cout << "|**     5. Afficher les boissons                **|" << endl;
            cout << "|**     6. Supprimer des boissons               **|" << endl;
            cout << "|**     7. Reservations de table                **|" << endl;
            cout << "|**     8. Afficher les reservations            **|" << endl;
            cout << "|**     9. Supprimer les reservations           **|" << endl;
            cout << "|**     10. Ajouter des commandes               **|" << endl;
            cout << "|**     11. Afficher les commandes              **|" << endl;
            cout << "|**     12. Supprimer des commandes             **|" << endl;
            cout << "|**     13. Calculer le total de la commande    **|" << endl;
            cout << "|**     14. Gestion des stocks                  **|" << endl;
            cout << "|**     15. Quitter                             **|" << endl;
            cout << "|**                                             **|" << endl;
            cout << "|*************************************************|" << endl;
            cout << "|________________________________By Asaad AZAROUAL| " << endl;
            cout << " " << endl;
            cout << "votre choix : ";
            cin >> choix;

            switch (choix)
            {
            case 1:
            {
                string nom, description;
                float prix;
                cout << " " << endl;
                cout << "Entrez le nom du plat : ";
                cin.ignore();
                getline(cin, nom);
                cout << "Entrez la description du plat : ";
                getline(cin, description);
                cout << "Entrez le prix du plat : ";
                cin >> prix;
                Plat plat(nom, description, prix);
                menu.ajouterPlat(plat);
                break;
            }
            case 2:
                menu.afficherPlats();
                break;
            case 3:
            {
                int index;
                cout << " " << endl;
                cout << "Entrez l'index du plat à supprimer : ";
                cin >> index;
                menu.supprimerPlat(index - 1);
                break;
            }
            case 4:
            {
                string nom, description;
                float prix;
                cout << " " << endl;
                cout << "Entrez le nom de la boisson : ";
                cin.ignore();
                getline(cin, nom);
                cout << "Entrez la description de la boisson : ";
                getline(cin, description);
                cout << "Entrez le prix de la boisson : ";
                cin >> prix;
                Boisson boisson(nom, description, prix);
                menu.ajouterBoisson(boisson);
                break;
            }
            case 5:
                menu.afficherBoissons();
                break;
            case 6:
            {
                int index;
                cout << " " << endl;
                cout << "Entrez l'index de la boisson à supprimer : ";
                cin >> index;
                menu.supprimerBoisson(index - 1);
                break;
            }
            case 7:
            {
                string date;
                int nbPersonnes;
                cout << " " << endl;
                cout << "Entrez la date et l'heure de la réservation : ";
                cin >> date;
                cout << "Entrez le nombre de personnes : ";
                cin >> nbPersonnes;
                Reservation reservation(date, nbPersonnes);
                menu.reserverTable(reservation);
                break;
            }
            case 8:
                menu.afficherReservations();
                break;
            case 9:
            {
                int index;
                cout << " " << endl;
                cout << "Entrez l'index de la réservation à supprimer : ";
                cin >> index;
                menu.supprimerReservation(index - 1);
                break;
            }
            case 10:
                menu.ajouterCommande();
                break;
            case 11:
                menu.afficherCommandes();
                break;
            case 12:
                int index;
                cout << " " << endl;
                cout << "Entrez l'index de la commande à supprimer : ";
                cin >> index;
                menu.supprimerCommande(index - 1);
                break;
            case 13:
                cout << "Nombre de commandes : " << menu.nombreCommandes() << endl;
                cout << "Total prix de toutes les commandes : " << menu.totalPrixCommandes() << " DH" << endl;
                break;
            case 14:
            {
                menu.updateStock();
                break;
            }
            case 15:
                cout << "Au revoir !" << endl;
                break;
            default:
                cout << "Choix invalide. Veuillez réessayer." << endl;
            }
        } while (choix != 15);

        return 0;
    }
    else
    {
        cout << "Type d'utilisateur invalide." << endl;
    }

    return 0;
}
