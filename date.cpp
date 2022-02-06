/**
 * @file Date.cpp
 *
 * @brief Définition de la classe Date (Gestion simplifiée des dates)
 *
 * @version 1.0
 *
 * @date 15/10/2021
 *
 * @author LEESTMANS Richard
 * @author COUDERT-BOUDET Nicolas
 */

#include "date.h"

/**
 * Renvoie la date en lettres.
 * @return Date en lettres en string. (Exemple: Vendredi 15 octobre 2021)
 */
std::string Date::getDateString() const {
    std::string date = getDayString() + " " + std::to_string(getDay()) + " "
            + getMonthString() + " " + std::to_string(getYear());
    return date;
}

/**
 * Retourne l'année représentée par la date
 * @return L'année représentée par la date (Exemple: 2021)
 */
unsigned int Date::getYear() const {
    return 1900 + this->tm.tm_year;
}

/**
 * Retourne l'index du jour en fonction de la semaine (commençant le Dimanche)
 * @return index du jour [0; 6]
 */
unsigned int Date::getDay() const {
    return this->tm.tm_mday;
}

/**
 * Retourne l'index du mois en fonction de l'année (commençant en Janvier)
 * @return index du mois [0; 11]
 */
unsigned Date::getMonth() const {
    return this->tm.tm_mon;
}

/**
 * Retourne le jour de la date représentée en lettres.
 * @return Jour de la semaine (Exemple: Lundi)
 *
 */
std::string Date::getDayString() const {
    std::string days[] = {
            "Dimanche", "Lundi", "Mardi", "Mercredi",
            "Jeudi", "Vendredi", "Samedi"
    };

    return days[this->tm.tm_wday]; // No index verification, we trust in C++
}

/**
 * Retourne le mois de la date représentée en lettres.
 * @return Mois de l'année (Exemple: Janvier)
 *
 */
std::string Date::getMonthString() const {
    std::string months[] = {
            "Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout",
            "Septembre", "Octobre", "Novembre", "Décembre"
    };
    return months[getMonth()]; // No index verification, we trust in C++
}

/**
 * Retourne la date au format SQLite (yyyy-mm-dd)
 * @note A utiliser si la précision s'arrête au jour. Sinon, utiliser le format avec le nombre de secondes depuis le 01/01/1970
 * @return Date au format SQLite (yyyy-mm-dd)
 */
std::string Date::getSqlFormat() const {

    std::string day = std::string(2 - std::to_string(getDay()).length(), '0') // Complete with 0
            + std::to_string(getDay()); // Add Day
    std::string month = std::string(2 - std::to_string(getMonth()+1).length(), '0')  // complete with 0
            + std::to_string(getMonth()+1); // Add Month

    std::string date = std::to_string(getYear()) + "-" + month+"-" + day;
    return date;
}

/**
 * Retourne la date en string sous un format compact
 * @return Date au format compact (Exemple: 08/04/2021)
 *
 */
std::string Date::getDateCompactString() const {
    std::string day = std::string(2 - std::to_string(getDay()).length(), '0') // Complete with 0
            + std::to_string(getDay()); // Add Day
    std::string month = std::string(2 - std::to_string(getMonth()+1).length(), '0')  // complete with 0
            + std::to_string(getMonth()+1); // Add Month
    return day + "/" + month + + "/" + std::to_string(getYear());
}


/**
 * Renvoie le nombre d'heures de la date représentée
 * @return Nombre d'heures
 */
unsigned int Date::getHour() const {
    return this->tm.tm_hour;
}

/**
 * Renvoie le nombre de minutes de la date représentée
 * @return Nombre de minutes
 */
unsigned int Date::getMinute() const {
    return this->tm.tm_min;
}

/**
 * Renvoie la représentation de la date modélisée en nombre de secondes depuis le 1er janvier 1970
 * @return Nombre de secondes depuis le 01/01/1970
 */
time_t Date::getTotalSeconds() {
    return std::mktime(&this->tm);
}

/**
 * Retourne si oui ou non la date semble valide
 * @return Date valide
 */
bool Date::isValid() const
{
    return !(tm.tm_year == 0 && tm.tm_mon == 0 && tm.tm_mday == 0
            && tm.tm_hour == 0 && tm.tm_min == 0 && tm.tm_sec == 0);
}

