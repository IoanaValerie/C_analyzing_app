#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct node
{
    int *timestamp;
    double *value;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct dl_list
{
    node_t *head;
    node_t *tail;
    size_t len;
} list_t;

/* functie care intitializeaza un nod cu niste valori date*/
node_t *init_node(int *value1, double *value2)
{
    node_t *new_node = malloc(sizeof(node_t));
    new_node->timestamp = malloc(sizeof(int));
    new_node->value = malloc(sizeof(double));
    *new_node->timestamp = *value1;
    *new_node->value = *value2;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

/* functie care intitializeaza o lista*/
list_t *init_list()
{
    list_t *new_list = malloc(sizeof(list_t));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->len = 0;
    return new_list;
}

/* functie care elibereaza memoria ocupata de un nod*/
void free_node(node_t *node)
{
    free(node->value);
    free(node->timestamp);
    free(node);
}

/* functie care elibereaza memoria ocupata de o lista*/
void destroy_list(list_t *list)
{
    node_t *aux;
    while (list->len > 0)
    {
        aux = list->tail;
        list->tail = list->tail->prev;
        free_node(aux);
        --list->len;
    }
    free(list);
}

/* functie care insereaza un nod intr o lista*/
int insert_node(list_t *list, int value1, double value2, long int position)
{
    node_t *node = init_node(&value1, &value2);
    if (position > list->len || position < 0)
        return -1;
    if (list->len == 0)
    {
        list->head = node;
        list->tail = node;
        list->head->prev = NULL;
        list->tail->next = NULL;
        list->len++;
        return 0;
    }
    if (position == 0)
    {
        node->next = list->head;
        list->head->prev = node;
        node->prev = NULL;
        list->head = node;
        list->len++;
        return 1;
    }
    if (position == list->len)
    {
        node->prev = list->tail;
        list->tail->next = node;
        node->next = NULL;
        list->tail = node;
        list->len++;
        return 2;
    }
    int i = 0;
    node_t *aux = list->head;
    while (i != position - 1)
    {
        aux = aux->next;
        i++;
    }
    node->next = aux->next;
    node->prev = aux;
    (aux->next)->prev = node;
    aux->next = node;
    list->len++;
    return 3;
}

/* functie care insereaza un nod intr o lista
(modificata pentru folosirea functiei de inserare crescatoare)*/
int insert_node1(list_t *list, long int position, node_t *node)
{
    // node_t *node = init_node(&value1, &value2);
    if (position > list->len || position < 0)
        return -1;
    if (list->len == 0)
    {
        list->head = node;
        list->tail = node;
        list->head->prev = NULL;
        list->tail->next = NULL;
        list->len++;
        return 0;
    }
    if (position == 0)
    {
        node->next = list->head;
        list->head->prev = node;
        node->prev = NULL;
        list->head = node;
        list->len++;
        return 1;
    }
    if (position == list->len)
    {
        node->prev = list->tail;
        list->tail->next = node;
        node->next = NULL;
        list->tail = node;
        list->len++;
        return 2;
    }
    int i = 0;
    node_t *aux = list->head;
    while (i != position - 1)
    {
        aux = aux->next;
        i++;
    }
    node->next = aux->next;
    node->prev = aux;
    (aux->next)->prev = node;
    aux->next = node;
    list->len++;
    return 3;
}

/*functie care insereaza crescator noduri in lista*/
int insert_sorted_asc(list_t *list, int timestamp, double value)
{
    node_t *node = init_node(&timestamp, &value);
    if (list->len == 0)
    {
        list->head = node;
        list->tail = node;
        list->head->prev = NULL;
        list->tail->next = NULL;
        list->len++;
        return 0;
    }
    if (*list->head->value > *node->value)
    {
        insert_node1(list, 0, node);
    }
    else if (*list->tail->value < *node->value)
    {
        insert_node1(list, list->len, node);
    }
    else
    {
        node_t *aux = list->head;
        int i = 0;
        while (*node->value > *aux->value)
        {
            aux = aux->next;
            i++;
        }
        insert_node1(list, i, node);
    }
    return 0;
}

/*functie care elimina un nod dintr-o lista*/
int remove_node(list_t *list, long int position)
{
    if (list->len == 0 || position < 0 || position > list->len - 1)
        return -1;
    if (position == 0)
    {
        node_t *node = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free_node(node);
        list->len--;
        return 0;
    }
    if (position == list->len - 1)
    {
        node_t *node = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free_node(node);
        list->len--;
        return 1;
    }
    node_t *node = list->head;
    int i = 0;
    while (i != position)
    {
        i++;
        node = node->next;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free_node(node);
    list->len--;
    return 2;
}

/*functie care afiseaza o lista*/
void print_list(list_t *list)
{
    printf("%lu\n", list->len);
    node_t *aux = list->head;
    // printf("%-25s", "Lista construita (->):");
    if (aux == NULL)
    {
        // Lista vida
        printf("NULL\n");
        return;
    }
    while (aux != list->tail)
    {
        printf("%d %.02lf\n", *aux->timestamp, *aux->value);
        aux = aux->next;
    }
    printf("%d %.02lf\n", *aux->timestamp, *aux->value);
}

/*functie pentru 2.1*/
void e1(list_t *list)
{
    /*se creeaza o lista
    si se copiaza in ea elementele din list*/
    list_t *list1 = init_list();
    int p = list->len;
    node_t *node = list->head;
    while (p--)
    {
        insert_node(list1, *node->timestamp, *node->value, list1->len);
        node = node->next;
    }
    /*se parcurge lista cu
    fereastra de dimensiune 5*/
    int i = 0, j = 0, m = (list->len) - 1, nr = 0;
    node_t *aux = list1->head;
    node_t *aux3 = aux;
    while (j <= m - 4)
    {
        double suma = 0, average = 0, deviation = 0;
        /*se calculeaza media valorilor din fiecare fereastra*/
        for (i = j; i < j + 5; i++)
        {
            suma += *aux->value;
            aux = aux->next;
        }
        average = suma / 5;
        /*se calculeaza deviatia standard a
        valorilor din fiecare fereastra*/
        suma = 0;
        aux = aux3;
        for (i = j; i < j + 5; i++)
        {
            suma += (((*aux->value) - average) * ((*aux->value) - average));
            aux = aux->next;
        }
        deviation = sqrt(suma / 5);
        /*se elimina nodul care nu se afla in
        intervalul dat(exceptia)*/
        aux = aux3;
        for (i = j; i <= j + 2; i++)
        {
            if (i == j + 2)
                if ((*aux->value < average - deviation) || (*aux->value > average + deviation))
                {
                    remove_node(list, j + 2 - nr);
                    nr++;
                }
            aux = aux->next;
        }
        aux3 = aux3->next;
        aux = aux3;
        j++;
    }
    /*se elibereaza memoria ocupata de lista creeata*/
    destroy_list(list1);
}

/*functie pentru 2.2.1*/
list_t *e2(list_t *list)
{
    /*se intializeaza lista in care
    vom insera nodurile cerute*/
    list_t *list1 = init_list();
    /*se parcurge lista cu
    fereastra de dimensiune 5*/
    int i = 0, j = 0, m = (list->len) - 1;
    node_t *aux = list->head;
    node_t *aux3 = aux, *aux2 = aux;
    while (j <= m - 4)
    {
        /*pentru fiecare fereastra se insereaza
        crescator nodurile intr-o lista nou creeata*/
        list_t *list2 = init_list();
        for (i = j; i < j + 5; i++)
        {
            insert_sorted_asc(list2, *aux->timestamp, *aux->value);
            aux = aux->next;
        }
        /*se parcurge lista creeata si creeam o noua
        lista in care vom insera nodurile cerute*/
        aux2 = list2->head;
        aux = aux3;
        for (i = j; i <= j + 2; i++)
        {
            if (i == j + 2)
                insert_node(list1, *aux->timestamp, *aux2->value, list1->len);
            aux = aux->next;
            aux2 = aux2->next;
        }
        aux3 = aux3->next;
        aux = aux3;
        j++;
        /*se elibereaza memoria ocupata de lista
        creeata intital*/
        destroy_list(list2);
    }
    /*se elibereaza memoria ocupata de lista data ca parametru*/
    destroy_list(list);
    /*se returneaza lista dorita*/
    return list1;
}

/*functie pentru 2.2.2*/
list_t *e3(list_t *list)
{
    /*se intializeaza lista in care
    vom insera nodurile cerute*/
    list_t *list1 = init_list();
    /*se parcurge lista cu
    fereastra de dimensiune 5*/
    int i = 0, j = 0, m = (list->len) - 1;
    node_t *aux = list->head;
    node_t *aux3 = aux;
    while (j <= m - 4)
    {
        /*se calculeaza media valorilor din fereastra*/
        double suma = 0;
        for (i = j; i < j + 5; i++)
        {
            suma += *aux->value;
            aux = aux->next;
        }
        suma = suma / 5;
        /*se insereaza nodurile cerute in lista creeata*/
        aux = aux3;
        for (i = j; i <= j + 2; i++)
        {
            if (i == j + 2)
                insert_node(list1, *aux->timestamp, suma, list1->len);
            aux = aux->next;
        }
        aux3 = aux3->next;
        aux = aux3;
        j++;
    }
    /*se elibereaza memoria ocupata de lista data ca parametru*/
    destroy_list(list);
    /*se returneaza lista dorita*/
    return list1;
}

/*functie pentru 2.3*/
void u(list_t *list)
{
    /*se parcurge lista*/
    int i = 0;
    node_t *aux = list->head->next;
    for (i = 1; i < list->len; i++)
    {
        /*se modifica datele nodurilor cerute*/
        if (*aux->timestamp - *aux->prev->timestamp >= 100 && *aux->timestamp - *aux->prev->timestamp <= 1000)
        {
            *aux->timestamp = (*aux->timestamp + *aux->prev->timestamp) / 2;
            *aux->value = (*aux->value + *aux->prev->value) / 2;
        }
        aux = aux->next;
    }
}

/*functie auxiliara pentru 2.4*/
double f(node_t *left, node_t *right, int timestampnext)
{
    double j = 0;
    double w0 = 0, w1 = 0, w2 = 0, w = 0;
    double numitor = 0;
    /*se calculeaza coeficientul care va scadea influenta
    punctelor pe masura ce ne departam de interval*/
    for (j = 0; j < 3; j++)
        numitor += ((j * j / 4) * 0.9 + 0.1);
    for (j = 0; j < 3; j++)
    {
        double numarator = (j * j / 4) * 0.9 + 0.1;
        if (j == 0)
            w0 = numarator / numitor;
        else if (j == 1)
            w1 = numarator / numitor;
        else
            w2 = numarator / numitor;
    }
    /*se calculeaza factorul de scalare*/
    double c = (timestampnext - *left->timestamp) / (double)(*right->timestamp - *left->timestamp);
    double valuenext = 0, sumal = 0, sumar = 0;
    /*se calculeaza valoarea nodului dupa formula data*/
    for (j = 0; j < 3; j++)
    {
        if (j == 0)
            w = w2;
        else if (j == 1)
            w = w1;
        else
            w = w0;
        sumal += ((*left->value) * w);
        sumar += ((*right->value) * w);
        left = left->prev;
        right = right->next;
    }
    valuenext = (1 - c) * sumal + c * sumar;
    /*se returneaza valoarea dorita*/
    return valuenext;
}

/*functie pentru 2.4*/
list_t *c(list_t *list)
{
    /*se parcurge lista*/
    node_t *curr = list->head, *right = list->head, *left = list->head;
    int i = 0;
    while (curr != list->tail)
    {
        /*se verifica daca diferenta de timestamp dintre 2
        noduri consecutive e mai mare decat 1000*/
        if (*curr->next->timestamp - *curr->timestamp >= 1000)
        {
            right = curr->next;
            left = curr;
            int timestampnext = 0;
            double valuenext = 0;
            /*se adauga noduri pana cand se ajunge la right*/
            while (*right->timestamp > *curr->timestamp + 200)
            {
                i++;
                timestampnext = *curr->timestamp + 200;
                /*se calculeaza valoarea fiecarui nod de inserat 
                cu ajutorul functiei auxiliare f*/
                valuenext = f(left, right, timestampnext);
                insert_node(list, timestampnext, valuenext, i);
                curr = curr->next;
            }
        }
        i++;
        curr = curr->next;
    }
    return list;
}

/*functie pentru 2.5*/
void stdelta(list_t *list, int delta)
{
    /*se insereaza crescator nodurile intr-o lista nou creeata*/
    list_t *list1 = init_list();
    node_t *aux = list->head;
    int i = 0;
    for (i = 0; i < list->len; i++)
    {
        insert_sorted_asc(list1, *aux->timestamp, *aux->value);
        aux = aux->next;
    }
    /*se afla intervalul de inceput*/
    int j = 0, nr = 0;
    node_t *node = list1->head;
    if (*node->value >= 0)
        j = (int)*node->value;
    else
        j = (int)*node->value - 1;
    /*se parcurge lista si se afiseaza
     intervalul si numarul de elemente*/
    while (j <= *list1->tail->value)
    {
        nr = 0;
        while (node != NULL)
            if (*node->value <= j + delta)
            {
                nr++;
                node = node->next;
            }
            else
                break;
        if (nr != 0)
            printf("[%d, %d] %d\n", j, j + delta, nr);
        j += delta;
    }
    /*se elibereaza memoria ocupata de lista creeata*/
    destroy_list(list1);
}

int main(int argc, char **argv)
{
    /*se creeaza o lista*/
    list_t *new_list = init_list();
    int i = 0;
    int x1 = 0;
    double x2 = 0;
    int n = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d%lf", &x1, &x2);
        insert_node(new_list, x1, x2, new_list->len);
    }
    int ok = 1;
    /*se parcurg argumentele din linia de comanda
    si se apeleaza functia corespunzatoare*/
    for (i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--e1") == 0)
        {
            e1(new_list);
            ok = 0;
        }
        else if (strcmp(argv[i], "--e2") == 0)
        {
            new_list = e2(new_list);
            ok = 0;
        }
        else if (strcmp(argv[i], "--e3") == 0)
        {
            new_list = e3(new_list);
            ok = 0;
        }
        else if (strcmp(argv[i], "--u") == 0)
        {
            u(new_list);
            ok = 0;
        }
        else if (strcmp(argv[i], "--c") == 0)
        {
            new_list = c(new_list);
            ok = 0;
        }
        else if (strstr(argv[i], "--st") != NULL)
        {
            int delta = (int)atoi(argv[i] + 4);
            stdelta(new_list, delta);
        }
    }
    if (ok == 0)
        print_list(new_list);
    /*se elibereaza memoria ocupata de lista creeata*/
    destroy_list(new_list);
    return 0;
}