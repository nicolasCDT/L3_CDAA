/**
 * @file date.h
 *
 * @brief Déclaration de la classe Date (Gestion simplifiée des dates)
 *
 * @version 1.0
 *
 * @date 15/10/2021
 *
 * @author LEESTMANS Richard
 * @author COUDERT Nicolas
 */

#ifndef CDAA_DATE_H
#define CDAA_DATE_H

#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>

/**
 * Classe permettant de gérer plus facilement les dates.
 * L'ensemble des accesseurs sont virtuels. La structure tm n'est pas modifiable directement.
 * \brief Classe permettant une gestion simplifiée des dates
 */
class Date {
private:
    struct tm tm{}; /*!< Structure tm qui stock la date. */

    // Voir Date.cpp pour la documentation des méthodes
public:
    [[nodiscard]] std::string getDateString() const;
    [[nodiscard]] std::string getDateCompactString() const;
    [[nodiscard]] std::string getDayString() const;
    [[nodiscard]] std::string getMonthString() const;
    [[nodiscard]] std::string getSqlFormat() const;

    [[nodiscard]] unsigned int getYear() const;
    [[nodiscard]] unsigned int getDay() const;
    [[nodiscard]] unsigned int getMonth() const;
    [[nodiscard]] unsigned int getHour() const;
    [[nodiscard]] unsigned int getMinute() const;

    [[nodiscard]] time_t getTotalSeconds();

    [[nodiscard]] bool isValid() const;

    // Setters
    void setDate(time_t seconds);

    // Surcharge d'opérateurs
    friend bool operator==(const Date& a, const Date& b);
    friend bool operator!=(const Date& a, const Date& b);
    friend bool operator<(const Date& a, const Date& b);
    friend bool operator>(const Date& a, const Date& b);
    friend bool operator<=(const Date& a, const Date& b);
    friend bool operator>=(const Date& a, const Date& b);
    friend std::ostream& operator<<(std::ostream& os, const Date& i);

    // Constructeurs et destructeur
    Date();
    explicit Date(time_t seconds);
    explicit Date(std::string& sqlTime, bool naturalLanguage=false);
    ~Date();
};


#endif //CDAA_DATE_H
