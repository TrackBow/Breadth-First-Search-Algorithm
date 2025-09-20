//COTTEL THIBAULT 3A_AVM
//TP3 - 20/10/2023

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // pour le sleep

typedef struct{
    int taille;     //taille = longueur = largeur
    int **tab;
}LABY;

typedef LABY L;

/*
typedef struct{
    int x;      //coordonnee x du couple
    int y;      //coordonnee y du couple
    struct file *queue;
}file;
*/
typedef struct Element Element;
struct Element{
    int x;
    int y;
    Element *suivant;
};

typedef struct file file;
struct file{
    Element *tete;
    Element *queue;
};

/**QUESTIONS 1-6 **/

void set_laby(LABY *L, int taille){
    L->taille = taille;
    L->tab = (int**)malloc(L->taille * sizeof(int*));     //Allocation dynamique pour 1ere dimension
    for(int i = 0 ;i<L->taille;i++){
        L->tab[i] = (int*)malloc(L->taille * sizeof(int));     //Allocation dynamique pour la 2eme dimension
    }
}

void free_laby(LABY *L){
    for(int i = 0;i<L->taille;i++){
        free(L->tab[i]);
    }
    free(L->tab);
}

LABY charge_laby(char *nom){
    LABY L;
    FILE *f = fopen("laby1.txt", "r");
    if(f == NULL){
        printf("ERREUR ouverture fichier\n");
    }
    fscanf(f, "%d", &L.taille);
    set_laby(&L, L.taille);
    for(int i = 0;i<L.taille;i++){
        for(int j = 0;j<L.taille;j++){
            fscanf(f, "%d", &L.tab[i][j]);
        }
    }

    fclose(f);  //ferme le fichier
    return L;
}

void afficher_laby(LABY L){
    char x = '0';
    //printf("%c\n\n", L.tab[0][0]);
    for(int i = 0;i<L.taille;i++){
        for(int j = 0;j<L.taille;j++){
                if(L.tab[i][j] == 0){
                    printf("%c", x);       //Mur
                }
                else{
                    printf("%d", L.tab[i][j]);       //Rien
                }
        }

        printf("\n");
    }
}

int dans_laby(LABY L,int x,int y){
    if((x<0) || (x>=L.taille) || (y<0) || (y>=L.taille)){                   //ATTENTION : les valeurs vont de 0 à 14 et non de 1 à 15
        return 0;
    }
    return 1;
}

int accessible(LABY L, int x, int y){
    if(dans_laby(L, x, y)){
        if(L.tab[x][y] == 1){
            return 1;
        }
    }
    return 0;
}

int impasse(LABY L, int x, int y){              //ATTENTION : si (x,y) est un mur -> on return 0 donc ce n'est pas une impasse
    int nb_impasses = 0;
    if(dans_laby(L, x, y)){
        if(accessible(L, x, y)){
            if(!accessible(L, x, y-1)){nb_impasses += 1;}
            if(!accessible(L, x, y+1)){nb_impasses += 1;}
            if(!accessible(L, x-1, y)){nb_impasses += 1;}
            if(!accessible(L, x+1, y)){nb_impasses += 1;}
        }
    }
    if(nb_impasses >= 3){return 1;}
    return 0;
}

/**QUESTIONS 6 - **/
/*
file *new_file(void){
    return NULL;
}
*/

file creer_file(void){
    file F;
    F.queue = NULL;
    F.tete = NULL;
    return F;
}


int file_vide(file f){
    if(f.tete == NULL){
        return 1;
    }
    return 0;
}

void enfiler(file *f, int x, int y){
    Element *nouveau = (Element *)malloc(sizeof(Element));

    if(nouveau == NULL){
        printf("Erreur lors de l'allocation mémoire");
        exit(1);
    }
    nouveau->x = x;
    nouveau->y = y;
    nouveau->suivant = NULL;


    if(file_vide(*f)){
        f->tete = nouveau;
        f->queue = nouveau;

    }
    else{
        f->queue->suivant = nouveau;
        f->queue = nouveau;

    }
}

void tete(file f, int *x, int *y){
    if(!file_vide(f)){
        *x = f.tete->x;
        *y = f.tete->y;
    }
    else{
        *x = -1;
        *y = -1;
    }

}

void defile(file *f){
    if(!file_vide(*f)){                 //Si pas vide alors on defile
        Element* ElementSupp = f->tete;
        f->tete = ElementSupp->suivant;
        //printf("Je defile (%d,%d)", ElementSupp->x, ElementSupp->y);
        printf("\n");
    if(f->tete == NULL){         //Cas ou la file est desormais vide
        f->queue = NULL;
    }
    free(ElementSupp);
    }
    else{printf("\nRien a defiler\n");}
}

int count_file(file F){
    int cmpt = 0;
    Element* ElementActuel = F.tete;
    while(ElementActuel != NULL){
        cmpt +=1;
        ElementActuel = ElementActuel->suivant;
    }
    return cmpt;
}

void afficher_file(file f) {
    Element* courant = f.tete;
    while (courant != NULL) {
        printf("(%d, %d) ", courant->x, courant->y);
        courant = courant->suivant;
    }
    printf("\n");
}


