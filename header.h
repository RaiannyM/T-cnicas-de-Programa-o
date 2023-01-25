/* Trabalho - Árvore B
   Nome: Mirelle Silva Vieira, RA: 0059636
   Nome: Raianny Magalhães Silva, RA: 0022116
*/

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include "serializable.h"

class header : public serializable{
    public:
        header(); // Construtor padrão
        header(const string t, unsigned int v); // Construtor paramétrico
        header(const header &h); // Construtor de cópia
        virtual ~header(); // Destrutor
        header operator=(const header &h); // Sobrecarga do operador =
        bool operator==(const header &h); // Sobrecarga do operador ==
        unsigned long long int getFirstDeleted() const; // Acessor do atributo FirstDeleted
        void setFirstDeleted(unsigned long long int r); // Modificador do atributo FirstDeleted
        unsigned long long int getRoot() const; // Acessor do atributo FirstValid
        void setRoot(unsigned long long int r); // Modificador do atributo FirstValid
        string getType() const; // Acessor do atributo Type
        void setType(string t); // Modificador do atributo Type
        unsigned int getVersion() const; // Acessor do atributo Version
        void setVersion(unsigned int v); // Modificador do atributo Version
        virtual string toString(); // Serialização
        virtual void fromString(string repr);  // Desserialização
        // *** Não implementados
        virtual string toXML() { return ""; };
        virtual void fromXML(string repr){};
        virtual string toCSV(){ return ""; };
        virtual void fromCSV(string repr){};
        virtual string toJSON(){ return ""; };
        virtual void fromJSON(string repr){};
        // ***
        virtual unsigned long long int size() const; // Calcula o tamanho de header
    protected:
        string type;
        unsigned int version;
        unsigned long long int root;
        unsigned long long int firstDeleted;
};

#endif // HEADER_H_INCLUDED
