char * _strdup (const char *s) {
	size_t len = strlen (s) + 1;
    void *new = malloc (len);

	if (new == NULL)
	    return NULL;

	return (char *) memcpy (new, s, len);
}
const char* get_csv_field (char * tmp, int i) {
    //se crea una copia del string tmp
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}

typedef struct producto producto;

typedef struct carrito carrito;

typedef struct objeto_en_carro objeto_en_carro;

struct producto{
    char nombre[150];
    char marca[150];
    char tipo[150];
    int stock;
    int precio;
};

struct objeto_en_carro{
    producto* objeto;
    int cantidad;
};

struct carrito{
    list* carro;
    char nombre[500];
};
// editar esta funcion*****************************
void agregarProductoNuevo(Map* mapa_nombre,Map * mapa_marca, Map * mapa_tipo){
    char nombre[500];
    producto* verificador = NULL;
    printf("Ingrese Nombre\n");
    getchar();
    scanf("%500[^\n]s", nombre);
    verificador = (producto *) searchMapString(mapa_nombre,nombre);

    if(verificador != NULL){
        verificador ->stock++;
        return;
    }
    verificador = (producto *) malloc (sizeof(producto));
    char tipo[500];
    char marca[500];

    int precio;

    printf("Ingrese Tipo\n");
    getchar();
    scanf("%500[^\n]s",tipo);

    printf("Ingrese Marca\n");
    getchar();
    scanf("%500[^\n]s", marca);

    printf("Ingrese el precio\n");
    scanf("%d", &precio);

    verificador ->stock = 1;
    verificador ->precio = precio;
    strcpy(verificador ->marca,marca);
    strcpy(verificador->tipo,tipo);
    strcpy(verificador->nombre,nombre);
//    insertMap()
    insertMap(mapa_tipo,tipo, verificador);
    insertMap(mapa_nombre,nombre, verificador);
    insertMap(mapa_marca,marca, verificador);

}

void buscarEnElCarrito (carrito* carro, producto* objeto){
    objeto_en_carro* actual_de_la_lista= list_first(carro -> carro);
    while(actual_de_la_lista != NULL){
        if(strcmp(objeto ->nombre, actual_de_la_lista ->objeto ->nombre) == 0){
            if(actual_de_la_lista ->cantidad < objeto ->stock){
                actual_de_la_lista ->cantidad++;
            }
            else
            {
                if(actual_de_la_lista ->cantidad == objeto ->stock){
                    printf("No hay stock suficiente\n");
                }
            }
            return;
        }
        actual_de_la_lista = list_next(carro->carro);
    }

    objeto_en_carro * nuevo_objeto_en_carro = (objeto_en_carro *) malloc (sizeof(objeto_en_carro));
    nuevo_objeto_en_carro ->objeto = objeto;
    nuevo_objeto_en_carro ->cantidad = 1;
    list_push_front(carro ->carro,nuevo_objeto_en_carro);
}

void agregarAlCarrito(producto* objeto , Map* mapa_carritos ){ // arreglar bug usar struct tipo carrito
    char nombre_persona[500];
    printf("Ingresa tu nombre\n");
    getchar();
    scanf("%500[^\n]s", nombre_persona);
    carrito* carro;

    carro = (carrito *) searchMapCarrito(mapa_carritos, nombre_persona);

    if(carro == NULL){
        carro = (carrito * ) malloc (sizeof(carrito));
        carro -> carro = list_create_empty();
        carro ->carro =list_create((list_release_object_callback) carro ->carro);

        strcpy(carro->nombre, nombre_persona);
        objeto_en_carro * nuevo_en_carro = (objeto_en_carro*) malloc (sizeof(objeto_en_carro));

        nuevo_en_carro ->cantidad = 1;
        nuevo_en_carro ->objeto = objeto;

        list_push_front(carro->carro, nuevo_en_carro);
        insertMap(mapa_carritos,carro ->nombre,carro);
    }
    else
    {
        buscarEnElCarrito(carro,objeto);

    }

}

void mostrarTodosLosProductos (Map * mapa_nombre){
    producto * actual = (producto *)firstMap(mapa_nombre);
    while(actual != NULL){
        printf("Nombre:%s \nMarca:%s \nTipo:%s \nStock:%d \nPrecio:%d\n\n", actual->nombre, actual->marca, actual->tipo, actual->stock, actual->precio);
        actual = nextMap(mapa_nombre);
    }
}

producto * buscarPorNombre(const char* nombre, Map * mapa_nombre){
    producto* objeto;
    objeto = (producto *) searchMapString(mapa_nombre,nombre);

    if(objeto == NULL){
        printf("El Objeto no existe\n");
        return NULL;
    }
    else
    {
        printf("Nombre:%s \nMarca:%s \nTipo:%s \nStock:%d \nPrecio:%d\n\n", objeto->nombre, objeto->marca, objeto->tipo, objeto->stock, objeto->precio);
        return objeto;
    }
}
/*
void buscarPorMarca(Map * mapa_marca){
    char marca[500];
    printf("Ingrese Nombre de la marca\n");
    getchar();
    scanf("%500[^\n]s", marca);
    long cont = 0;

    producto * actual = (producto *)firstMap(mapa_marca);
    while(actual != NULL){
        if(strcmp(actual->marca,marca) == 0){
            printf("Nombre:%s \nMarca:%s \nTipo:%s \nStock:%d \nPrecio:%d\n\n", actual->nombre, actual->marca, actual->tipo, actual->stock, actual->precio);
            cont++;
        }
        actual = nextMap(mapa_marca);
    }

    if(cont == 0){
        printf("No existe esa marca\n");
        return;
    }

}


void buscarPorTipo(Map* mapa_tipo){
    char tipo[500];
    long cont = 0;
    printf("Ingrese Nombre del tipo\n");
    getchar();
    scanf("%500[^\n]s", tipo);

    producto * actual = (producto *)firstMap(mapa_tipo);
    while(actual != NULL)
    {
        if(strcmp(actual->tipo,tipo) == 0){
            printf("Nombre:%s \nMarca:%s \nTipo:%s \nStock:%d \nPrecio:%d\n\n", actual->nombre, actual->marca, actual->tipo, actual->stock, actual->precio);
            cont++;
        }
        actual = nextMap(mapa_tipo);
    }

    if(cont == 0){
        printf("No hay productos de ese tipo\n");
        return;
    }
}*/

