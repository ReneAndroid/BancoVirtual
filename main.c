#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<unistd.h>

/*ESTRUTURAS*/

typedef struct
{
    int numero;
    int agencia;
    char senha[7];
    long double saldo;
}Conta;

typedef struct
{
    char nome[50];
    char cpf[11];
    int acessos;
    int estado;
    Conta conta;
}Cliente;

typedef struct
{
    char nome[50];
    char cpf[11];
    int conta;
    char senha[7];
}Funcionario;

typedef struct
{
    int origem;
    int destino;
    long double valor;
    int tipo;
}Transacoes;


  void pesquisar(){
  	
  	FILE *arquivo;
  	Cliente ctt;
  	char nome [50];
  	arquivo=fopen("Clientes.txt","rb");
  	
  	if(arquivo==NULL){
  		printf("problemas ao abrir");
  		
  		 }else{
  			fflush(stdin);
  			printf("digite o nome que você quer pesquisar\n");
  			gets(nome);
  			
  			while(fread(&ctt,sizeof(Cliente),1,arquivo)==1){
  			if(strcmp(nome,ctt.nome)==0){
  			printf("nome %s\n",ctt.nome);
  			printf("nome %s\n ",ctt.cpf);
 			printf("-------------------------------------------------------------------------------------\n\n");
		 }
  					
				  }
			  }
		 
	  }
  
  



/**Ps.: A contagem do FOR vai até "j<100", por estar predefinido um vetor com 100 espaços para conta (sem alocação dinâmica implementada).


FUNÇÃO DE VALIDAÇÃO (LÊ AGÊNCIA, CONTA, SENHA E COMPARA. RETORNA 1 SE A VALIDAÇÃO FOR CONFIRMADA.)**/

char* pegarSenha(){
    char *senha = (char*) malloc(7*sizeof(char));
    char t;
    int i;
    for(i = 0; i < 6;i++){
        t = getch();
        if(t == '\b'){
            i = -1;
            printf("\nSenha: ");
        }else{
            senha[i] = t;
            putchar('*');
        }
    }
    senha[6] = '\0';
    return senha;

}
int validar(Cliente clientes[], int* origem, int num_clientes)
{
    int j;
    int aux_agencia, aux_conta;

    /**CAPTURA DE DADOS (AGÊNCIA, CONTA, SENHA)**/
    fflush(stdin);

    printf("\nDigite o número da agência: ");
    scanf("%i", &aux_agencia);

    fflush(stdin);
    printf("Digite o número da conta: ");
    scanf ("%i", &aux_conta);

    fflush(stdin);

    printf("Digite sua senha: ");
    int i;
    char *senha1 = pegarSenha();
    fflush(stdin);


    /**FUNÇÃO QUE COMPARA O Nº DE AGÊNCIA, CONTA E SENHA DIGITADOS**/
    for(j=0; j<=num_clientes+1; j++)
        {
            if(clientes[j].conta.agencia == aux_agencia && clientes[j].conta.numero == aux_conta)
            {


                if (strcmp(clientes[j].conta.senha, senha1) == 0)
                {
                    if(clientes[j].estado == 1)
                    {

                    printf("VALIDAÇÃO BEM SUCEDIDA!\n");
                    *origem = j;
                    return 3;
                    }
                    else
                    {

                        printf("\nESTA CONTA ESTÁ DESATIVADA.\n");
                    }
                }
                else
                {

                    printf("\n*****SENHA INCORRETA!*****\n");
                }

            }
            else if (j==num_clientes+1)
                {

                    printf("\nAGÊNCIA OU CONTA INVÁLIDA!\n");
                    break;
                }

        }

}




/**FUNÇÃO DE VALIDAÇÃO DA CONTA DESTINO EM UMA TRANSFERÊNCIA (LÊ AGÊNCIA E CONTA E COMPARA. RETORNA 1 SE A VALIDAÇÃO FOR CONFIRMADA.)**/

