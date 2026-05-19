#include <stdio.h>
#include <stdlib.h>


typedef struct Nod {
    int data;
    struct Nod *next;
} Nod;


typedef struct Graf {
    int numarNoduri;
    int *vizitat;
    Nod **listaAdiacenta;
} Graf;


Nod* creareNod(int valoare) {
    Nod *nodNou = (Nod*)malloc(sizeof(Nod));
    nodNou->data = valoare;
    nodNou->next = NULL;
    return nodNou;
}


Graf* creareGraf(int numarNoduri) {
    Graf *graf = (Graf*)malloc(sizeof(Graf));
    graf->numarNoduri = numarNoduri;
    
   
    graf->listaAdiacenta = (Nod**)malloc(numarNoduri * sizeof(Nod*));
    graf->vizitat = (int*)malloc(numarNoduri * sizeof(int));

   
    for (int i = 0; i < numarNoduri; i++) {
        graf->listaAdiacenta[i] = NULL;
        graf->vizitat[i] = 0;
    }
    
    return graf;
}


void adaugaMuchie(Graf *graf, int sursa, int destinatie) {
    
    Nod *nodNou = creareNod(destinatie);
    nodNou->next = graf->listaAdiacenta[sursa];
    graf->listaAdiacenta[sursa] = nodNou;

    
    nodNou = creareNod(sursa);
    nodNou->next = graf->listaAdiacenta[destinatie];
    graf->listaAdiacenta[destinatie] = nodNou;
}


void dfs(Graf *graf, int nodCurent) {
    
    graf->vizitat[nodCurent] = 1;
    
    Nod *aux = graf->listaAdiacenta[nodCurent];

    
    while (aux != NULL) {
        int nodConectat = aux->data;
        if (graf->vizitat[nodConectat] == 0) {
            dfs(graf, nodConectat);
        }
        aux = aux->next;
    }
}


void reseteazaVizitat(Graf *graf) {
    for (int i = 0; i < graf->numarNoduri; i++) {
        graf->vizitat[i] = 0;
    }
}


void existaDrum(Graf *graf, int start, int destinatie) {
    reseteazaVizitat(graf);
    

    dfs(graf, start);

    
    if (graf->vizitat[destinatie] == 1) {
        printf("DA! Exista drum intre restaurantul %d si restaurantul %d.\n", start, destinatie);
    } else {
        printf("NU exista drum intre restaurantul %d si restaurantul %d.\n", start, destinatie);
    }
}

int main() {
    int numarRestaurante, numarMuchii;

    printf("Cate restaurante (noduri) are reteaua? ");
    scanf("%d", &numarRestaurante);

    printf("Cate legaturi (muchii) exista intre ele? ");
    scanf("%d", &numarMuchii);

    Graf *graf = creareGraf(numarRestaurante);

    printf("Adauga cele %d legaturi (ex: '0 1' pt un drum intre rest. 0 si 1):\n", numarMuchii);
    for (int i = 0; i < numarMuchii; i++) {
        int sursa, destinatie;
        scanf("%d %d", &sursa, &destinatie);
        adaugaMuchie(graf, sursa, destinatie);
    }

    int rest1, rest2;
    printf("\nIntrodu cele 2 restaurante pentru a verifica daca exista un drum intre ele: ");
    scanf("%d %d", &rest1, &rest2);

    existaDrum(graf, rest1, rest2);

    return 0;
}