void concretarCompra(const char* nombre_carrito, Map* carritos, FILE * salida){

    carrito* carro = NULL;

    carro = (carrito *) searchMapCarrito(carritos,nombre_carrito);

    if(carro == NULL){
        printf("nombre Invalido\n");
        return;
    }
    objeto_en_carro* objeto_actual = (objeto_en_carro *) list_first(carro -> carro);

    unsigned int precio_final = 0 ;
    while(objeto_actual != NULL){
        printf("Nombre:%s \nMarca:%s \nTipo:%s \nStock:%d \nPrecio:%d\n\n", objeto_actual ->objeto->nombre,objeto_actual -> objeto->marca,objeto_actual -> objeto->tipo,objeto_actual ->objeto->stock,objeto_actual ->objeto->precio);

        fprintf(salida,objeto_actual ->objeto->nombre);
        fprintf(salida,",");
        fprintf(salida,objeto_actual ->objeto->marca);
        fprintf(salida,",");
        fprintf(salida,(const char *) objeto_actual ->objeto->precio);
        fprintf(salida,",");
        fprintf(salida,objeto_actual ->objeto->tipo);
        fprintf(salida,"\n");
        precio_final += objeto_actual -> objeto-> precio * objeto_actual ->cantidad;
        objeto_actual ->objeto ->stock = objeto_actual ->objeto ->stock - objeto_actual ->cantidad;
        free(objeto_actual);
        objeto_actual = (objeto_en_carro *) list_next(carro->carro);
    }

    objeto_actual = (objeto_en_carro *) list_first(carro -> carro);
    printf("El precio a pagar es de %u\n",precio_final);

}

void ingresoPorArchivo (producto* objeto, char palabra[], Map* mapa_nombre,Map* mapa_marca,Map* mapa_tipo, Map * mapa_tipo_lista, Map * mapa_marca_lista){
    strcpy(objeto ->nombre, get_csv_field(palabra,1));
    strcpy(objeto ->marca, get_csv_field(palabra,2));
    strcpy(objeto ->tipo, get_csv_field(palabra,3));
    objeto -> stock = atoi(get_csv_field(palabra,4));
    objeto -> precio = atoi(get_csv_field(palabra,5));

//******************************
    list* lista_tipo = NULL;
    lista_tipo = searchMapCarrito(mapa_tipo_lista,objeto->tipo);
    if(lista_tipo == NULL)
    {
        lista_tipo = list_create_empty();
        lista_tipo = list_create((list_release_object_callback) lista_tipo);
        list_push_back(lista_tipo,objeto);
        insertMap(mapa_tipo_lista,objeto->tipo,lista_tipo);
    }
    else
    {
        list_push_back(lista_tipo,objeto);
    }
//***********************************
    list* lista_marca = NULL;
    lista_marca = searchMapCarrito(mapa_marca_lista,objeto->marca);
    if(lista_marca == NULL)
    {
        lista_marca = list_create_empty();
        lista_marca =list_create((list_release_object_callback) lista_marca);
        list_push_back(lista_marca,objeto);
        insertMap(mapa_marca_lista, objeto->marca, lista_marca);
    }
    else
    {
        list_push_back(lista_marca,objeto);
    }

    insertMap(mapa_nombre , objeto ->nombre , objeto);
    insertMap(mapa_marca,objeto ->marca , objeto);
    insertMap(mapa_tipo, objeto ->tipo , objeto);

}

void buscarPorTipoLista(Map * Mapa_tipo_lista){
    char tipo[500];
    printf("Ingrese Nombre del tipo\n");
    getchar();
    scanf("%500[^\n]s", tipo);


    list * lista =NULL;
    lista = searchMapCarrito(Mapa_tipo_lista,tipo);

    if(lista == NULL){
        printf("Ese tipo no existe\n");
        return;
    }
    else
    {
        for(producto* actual = list_first(lista);actual != NULL; actual = list_next(lista)){
            printf("Nombre:%s \nMarca:%s \nTipo:%s \nStock:%d \nPrecio:%d\n\n", actual->nombre, actual->marca, actual->tipo, actual->stock, actual->precio);

        }
    }
}

void buscarPorMarcaLista(Map * Mapa_marca_lista){
    char marca[500];
    printf("Ingrese Nombre de la marca\n");
    getchar();
    scanf("%500[^\n]s", marca);

    list * lista =NULL;
    lista = searchMapCarrito(Mapa_marca_lista,marca);

    if(lista == NULL){
        printf("Esa marca no existe\n");
        return;
    }
    else
    {
        for(producto* actual = list_first(lista);actual != NULL; actual = list_next(lista)){
            printf("Nombre:%s \nMarca:%s \nTipo:%s \nStock:%d \nPrecio:%d\n\n", actual->nombre, actual->marca, actual->tipo, actual->stock, actual->precio);
        }
    }
}



