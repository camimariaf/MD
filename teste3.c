long int gcdExtended(long int a, long int b, long int *x, long int *y);

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int x, y, n, t, i, flag;
long int e[500], d[500], temp[500], j, m[10000], en[10000];
char msg[10000];

int prime(long int pr) {
    int i;
    j = sqrt(pr);
    for(i = 2; i <= j; i++) {
        if(pr % i == 0)
            return 0;
    }
    return 1;
}

int euclides(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    } else {
        int x1, y1;
        int gcd = euclides(b, a % b, &x1, &y1);
        *x = y1;
        *y = x1 - (a / b) * y1;
        return gcd;
    }
}

int moduloinverso(int e, int m) {
    int x, y;
    int mdc = euclides(e, m, &x, &y);
    if (mdc != 1) {
        printf("Inverso multiplicativo não existe.\n");
        return -1;
    }
    return (x % m + m) % m;
}

int ehprimo(int numero) {
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

void encryption_key() {
    int k = 0;
    for(i = 2; i < t; i++) {
        if(t % i == 0)
            continue;
        flag = prime(i);
        if(flag == 1 && i != x && i != y) {
            e[k] = i;
            flag = gcdExtended(t, e[k], &x, &y);
            if(flag > 0) {
                d[k] = flag;
                k++;
            }
            if(k == 49)
                break;
        }
    }
}

long int gcdExtended(long int a, long int b, long int *x, long int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    } else {
        long int x1, y1;
        long int gcd = gcdExtended(b, a % b, &x1, &y1);
        *x = y1;
        *y = x1 - (a / b) * y1;
        return gcd;
    }
}

void encrypt() {
    long int pt, ct, key = e[0], k, len;
    i = 0;
    len = strlen(msg);

    FILE *arquivoCriptografado = fopen("mensagem_criptografada.txt", "w");
    if (arquivoCriptografado == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    while (i < len) {
        pt = msg[i] - 32;
        k = 1;
        for (j = 0; j < key; j++) {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 32;
        fprintf(arquivoCriptografado, "%ld ", ct);
        i++;
    }
    fclose(arquivoCriptografado);
    printf("\nMensagem encriptada e salva no arquivo 'mensagem_criptografada.txt'.\n");
}

void decrypt() {
    long int pt, ct, key = d[0], k;
    i = 0;
    FILE *arquivoCriptografado = fopen("mensagem_criptografada.txt", "r");
    FILE *arquivoDesencriptado = fopen("mensagem_desencriptada.txt", "w");

    if (arquivoCriptografado == NULL || arquivoDesencriptado == NULL) {
        printf("Erro ao abrir os arquivos para leitura/escrita.\n");
        exit(1);
    }

    while (fscanf(arquivoCriptografado, "%ld", &ct) == 1) {
        k = 1;
        for (j = 0; j < key; j++) {
            k = k * ct;
            k = k % n;
        }
        pt = k + 32;  // Adiciona 32 para trazer de volta ao intervalo ASCII original
        m[i] = pt;
        fprintf(arquivoDesencriptado, "%c", m[i]);
        i++;
    }

    m[i] = '\0'; // Adiciona o caractere nulo ao final da string
    fclose(arquivoCriptografado);
    fclose(arquivoDesencriptado);

    printf("\nMensagem desencriptada e salva no arquivo 'mensagem_desencriptada.txt'.\n");
}


void gerarChavePublica() {
    unsigned long int p, q, e;

    printf("\nDigite o primeiro numero primo (p): ");
    scanf("%ld", &p);
    p = verificacao(p);

    printf("\nDigite o segundo numero primo (q): ");
    scanf("%ld", &q);
    q = verificacao(q);

    printf("\nDigite o valor para E (expoente relativamente primo a (p-1)*(q-1)): ");
    scanf("%ld", &e);

    n = p * q;
    t = (p - 1) * (q - 1);

    encryption_key();

    FILE *chavePublica = fopen("chave_publica.txt", "w");
    fprintf(chavePublica, "%ld %ld", e, n);
    fclose(chavePublica);

    printf("\nChave publica gerada e salva no arquivo 'chave_publica.txt'.\n");
}

int main() {
    int escolha;

    printf("Escolha uma opcao:\n");
    printf("1 - Gerar chave publica\n");
    printf("2 - Encriptar\n");
    printf("3 - Desencriptar\n");
    scanf("%d", &escolha);

    switch(escolha) {
        case 1:
            gerarChavePublica();
            break;
        case 2:
            printf("\nDigite a mensagem a ser encriptada:\n");
            scanf(" %[^\n]", msg);
            printf("\nDigite a chave publica (E N):\n");
            scanf("%ld %d", &e[0], &n);
            encrypt();
            break;
        case 3:
            printf("\nDigite p, q e e (chave privada):\n");
            scanf("%d %d %ld", &x, &y, &e[0]);
            t = (x - 1) * (y - 1);
            n = x * y;
            encryption_key();
            decrypt();
            break;
        default:
            printf("\nOpcao invalida.\n");
    }

    return 0;
}