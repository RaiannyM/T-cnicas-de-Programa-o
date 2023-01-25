/* Trabalho - Árvore B
   Nome: Mirelle Silva Vieira, RA: 0059636
   Nome: Raianny Magalhães Silva, RA: 0022116
*/

#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "typedfile.h"
#include "node.h"
#include "record.h"

using namespace std;

template <class T, const unsigned int MIN_DEGREE>
class btree : private typedFile <T, MIN_DEGREE>{
    protected:
        node<T, MIN_DEGREE> root;
        int searchAux(node<T, MIN_DEGREE> rec, T key); // Método que irá auxiliar na busca
        void printAux(node<T, MIN_DEGREE> x, vector<string> &v, unsigned int lvl); // Método que irá auxiliar na impressão da árvore
    public:
        btree(); // Construtor padrão
        btree(const string new_name, const string new_type, const unsigned int new_version); // Construtor paramétrico
        virtual ~btree(); // Destrutor
        void setRoot(node<T, MIN_DEGREE> new_root); // Modificador do atributo root
        node<T, MIN_DEGREE> getRoot() const; // Acessor do atributo root
        void close(); // Método que irá fechar o arquivo
        bool isOpen(); // Método que irá verificar se o arquivo foi aberto
        void print(); // Método que irá imprimir a árvore
        int search(T key); // Método que irá realizar a procura de uma chave na árvore
        bool insertKey(T key); // Método que realiza a inserção da chave em uma página da árvore
        bool insertNonFull(node<T, MIN_DEGREE>& node, T key, unsigned int index); // Método que auxilia na inserção
        bool remove(T key); // Método que realiza a remoção de uma chave em uma página da árvore
        unsigned int hasKey(node<T, MIN_DEGREE> x, T key);
        node<T, MIN_DEGREE> readNode(unsigned int i);
        bool insertRoot(node<T, MIN_DEGREE> new_node);
        bool writeNode(node<T, MIN_DEGREE> x, unsigned long long int index, bool recent);
        void splitChild(node<T, MIN_DEGREE>& x, unsigned int index, unsigned int indexOfNodeX);
        bool deleteNode(node<T, MIN_DEGREE> n, unsigned int i);
};

template <class T, const unsigned int MIN_DEGREE> // Construtor padrão
btree<T, MIN_DEGREE>::btree():typedFile<T, MIN_DEGREE>::typedFile(){
    setRoot(readNode(typedFile<T, MIN_DEGREE>::getFirstValid())); // O nó será a raíz da árvore
}

template <class T, const unsigned int MIN_DEGREE> // Construtor paramétrico
btree<T, MIN_DEGREE>::btree(const string new_name, const string new_type, const unsigned int new_version):typedFile<T, MIN_DEGREE>(new_name, new_type, new_version){
    setRoot(readNode(typedFile<T, MIN_DEGREE>::getFirstValid()));
}

