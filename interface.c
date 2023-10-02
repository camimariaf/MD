#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void main() {

    int opcao;
    printf("Escolha uma das seguintes opcoes numericas:\n1 - Gerar chave publica.\n2 - Criptografar mensagem.\n3 - Descriptografar mensagem.\n");

    scanf("%d", &opcao);
    if (opcao == 1)
    {
        // Gerar chave publica
    } else if (opcao == 2)
    {
        // Criptografar mensagem
    } else if (opcao == 3)
    {
        // Descriptografar mensagem
    } else
    {
        printf("Digite um valor valido.\n");
        return main();
    }

    int escolha;
    printf("Caso deseje continuar digite: 1\nCaso deseje encerar o progama digite: 2\n");
    scanf("%d",&escolha);
    if (escolha == 1)
    {

        return main();
    }
    return;
}