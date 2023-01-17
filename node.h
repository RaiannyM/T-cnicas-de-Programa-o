
#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>
#include <vector>
#include "serializable.h"

using namespace std;

template <class T, const unsigned int MIN_DEGREE>
class node : serializable{
        public:
            node(); // Construtor padrão
            node(bool leaf); // Construtor paramétrico
            node(const node& other); // Construtor de cópia
            virtual ~node(); // Destrutor
            void setLeaf(bool nleaf); // Modificador do atributo leaf
            bool isLeaf() const; // Acessor do atributo leaf
            void setSize(unsigned int n); // Modificador do atributo n
            unsigned int getSize() const; // Acessor do atributo n
            void setKey(unsigned int i, T k); // Modificador do atributo key
            T getKey(unsigned int i); // Acessor do atributo key
            void setChild(unsigned int i, unsigned int indexFile); // Modificador do atributo child
            unsigned int getChild(unsigned int i); // Acessor do atributo child
            node<T, MIN_DEGREE> operator=(const node<T, MIN_DEGREE>& other);

            static const unsigned int MIN = MIN_DEGREE - 1; // A quantidade mínima de chaves em uma página
                                                            // é o grau mínimo menos um
            static const unsigned int MAX = 2 * MIN_DEGREE - 1; // A quantidade máxima de chaves em uma página
                                                                // é o dobro do grau máximo menos um
            static const unsigned int NOT_FOUND = -1;

            virtual string toString(); // Serialização da página
            virtual void fromString(string repr); // Desserialização da página
            // *** Não implementados
            virtual string toXML() { return "";};
            virtual void fromXML(string repr) {};
            virtual string toCSV() { return ""; };
            virtual void fromCSV(string repr) {};
            virtual string toJSON() { return ""; };
            virtual void fromJSON(string repr) {};
            // *** Nâo implementados
            virtual unsigned long long int size() const; // Método que calcula o tamanho da página
        protected:
            vector<T> keys; // Chaves da página
            vector<unsigned int> children; // Descendentes da página
            bool leaf; // Atributo que guarda se a página é folha ou não
            unsigned int n; // Atributo que guarda a quantidade de chaves que a página possui
};

template<class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::node(){ // Construtor padrão
    unsigned int i; // Variável auxiliar utilizada para modificar children

    setSize(0); // Tamanho da página é 0

    keys.resize(MAX); // A capacidade total da página é redimensionada para MAX
    children.resize(MAX + 1); // O número máximo de descendentes de uma página é
                              // o número máximo de chaves que ela pode ter + 1

    setLeaf(true); // Página marcada como folha

    for(i = 0; i < children.size(); i++){
        setChild(i, NOT_FOUND); // Não haverá descedentes no momento
    }
}

template<class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::node(bool new_leaf){ // Construtor paramétrico
    unsigned int i; // Variável auxiliar utilizada para modificar children

    setSize(0); // Tamanho da página é 0

    keys.resize(MAX); // A capacidade total da página é redimensionada para MAX
    children.resize(MAX + 1); // O número máximo de descendentes de uma página é
                              // o número máximo de chaves que ela pode ter + 1

    setLeaf(new_leaf); // Página marcada como o parâmetro passado

    for(i = 0; i < children.size(); i++){
        setChild(i, NOT_FOUND); // Não háverá descendentes no momento
    }
}

template<class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::node(const node<T, MIN_DEGREE>&other){ // Construtor de cópia
    // A página que chama o construtor de cópia terá o mesmo estado para os atributos
    // em relação a página passada por parâmetro

    setLeaf(other.isLeaf());
    setSize(other.getSize());

    keys.resize(MAX);
    children.resize(MAX + 1);

    children = other.children;
    keys = other.keys;
}

template<class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::~node(){ // Destrutor

}

template<class T, const unsigned int MIN_DEGREE>
string node<T, MIN_DEGREE>::toString(){ // Serialização da página
    string aux = ""; // Variável auxiliar que irá guardar os dados convertidos em bytes
    unsigned int i; // Variável auxiliar que irá ser utilizada para serializar
                    // as chaves e os descendentes da página

    aux += string(reinterpret_cast<char*>(&leaf), sizeof(leaf));
    aux += string(reinterpret_cast<char*>(&n), sizeof(n));

    for(i = 0; i < keys.size(); i++){
        aux += keys[i].toString();
    }

    for(i = 0; i < children.size(); i++){
        aux += string(reinterpret_cast<char*>(&children[i]), sizeof(children[i]));
    }

    return aux;
}

template<class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::fromString(string repr){ // Desserialização da página
    int pos = 0; // Variável auxiliar que irá ser utilizada durante a cópia de repr para os atributos da página
    unsigned int i; // Variável auxiliar que irá ser utilizada durante a desserialização das chaves e descendentes da págian

    repr.copy(reinterpret_cast<char*>(&leaf), sizeof(leaf), pos);
    pos += sizeof(leaf);

    repr.copy(reinterpret_cast<char*>(&n), sizeof(n), pos);
    pos += sizeof(n);

    string dataString = "";

    for(i = 0; i < keys.size(); i++){
        dataString = repr.substr(pos, keys[i].size());
        keys[i].fromString(dataString);
        pos += keys[i].size();
        dataString = "";
    }

    for(i = 0; i < children.size(); i++){
        repr.copy(reinterpret_cast<char*>(&children[i]), sizeof(children[i]), pos);
        pos += sizeof(children[i]);
    }
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::setKey(unsigned int i, T key){
    keys[i] = key;
}

template <class T, const unsigned int MIN_DEGREE>
T node<T, MIN_DEGREE>::getKey(unsigned int i){
    return keys[i];
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int node<T, MIN_DEGREE>::size() const{ // Calcula o tamanho da página
    return sizeof(children[0])*children.size() + keys[0].size()*keys.size() + sizeof(leaf) + sizeof(n);
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::setChild(unsigned int i, unsigned int indexFile){
    children[i] = indexFile;
}

template <class T, const unsigned int MIN_DEGREE>
unsigned int node<T, MIN_DEGREE>::getChild(unsigned int i){
    return children[i];
}

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE> node <T, MIN_DEGREE>::operator=(const node<T, MIN_DEGREE>& other){
  //  node<T, MIN_DEGREE> aux(other);
/*
    if(this == &other){
       return *this;
    }

    for(int i = 0; i < other.children.size(); i++){
        children[i] = other.getChild(i);
    }

    for(int i = 0; i < other.keys.size(); i++){
        keys[i] = other.getKeys(i);
    }
*/
    if(this != &other){
        children = other.children;
        keys = other.keys;
        leaf = other.isLeaf();
        n = other.getSize();
        return *this;
    }

    return *this;
}

template <class T, const unsigned int MIN_DEGREE>
unsigned int node<T, MIN_DEGREE>::getSize() const{
    return n;
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::setSize(unsigned int new_n){
    n = new_n;
}

template <class T, const unsigned int MIN_DEGREE>
bool node<T, MIN_DEGREE>::isLeaf() const{
    return leaf;
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::setLeaf(bool n_leaf){
    leaf = n_leaf;
}
#endif // NODE_H_INCLUDED
