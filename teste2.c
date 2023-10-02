#include <stdio.h>
#include <math.h>
#include <string.h>  // Para strtok
#include <stdlib.h>  // Para atoi
/*
    D é o inverso de E modulo (p-1) * (q-1)
*/
// algaritmo extendido de euclides
int euclides(int e, int b, int *x, int *y){
    if (b == 0){
        *x = 1;
        *y = 0;
        return e;
    }
    else {
        int x1, y1;
        int mdc = euclides(b, e % b, &x1, &y1);
        *x = y1;
        *y = x1 - (e /b) * y1;
        return mdc;
    }

}
//codigo para o inverso multiplicativo
int moduloinverso(int e,  int m){
    int x, y;
    int mdc = euclides(e, m, &x, &y);
    if (mdc != 1){
        printf("Inverso multiplicativo não existe. \n");
        return -1;
    }

    return (x % m + m) % m;
}

//checagem se p e q são primos
int ehprimo(int numero){
    for (int contador = 2; contador <= sqrt(numero); contador++) {
        if ((numero % contador) == 0) {
            return 0;
        }
    }

    return 1;
}

int verificacao(int numero) {
    while (!ehprimo(numero)) {
        printf("O numero digitado nao e primo\n");
        printf("Digite um novo numero: ");
        scanf("%d", &numero);
    }
    return numero;
}

// Função para encriptar a mensagem
void encriptarMensagem(char mensagem[], int tamanho, int chavePublica, int n) {
    FILE *arquivoCriptografado = fopen("mensagem_criptografada.txt", "w");

    for (int i = 0; i < tamanho; i++) {
        char caractere = mensagem[i];

        if (caractere >= 32 && caractere <= 126) {
            // Encriptar usando a fórmula c ≡ m^e mod n
            int mensagemEncriptada = fmod(pow(caractere, chavePublica), n);

            // Escrever o caractere encriptado no arquivo
            fprintf(arquivoCriptografado, "%d ", mensagemEncriptada);
        } else {
            // Caracteres fora do intervalo [32, 126] não são encriptados e são ignorados
        }
    }

    fclose(arquivoCriptografado);

}

// Função para desencriptar a mensagem
void desencriptarMensagem(char mensagemCriptografada[], int tamanho, int chavePrivada, int n) {
    FILE *arquivoDesencriptado = fopen("mensagem_desencriptada.txt", "w");

    // Tokenizar a mensagem criptografada
    char *token = strtok(mensagemCriptografada, " ");
    while (token != NULL) {
        int valorCriptografado = atoi(token);

        // Desencriptar usando a fórmula m ≡ c^d mod n
        int mensagemDesencriptada = fmod(pow(valorCriptografado, chavePrivada), n);

        // Escrever o caractere desencriptado no arquivo
        fprintf(arquivoDesencriptado, "%c", (char)mensagemDesencriptada);

        // Avançar para o próximo token
        token = strtok(NULL, " ");
    }

    fclose(arquivoDesencriptado);
}

int main(){

    unsigned long int q, p, n, e, z;

    printf("Digite o primeiro numero primo para gerar a chave publica: \n");
    scanf("%ld", &p);
    p = verificacao(p);
    printf("\nDigite o segundo numero primo: \n");
    scanf("%ld", &q);
    q = verificacao(q);

    printf("\nDigite o valor para E: \n");
    scanf("%ld", &e);

    n = p * q;
    z = (p - 1) * (q - 1);
    int inverso = moduloinverso(e, z);
    printf("\ninverso: %d\n", inverso);

    printf("\nDigite a mensagem a ser encriptada: \n");

    char mensagem[1000]; // Tamanho arbitrário, ajustar conforme necessário
    getchar(); // Consumir o caractere de nova linha deixado pelo scanf anterior
    fgets(mensagem, sizeof(mensagem), stdin);

    // Solicitar que o usuário digite a chave pública recebida previamente
    int chavePublica;
    printf("\nDigite a chave publica: \n");
    scanf("%d", &chavePublica);

    // Encriptar a mensagem usando a chave pública e salvar em um arquivo
    encriptarMensagem(mensagem, sizeof(mensagem), chavePublica, n);

    printf("\nMensagem encriptada e salva no arquivo 'mensagem_criptografada.txt'.\n");

    // Solicitar que o usuário digite a mensagem criptografada
    printf("\nDigite a mensagem criptografada: \n");
    char mensagemCriptografada[10000]; // Tamanho arbitrário, ajustar conforme necessário
    getchar(); // Consumir o caractere de nova linha deixado pelo scanf anterior
    fgets(mensagemCriptografada, sizeof(mensagemCriptografada), stdin);

    // Solicitar que o usuário digite a chave privada
    int chavePrivada;
    printf("\nDigite a chave privada: \n");
    scanf("%d", &chavePrivada);

    // Desencriptar a mensagem usando a chave privada e salvar em um arquivo
    desencriptarMensagem(mensagemCriptografada, sizeof(mensagemCriptografada), chavePrivada, n);

    printf("\nMensagem desencriptada e salva no arquivo 'mensagem_desencriptada.txt'.\n");

    return 0;
}