/*
#ifndef SERIALCURRENCY_H_INCLUDED
#define SERIALCURRENCY_H_INCLUDED

#include "serializable.h"

class serialCurrency : serializable{
    protected:
        int x; // x é o atributo que refere-se a parte inteira do valor
        int y; // y é o atributo que refere-se a parte fracionária do valor
    public:
        serialCurrency(); // Construtor padrão
        serialCurency(int nx, int ny); // Construtor paramétrico
        serialCurrency(const serialCurrency& other); // Construtor de cópia
        virtual ~serialCurrency(); // Destrutor
        serialCurrency operator=(const serialCurrency& other); // Sobrecarga do operador =
        bool operator==(const serialCurrency &other) const; // Sobrecarga do operador ==
        bool operator<(const serialCurrency &other) const; // Sobrecarga do operador <
        bool operator<=(const serialCurrency &other) const; // Sobrecarga do operador <=
        bool operator>(const serialCurrency &other) const; // Sobrecarga do operador >
        bool operator>=(const serialCurrency &other) const; // Sobrecarga do operador >=
        bool operator!=(const serialCurrency &other) const; // Sobrecarga do operador !=
        void setX(int nx); // Modificador do atributo x
        int getX() const; // Acessor do atributo x
        void setY(int ny); // Modificador do atributo y
        int getY() const; // Acessor do atributo y
        virtual string toString(); // Serialização
        virtual void fromString(string repr); // Desserialização
        // *** Não implementados
        virtual string toXML();
        virtual void fromXML(string repr);
        virtual string toCSV();
        virtual void fromCSV(string repr);
        virtual string toJSON();
        virtual void fromJSON(string repr);
        // ***
        virtual unsigned long long int size() const; // Método que calcula o tamanho do objeto da classe serialCurrency
}

#endif // SERIALCURRENCY_H_INCLUDED
*/
