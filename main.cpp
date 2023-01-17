#include <iostream>
#include "btree.h"
#include "charserial.h"
#include <clocale>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese");
    btree<charserial, 3> disk("file.dat", "DTB", 3);
    char vetorpraInserir[20] = {')', '6', 'O', 'b', 'L', 'G', 'P', 'C', '3', '%', 'm', '(', 'H', 'W', 'Y', '&', 'k', '1', 'X', '-'};
    char vetorpraRemover[10] = {'C', 'm', '1', 'O', ')', 'W', 'Y', 'L', 'X', '('};
    charserial caractere;
    char valor;
    string op;
    int resp;

    if(disk.isOpen()){
        do{
            cout << "--------------------------\n"
                 << "Árvore B em Disco\n"
                 << "Selecione uma opção:\n\n"
                 << "1. Inserir um caractere\n"
                 << "2. Remover um caractere\n"
                 << "3. Pesquisar um caractere\n"
                 << "4. Imprimir árvore\n"
                 << "5. Teste automatizado\n"
                 << "6. Sair\n\n"
                 << "Sua opção: ";
            cin >> resp;

            switch(resp){
                case 1:
                    cout << "Digite um caractere: ";
                    cin >> valor;
                    caractere.setValue(valor);
                    if(disk.insertKey(caractere)){
                        disk.print();
                    }else{
                        cout << "Não foi possível inserir o caractere!" << endl;
                    }
                    break;
                case 2:
                    cout << "Digite um character: ";
                    cin >> valor;
                    caractere.setValue(valor);
                    if(disk.remove(caractere)){
                        disk.print();
                    }else{
                        cout << "Não foi possível remover o caractere!" << endl;
                    }
                    break;
                case 3:
                    cout << "Digite um caractere: ";
                    cin >> valor;
                    caractere.setValue(valor);
                    if(disk.search(caractere)){
                        cout << "Valor encontrado" << endl;
                    }else{
                        cout << "Valor não encontrado" << endl;
                    }
                    break;
                case 4:
                    disk.print();
                    break;
                case 5:
                    cout << endl
                         << "----------------------Efetuando as inserções--------------------"
                         << endl;
                    for(int i = 0; i< 20; i++){
                        caractere.setValue(vetorpraInserir[i]);
                        if(disk.insertKey(caractere)){
                            cout << "Mostrando após a Inserção de: " << vetorpraInserir[i] << endl;
                            disk.print();
                        }
                    }
                    cout << endl
                         << "----------------------Efetuando as Remoções--------------------"
                         << endl;
                    for(int i = 0; i< 10; i++){
                        caractere.setValue(vetorpraRemover[i]);
                        if(disk.remove(caractere)){
                            cout << "Mostrando após a Remoção de: "<< vetorpraRemover[i] << endl;
                            disk.print();
                        }
                    }
                    break;
                case 6:
                    cout << "Encerrando o programa... ";
                    disk.close();
                    cout << "Concluído! " << endl;
                    return 0;
                    break;
                default:
                    cout << "Opção inválida! Tente novamente... " << endl;
                    break;
            }
    } while(true);
    }else{
        cout << "Verifique se: " << endl
             << "- As versões entre o arquivo e a informada batem" << endl
             << "- O grau da árvore é o mesmo que a versão" << endl
             << "- Caso o grau da árvore não seja o mesmo que a versão, por favor, forneça um arquivo com grau = ver" << endl;
    }
    return 0;
}