/**
 * Définit une nouvelle date à représenter.
 * @param seconds Nombre de secondes depuis le 1er janvier 1970.
 */
void Date::setDate(time_t seconds) {
    //Unsecure
    this->tm = *localtime(&seconds);
    //localtime_s(&this->tm, &s); <-- Better
}

/**
 * Surcharge de l'opérateur d'égalité. (Date1 == Date2)
 * La comparaison se fait à la seconde près.
 * @param a Première Date à comparer
 * @param b Deuxième Date à comparer
 * @return Si les dates sont égales
 */
bool operator==(const Date& a, const Date& b) {
    Date a1 = a; // Copy because mktime() cannot be const
    Date b1 = b;
    return a1.getTotalSeconds() == b1.getTotalSeconds();
}

/**
 * Surcharge de l'opérateur de différence (Date1 != Date2)
 * La comparaison se fait à la seconde près.
 * @param a Première Date à comparer
 * @param b Deuxième Date à comparer
 * @return Si les dates ne sont pas égales
 */
bool operator!=(const Date& a, const Date& b) {
    return !(a == b);
}

/**
 * Surcharge de l'opérateur d'infériorité. (Date1 < Date2)
 * La comparaison se fait à la seconde près.
 * @param a Première Date à comparer
 * @param b Deuxième Date à comparer
 * @return Si la date a est plus ancienne que la date b
 */
bool operator<(const Date& a, const Date& b) {
    Date a1 = a;
    Date a2 = b;
    return a1.getTotalSeconds() < a2.getTotalSeconds();
}

/**
 * Surcharge de l'opérateur de supériorité. (Date1 < Date2)
 * La comparaison se fait à la seconde près.
 * @param a Première Date à comparer
 * @param b Deuxième Date à comparer
 * @return Si la date a est plus récente que la date b
 */
bool operator>(const Date& a, const Date& b) {
    Date a1 = a;
    Date a2 = b;
    return a1.getTotalSeconds() > a2.getTotalSeconds();
}

/**
 * Surcharge de l'opérateur de supériorité/égalité. (Date1 < Date2)
 * La comparaison se fait à la seconde près.
 * @param a Première Date à comparer
 * @param b Deuxième Date à comparer
 * @return Si la date a est plus récente que la date b (ou égale)
 */
bool operator>=(const Date& a, const Date& b) {
    return (a > b) || (a == b);
}

/**
 * Surcharge de l'opérateur d'infériorité/égalité. (Date1 < Date2)
 * La comparaison se fait à la seconde près.
 * @param a Première Date à comparer
 * @param b Deuxième Date à comparer
 * @return Si la date a est plus ancienne que la date b (ou égale)
 */
bool operator<=(const Date& a, const Date& b) {
    return (a < b) || (a == b);
}

/**
 * Constructeur de la classe sans argument.
 * La date est initialisée sur la date de la machine.
 */
Date::Date() {
    time_t t = time(nullptr);
    //Unsecure
    this->tm = *localtime(&t);
    //localtime_s(&this->tm, &t); <-- Better
}

/**
 * Constructeur de la classe.
 * La date est initialisée en fonction du paramètre seconds donné.
 * @param seconds Nombre de secondes depuis le 1er janvier 1970.
 */
Date::Date(time_t seconds)
{
    setDate(seconds);
}

/**
 * Constructeur de la classe.
 * La date est initialisée en fonction du paramètre sqlTime qui doit être de la forme des dates SqLite: yyyy-mm-dd
 * @param sqlTime Date de la forme yyyy-mm-dd
 * @param useHyphen Utiliser le langage courant (jour/mois/année
 */
Date::Date(std::string &sqlTime, bool naturalLanguage) {
    std::istringstream ss(sqlTime);
    if(naturalLanguage)
        ss >> std::get_time(&this->tm, "%d/%m/%Y");
    else
        ss >> std::get_time(&this->tm, "%Y-%m-%d");
}

/**
 * Surcharge de l'opérateur <<
 * @param os Stream de sortie
 * @param i Date courante
 * @return Représentation textuelle de l'objet
 */
std::ostream &operator<<(std::ostream &os, const Date &i) {
    const Date& i1 = i;
    os << "Date(";
    os << i1.getDateCompactString();
    os << ")";
    return os;
}

/**
 * Destructeur par défaut (géré par le compilateur).
 */
Date::~Date() = default;
