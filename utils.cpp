/**
 * @file utils.cpp
 *
 * @brief Définition de la classe Utils.
 *
 * @version 1.0
 *
 * @author LEESTMANS Richard
 * @author COUDERT-BOUDET Nicolas
 */

#include "utils.h"

/**
 * Sécurise une string pour la base de données.
 * @brief Utils::addSlashes Sécuisation de string
 * @param s String à sécuriser
 */
void Utils::addSlashes(std::string& s)
{
    // Chars found on stackoverflow and addlshases function in python language
    std::vector<char> charToCancel = {'\\', '\'', '"'};
    std::vector<char> charToDelete = {'\r', '\x1A'};

    for (auto i = s.begin();;) {
        auto const pos = std::find_if(
            i, s.end(),
            [charToCancel](char const c) { return std::count(charToCancel.begin(), charToCancel.end(), c); }
        );
        if (pos == s.end()) {
            break;
        }
        i = std::next(s.insert(pos, '\\'), 2);
    }

    s.erase(
        std::remove_if(
            s.begin(), s.end(), [charToDelete](char const c) {
                return std::count(charToDelete.begin(), charToDelete.end(), c);
            }
        ),
        s.end()
    );
}

/**
 * Vérifie qu'une date est correct (string) et la stock dans un objet Date
 * @param s string à vérifier
 * @param d Pointeur sur objet Date où stocker la date si elle est valide
 * @return Si l'opération s'est correctement déroulée ou non
 */
bool Utils::checkForDate(std::string s, Date* d)
{
    if(s.length() == 10) {
        Date dd(s, true);
        if(dd.isValid())
        {
            *d = dd;
            return true;
        }
    }

    return false;
}
