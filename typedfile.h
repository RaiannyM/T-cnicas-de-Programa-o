#ifndef TYPEDFILE_H_INCLUDED
#define TYPEDFILE_H_INCLUDED

#include <fstream>
#include <type_traits>
#include "record.h"
#include "header.h"

using namespace std;

const ios::openmode mode = ios::in | ios::out | ios::binary;

template <class T, const unsigned int MIN_DEGREE>
class typedFile : private fstream{
    static_assert(is_base_of<serializable, T>::value, "T must be serializable");
    public:
        typedFile(); // Construtor padrão
        typedFile(const string new_name, const string new_type, const unsigned int new_version, ios::openmode openmode = mode); // Construtor paramétrico
        virtual ~typedFile(); // Destrutor
        bool open(const string new_name, const string new_type, const unsigned int new_version, ios::openmode openmode = mode); // Método que realiza a abertura do arquivo
        bool isOpen(); // Método que verifica se o arquivo está aberto
        bool close(); // Método que fecha o arquivo
        void clear(); // Método que limpa as flags de erro do arquivo
        bool readRecord(record<T, MIN_DEGREE> &r, unsigned long long int i); // Método que realiza a leitura de um registro
        bool writeRecord(record<T, MIN_DEGREE> &r, unsigned long long int i); // Método que realiza a escrita de um registro
        bool insertRoot(record<T, MIN_DEGREE> &r); // Método que realiza a inserção de um registro
        bool deleteRecord(unsigned long long int i); // Método que apaga um registro
        bool writeNode(record<T, MIN_DEGREE> &r, unsigned long long int i, bool isnew); // Método que realiza a escrita de um nó
        //unsigned long long int getRoot(); // Acessor do atributo root
        unsigned long long int getFirstValid(); // Acessor do atributo firstValid
        unsigned long long int getFirstDeleted(); // Acessor do atributo firstDeleted
        unsigned long long int search(T data); // Método que realiza a busca de um registro
        unsigned long long int findIndex(); // Método que encontra o índice
        void setFirstValid(unsigned long long int index);
        bool deleteNode(record<T, MIN_DEGREE> &r, unsigned long long int i);
    protected:
        header head; // Cabeçalho do arquivo
        bool readHeader(header &h); // Método que lê o cabeçalho
        bool writeHeader(header &h); // Método que escreve o cabeçalho
        unsigned long long int index2pos(unsigned long long int i); // Método que converte o índice em posição
        unsigned long long int pos2index(unsigned long long int p); // Método que converte a posição em índice
        bool deletefromBeg(unsigned long long int indexOfRecord);
        bool deletefromRightNeighbor(unsigned long long int indexOfNeighborRecord);
};

template <class T, const unsigned int MIN_DEGREE>
typedFile<T, MIN_DEGREE>::typedFile() : fstream() { // Construtor padrão
    if(open("file.dat", "DTB", MIN_DEGREE, mode)) // Se o arquivo for aberto com sucesso, o usuário é avisado
        cout << "O arquivo ArvoreB.dat foi aberto com sucesso!" << endl;
    else{
        cout << "Erro ao abrir o arquivo ArvoreB.dat" << endl;
        close(); // Caso contrário, o usuário é avisado e o arquivo é fechado
    }
}

template <class T, const unsigned int MIN_DEGREE> // Construtor paramétrico
typedFile<T, MIN_DEGREE>::typedFile(const string new_name, const string new_type, const unsigned int new_version, ios::openmode openmode) : fstream(new_name.c_str(), mode){
    if(open(new_name, new_type, new_version, mode)) // Se o arquivo for aberto com sucesso, o usuário é avisado
        cout << "O arquivo " << new_name << " foi aberto com sucesso!" << endl;
    else{
        cout << "Erro ao abrir o arquivo " << new_name << "!" << endl;
        cout << "As versões ou os tipos não são os mesmos." << endl;
        close(); // Caso contrário, o usuário é avisado e o arquivo é fechado
    }
}

