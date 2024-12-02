#include <stdio.h>
#include <stdlib.h>


int countLines(FILE *fptr) {
    int lines = 0;
    char ch;

    rewind(fptr);
    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    return lines + 1;
}

//mi serve per il quick-sort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

//calcoliamo la distanza
int calculateTotalDistance(int *leftList, int *rightList, int numItems) {
    int totalDistance = 0;

    //sto calcolanndo la distanza tra le due liste
    for (int i = 0; i < numItems; i++) {
        int distance = abs(leftList[i] - rightList[i]);
        totalDistance += distance;
    }

    return totalDistance;
}

int calculateSimilarityScore(int *leftList, int *rightList, int numItems) {
    int similarityScore = 0;

    int maxVal = 1000000000; 
    int *frequency = (int *)calloc(maxVal, sizeof(int));
    if (frequency == NULL) {
        printf("Errore nell'allocazione della memoria per il calcolo delle frequenze.\n");
        return -1;
    }

    for (int i = 0; i < numItems; i++) {
        frequency[rightList[i]]++;
    }

    for (int i = 0; i < numItems; i++) {
        int count = frequency[leftList[i]];
        similarityScore += leftList[i] * count;
    }

    free(frequency);
    return similarityScore;
}

int main(void) {
    printf("Advent of Code - Day 01 ;)\n");
    FILE *fptr;

    fptr = fopen("./day-1_puzzle-input.txt", "r");
    if (fptr == NULL) {
        printf("il tuo file fa schifo :(\n");
        return 1;
    }

    int numLines = countLines(fptr);
    printf("il tuo file ha questo numero di righe: %d\n", numLines);

    int *firstNumbers = (int *)malloc(numLines * sizeof(int));
    int *secondNumbers = (int *)malloc(numLines * sizeof(int));
    if (firstNumbers == NULL || secondNumbers == NULL) {
        printf("fallimento nell'allocazione della memoria\n");
        fclose(fptr);
        return 1;
    }

    rewind(fptr); //fa schifo ma ritorno all'inizio del file per prendere anche i secondi numeri
    for (int i = 0; i < numLines; i++) {
        if (fscanf(fptr, "%d %d", &firstNumbers[i], &secondNumbers[i]) != 2) {
            printf("erroreeee %d\n", i + 1);
            free(firstNumbers);
            free(secondNumbers);
            fclose(fptr);
            return 1;
        }
    }

    fclose(fptr); //Best practice è chiudere sempre il file cosi' C e' contento

    qsort(firstNumbers, numLines, sizeof(int), compare);
    qsort(secondNumbers, numLines, sizeof(int), compare);

    //facciamo tutto il calcolo del caso
    int totalDistance = calculateTotalDistance(firstNumbers, secondNumbers, numLines);
    printf("risultato finale: %d\n", totalDistance);


    //similarity score
    int similarityScore = calculateSimilarityScore(firstNumbers, secondNumbers, numLines);
    printf("Similarity score: %d\n", similarityScore);


    //liberiamo memoria cosi' C e' contento
    free(firstNumbers);
    free(secondNumbers);

    return 0;
}


