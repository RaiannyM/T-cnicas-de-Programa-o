#ifndef SERIALCURRENCY_H_INCLUDED
#define SERIALCURRENCY_H_INCLUDED

#include "serializable.h"
#include <iomanip>

class serialcurrency : serializable{
    protected:
        double intPart; // intPart é o atributo que refere-se a parte inteira do valor
        double fracPart; // fracPart é o atributo que refere-se a parte fracionária do valor
    public:
        serialcurrency(); // Construtor padrão
        void setSerialCurrency(double value); // Construtor paramétrico
        serialcurrency(const serialcurrency& other); // Construtor de cópia
        virtual ~serialcurrency(); // Destrutor
        serialcurrency operator=(const serialcurrency& other); // Sobrecarga do operador =
        bool operator==(const serialcurrency &other) const; // Sobrecarga do operador ==
        bool operator<(const serialcurrency &other) const; // Sobrecarga do operador <
        bool operator<=(const serialcurrency &other) const; // Sobrecarga do operador <=
        bool operator>(const serialcurrency &other) const; // Sobrecarga do operador >
        bool operator>=(const serialcurrency &other) const; // Sobrecarga do operador >=
        bool operator!=(const serialcurrency &other) const; // Sobrecarga do operador !=
        void setIntPart(double newIntPart); // Modificador do atributo x
        double getIntPart() const; // Acessor do atributo x
        void setFracPart(double newFracPart); // Modificador do atributo y
        double getFracPart() const; // Acessor do atributo y
        virtual string toString(); // Serialização
        virtual void fromString(string repr); // Desserialização
        friend ostream& operator<<(ostream& os, serialcurrency &sc){ // Sobrecarga do operador <<
            os << fixed << setprecision(2) << sc.intPart + sc.fracPart;
            return os;
        }
        string getSerialCurrency() const;
        // *** Não implementados
        virtual string toXML(){ return ""; };
        virtual void fromXML(string repr){};
        virtual string toCSV(){ return ""; };
        virtual void fromCSV(string repr){};
        virtual string toJSON(){ return ""; };
        virtual void fromJSON(string repr){};
        // ***
        virtual unsigned long long int size() const; // Método que calcula o tamanho do objeto da classe serialCurrency
};

#endif // SERIALCURRENCY_H_INCLUDED
