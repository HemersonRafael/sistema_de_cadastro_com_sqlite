/*
SISTEMA DE CONTROLE DE ESTOQUE- SCE

DESENVOLVEDORES:
Hemerson Rafael Pereira Pontes
*/
#include <cstdlib> //Utilizada devido a função system
#include <cstdio> //Utilizado devido as funções fprintf e printf
#include <iostream>//Utilizado devido as funções cout, cin
#include "sqlite3.h"//Utilizado para criar e manipular o banco de dados
#include <sstream>// Utilizada devido ao uso de stringstream
#define TXT 35
#define TCPF 12
#define TCNPJ 15
#define TCODIGO 14
#define TCONTATO 10

using namespace std;

// Declarações do Banco de dados (padrão do SQLite)
sqlite3 *db;
char *zErrMsg = 0;
int rc;
// Declaração dos tipos de estruturas utilizado no código
struct Produto{

    unsigned int id;
    char nome[TXT];
    char cor [TXT];
    char marca [TXT];
    char codigo[TCODIGO];
    char setor[TXT];
    float valor;
    int quantidade;

};

struct Cliente{

    unsigned int id;
    char nome[TXT];
    char cpf[TCPF];
    char contato[TCONTATO];

};

struct Fornecedor{

    unsigned int id;
    char nome[TXT];
    char cnpj[TCNPJ];
    char contato[TCONTATO];

};
//A função connect realizar a conexão com banco de dados SQL
void connect(const char *db_file) {
   //Cria o banco de dados SQL
   rc = sqlite3_open(db_file, &db);

   if( rc ){

      fprintf(stderr, "Nao foi possivel abrir o banco de dados: %s\n", sqlite3_errmsg(db));
      return;
   }
   else{

      fprintf(stderr, "Banco de bados aberto com sucesso\n");
   }
}
//A função callback obtem os resultados de uma instrução SELECT
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
// A função exec utilizada para receber as instruções SQL
void exec(const char *sql) {
   // Executa as instruções SQL
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ){

        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

   else{

      fprintf(stdout, " com sucesso!\n");
   }
}
//A função CadastarProduto é utilizada para realizar o cadastro de produtos ao banco de dados
void CadastrarProduto(){

    stringstream sql;
    Produto p;
    int operador;

    do{

        do{

            system("clear");

            cout << "_______ TELA DE CADASTRO DE PRODUTOS _______\n\n";

            cout << "Informe o nome do produto: \n";
            cin.ignore();
            cin.getline(p.nome,TXT);

            cout << "Informe a marca do produto: \n";
            cin.getline(p.marca,TXT);

            cout << "Informe a cor do produto: \n";
            cin.getline(p.cor,TXT);

            cout << "Informe o codigo do produto: \n";
            cin.getline( p.codigo,TCODIGO);

            cout << "Informe o setor do produto: \n";
            cin.getline(p.setor,TXT);

            cout << "Informe o valor do produto \n";
            cin >> p.valor;

            cout << "Informe a quantidade deste produto \n";
            cin >> p.quantidade;

            cout << "Deseja realmente cadastrar esse produto?\n";
            cout << "\t1- Para sim \n\t0- Para nao \n: ";
            cin >> operador;

            if(operador == 1){

                sql << "INSERT INTO PRODUTO (ID, NOME, COR, MARCA, CODIGO, SETOR, VALOR, QUANTIDADE) VALUES (NULL , '" << p.nome << "', '" << p.cor << "', '" << p.marca <<"', '" << p.codigo << "', '" << p.setor << "', " << p.valor  << ", " << p.quantidade <<" ); ";

                string tmp = sql.str();
                const char * s = tmp.c_str();

                cout << "\n Produto cadastrado";

                exec(s);

                cout << endl;



            }

            else{

                cout << "\n Produto informado nao foi cadastrado!\n";
                system("read -p \"Pressione enter para continuar\" saindo");
                system("clear");
            }

        }while(operador != 1);

        do{

            cout << "\n_________________________________________________\n\n";
            cout << "Deseja cadastrar mais algum produto?\n";
            cout << "\t1- Para sim \n\t0- Para nao\n: ";
            cin >> operador;
            if(operador < 0 || operador > 1){
                    cout << "\nInforme uma operacao valida!\n\n";
                    system("read -p \"Pressione enter para continuar\" saindo");
                    system("clear");
            }

        }while(operador < 0 || operador > 1);

        system("clear");

    }while(operador !=0);

}
//A função CadastarProduto é utilizada para realizar o cadastro de clientes ao banco de dados
void CadastrarCliente(){

    stringstream sql;
    int operador;
    Cliente c;

    do{

        do{

            system("clear");

            cout << "\n_______ TELA DE CADASTRO DE CLIENTES _______\n\n";
            cout << "Informe o nome do cliente: \n";
            cin.ignore();
            cin.getline(c.nome,TXT);

            cout << "Informe o CPF do cliente: \n";
            cin.getline(c.cpf,TCPF);

            cout << "Informe o numero para contato: \n";
            cin.getline(c.contato,TCONTATO);
            cout << "Deseja realmente cadastrar esse produto?\n";
            cout << "\t1- Para sim \n\t0- Para nao\n: ";
            cin >> operador;

            if(operador == 1){

                sql << "INSERT INTO CLIENTE (ID, NOME, CPF, CONTATO) VALUES (NULL , '" << c.nome << "','" << c.cpf << "','" << c.contato  <<"' ); ";

                string tmp = sql.str();
                const char * s = tmp.c_str();

                cout << "\n Cliente cadastrado";

                exec(s);

                cout << endl;

            }

            else{

                cout << "\n Cliente informado nao foi cadastrado!\n";
                system("read -p \"Pressione enter para continuar\" saindo");
                system("clear");
            }

        }while(operador != 1);

        do{
            cout << "\n__________________________________________________\n\n";
            cout << "Deseja cadastrar mais algum cliente?\n";
            cout << "\t1- Para sim \n\t0- Para nao\n: ";
            cin >> operador;

            if(operador < 0 || operador > 1){
                    cout << "\nInforme uma operacao valida!\n\n";
                    system("read -p \"Pressione enter para continuar\" saindo");
                    system("clear");
            }

        }while(operador < 0 || operador > 1);

        system("clear");


    }while(operador != 0);


}
//A função CadastarProduto é utilizada para realizar o cadastro de fornecedos ao banco de dados
void CadastrarFornecedor(){

    stringstream sql;
    int operador;
    Fornecedor f;


    do{

        do{

            system("clear");

            cout << "\n_________ TELA DE CADASTRO DE FORNECEDORES _________\n\n";

            cout << "Informe o nome do fornecedor:\n";
            cin.ignore();
            cin.getline(f.nome,TXT);

            cout << "Informe o CNPJ do fornecedor:\n";
            cin.ignore();
            cin.getline(f.cnpj,TCNPJ);

            cout << "Informe o numero para contato: \n";
            cin.ignore();
            cin.getline(f.contato,TCONTATO);

            cout << "Deseja realmente cadastrar esse fornecedor?\n";
            cout << "\t1- Para sim \n\t0- Para nao \n: ";
            cin >> operador;

            if(operador == 1){

                sql << "INSERT INTO FORNECEDOR (ID, NOME, CNPJ, CONTATO) VALUES (NULL , '" << f.nome << "','" << f.cnpj << "','" << f.contato  <<"'); ";

                string tmp = sql.str();
                const char * s = tmp.c_str();

                cout << "\n Fornecedor cadastrado";

                exec(s);

                cout << endl;

            }

            else{

                cout << "\n Fornecedor informado nao foi cadastrado!\n";
                system("read -p \"Pressione enter para continuar\" saindo");
                system("clear");
            }

        }while(operador != 1);

        do{
            cout << "\n__________________________________________________\n\n";

            cout << "\nDeseja cadastrar mais algum fornecedor?\n";
            cout << "\t1- Para sim \n\t0- Para nao\n: ";
            cin >> operador;

            if(operador < 0 || operador > 1){
                    cout << "\nInforme uma operacao valida!\n\n";
                    system("read -p \"Pressione enter para continuar\" saindo");
                    system("clear");
            }

        }while(operador < 0 || operador > 1);

        system("clear");

    }while(operador != 0);


}
//A função CriarTabelas é utilizada para realizar o criação de tabelas de produtos, cliente e fornecedor no banco de dados
void CriarTabelas(){

    stringstream sql;

    sql << "CREATE TABLE IF NOT EXISTS PRODUTO( ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, NOME VARCHAR(" << TXT << ") NOT NULL, COR VARCHAR(" << TXT << ") NOT NULL, MARCA VARCHAR(" << TXT << ") NOT NULL, CODIGO VARCHAR(" << TCODIGO << ") NOT NULL, SETOR VARCHAR(" << TXT << ") NOT NULL, VALOR FLOAT NOT NULL, QUANTIDADE INT NOT NULL);";

    sql << "CREATE TABLE IF NOT EXISTS CLIENTE( ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, NOME VARCHAR(" << TXT << ") NOT NULL, CPF VARCHAR(" << TCPF << ") NOT NULL UNIQUE, CONTATO  VARCHAR(" << TCONTATO << ") NOT NULL );";

    sql << "CREATE TABLE IF NOT EXISTS FORNECEDOR(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, NOME VARCHAR(" << TXT << ") NOT NULL, CNPJ VARCHAR(" << TCNPJ << ") NOT NULL UNIQUE, CONTATO VARCHAR(" << TCONTATO << ") NOT NULL );";

    string tmp = sql.str();
    const char * s = tmp.c_str();

    exec(s);
}
// A função é utilizada para realizar busca no banco de dados
void Buscar(string tabela, string coluna){

    system("clear");

    stringstream sql;

    sql << "SELECT " << coluna << "  FROM " << tabela <<";";

    string tmp = sql.str();
    const char * s = tmp.c_str();
    cout << "\n__________ LISTA DE " << tabela << " CADASTRADOS __________" << endl << endl;

    exec(s);
    cout << "_________________________________________________" << endl << endl;

}
// A função é utilizada para realizar busca no banco de dados
void BuscarChave(string tabela,  string coluna, string chave){

    system("clear");

    stringstream sql;


    sql << "SELECT * FROM " << tabela <<" WHERE " << coluna <<" LIKE '" << chave << "%';";

    string tmp = sql.str();
    const char * s = tmp.c_str();
    cout << "\n__________ LISTA DE " << tabela << " CADASTRADOS __________" << endl << endl;

    exec(s);
    cout << "_________________________________________________" << endl << endl;

}
// A função é utilizada para deletar elementos de uma tabela no banco de dados
void Deletar(string tabela, int id){

    stringstream sql;

    sql << "DELETE FROM " << tabela << " WHERE ID = " << id << ";";

    string temp = sql.str();

    const char *s =temp.c_str();

    exec(s);
}
// A função é utilizada para alterar elementos de uma tabela no banco de dados do tipo char
void Alterar(string tabela, string coluna, int id, string substituto){

    stringstream sql;

    sql << "UPDATE " << tabela << " SET " <<coluna <<" = '" << substituto << "' WHERE ID = " << id << ";";

    string temp = sql.str();

    const char *s =temp.c_str();

    exec(s);
}
// A função é utilizada para alterar elementos de uma tabela no banco de dados do tipo int
void AlterarI(string tabela, string coluna, int id, int substituto){

    stringstream sql;

    sql << "UPDATE " << tabela << " SET " <<coluna <<" = '" << substituto << "' WHERE ID = " << id << ";";

    string temp = sql.str();

    const char *s =temp.c_str();

    exec(s);
}
// A função é utilizar para organizar a manipulação das funções Buscar, Deletar, Alterar e AlterarI
void Manipular(string tabela){

    int operador, seletor, id, valor, quantidade;
    string sub;

    do{
        cout << "\nDeseja manipular algum elemento da lista acima\n";
        cout << "\t1-Para alterar\n\t2-Para deletar\n\t0-volta para menu\n: ";
        cin >> operador;

        if(operador == 0){

            return;
        }

        else if (operador < 0 || operador > 2){

            cout << "\nInforme uma operacao valida!\n\n";
            system("read -p \"Pressione enter para continuar\" saindo");
            system("clear");
        }

    }while(operador < 0 || operador > 2);

    if(tabela == "PRODUTO"){

        if(operador == 1){

            do{

                cout << "\nInforme o ID do produto que sera alterado: \n";
                cin >> id;
                cout << "Selecione qual campo do produto deseja alterar\n";
                cout << "\t1-Para nome\n\t2-Para cor\n\t3-Para marca\n\t4-Para codigo\n\t5-Para setor\n\t6-Para valor\n\t7-Para quantidade\n: ";
                cin >> seletor;

                if (seletor < 1 || seletor > 7){

                    cout << "\nInforme uma operacao valida!\n\n";
                    system("read -p \"Pressione enter para continuar\" saindo");
                    system("clear");
                }

            }while(seletor < 1 || seletor > 7);

            switch(seletor){
                case 1:{
                    cout << "Informe o novo nome: \n";
                    cin.ignore();
                    getline(cin,sub);
                    Alterar("PRODUTO", "NOME", id, sub);
                    break;
                }
                case 2:{
                    cout << "Informe a nova cor: \n";
                    cin.ignore();
                    getline(cin,sub);
                    Alterar("PRODUTO", "COR", id, sub);
                    break;
                }
                case 3:{
                    cout << "Informe a nova marca: \n";
                    cin.ignore();
                    getline(cin,sub);
                    Alterar("PRODUTO", "MARCA", id, sub);
                    break;
                }
                case 4:{
                    cout << "Informe o novo codigo: \n";
                    cin.ignore();
                    getline(cin,sub);
                    Alterar("PRODUTO", "CODIGO", id, sub);
                    break;
                }
                case 5:{
                    cout << "Informe o novo setor: \n";
                    cin.ignore();
                    getline(cin,sub);
                    Alterar("PRODUTO", "SETOR", id, sub);
                    break;
                }
                case 6:{
                    cout << "Informe o novo valor: \n";
                    cin >> valor;
                    AlterarI("PRODUTO", "VALOR", id, valor);
                    break;
                }
                case 7:{
                    cout << "Informe a nova quantidade: \n";
                    cin >> quantidade;
                    AlterarI("PRODUTO", "QUANTIDADE", id, quantidade);
                    break;
                }


            }
        }

        else if(operador == 2){

            cout << "Informe o ID do produto que sera deletado: \n";
            cin >> id;
            Deletar("PRODUTO", id);
        }
    }

    else if(tabela == "CLIENTE"){

        if(operador == 1){

            do{
                cout << "Informe o ID do cliente que sera alterado: \n";
                cin >> id;
                cout << "Selecione qual campo do cliente deseja alterar\n";
                cout << "\t1-Para nome\n\t2-Para cpf\n\t3-Para contato\n: ";
                cin >> seletor;

                if (seletor < 1 || seletor > 3){

                    cout << "\nInforme uma operacao valida!\n\n";
                    system("read -p \"Pressione enter para continuar\" saindo");
                    system("clear");
                }

            }while(seletor < 1 || seletor > 3);

            switch(seletor){
                case 1:{
                    cout << "Informe o novo nome: \n";
                    cin.ignore();
                    getline(cin,sub);
                    Alterar("CLIENTE", "NOME", id, sub);
                    break;
                }
                case 2:{
                    cout << "Informe o novo cpf: \n";
                    cin.ignore();
                    getline(cin,sub);
                    Alterar("CLIENTE", "CPF", id, sub);
                    break;
                }
                case 3:{
                    cout << "Informe o novo contato: \n";
                    cin.ignore();
                    getline(cin,sub);
                    Alterar("CLIENTE", "CONTATO", id, sub);
                    break;
                }

            }
        }

        else if(operador == 2){

            cout << "Informe o ID do cliente que sera deletado: \n";
            cin >> id;
            Deletar("CLIENTE", id);
        }
    }

    else if(tabela == "FORNECEDOR"){

        if(operador == 1){

            do{

                cout << "Informe o ID do fornecedor que sera alterado: \n";
                cin >> id;
                cout << "Selecione qual campo do fornecedor deseja alterar\n";
                cout << "\t1-Para nome\n\t2-Para cnpj\n\t3-Para contato\n: ";
                cin >> seletor;

                if (seletor < 1 || seletor > 3){

                    cout << "\nInforme uma operacao valida!\n\n";
                    system("read -p \"Pressione enter para continuar\" saindo");
                    system("clear");
                }

            }while(seletor < 1 ||seletor > 3);

            switch(seletor){

                case 1:{
                    cout << "Informe o novo nome: \n";
                    cin.ignore();
                    getline(cin,sub);
                    Alterar("FORNECEDOR", "NOME", id, sub);
                    break;
                }
                case 2:{
                    cout << "Informe o novo cnpj: \n";
                    cin.ignore();
                    getline(cin,sub);
                    Alterar("FORNECEDOR", "CNPJ", id, sub);
                    break;
                }
                case 3:{
                    cout << "Informe o novo contato: \n";
                    cin.ignore();
                    getline(cin,sub);
                    Alterar("FORNECEDOR", "CONTATO", id, sub);
                    break;
                }

            }
        }

        else if(operador == 2){

            cout << "Informe o ID do fornecedor que sera deletado: \n";
            cin >> id;
            Deletar("FORNECEDOR", id);
        }
    }

}
// A função é utilizar para organizar a navegação no sistema
void menu(){

    int operador;

    do{



        cout << "________________ MENU DO SISTEMA ________________" << endl << endl;
        cout << "  PRODUTO:" << endl << endl;
        cout << " \t1 -  Cadastrar novos produtos" << endl;
        cout << " \t2 -  Lista de produtos cadastrados"  << endl;
        cout << " \t3 -  Buscar produto cadastrado" << endl << endl;
        cout << "  CLIENTE:" << endl << endl;
        cout << " \t4 -  Cadastrar novos clientes" << endl;
        cout << " \t5 -  Lista de clientes cadastrados" << endl;
        cout << " \t6 -  Buscar cliente cadastrado" << endl << endl;
        cout << "  FORNECEDOR:" << endl << endl;
        cout << " \t7 -  Cadastrar novos fornecedores" << endl;
        cout << " \t8 -  Lista de fornecedores cadastrados" << endl;
        cout << " \t9 -  Buscar fornecedor cadastrado" << endl << endl;
        cout << "  SAIR:" << endl << endl;
        cout << " \t0 -  Sair do sistema" << endl << endl;
        cout << "_________________________________________________" << endl << endl;
        cout << "Informe o numero da operacao desejada: ";
        cin >> operador;


        switch(operador){
            case 1:
                CadastrarProduto();
                break;
            case 2:{
                Buscar("PRODUTO","*");
                Manipular("PRODUTO");
                break;
            }
            case 3:{

                int seletor;

                do{

                    cout << "_________________________________________________" << endl << endl;
                    cout << "Selecione por qual campo de produto deseja realizar uma busca\n";
                    cout << "\t1-Para nome\n\t2-Para cor\n\t3-Para marca\n\t4-Para codigo\n\t5-Para setor\n\t6-Para valor\n\t7-Para quantidade\n: ";
                    cin >> seletor;

                    if (seletor < 1 || seletor > 7){

                        cout << "\nInforme uma operacao valida!\n\n";
                        system("read -p \"Pressione enter para continuar\" saindo");
                        system("clear");
                    }

                }while(seletor < 1 ||seletor > 7);

                string chave;

                switch(seletor){

                    case 1:{

                        cout << "Informe por qual nome deseja buscar: \n";
                        cin >> chave;
                        BuscarChave("FORNECEDOR","NOME", chave);
                        break;
                    }
                    case 2:{

                        cout << "Informe por qual cor deseja buscar: \n";
                        cin >> chave;
                        BuscarChave("FORNECEDOR","COR", chave);
                        break;
                    }
                    case 3:{

                        cout << "Informe por qual marca deseja buscar: \n";
                        cin >> chave;
                        BuscarChave("FORNECEDOR","MARCA", chave);
                        break;
                    }
                    case 4:{

                        cout << "Informe por qual codigo deseja buscar: \n";
                        cin >> chave;
                        BuscarChave("FORNECEDOR","CODIGO", chave);
                        break;
                    }
                    case 5:{

                        cout << "Informe por qual setor deseja buscar: \n";
                        cin >> chave;
                        BuscarChave("FORNECEDOR","SETOR", chave);
                        break;
                    }
                    case 6:{

                        cout << "Informe por qual valor deseja buscar: \n";
                        cin >> chave;
                        BuscarChave("FORNECEDOR","VALOR", chave);
                        break;
                    }
                    case 7:{

                        cout << "Informe por qual quantidade deseja buscar: \n";
                        cin >> chave;
                        BuscarChave("FORNECEDOR","QUANTIDADE", chave);
                        break;
                    }

                }
                Manipular("PRODUTO");
                break;
            }
            case 4:
                CadastrarCliente();
                break;
            case 5:{
                Buscar("CLIENTE","*");
                Manipular("CLIENTE");
                break;
            }
            case 6:{

                int seletor;

                do{

                    cout << "_________________________________________________" << endl << endl;
                    cout << "Selecione por qual campo de cliente deseja realizar uma busca\n";
                    cout << "\t1-Para nome\n\t2-Para cpf\n\t3-Para contato\n: ";
                    cin >> seletor;

                    if (seletor < 1 || seletor > 3){

                        cout << "\nInforme uma operacao valida!\n\n";
                        system("read -p \"Pressione enter para continuar\" saindo");
                        system("clear");
                    }

                }while(seletor < 1 ||seletor > 3);

                string chave;

                switch(seletor){

                    case 1:{

                        cout << "Informe por qual nome deseja buscar: \n";
                        cin >> chave;
                        BuscarChave("CLIENTE","NOME", chave);
                        break;
                    }
                    case 2:{

                        cout << "Informe por qual cpf deseja buscar: \n";
                        cin >> chave;
                        BuscarChave("CLIENTE","CPF", chave);
                        break;
                    }
                    case 3:{

                        cout << "Informe por qual contato deseja buscar: \n";
                        cin >> chave;
                        BuscarChave("CLIENTE","CONTATO", chave);
                        break;
                    }

                }
                Manipular("CLIENTE");
                break;
            }
            case 7:
                CadastrarFornecedor();
                break;
            case 8:{
                Buscar("FORNECEDOR","*");
                Manipular("FORNECEDOR");
                break;
            }
            case 9:{

                int seletor;

                do{

                    cout << "_________________________________________________" << endl << endl;
                    cout << "\nSelecione por qual campo de fornecedor deseja realizar uma busca\n";
                    cout << "\t1-Para nome\n\t2-Para cnpj\n\t3-Para contato\n: ";
                    cin >> seletor;

                    if (seletor < 1 || seletor > 3){

                        cout << "\nInforme uma operacao valida!\n\n";
                        system("read -p \"Pressione enter para continuar\" saindo");
                        system("clear");
                    }

                }while(seletor < 1 ||seletor > 3);

                string chave;

                switch(seletor){

                    case 1:{

                        cout << "Informe por qual nome deseja buscar: \n";
                        cin >> chave;
                        BuscarChave("FORNECEDOR","NOME", chave);
                        break;
                    }
                    case 2:{

                        cout << "Informe por qual cnpj deseja buscar: \n";
                        cin >> chave;
                        BuscarChave("FORNECEDOR","CNPJ", chave);
                        break;
                    }
                    case 3:{

                        cout << "Informe por qual contato deseja buscar: \n";
                        cin >> chave;
                        BuscarChave("FORNECEDOR","CONTATO", chave);
                        break;
                    }

                }
                Manipular("FORNECEDOR");
                break;
            }




        }

        if(operador < 0 || operador > 9){

            cout << "\nInforme uma operacao valida!\n\n";
            system("read -p \"Pressione enter para continuar\" saindo");
            system("clear");

        }

    }while(operador != 0);


}
//Função princípal
int main(int argc, char* argv[]){
    // Abrindo o banco de dados
    connect("cadastros.db");
    //
    CriarTabelas();

    menu();
    //Fechando banco de dados
    sqlite3_close(db);
   return 0;
}