int validar_destino(Cliente clientes[], int* destino, int num_clientes)
{

    int j;
    int aux_agencia2, aux_conta2;

    fflush(stdin);

        printf("\nDigite o número da agência de destino: ");
        scanf("%d", &aux_agencia2);

        fflush(stdin);

        printf("Digite o número da conta de destino: ");
        scanf ("%d",&aux_conta2);


        for(j=0; j<=num_clientes+1; j++)
            {
                if(clientes[j].conta.agencia == aux_agencia2 && clientes[j].conta.numero == aux_conta2)
                {
                    if(clientes[j].estado == 1)
                    {
                        *destino = j;
                        return 1;
                    }
                    else
                    {

                        printf("ESTA CONTA ESTÁ DESATIVADA!");
                        return 0;
                    }

                }else if (j==num_clientes+1)
                    {

                        printf("\nAGÊNCIA OU CONTA INVÁLIDA!");
                        return 0;
                    }

            }

}

/**FUNÇÃO SALDO:**/

void saldo(Cliente clientes[], int *origem)
{
    printf("Saldo disponível: R$%.2Lf \n", clientes[*origem].conta.saldo);

}


/*FUNÇÃO SAQUE:*/

float saque(Cliente clientes[], int *origem)
{
    float valor;

    printf("Saldo disponível: R$%.2Lf \n",clientes[*origem].conta.saldo);
    printf("Valor do saque: ");
    fflush(stdin);
    scanf("%f", &valor);
    if(valor <= clientes[*origem].conta.saldo && valor >= 0)
    {
        clientes[*origem].conta.saldo = clientes[*origem].conta.saldo - valor;
        printf("\nSaque realizado com sucesso! Retire o dinheiro no local indicado.\n");
    }
    else if(valor <= 0)
    {
        printf("Não é possível sacar valor nulo ou negativo\n");
    }
    else
    {
        printf("\a\nSeu saldo é insuficiente para realizar esse saque!\n");
    }


    printf("Novo saldo: R$%.2Lf \n", clientes[*origem].conta.saldo);

    return valor;

}


/*FUNÇÃO DEPÓSITO:*/

float deposito(Cliente clientes[], int *origem)
{
    float valor;


    printf("Valor do depósito: ");
    fflush(stdin);
    scanf("%f", &valor);
    if(valor >=0)
    {
        clientes[*origem].conta.saldo = clientes[*origem].conta.saldo + valor;


        printf("Depósito realizado com sucesso!\n");


        printf("Novo saldo: R$%.2Lf \n", clientes[*origem].conta.saldo);



        return valor;
    }
    else
    {

        printf("Você não pode depositar um valor negativo.\n");
        return 0;
    }

    return valor;
}




/*FUNÇÃO TRANSFERÊNCIA:*/

float transferencia(Cliente clientes[], int* origem, int* destino, int num_clientes)
{
    float valor;
    int continuar;

       printf("Saldo disponível: R$%.2f \n", clientes[*origem].conta.saldo);

    printf("Conta destino: %i\nCliente: %s\n\n", clientes[*destino].conta.numero, clientes[*destino].nome);


    printf("Pressione 1 para confirmar ou 2 para cancelar operação.\n");
    scanf("%i", &continuar);

    if(continuar == 1)
    {

       printf("Valor a ser transferido: ");
       fflush(stdin);
       scanf("%f", &valor);

       if(valor <= clientes[*origem].conta.saldo && valor >= 0)
        {

            clientes[*destino].conta.saldo = clientes[*destino].conta.saldo + valor;
            clientes[*origem].conta.saldo = clientes[*origem].conta.saldo - valor;

            printf("Tranferência realizada com sucesso!\n");
            printf("Novo saldo: R$%.2f \n", clientes[*origem].conta.saldo);

            return valor;

        }
        else if(valor < 0)
        {

            printf("\nVocê não pode transferir um valor negativo.\n");
            return 0;
        }
        else
        {

            printf("\nSaldo insuficiente!\n");
            return 0;
        }
    }
    else
    {

        printf("Operação cancelada com sucesso.\n");
    }


}


