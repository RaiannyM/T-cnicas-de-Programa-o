#ifndef SERIALIZABLE_H_INCLUDED
#define SERIALIZABLE_H_INCLUDED

#include <string>

using namespace std;

class serializable{
    public:
        serializable(){} // Construtor padrão
        virtual ~serializable(){} // Destrutor
        virtual string toString() = 0; // Serialização
        virtual void fromString(string repr) = 0; // Desserialização
        // *** Métodos não implementados
        virtual string toXML() = 0;
        virtual void fromXML(string repr) = 0;
        virtual string toCSV() = 0;
        virtual void fromCSV(string repr) = 0;
        virtual string toJSON() = 0;
        virtual void fromJSON(string repr) = 0;
        //****
        virtual unsigned long long int size() const = 0; // Calcula o tamanho de um objeto da classe serializable
};

#endif // SERIALIZABLE_H_INCLUDED
