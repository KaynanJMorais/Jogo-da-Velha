#include <stdio.h>   // Biblioteca padrão para entrada e saída
#include <stdlib.h>  // Biblioteca padrão para uso de funções como system()
#include <ctype.h>   // Biblioteca para manipulação de caracteres, como toupper()

#define SIZE 3  // Define o tamanho do tabuleiro como uma constante

// Declaração das funções utilizadas no programa
void inicializarTabuleiro(char tabuleiro[SIZE][SIZE]);  // Inicializa o tabuleiro
void exibirTabuleiro(char tabuleiro[SIZE][SIZE]);       // Exibe o tabuleiro
int jogadaValida(char tabuleiro[SIZE][SIZE], int linha, int coluna); // Verifica se a jogada é válida
int verificarVitoria(char tabuleiro[SIZE][SIZE]);       // Verifica se há um vencedor
void jogar();                                            // Função principal do jogo

int main() {
    char opcao;  // Variável para armazenar a escolha do jogador
    do {
        jogar();  // Chama a função principal do jogo
        printf("\nDeseja jogar novamente? (S/N): ");  // Pergunta se o jogador quer jogar novamente
        scanf(" %c", &opcao);  // Lê a escolha do jogador
    } while (toupper(opcao) == 'S');  // Converte para maiúscula e verifica se é 'S'
    
    printf("\nObrigado por jogar!\n");  // Mensagem de despedida
    return 0;  // Encerra o programa
}

void jogar() {
    char tabuleiro[SIZE][SIZE];  // Matriz para armazenar o estado do tabuleiro
    int linha, coluna, jogador = 1, movimentos = 0;  // Variáveis auxiliares para controle
    char simbolo;  // Símbolo do jogador atual ('X' ou 'O')
    
    inicializarTabuleiro(tabuleiro);  // Inicializa o tabuleiro vazio
    while (1) {  // Loop infinito até o jogo acabar
        exibirTabuleiro(tabuleiro);  // Exibe o tabuleiro atualizado
        simbolo = (jogador == 1) ? 'X' : 'O';  // Define o símbolo do jogador atual
        printf("\nJogador %d (%c), informe linha e coluna (1-3): ", jogador, simbolo);  // Solicita a jogada
        scanf("%d %d", &linha, &coluna);  // Lê a jogada do jogador
        
        linha--;  // Ajusta para índice baseado em 0
        coluna--;  // Ajusta para índice baseado em 0
        
        if (!jogadaValida(tabuleiro, linha, coluna)) {  // Verifica se a jogada é válida
            printf("Posicao invalida! Tente novamente.\n");  // Mensagem de erro
            continue;  // Pede nova entrada se a posição for inválida
        }
        
        tabuleiro[linha][coluna] = simbolo;  // Marca a jogada no tabuleiro
        movimentos++;  // Incrementa o contador de jogadas
        
        if (verificarVitoria(tabuleiro)) {  // Verifica se houve um vencedor
            exibirTabuleiro(tabuleiro);  // Exibe o tabuleiro final
            printf("\nJogador %d (%c) venceu!\n", jogador, simbolo);  // Mensagem de vitória
            break;  // Sai do loop se alguém vencer
        }
        
        if (movimentos == SIZE * SIZE) {  // Verifica se todas as casas foram preenchidas (empate)
            exibirTabuleiro(tabuleiro);  // Exibe o tabuleiro final
            printf("\nEmpate!\n");  // Mensagem de empate
            break;  // Sai do loop em caso de empate
        }
        
        jogador = (jogador == 1) ? 2 : 1;  // Alterna entre os jogadores
    }
    
    // Pergunta se o jogador deseja reiniciar a partida
    char reiniciar;
    printf("\nDeseja reiniciar a partida? (S/N): ");  // Pergunta se deseja reiniciar
    scanf(" %c", &reiniciar);  // Lê a resposta do jogador
    if (toupper(reiniciar) == 'S') {  // Se a resposta for 'S'
        jogar();  // Reinicia a partida chamando a função jogar novamente
    }
}

void inicializarTabuleiro(char tabuleiro[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {  // Loop para cada linha
        for (int j = 0; j < SIZE; j++) {  // Loop para cada coluna
            tabuleiro[i][j] = ' ';  // Inicializa todas as posições com espaço em branco
        }
    }
}

void exibirTabuleiro(char tabuleiro[SIZE][SIZE]) {
    printf("\n");  // Nova linha para melhor formatação
    for (int i = 0; i < SIZE; i++) {  // Loop para cada linha
        for (int j = 0; j < SIZE; j++) {  // Loop para cada coluna
            printf(" %c ", tabuleiro[i][j]);  // Exibe a célula do tabuleiro
            if (j < SIZE - 1) printf("|");  // Adiciona separador vertical entre colunas
        }
        printf("\n");  // Nova linha após cada linha do tabuleiro
        if (i < SIZE - 1) printf("---|---|---\n");  // Adiciona separador horizontal entre linhas
    }
}

int jogadaValida(char tabuleiro[SIZE][SIZE], int linha, int coluna) {
    // Retorna verdadeiro se a jogada for válida: dentro dos limites e a posição está vazia
    return (linha >= 0 && linha < SIZE && coluna >= 0 && coluna < SIZE && tabuleiro[linha][coluna] == ' ');
}

int verificarVitoria(char tabuleiro[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {  // Verifica linhas
        if (tabuleiro[i][0] != ' ' && tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2])
            return 1;  // Vitória encontrada na linha
        if (tabuleiro[0][i] != ' ' && tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i])
            return 1;  // Vitória encontrada na coluna
    }
    // Verifica diagonais
    if (tabuleiro[0][0] != ' ' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2])
        return 1;  // Vitória encontrada na diagonal principal
    if (tabuleiro[0][2] != ' ' && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0])
        return 1;  // Vitória encontrada na diagonal secundária
    
    return 0;  // Retorna 0 se não houver vitória
}