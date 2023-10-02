#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

long long verificaPrimo(long long p) {
    long long i;
    double j = sqrt(p);

    for (i = 2; i <= j; i++) {
        if (p % i == 0)
            return 0;
    }
    return 1;
}

long long escolheE(long long phi, long long p, long long q) {
    long long i, e;
    for (i = 2; i < phi; i++) {
        if (phi % i != 0 && verificaPrimo(i) && i != p && i != q) {
            e = i;
            break;
        }
    }
    return e;
}

void divisao(long long *resto, long long *quociente, long long a, long long b) {
    if (a >= 0) {
        *quociente = 0;
        *resto = a;

        while (*resto >= b) {
            *resto -= b;
            *quociente = *quociente + 1;
        }
    }
}

long long mdcEstendido(long long a, long long b) {
    long long resto, quociente, xB = 1, yB = 0, x = 0, y = 1, alpha, beta, phi;
    phi = a;

    resto = a;
    while (resto != 0) {
        divisao(&resto, &quociente, a, b);
        a = b;
        b = resto;
        if (resto > 0) {
            alpha = xB - quociente * x;
            beta = yB - quociente * y;

            xB = x;
            yB = y;
            x = alpha;
            y = beta;
        }
    }

    if (beta < 0)
        beta = phi + beta;

    return beta;
}

long potencia(long long a, long long e, long long n) {
    long long A = a, P = 1, E = e;

    while (1) {
        if (E == 0)
            return P;
        else if (E % 2 != 0) {
            P = (A * P) % n;
            E = (E - 1) / 2;
        } else {
            E = E / 2;
        }
        A = (A * A) % n;
    }
}

int *codifica(char *mensagem, long long e, long long n) {
    long long i;
    int *mensagemC;

    mensagemC = malloc(100 * sizeof(int));
    for (i = 0; i < 10000; i++) {
        mensagemC[i] = potencia(mensagem[i], e, n);
    }

    return mensagemC;
}

char *decodifica(int *mensagemC, long long d, long long n) {
    long long i;
    char *mensagem;

    mensagem = malloc(10000 * sizeof(char));

    for (i = 0; i < 10000; i++) {
        mensagem[i] = potencia(mensagemC[i], d, n);
    }

    return mensagem;
}

int main(void) {
    long long i, p, q, n, phi, e, d, expoente;
    int opcao;

    printf("\nEscolha a opcao:\n");
    printf("1. Gerar Chave Publica\n");
    printf("2. Encriptar\n");
    printf("3. Desencriptar\n");
    scanf("%d", &opcao);

    if (opcao == 1) {
        printf("\nDigite o primeiro numero primo (p): ");
        scanf("%llu", &p);

        if (!verificaPrimo(p)) {
            printf("Voce nao digitou um primo\n");
            return 0;
        }

        printf("\nDigite o segundo numero primo (q): ");
        scanf("%llu", &q);

        if (!verificaPrimo(q) || p == q) {
            printf("\nVoce nao digitou um primo\n");
            return 0;
        }

        phi = (p - 1) * (q - 1);

        printf("\nDigite o expoente (deve ser coprimo com %llu): ", phi);
        scanf("%llu", &expoente);

        e = expoente;

        printf("\nChave publica: (%llu, %llu)\n", e, p * q);
    } else if (opcao == 2) {
        char mensagem[10000];
        printf("\nDigite a mensagem de texto a encriptar: ");
        scanf("\n");
        fgets(mensagem, 10000, stdin);

        printf("\nDigite a chave publica: ");
        scanf("%llu", &e, &n);


        int *mensagemC = codifica(mensagem, e, n);

        printf("\nMensagem encriptada: ");
        for (i = 0; i < strlen(mensagem); i++) {
            printf("%c", mensagemC[i]);
        }
        printf("\n");
        free(mensagemC);
    } else if (opcao == 3) {
        printf("\nDigite o primeiro numero primo (p): ");
        scanf("%llu", &p);

        if (!verificaPrimo(p)) {
            printf("Voce nao digitou um primo\n");
            return 0;
        }

        printf("\nDigite o segundo numero primo (q): ");
        scanf("%llu", &q);

        if (!verificaPrimo(q) || p == q) {
            printf("\nVoce nao digitou um primo\n");
            return 0;
        }

        printf("\nDigite a chave publica (e): ");
        scanf("%llu", &e);

        printf("\nDigite a chave privada (d): ");
        scanf("%llu", &d);

        char mensagem[10000];
        printf("\nDigite a mensagem de texto a desencriptar: ");
        scanf("\n");
        fgets(mensagem, 10000, stdin);

        int *mensagemC = codifica(mensagem, e, n);
        char *mensagemD = decodifica(mensagemC, d, n);

        printf("\nMensagem desencriptada: %s\n\n", mensagemD);

        free(mensagemC);
        free(mensagemD);
    } else {
        printf("\nOpcao invalida.\n");
        return 0;
    }

    return 0;
}