void alterar_senha(Cliente* cliente, int* origem, int num_clientes)
{
    char senha1[6];
    int j, i;

    printf("Informe sua senha atual: ");
    for (i=0;i<6;i++)
    {
        senha1[i] = getch();
        putchar('*');
    }

    if (strcmp(cliente[*origem].conta.senha, senha1) == 0)
    {

        printf("\n\nInforme a nova senha: ");
        int i;
        fflush(stdin);
        for (i=0;i<6;i++)
        {
            cliente[*origem].conta.senha[i] = getch();
            putchar('*');
        }

        printf("\nSenha alterada com sucesso!\n");
    }
    else
    {

        printf("\n*****SENHA INCORRETA!*****\n");
    }
}

void endereco()
{
  printf("1 - Av Domingos Ferreira numero 665, Recife PE\n");
  printf("2 - Rua da hora numero 14, Recife PE\n");
  printf("3 - Av Getulio Vargas numero 80, Olinda PE\n");
  printf("4 - Av Agamenon Magalhães numero 176, Recife PE\n");
}


void cadastrar_funcionario(Funcionario funcionario[], int num_funcionarios)
{
    printf("%d\n", num_funcionarios);
    int agencia_aux;
    char cpf_aux[11];
    fflush(stdin);

    printf("Nome: ");
    gets(funcionario[num_funcionarios].nome);
    fflush(stdin);

    printf("CPF: ");
    gets(funcionario[num_funcionarios].cpf);
    fflush(stdin);


    printf("Senha: ");
    fflush(stdin);
    strcpy(funcionario[num_funcionarios].senha, pegarSenha());
    funcionario[num_funcionarios].conta = num_funcionarios;

    printf("\n");
    fflush(stdin);

}

void cadastrar_cliente(Cliente* cliente, int num_clientes)
{
        int agencia_aux;
        char cpf_aux[11];
        fflush(stdin);

        printf("Nome: ");
        gets(cliente[num_clientes].nome);
        fflush(stdin);

        printf("CPF: ");
        gets(cliente[num_clientes].cpf);


        fflush(stdin);
        cliente[num_clientes].conta.numero = num_clientes;

        printf("Selecione uma agência: \n");
        endereco();
        do
        {
            scanf("%i", &agencia_aux);
            if(agencia_aux != 1 && agencia_aux != 2 &&agencia_aux != 3 && agencia_aux != 4)
            {

                printf("Digite uma agência válida.\n");
            }
        }while(agencia_aux != 1 && agencia_aux != 2 &&agencia_aux != 3 && agencia_aux != 4);

        cliente[num_clientes].conta.agencia = agencia_aux;
        fflush(stdin);
        int i;
        printf("Senha: ");
        fflush(stdin);
        strcpy(cliente[num_clientes].conta.senha, pegarSenha());
        printf("\n");
        fflush(stdin);

        printf("O numero de sua conta é: %i\n\n", num_clientes);
        cliente[num_clientes].conta.saldo = 0;
        cliente[num_clientes].acessos = 0;
        cliente[num_clientes].estado = 1;

}



void logo()
{
    printf("----------------------------------------\n");
    printf("                        Bem vindo ao BCC\n");
    printf("----------------------------------------\n");
}
void ambiente_funcao()
{
    system("cls");
    logo();
    printf("\n");
}
 /*FUÇAO QUE USA UM VETOR DE Transacoes PARA NUMERAR E IMPRIMIR OS EXTRATOS (ler pra entender bem)*/
