/* Trabalho - Árvore B
   Nome: Mirelle Silva Vieira, RA: 0059636
   Nome: Raianny Magalhães Silva, RA: 0022116
*/

#ifndef RECORD_H_INCLUDED
#define RECORD_H_INCLUDED

#include <string>
#include "serializable.h"
#include "node.h"

using namespace std;

template <class T, const unsigned int MIN_DEGREE>
class record : public serializable{
    static_assert(is_base_of<serializable, T>::value, "T must be serializable");
    public:
        record(); // Construtor padrão
        record(node<T, MIN_DEGREE> d); // Construtor paramétrico
        record(const record<T, MIN_DEGREE> &other); // Construtor de cópia
        virtual ~record(); // Destrutor
        record<T, MIN_DEGREE> operator=(const record<T, MIN_DEGREE> &other); // Sobrecarga do operador =
        bool operator==(const record<T, MIN_DEGREE> &other); // Sobrecarga do operador ==
        node<T, MIN_DEGREE> getData() const; // Acessor de data
        void setData(node<T, MIN_DEGREE> new_data); // Modificador de data
        unsigned long long int getNext() const; // Acessor de next
        void setNext(unsigned long long int new_next); // Modificador de next
        bool isDeleted() const; // Acessor de deleted
        void del(); // Modificador de deleted para true
        void undel(); // Modificador de deleted para false
        virtual string toString(); // Serialização
        virtual void fromString(string repr); // Desserialização
        // *** Não implementados
        virtual string toCSV() { return "";};
        virtual void fromCSV(string repr) {};
        virtual string toJSON() { return "";};
        virtual void fromJSON(string repr) {};
        virtual string toXML() { return "";};
        virtual void fromXML(string repr) {};
        // ****
        virtual unsigned long long int size() const; // Calcula o tamanho do registro
    protected:
        node<T, MIN_DEGREE> data;
        bool deleted;
        unsigned long long int next;
};

template <class T, const unsigned int MIN_DEGREE>
record<T, MIN_DEGREE>::record() : serializable(){ // Construtor padrão
    node<T, MIN_DEGREE> data;

    this->data = data;
    deleted = true;
    next = 0;
}

template <class T, const unsigned MIN_DEGREE>
record<T, MIN_DEGREE>::record(node<T, MIN_DEGREE> new_data) : serializable(){ // Construtor paramétrico
    data = new_data;
    deleted = false;
    next = 0;
}

template <class T, const unsigned MIN_DEGREE>
record<T, MIN_DEGREE>::record(const record<T, MIN_DEGREE> &other){ // Construtor de cópia
    data = other.getData();
    deleted = other.isDeleted();
    next = other.getNext();
}

template <class T, const unsigned int MIN_DEGREE> // Destrutor
record<T, MIN_DEGREE>::~record(){

}

template <class T, const unsigned MIN_DEGREE>
record<T, MIN_DEGREE> record<T, MIN_DEGREE>::operator=(const record<T, MIN_DEGREE> &other){ // Sobrecarga do operador =
    record aux(other);

    if(this == &other){ // Se o registro que está chamando for igual ao registro
                        // passado por parâmetro ...
        return *this;
    }
    // Caso não seja igual, iguale
    data = other.getData();
    next = other.getNext();
    deleted = other.isDeleted();

    return aux;
}

template <class T, const unsigned int MIN_DEGREE>
bool record<T, MIN_DEGREE>::operator==(const record<T, MIN_DEGREE> &other){ // Sobrecarga do operador ==
    return data == other.getData() && deleted == other.isDeleted() && next == other.getNext();
}

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE> record<T, MIN_DEGREE>::getData() const{ // Acessor de data
    return data;
}

template <class T, const unsigned int MIN_DEGREE>
void record<T, MIN_DEGREE>::setData(node<T, MIN_DEGREE> new_data){ // Modificador de data
    data = new_data;
}

template <class T, const unsigned int MIN_DEGREE> // Acessor de next
unsigned long long int record<T, MIN_DEGREE>::getNext() const{
    return next;
}

template <class T, const unsigned int MIN_DEGREE> // Modificador de next
void record<T, MIN_DEGREE>::setNext(unsigned long long int new_next){
    next = new_next;
}

template <class T, const unsigned int MIN_DEGREE> // Acessor de deleted
bool record<T, MIN_DEGREE>::isDeleted() const{
    return deleted;
}

template <class T, const unsigned int MIN_DEGREE> // Modificador de deleted para true
void record<T, MIN_DEGREE>::del(){
    deleted = true;
}

template <class T, const unsigned int MIN_DEGREE> // Modificador de deleted para false
void record<T, MIN_DEGREE>::undel(){
    deleted = false;
}

template <class T, const unsigned int MIN_DEGREE>
string record<T, MIN_DEGREE>::toString(){ // Serialização
    string aux = ""; // Objeto aux onde irá ser armazenado os atributos serializados de record

    aux += data.toString();
    aux += string(reinterpret_cast<char*>(&deleted), sizeof(deleted));
    aux += string(reinterpret_cast<char*>(&next), sizeof(next));

    return aux;
}

template <class T, const unsigned int MIN_DEGREE>
void record<T, MIN_DEGREE>::fromString(string repr){ // Desserialização
    int pos = 0; // Variável que irá auxiliar no posicionamento correto durante a desserialização
    string dataString; // É instanciado um objeto dataString da classe string
                       // para auxiliar na desserialização de "data"

    dataString = repr.substr(pos, data.size()); // dataString recebe "data" serializado
    data.fromString(dataString); // dataString é desserializada
    pos += data.size();

    repr.copy(reinterpret_cast<char*>(&deleted), sizeof(deleted), pos);
    pos += sizeof(deleted);

    repr.copy(reinterpret_cast<char*>(&next), sizeof(next), pos);
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int record<T, MIN_DEGREE>::size() const{ // Calcula o tamanho de record
    return data.size() + sizeof(deleted) + sizeof(next);
}

#endif // RECORD_H_INCLUDED