template <class T, const unsigned int MIN_DEGREE> // Método que irá verificar se o arquivo foi aberto
bool btree<T, MIN_DEGREE>::isOpen(){
    return typedFile<T, MIN_DEGREE>::isOpen();
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::close(){ // Método que irá fechar o arquivo
    typedFile<T, MIN_DEGREE>::close();
}

template <class T, const unsigned int MIN_DEGREE> // Método auxiliar que irá ler uma página
node<T, MIN_DEGREE> btree<T, MIN_DEGREE>::readNode(unsigned int index){
    record<T, MIN_DEGREE> rec;

    typedFile<T, MIN_DEGREE>::readRecord(rec, index);

    return rec.getData();
}

template <class T, const unsigned int MIN_DEGREE>
int btree<T, MIN_DEGREE>::search(T key){ // Método que realiza a busca por uma chave
    node<T, MIN_DEGREE> rec; // Nó auxiliar que irá guardar a raíz

    rec = getRoot();

    return searchAux(rec, key);
}

template <class T, const unsigned int MIN_DEGREE>
int btree<T, MIN_DEGREE>::searchAux(node<T, MIN_DEGREE> rec, T key){ // Método auxiliar na busca pela chave
    unsigned int i = 0; // Variável auxiliar que irá armazenar temporariamente índices durante a busca
    node<T, MIN_DEGREE> aux; // Nó auxiliar que irá armazenar temporariamente nós durante a busca

    while(i < rec.getSize() && key > rec.getKey(i)){ // Buscando na página atual para descobrir se a chave key está presente
        i++;                                         // Enquanto a chave a ser procurada for maior que a chave do registro,
                                                     // a variável i será incrementada
    }
    // Laço de repetição para quando é encontrada no registro uma chave maior em relação a procurada
    if(i < rec.getSize() && rec.getKey(i) == key) // A chave do registro é igual a procurada?
        return i; // Se sim, devolva a sua posição
    else{
        if(rec.isLeaf()){ // Caso não seja e a página seja folha
            rec = NULL;
            return -1; // A chave não está presente na árvore
        }else{ // Caso a página não seja folha, a busca pela chave continua....
            aux = readNode(rec.getChild(i));

            return searchAux(aux, key);
        }
    }
}

template <class T, const unsigned int MIN_DEGREE> // Método auxiliar que irá realizar a inserção da chave na raíz
bool btree<T, MIN_DEGREE>::insertRoot(node<T, MIN_DEGREE> new_node){
    record<T, MIN_DEGREE> new_rec;

    new_rec.setData(new_node);

    return typedFile<T, MIN_DEGREE>::insertRoot(new_rec);
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::insertKey(T key){
    bool result = false;
    node <T, MIN_DEGREE> rAux;
    rAux = btree<T, MIN_DEGREE>::getRoot();

    if(rAux.getSize() == rAux.MAX){ // A raíz está cheia? Se sim, dê split
        node<T, MIN_DEGREE> new_root, aux; // Nova raíz é criada

        new_root.setLeaf(false); // A nova raíz não é folha

        unsigned int aux_index = 0; // Variável auxiliar que irá guardar índices

        new_root.setChild(0, typedFile<T, MIN_DEGREE>::getFirstValid()); // A antiga raíz se torna a sua filha da esquerda

        insertRoot(new_root); // Atualizando a raíz da árvore...

        splitChild(new_root, 0, typedFile<T, MIN_DEGREE>::getFirstValid()); // Dividindo o filho mais à esquerda da nova raíz
                                                                                // para realizar a divisão corretamente e inserir
                                                                                // a chave da posição mediana na nova raíz

        if(new_root.getKey(0) < key){ // Depois que a divisão é feita, para qual página devo descer?
            aux_index++;
        }

        aux = readNode(new_root.getChild(aux_index)); // O filho escolhido é lido

        result = insertNonFull(aux, key, new_root.getChild(aux_index));

        setRoot(new_root);

        return result;
    } else{
        result = insertNonFull(rAux, key, typedFile<T, MIN_DEGREE>::getFirstValid());
        setRoot(rAux);

        return result;
    }
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::insertNonFull(node<T, MIN_DEGREE>& x, T key, unsigned int index){
    int i;

    i = x.getSize() - 1;

    if(x.isLeaf()){
        while(i >= 0 && key < x.getKey(i)){
            x.setKey(i + 1, x.getKey(i));
            i--;
        }
        i++;
        x.setKey(i, key);
        x.setSize(x.getSize() + 1);
       return writeNode(x, index, false);
    } else{
        node<T, MIN_DEGREE> aux;

        int n = 0;

        while(n <= i && x.getKey(n) < key){
            n++;
        }

        aux = readNode(x.getChild(n));

        if(aux.getSize() == aux.MAX){
            splitChild(x, n, index);

            if(x.getKey(n) < key){
                n++;
            }
        }

        aux = readNode(x.getChild(n));

        return insertNonFull(aux, key, x.getChild(n));
    }
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::splitChild(node<T, MIN_DEGREE>& nodeX, unsigned int index, unsigned int indexOfNodeX){
    node <T, MIN_DEGREE> nodeY, nodeZ;
    unsigned int j;

    nodeY = readNode(nodeX.getChild(index));

    nodeZ.setLeaf(nodeY.isLeaf()); // Como z e y estão no mesmo nível, se um for folha, o outro também será.
                                   // Caso contrário, se um for nó interno, o outro necessariamente também será.
    nodeZ.setSize(nodeZ.MIN);

    // As chaves de y são copiadas para z
    for(j = 0; j < nodeZ.getSize(); j++){ // Devo alterar j < nodeZ.getSize() para j < MIN_DEGREE + 1?
        nodeZ.setKey(j, nodeY.getKey(j + MIN_DEGREE));
    }

    if(!nodeY.isLeaf()){
        for(j = 0; j < MIN_DEGREE; j++){
            nodeZ.setChild(j, nodeY.getChild(j + MIN_DEGREE));
        }
    }

    nodeY.setSize(nodeY.MIN);

    for(j = nodeX.getSize(); j >= (index + 1); j--){
        nodeX.setChild(j+1, nodeX.getChild(j));
        if(j == 0)
            break;
    }

    nodeX.setChild(index + 1, typedFile<T, MIN_DEGREE>::findIndex());

    if(nodeX.getSize() > 0){
        for(j = nodeX.getSize() - 1; j >= index; j--){
            nodeX.setKey(j + 1, nodeX.getKey(j));
            if(j == 0) // Existe uma melhor maneira para implementar isso?
                break;
        }
    }

    nodeX.setKey(index, nodeY.getKey(nodeY.MIN));
    nodeX.setSize(nodeX.getSize() + 1);

    writeNode(nodeX, indexOfNodeX, false); // WriteNode tem que ser inserido em Node!!
    writeNode(nodeY, nodeX.getChild(index), false);
    writeNode(nodeZ, 0, true);
}

template <class T, const unsigned int MIN_DEGREE>
btree<T, MIN_DEGREE>::~btree(){ // Destrutor
    close();
}

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE> btree<T, MIN_DEGREE>::getRoot() const{ // Acessor do atributo root
    return root;
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::setRoot(node<T, MIN_DEGREE> new_root){ // Modificador do atributo root
    root = new_root;
}

template <class T, const unsigned int MIN_DEGREE> // Método que irá realizar a inserção de uma chave em uma página
bool btree<T, MIN_DEGREE>::writeNode(node<T, MIN_DEGREE> x, unsigned long long int index, bool recent){
    record<T, MIN_DEGREE> rec;

    rec.setData(x);

    return typedFile<T, MIN_DEGREE>::writeNode(rec, index, recent);
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::print(){ // Método que irá imprimir a árvore
    int lvl; // Variável auxiliar que irá melhorar a visualização da árvore de acordo com o nível para o usuário

    lvl = 0;

    vector<string> levels(1);
    printAux(root, levels, lvl); // A árvore será percorrida e suas chaves salvas no vetor levels de acordo
                                 // com o nível da página em que elas se encontram

    for(string s : levels){ // O que está armazenado no vetor levels é atribuído ao objeto s de acordo com o nível
        cout << s << endl;
    }
}

template <class T, const unsigned int MIN_DEGREE> // Método que irá auxiliar na impressão da árvore
void btree<T, MIN_DEGREE>::printAux(node<T, MIN_DEGREE> x, vector<string> &v, unsigned int lvl){
    string auxStr = "["; // objeto auxStr irá armazenar as chaves enquanto a árvore é percorrida é inicializado
    unsigned int i = 0; // Variável auxiliar que irá armazenar índices durante a impressão

    if(v.size() < lvl + 1){ // Se o nível mudou, o vetor v é redimensionado
        v.resize(lvl + 1);
    }

    if(!x.isLeaf()){ // Se x não for folha ...
        for(i = 0; i <= x.getSize(); i++){ // Seus filhos são visitados
            if(x.getChild(i) != x.NOT_FOUND){
                node<T, MIN_DEGREE> aux;

                aux = readNode(x.getChild(i));
                printAux(aux, v, lvl+1); // Chamada recursiva a printAux aumentando o nível em uma unidade
            }
        }
    }

    for(i = 0; i < x.getSize(); i++){
        double aux;

        auxStr += x.getKey(i).getValue() + ", "; // Todas as chaves são armazenadas em auxStr
    }

    if(auxStr.length() > 1){ // auxStr é organizada
        auxStr +=  "\b\b]";
    } else{
        auxStr += "]";
    }

    v[lvl] += auxStr; // A cada chamada recursiva, o nível de v é incrementado
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::remove(T key){
    node<T, MIN_DEGREE> root = getRoot();

    if(root.getSize() == 0){
        return false;
    }
}

template <class T, const unsigned int MIN_DEGREE>
unsigned int btree<T, MIN_DEGREE>::hasKey(node<T, MIN_DEGREE> x, T key){
    unsigned int index = 0;

    while(index < x.getSize() && key > x.getKey(index)){
        index++;
    }

    return index;
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::deleteNode(node<T, MIN_DEGREE> x, unsigned int i){
    record<T, MIN_DEGREE> rec;

    rec.setData(x);

    return typedFile<T, MIN_DEGREE>::deleteNode(rec, i);
}
#endif // BTREE_H_INCLUDED