void extrato(Cliente cliente[], Transacoes transacoes[], int* origem, int num_transacoes)
{
    int i;


    printf("Extrato de %s:\n\n", cliente[*origem].nome);

    for(i=0; i<=num_transacoes; i++)
    {
        if(cliente[*origem].conta.numero == transacoes[i].origem || cliente[*origem].conta.numero == transacoes[i].destino)
        {

            if(transacoes[i].tipo == 1)
            {
                printf("%s ---> %s\n", cliente[transacoes[i].origem].nome, cliente[transacoes[i].destino].nome);
                printf("Valor: (+) %.2Lf\t(Depósito)\n\n", transacoes[i].valor);

            }
            else if(transacoes[i].tipo == 2)
            {
                printf("%s ---> %s\n", cliente[transacoes[i].origem].nome, cliente[transacoes[i].destino].nome);
                printf("Valor: (-) %.2Lf\t(Saque)\n\n", transacoes[i].valor);
            }
            else if(transacoes[i].tipo == 3)
            {
                if(cliente[*origem].conta.numero == transacoes[i].origem)
                {
                    printf("%s ---> %s\n", cliente[transacoes[i].origem].nome, cliente[transacoes[i].destino].nome);
                    printf("Valor: (-) %.2Lf\t(Transferência)\n\n", transacoes[i].valor);
                }
                else if(cliente[*origem].conta.numero == transacoes[i].destino)
                {
                    printf("%s ---> %s\n", cliente[transacoes[i].origem].nome, cliente[transacoes[i].destino].nome);
                    printf("Valor: (+) %.2Lf\t(Transferência)\n\n", transacoes[i].valor);
                }
            }
            else if(transacoes[i].tipo == 4)
            {
                if(cliente[*origem].conta.numero == transacoes[i].origem)
                {
                printf("%s <--- Banco\n", cliente[transacoes[i].origem].nome);
                printf("Valor: (+) %.2Lf\t(Empréstimo)\n\n", transacoes[i].valor);
                }
            }
        }
    }
}

void recuperar_conta(Cliente cliente[], int num_clientes)
{

    printf("Informe o CPF do cliente: ");
    char cpf_aux[11];
    fflush(stdin);
    gets(cpf_aux);

    int i;
    int opcao=0;
    char senha[6];
    int j;

    for(i=0;i<=num_clientes+1;i++)
    {
        if(strcmp(cliente[i].cpf, cpf_aux) == 0)
        {
            printf("\nNome: %s\nConta: %i\nAgência: %i\nCPF: %s\n\n", cliente[i].nome, cliente[i].conta.numero, cliente[i].conta.agencia, cliente[i].cpf);

            while(opcao != 1 || opcao != 2)
            {

                printf("Deseja cadastrar nova senha?\n1 - sim\n2 - não\n");
                scanf("%i", &opcao);
                if(opcao == 1)
                {

                    printf("Informe a nova senha: ");
                    fflush(stdin);
                    for (j=0;j<6;j++)
                    {
                        cliente[i].conta.senha[j] = getch();
                        putchar('*');
                    }

                    printf("\nSenha alterada com sucesso!\n\n");
                    break;
                }
                else if(opcao == 2)
                {

                    printf("Operação finalizada.\n");
                    break;
                }
                else
                {

                    printf("Opção inválida.\n");
                }
            }
        }
    }
    /* caso nao encontre nenhum cpf igual ao aux no vetor, opcao continuara sendo = 0*/
    if(opcao == 0)
    {

        printf("Cliente não encontrado.\n");
    }
}