template <class T, const unsigned int MIN_DEGREE> // Destrutor
typedFile<T, MIN_DEGREE>::~typedFile(){
    close();
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::open(const string new_name, const string new_type, const unsigned int new_version, ios::openmode openmode){
    fstream::open(new_name.c_str(), openmode);

    if(!isOpen() && new_version == MIN_DEGREE){
        fstream::open(new_name.c_str(), ios::out); // Criação do arquivo caso ele não exista
        fstream::close(); // Ele é fechado
        fstream::open(new_name.c_str(), openmode); // Ele é aberto agora com as flags openmode
                                       // Caso tivessemos apenas um open, não daria certo pois
                                       // ios::in impede a criação de um arquivo

        // Cabeçalho é definido...
        head.setType(new_type);
        head.setRoot(0);
        head.setFirstDeleted(0);
        head.setVersion(new_version);

        writeHeader(head);

        record<T, MIN_DEGREE> rec;
        insertRoot(rec);

        return true;
    } else{ // Se o cabeçalho já existe...
        readHeader(head); // Ele é carregado para a memória

        if(new_type == head.getType() && new_version == head.getVersion() && new_version == MIN_DEGREE){ // Verifica se o arquivo possui
                                                                                                         // possui os atributos que os
                                                                                                         // passados como argumentos
            return true;
        } else{
            return false;
        }
    }
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::isOpen(){ // Método que verifica se o arquivo está aberto
    return fstream::is_open();
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::close(){ // Método que fecha o arquivo
    fstream::close();
    return !isOpen();
}

template <class T, const unsigned int MIN_DEGREE>
void typedFile<T, MIN_DEGREE>::clear(){ // Método que limpa as flags de erro
    fstream::clear();
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::readRecord(record<T, MIN_DEGREE> &r, unsigned long long int i){
      if(isOpen()){
        char *aux = new char[r.size()]; // Ponteiro aux aponta é alocado dinamicamente
                                        // e agora aponta para um vetor de char
                                        // que possui a capacidade para guardar um registro
        clear();

        seekg(index2pos(i), ios::beg); // A cabeça de leitura é posicionada em i a partir do começo

        read(aux, r.size()); // A leitura do registro é feita e as suas informações postas no vetor apontado por aux

        string serializedRec; // Objeto auxiliar na leitura do registro serializado

        serializedRec = string(aux, r.size()); // Passando os dados para serializedRecord

        r.fromString(serializedRec); // O registro é desserializado

        delete[] aux; // O vetor é apagado do heap
        aux = nullptr; // O ponteiro aux agora não irá apontar para nada

        return true; // Leitura feita com sucesso!
      } else{
        cerr << "Não foi possível ler o registro!"<< endl;
        return false; // O registro não pode ser lido quando o arquivo estiver fechado
      }
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::writeRecord(record<T, MIN_DEGREE> &rec, unsigned long long int index){
    if(isOpen()){
        clear();

        seekp(index2pos(index), ios::beg); // A cabeça de escrita é posicionada na posição index
                                           // a partir do início

        write(rec.toString().c_str(), rec.size()); // É escrito no arquivo o record r

        return true;
    } else{
        cerr << "Não foi possível escrever o registro!" << endl;
        return false;
    }
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::insertRoot(record<T, MIN_DEGREE> &r){
    if(head.getFirstDeleted() != 0){ // Se existe registro que já foi apagado
        unsigned long long int index = head.getFirstDeleted(); // O índice do registro apagado é armazenado em index
        record<T, MIN_DEGREE> rec;

        if(readRecord(rec, index)){ // Consigo ler o registro rec?
            head.setFirstDeleted(rec.getNext());

            rec = r;
            rec.setNext(head.getRoot());

            head.setRoot(index); // A nova raíz é salva
            writeRecord(rec, index); // O registro é escrito
            writeHeader(head); // O cabeçalho é escrito
            return true;
        } else{
            return false;
        }
    } else{
        unsigned long long int pos;

        seekp(0, ios::end); // Cabeça de escrita é posicionada no fim do arquivo

        pos = tellp(); // tellp() retorna  a posição atual do caracter apontado pela cabeça de escrita

        r.setNext(head.getRoot());

        head.setRoot(pos2index(pos));

        // As alterações são salvas no arquivo...
        writeHeader(head);
        writeRecord(r, pos2index(pos));

        return true;
    }
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::deleteRecord(unsigned long long int id){
    unsigned long long int index, leftNeighbordIndex;
    record<T, MIN_DEGREE> aux;


    index = getFirstValid();
    leftNeighbordIndex = 0;

    if(id != index){
        while(index != 0 && good()){
            readRecord(aux, index);
            if(id == aux.getNext()){
                leftNeighbordIndex = index;
                return deletefromRightNeighbor(leftNeighbordIndex);
            }
            leftNeighbordIndex = index;
            index = aux.getNext();
        }
        return false;
    } else{
        readRecord(aux, index);
        return deletefromBeg(index);
    }
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::deletefromBeg(unsigned long long int indexOfRecord){
    record<T, MIN_DEGREE> deletedRecord;

    unsigned long long int indexOfFirstDeleted = getFirstDeleted();

    readRecord(deletedRecord, indexOfRecord);
    head.setRoot(deletedRecord.getNext());
    deletedRecord.setNext(indexOfFirstDeleted);
    deletedRecord.del();

    head.setFirstDeleted(indexOfRecord);
    writeRecord(deletedRecord, indexOfRecord);
    writeHeader(head);
    return true;
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::deletefromRightNeighbor(unsigned long long int indexOfNeighborRecord){
    record<T, MIN_DEGREE> deletedRecord, neighborOfRecord;
    unsigned long long int indexOfRecord, indexOfFirstDeleted;

    indexOfFirstDeleted = getFirstDeleted();

    readRecord(neighborOfRecord, indexOfNeighborRecord);
    indexOfRecord = neighborOfRecord.getNext();
    readRecord(deletedRecord, indexOfRecord);

    neighborOfRecord.setNext(deletedRecord.getNext());
    deletedRecord.setNext(indexOfFirstDeleted);
    deletedRecord.del();
    head.setFirstDeleted(indexOfRecord);

    writeRecord(neighborOfRecord, indexOfNeighborRecord);
    writeRecord(deletedRecord, indexOfRecord);
    writeHeader(head);

    return  true;
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int typedFile<T, MIN_DEGREE>::getFirstValid(){
    return head.getRoot();
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int typedFile<T, MIN_DEGREE>::getFirstDeleted(){
    return head.getFirstDeleted();
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int typedFile<T, MIN_DEGREE>::search(T data){
    unsigned long long int aux;

    aux = getFirstValid();

    while(aux != 0 && good()){
        record<T, MIN_DEGREE> rec;

        readRecord(rec, aux);

        if(data == rec.getData()) // A informação do registro lido é igual a passada pelo parâmetro?
            return aux; // Se sim, retorne a sua posição

        aux = rec.getNext(); // Se não, continue procurando...
    }
    return 0;
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::readHeader(header &h){
    if(isOpen()){
        char *aux = new char[head.size()]; //  Um vetor é alocado dinamicamente e agora aponta para
                                           //  um vetor de char no heap cujo tamanho é igual ao tamanho de head
        clear(); // Flags de erro são limpadas

        string headerAux;

        seekg(0, ios::beg); // A cabeça de escrita é posicionada na posição 0 a partir do início
        read(aux, head.size()); // Os dados de header são copiados para aux
        headerAux = string(aux, h.size()); // O que está em aux é passado para headerAux

        head.fromString(headerAux);

        delete [] aux;
        aux = nullptr;
        return true;
    } else{
        cerr << "Não foi possível ler o cabeçalho do arquivo!";
        return false;
    }
}

template <class T, const unsigned int MIN_DEGREE>// OK
bool typedFile<T, MIN_DEGREE>::writeHeader(header &h){
    if(isOpen() && good()){
        clear();
        string serializedHead = h.toString(); // h é serializado e atribuído a serializedHead, que irá auxiliar na escrita
        seekp(0, ios::beg); // A cabeça de escrita é posicionada em 0 a partir do início
        write(serializedHead.c_str(), h.size()); // A escrita é feita no arquivo
        return true;
    } else{
        cerr << "Não foi possível escrever o cabeçalho do arquivo!";
        return false;
    }
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int typedFile<T, MIN_DEGREE>::index2pos(unsigned long long int index){
    unsigned long long int pos;
    record<T, MIN_DEGREE> aux;

    pos = head.size() + ((index - 1) * aux.size()); // Index é convertido em posição

    return pos;
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int typedFile<T, MIN_DEGREE>::pos2index(unsigned long long int pos){
    unsigned long long int index;
    record<T, MIN_DEGREE> aux;

    index = ((pos - head.size()) / aux.size()) + 1; // Posição é convertido em index

    return index;
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int typedFile<T, MIN_DEGREE>::findIndex(){
    if(head.getFirstDeleted() != 0){
        return head.getFirstDeleted();
    } else{
        unsigned long long int pos;
        seekp(0, ios::end);
        pos = tellp();
        return pos2index(pos);
    }
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::writeNode(record<T, MIN_DEGREE> &r, unsigned long long int i, bool isnew){
    if(!isnew){
        return writeRecord(r, i);
    } else{
        if(head.getFirstDeleted() != 0){
            i = head.getFirstDeleted();
            record<T, MIN_DEGREE> rec;

            if(readRecord(rec, i)){
                head.setFirstDeleted(rec.getNext());
                rec = r;
                writeRecord(rec, i);
                writeHeader(head);

                return true;
            } else{
                return false;
            }
        } else{
            unsigned long long int pos;

            seekp(0, ios::end);
            pos = tellp();
            i = pos2index(pos);
            writeRecord(r, i);
            return true;
        }
    }
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::deleteNode(record<T, MIN_DEGREE> &rec, unsigned long long int index){
    rec.setNext(getFirstDeleted());
    head.setFirstDeleted(index);

    writeHeader(head);

    return writeRecord(rec, index);
}

template <class T, const unsigned int MIN_DEGREE>
void typedFile<T, MIN_DEGREE>::setFirstValid(unsigned long long int index){
    head.setRoot(index);
    writeHeader(head);
}

#endif // TYPEDFILE_H_INCLUDED