void largeur(LABY L){
    file F = creer_file();
    int x = 0;
    int y = 0;
    enfiler(&F, x, y);

    //printf("\n\n%d\n\n", L.tab[0][0]);

    while(!((x == L.taille-1)&&(y == L.taille-1))){
        printf("----------TAB-----------");
        tete(F, &x, &y);
        defile(&F);
        L.tab[x][y] = 4;
        afficher_laby(L);
        printf("\n");
        sleep(1);   //temporise d'une seconde

    if((x == L.taille-1)&&(y == L.taille-1)){
        printf("CHEMIN TROUVE !\n");
        L.tab[x][y] = 4;
        break;
    }
    if(accessible(L, x-1, y)&&L.tab[x-1][y] ==1){
        enfiler(&F, x-1, y);
    }
    if(accessible(L, x+1, y)&& L.tab[x+1][y] ==1){
        enfiler(&F, x+1, y);
    }
    if(accessible(L, x, y-1)&& L.tab[x][y-1] ==1){
        enfiler(&F, x, y-1);
    }
    if(accessible(L, x, y+1)&& L.tab[x][y+1]){
        enfiler(&F, x, y+1);
    }
    L.tab[x][y] = 2;
    }
}

struct pile_element{
    int *x;
    int *y;
    struct pile_element *precedent;
    struct pile_element *suivant;
}; typedef struct pile_element Pile_element;

struct pile{
    Pile_element *top;
}; typedef struct pile Pile;


Pile *creer_pile(){
    Pile *pile = (Pile*)malloc(sizeof(Pile));
    if(pile == NULL){
        printf("Erreur lors de l'allocation memoire");
        exit(1);
    }
    pile->top = NULL;
    return pile;
}

int pile_vide(Pile *pile){
    if(pile->top == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void empile(Pile **p, int *x, int *y){
    if(p != NULL){
        Pile_element *element = *p;
        Pile_element *nouveau= NULL;

        nouveau = (Pile_element *)malloc(sizeof(Pile_element));

        nouveau->x = x;
        nouveau->y = y;

        nouveau->suivant = NULL;
        nouveau->precedent = element;

        if(element!=NULL){
            element->suivant = nouveau;
        }
        *p = nouveau;
        }
    }

void sommet(Pile *p, int *x, int *y){
    if(pile_vide(p)){
        printf("Pile vide\n");
        //break;
    }
    else{
        *x = p->top->x;
        *y = p->top->y;
        p->top--;
    }
}

void depile(Pile **p){
    Pile_element *p1 = *p;
    Pile_element *p1_prec = p1->precedent;

    if(p1->precedent != NULL){
        p1->precedent = NULL;
    }
    int x = p1->x;
    int y = p1->y;

    free(p1);

    p1 = NULL;
    *p = p1_prec;
}

int main()
{
    /**QUESTIONS 1 & 2**/
    //LABY L = {0};
    //set_laby(&L, 5);
    LABY L = charge_laby("laby1.txt");
    afficher_laby(L);
    //int x = 1, y = 10;                               //Ici pour modifier les valeurs de (x,y)
    /**QUESTION 3**/
    /*
    if(dans_laby(L, x, y)){
        printf("La case de coordonnee (%d,%d) est dans le tableau \n", x, y);
    }
    else {
        printf("La case de coordonnee (%d,%d) n'est pas dans le tableau \n", x, y);
    }
    */
    /**QUESTION 4**/
    /*
    if(accessible(L, x, y)){
        printf("La case de coordonnee (%d,%d) est accessible \n", x, y);
    }
    else{
        printf("La case de coordonnee (%d,%d) n'est pas accessible \n", x, y);
    }
    */
    /**QUESTION 5**/            //Pour tester (1,11) est une impasse dans laby1
    /*
    if(impasse(L, x, y)){
        printf("La case de coordonnee (%d,%d) est une impasse", x, y);
    }
    else{
        printf("La case de coordonnee (%d,%d) n'est pas une impasse", x, y);
    }
    */

    /**QUESTIONS 6-7**/
    //file testFile = creer_file();
    /*
    if(file_vide(testFile)){
        printf("La file est vide ! \n");
    }
    else{
        printf("La file n'est pas vide ! \n");
    }
    */
    /*
    enfile(&testFile, 1, 2);
    enfile(&testFile, 3, 4);
    enfile(&testFile, 5, 6);
    */
    /*
    enfiler(&testFile, 1, 2);
    enfiler(&testFile, 3, 4);
    enfiler(&testFile, 5, 6);
    //Verification si bien enfile//             //PB : Seul la derniere valeur enfilee est prise en compte
    printf("Contenu de la file(avant defilement) : \n");
    afficher_file(testFile);

    printf("\n%d", count_file(testFile));
    printf("\n");

    defile(&testFile);
    printf("Contenu de la file (apres defilement) : \n");
    afficher_file(testFile);
    */
    /**QUESTION 8 &9**/
    largeur(L);


    /*
    *x = x;
    *y = y;


    creer_file();
    enfile(F, 10, 10);
    tete(F, &x, &y);
    defile(F);
    */
    free_laby(&L);
    return 0;
}