void status_conta(Cliente cliente[], int num_clientes)
{

    printf("Informe o CPF do cliente: ");
    char cpf_aux[11];
    fflush(stdin);
    gets(cpf_aux);

    int i;
    int opcao=0;
    char senha[6];
    int j;

    for(i=0;i<=num_clientes+1;i++)
    {
        if(strcmp(cliente[i].cpf, cpf_aux) == 0)
        {
            printf("\nNome: %s\nConta: %i\nAgência: %i\n", cliente[i].nome, cliente[i].conta.numero, cliente[i].conta.agencia);
            if(cliente[i].estado == 0)
            {

                printf("Status: Desativada\n\n");

                while(opcao != 1 || opcao != 2)
                {

                    printf("Ativar conta?\n1 - sim\n2 - não\n");
                    scanf("%i", &opcao);
                    if(opcao == 1)
                    {
                        cliente[i].estado = 1;

                        printf("\nConta Ativada!\n\n");
                        break;
                    }
                    else if(opcao == 2)
                    {

                        printf("Operação finalizada.\n");
                        break;
                    }
                    else
                    {

                        printf("Opção inválida.\n");
                    }
                }
            }
            else if(cliente[i].estado == 1)
            {
                printf("Status: Ativada\n\n");

                while(opcao != 1 || opcao != 2)
                {

                    printf("Desativar conta?\n1 - sim\n2 - não\n");
                    scanf("%i", &opcao);
                    if(opcao == 1)
                    {
                        cliente[i].estado = 0;

                        printf("\nConta Desativada!\n\n");
                        break;
                    }
                    else if(opcao == 2)
                    {

                        printf("Operação finalizada.\n");
                        break;
                    }
                    else
                    {

                        printf("Opção inválida.\n");
                    }
                }
            }

        }
    }
    if(opcao == 0)
    {

        printf("Cliente não encontrado.\n");
    }
}

float emprestimo(Cliente clientes[], int *origem)
{
  float salario, emprestimo;
  int parcelas;
  float valor_mes;

      do
      {

          printf("Digite seu salario: ");
        scanf("%f", &salario);
        if(salario<0)
        {

            printf("Salário não pode ser menor que 0\n");
        }
    }while(salario<0);


      do
      {
          ;
        printf("Digite o valor do emprestimo: ");
        scanf("%f", &emprestimo);
        if(emprestimo<0)
        {

            printf("Emprestimo não pode ser menor que 0\n");
        }
    }while(emprestimo<0);

    do
      {

        printf("Digite o número de parcelas: ");
        scanf("%i", &parcelas);
          valor_mes = emprestimo/parcelas;
          if(parcelas<0)
        {

            printf("Parcelas não pode ser menor que 0\n");
        }
      }while(parcelas<0);

    if (0.3*salario>=valor_mes)
    {
        clientes[*origem].conta.saldo += emprestimo;

        printf("\nEmprestimo concedido. Seu saldo atual é de R$ %.2f\n", clientes[*origem].conta.saldo);
        return emprestimo;
      }
      else
    {

        printf("\nEmprestimo negado\n");
        return 0;
      }
}

void calculadora()
{

    float juros,meses,capital_inicial,montante;


    printf("Digite em quantos meses a divida devera ser paga: ");
    scanf("%f", &meses);

    printf("Digite a taxa de juros mensais: ");
    scanf("%f", &juros);

    printf("Digite o capital inicial: ");
    scanf("%f",&capital_inicial);
    montante = 1.0 + (juros/100.0);
    montante = pow(montante,meses);
    montante =  capital_inicial*montante;

    printf("O montante total a ser pago é R$%2.f a juros compostos\n",montante);
}

/*///////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////*/

int validar_funcionario(Funcionario funcionario[], int num_funcionarios)
{
    char cpf_aux[11];

    printf("Digite o CPF: ");
    fflush(stdin);
    gets(cpf_aux);


    fflush(stdin);

    printf("Digite sua senha: ");

    int j;
    char *senha1 = pegarSenha();

    int i;

    for(i=0;i<=num_funcionarios+1;i++)
    {
        if(strcmp(funcionario[i].cpf, cpf_aux) == 0 && strcmp(funcionario[i].senha, senha1) == 0)
        {

            printf("Bem vindo(a), ");
            puts(funcionario[i].nome);

            return 1;



        }
        else
        {
            printf("CPF ou senha inválidos!");
            system("pause");
            return 0;
        }

    }
}



