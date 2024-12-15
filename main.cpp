#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 100
#define MAX_NOME 50

// Definindo a estrutura para armazenar informações de cada aluno
typedef struct {
    char name[MAX_NOME];     // Nome do aluno
    float grades[3];         // Notas das 3 provas
    float attendance;        // Frequência em porcentagem
} Student;

// Função para calcular a media das duas maiores notas
float calculateAverage(float grades[3]) {
    float temp;
    
    // Ordenando as notas para encontrar as duas maiores
    if (grades[0] > grades[1]) {
        temp = grades[0];
        grades[0] = grades[1];
        grades[1] = temp;
    }
    if (grades[0] > grades[2]) {
        temp = grades[0];
        grades[0] = grades[2];
        grades[2] = temp;
    }
    if (grades[1] > grades[2]) {
        temp = grades[1];
        grades[1] = grades[2];
        grades[2] = temp;
    }

    // Calculando a média das duas maiores notas
    return (grades[1] + grades[2]) / 2.0;
}

// Função para verificar se o aluno está aprovado ou reprovado
const char* checkApproval(float average, float attendance) {
    if (average >= 7.0 && attendance >= 75.0) {
        return "Aprovado";
    } else {
        return "Reprovado";
    }
}

// Função para exibir o relatório
void printReport(Student students[], int numStudents) {
    printf("\nRelatorio Final:\n");
    printf("===============================================\n");
    printf("Nome do Aluno         | Media Final | Situacao\n");
    printf("===============================================\n");

    for (int i = 0; i < numStudents; i++) {
        float average = calculateAverage(students[i].grades);
        const char* status = checkApproval(average, students[i].attendance);
        printf("%-20s | %.2f       | %s\n", students[i].name, average, status);
    }

    printf("===============================================\n");
}

int main() {
    int numStudents;
    
    // Solicita o número de alunos
    printf("Digite o numero de alunos: ");
    if (scanf("%d", &numStudents) != 1 || numStudents <= 0 || numStudents > MAX_ALUNOS) {
        printf("Numero de alunos invalido. O numero deve estar entre 1 e %d.\n", MAX_ALUNOS);
        return 1;
    }

    // Declaração do array de structs para armazenar os dados dos alunos
    Student students[MAX_ALUNOS];
    
    // Leitura dos dados dos alunos
    for (int i = 0; i < numStudents; i++) {
        printf("\nAluno %d:\n", i + 1);
        
        // Leitura do nome do aluno
        printf("Digite o nome do aluno: ");
        getchar(); // Limpa o buffer do \n
        fgets(students[i].name, MAX_NOME, stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0'; // Remove o \n do final do nome
        
        // Leitura das 3 notas
        printf("Digite as 3 notas: ");
        for (int j = 0; j < 3; j++) {
            if (scanf("%f", &students[i].grades[j]) != 1) {
                printf("Entrada invalida para as notas. Tente novamente.\n");
                return 1;
            }
        }
        
        // Leitura da frequência
        printf("Digite a frequencia (em porcentagem): ");
        if (scanf("%f", &students[i].attendance) != 1 || students[i].attendance < 0 || students[i].attendance > 100) {
            printf("Entrada invalida para a frequencia. A frequencia deve ser entre 0 e 100.\n");
            return 1;
        }
    }

    // Exibe o relatório final
    printReport(students, numStudents);

    return 0;
}