void main()
{
	system("color 1F");
	setlocale(LC_ALL, "portuguese");

	int senha_gerente = 123456;

	int opcao=9;
	int audio=1;

	/*Arquivo num_clientes*/
	int num_clientes;

	FILE *arq;
	arq = fopen("num_clientes.txt", "r");
	if(arq == NULL)
	{
		printf("Falha em abrir Arquivo num_clientes.txt.\n");
	}
	else
	{
		fread(&num_clientes, sizeof(int), 1, arq);
		fclose(arq);
	}

	/*Arquivo cliente*/
	Cliente* cliente = (Cliente*)malloc((num_clientes+2)*sizeof(Cliente));

	arq = fopen("clientes.txt", "r");
	if(arq == NULL)
	{
		printf("Falha em abrir Arquivo cliente.txt.\n");
	}
	else
	{
		fread(cliente, sizeof(Cliente), num_clientes+2, arq);
		fclose(arq);
	}

	/*arquivo num_funcionarios*/
	int num_funcionarios;

	arq = fopen("num_funcionarios.txt", "r");
	if(arq == NULL)
	{
		printf("Falha em abrir Arquivo num_funcionarios.txt.\n");
	}
	else
	{
		fread(&num_funcionarios, sizeof(int), 1, arq);
		fclose(arq);
	}

	/*arquivo funcionarios*/
	Funcionario* funcionario = (Funcionario*)malloc((num_funcionarios+2)*sizeof(Funcionario));

	arq = fopen("funcionarios.txt", "r");
	if(arq == NULL)
	{
		printf("Falha em abrir Arquivo funcionarios.txt.\n");
	}
	else
	{
		fread(funcionario, sizeof(Funcionario), num_funcionarios+2, arq);
		fclose(arq);
	}


	/*Arquivo Numero de transacoes*/
	int num_transacoes;

	arq = fopen("num_transacoes.txt", "r");
	if(arq == NULL)
	{
		printf("Falha em abrir Arquivo num_transacoes.txt.\n");
	}
	else
	{
		fread(&num_transacoes, sizeof(int), 1, arq);
		fclose(arq);
	}

	/*Arquivo transacoes*/
	Transacoes* transacoes = (Transacoes*)malloc((num_transacoes+2)*sizeof(Transacoes));

	arq = fopen("transacoes.txt", "r");
	if(arq == NULL)
	{
		printf("Falha em abrir Arquivo transacoes.txt.\n");
	}
	else
	{
		fread(transacoes, sizeof(Transacoes), num_transacoes+2, arq);
		fclose(arq);
	}


	int confirmar_cadastro;



	while(opcao != 0)
	{
		system("cls");
		logo();

		printf("\nO que deseja?\n\n1 - Acesso Cliente\n2 - Acesso funcionário\n3 - cadastro funcionario\n4 - pesquisar por nome \n0 - Sair");
		scanf("%i", &opcao);

		/*menu inicial*/

		switch(opcao)
		{
				case 4:
					{
					
					 pesquisar();
				}
			case 1:
				{

					system("cls");


					int validacao = 0;
					int origem;
					int destino;
					float valor;

					/*sistema de login*/
					while(validacao != 1 && validacao != 3)
					{
						logo();
						printf("\nTela de acesso\n");
						validacao = validar(cliente, &origem, num_clientes);
						if(validacao != 3)
						{
							printf("\nDigite 1 para sair ou 2 para tentar novamente.\n");
							scanf("%i", &validacao);
							system("cls");
						}
						if(validacao == 3)
						{
							system("pause");
						}

					}
					/*Menu pós login*/
					if(validacao == 3)
					{
						while(opcao != 9)
						{

							system("cls");
							logo();

							printf("\nBem vindo(a), %s!\n\n1 - Consultar saldo\n2 - Depósito\n3 - Saque\n4 - Transferência\n5 - Extrato\n6 - Empréstimo\n7 - Calculadora de juros\n8 - Alterar senha\n9 - Sair\n", cliente[origem].nome);
							scanf("%i", &opcao);
							switch(opcao)
							{
								/*consultar saldo*/
								case 1:
									{
										ambiente_funcao();
										saldo(cliente, &origem);

										system("pause");
										system("cls");
										break;
									}
								/*Ralizar depósito*/
								case 2:
									{
										ambiente_funcao();
										valor = deposito(cliente, &origem);
										if(valor > 0)
										{
											num_transacoes++;
											transacoes = (Transacoes*)realloc(transacoes, (num_transacoes+2)*sizeof(Transacoes));
											transacoes[num_transacoes].origem = origem;
											transacoes[num_transacoes].destino = origem;
											transacoes[num_transacoes].valor = valor;
											transacoes[num_transacoes].tipo = 1;
										}


										system("pause");
										system("cls");
										break;
									}
								/*Realizar saque*/
								case 3:
									{
										ambiente_funcao();

										valor = saque(cliente, &origem);
										if(valor > 0)
										{
											num_transacoes++;
											transacoes = (Transacoes*)realloc(transacoes, (num_transacoes+2)*sizeof(Transacoes));
											transacoes[num_transacoes].origem = origem;
											transacoes[num_transacoes].destino = origem;
											transacoes[num_transacoes].valor = valor;
											transacoes[num_transacoes].tipo = 2;
										}
										system("pause");
										system("cls");
										break;
									}
								case 4:
									{
										ambiente_funcao();
										validacao = validar_destino(cliente, &destino, num_clientes);
										if(validacao == 1)
										{
											valor = transferencia(cliente, &origem, &destino, num_clientes);
											if(valor > 0)
											{
												num_transacoes++;
												transacoes = (Transacoes*)realloc(transacoes, (num_transacoes+2)*sizeof(Transacoes));
												transacoes[num_transacoes].origem = origem;
												transacoes[num_transacoes].destino = destino;
												transacoes[num_transacoes].valor = valor;
												transacoes[num_transacoes].tipo = 3;
											}
										}

										system("pause");
										system("cls");
										break;
									}
								case 5:
									{
										ambiente_funcao();
										extrato(cliente, transacoes, &origem, num_transacoes);
										saldo(cliente, &origem);
										system("pause");
										system("cls");
										break;
									}
								case 6:
									{
										ambiente_funcao();
										valor = emprestimo(cliente, &origem);
										if(valor > 0)
										{
											num_transacoes++;
											transacoes = (Transacoes*)realloc(transacoes, (num_transacoes+2)*sizeof(Transacoes));

											transacoes[num_transacoes].origem = origem;
											transacoes[num_transacoes].destino = destino;
											transacoes[num_transacoes].valor = valor;

											transacoes[num_transacoes].tipo = 4;
										}

										system("pause");
										system("cls");
										break;
									}
								case 7:
									{
										ambiente_funcao();
										calculadora();
										system("pause");
										system("cls");
										break;
									}
								case 8:
									{
										ambiente_funcao();
										alterar_senha(cliente, &origem, num_clientes);
										system("pause");
										system("cls");
										break;
									}
								case 9:
									{
										system("cls");
										break;
									}

							}
						}
					}
					break;
				}
				
			
			case 2:
				{
					/*Colocar sistema de Login*/
					int aux;
					system("cls");
					logo();
					aux = validar_funcionario(funcionario, num_funcionarios);
					printf("aux = %i\n", aux);
					if(aux == 1)
					{
						opcao = 0;
						while(opcao != 5)
						{		/*menu acesso funcionário*/
							logo();
							system("cls");

							printf("\nAcesso Funcionário\n\n1 - Cadastrar cliente\n2 - Recuperar conta\n3 - Ativar/Desativar cliente\n4 - Cadastrar funcionário\n5 - Sair\n");
							scanf("%i", &opcao);
							switch(opcao)
							{
								
									
								case 1:
									{
										ambiente_funcao();
										num_clientes++;
										cliente = (Cliente*)realloc(cliente, (num_clientes+2)*sizeof(Cliente));
										cadastrar_cliente(cliente, num_clientes);
										system("pause");
										system("cls");
										break;
									}
								case 2:
									{
										ambiente_funcao();
										recuperar_conta(cliente, num_clientes);
										system("pause");
										system("cls");
										break;
									}
								case 3:
									{
										ambiente_funcao();
										status_conta(cliente, num_clientes);
										system("pause");
										system("cls");
										break;
									}
								case 4:
									{
										ambiente_funcao();
										num_funcionarios++;
										funcionario = (Funcionario*)realloc(funcionario, (num_funcionarios+2)*sizeof(Funcionario));
										cadastrar_funcionario(funcionario, num_funcionarios);
										system("pause");
										system("cls");
										break;
									}
						}
					}
						break;
						system("cls");

					}
					break;

				}
			case 3:
				{
					ambiente_funcao();
										num_funcionarios++;
										funcionario = (Funcionario*)realloc(funcionario, (num_funcionarios+2)*sizeof(Funcionario));
										cadastrar_funcionario(funcionario, num_funcionarios);
										system("pause");
										system("cls");
										break;
				}
		}
	}



	printf("Preparando para salvar arquivos...\n");

	arq = fopen("num_clientes.txt", "w");
	if (arq == NULL)
	{
		printf("Falha em salvar Arquivo num_clientes.txt!");
		fclose(arq);
	}
	else
	{
		fwrite(&num_clientes, sizeof(int), 1, arq);
        fclose(arq);

		printf("Numero de clientes atualizado: %i.\n", num_clientes+1);
	}

	arq = fopen("clientes.txt", "w");
	if(arq == NULL)
	{
		printf("Falha em salvar Arquivo clientes.txt!\n");
		fclose(arq);
	}
	else
	{
		fwrite(cliente, sizeof(Cliente), num_clientes+2, arq);
		fclose(arq);

		printf("Lista de clientes salva!\n");
	}


	arq = fopen("num_transacoes.txt", "w");
	if (arq == NULL)
	{
		printf("Falha em salvar Arquivo num_transacoes.txt!");
		fclose(arq);
	}
	else
	{
		fwrite(&num_transacoes, sizeof(int), 1, arq);
        fclose(arq);

		printf("Numero de transacoes atualizado: %i.\n", num_transacoes+1);
	}

	arq = fopen("transacoes.txt", "w");
	if(arq == NULL)
	{
		printf("Falha em salvar Arquivo transacoes.txt!\n");
		fclose(arq);
	}
	else
	{
		fwrite(transacoes, sizeof(Transacoes), num_transacoes+2, arq);
		fclose(arq);

		printf("Transacoes realizadas salvas!\n");
	}

	arq = fopen("funcionarios.txt", "w");
	if(arq == NULL)
	{
		printf("Falha em salvar Arquivo funcionarios.txt!\n");
		fclose(arq);
	}
	else
	{
		fwrite(funcionario, sizeof(Funcionario), num_funcionarios+2, arq);
		fclose(arq);

		printf("Lista de funcionarios salva!\n");
	}

	arq = fopen("num_funcionarios.txt", "w");
	if (arq == NULL)
	{
		printf("Falha em salvar Arquivo num_funcionarios.txt!");
		fclose(arq);
	}
	else
	{
		fwrite(&num_funcionarios, sizeof(int), 1, arq);
        fclose(arq);

		printf("Numero de funcionarios atualizado: %i.\n", num_funcionarios+1);
	}

	system("pause");
	return 0;
}
