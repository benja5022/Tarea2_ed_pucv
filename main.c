#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"
#include "Map.h"
#include "Funciones.c"
int main()
{
    int validacion = 0;
    Map * mapa_nombre = NULL;
    mapa_nombre =createMap((MapCompareCallBack)mapa_nombre);
    Map * mapa_tipo = NULL;
    mapa_tipo =createMap((MapCompareCallBack)mapa_tipo);
    Map * mapa_marca  = NULL;
    mapa_marca =createMap((MapCompareCallBack)mapa_marca);
    Map * mapa_carrito = NULL;
    mapa_carrito =createMap((MapCompareCallBack)mapa_carrito);
    //*************
    Map * mapa_tipo_lista = NULL;
    mapa_tipo_lista = createMap((MapCompareCallBack) mapa_tipo_lista);
    Map * mapa_marca_lista = NULL;
    mapa_marca_lista = createMap((MapCompareCallBack) mapa_tipo_lista);
    //***************
    producto * objeto =(producto *) malloc (sizeof(producto));
    char palabra[500];
    FILE * fp = fopen("Archivo_100productos.csv","r");
    if(fp == NULL){
        return 1;
    }

    while(fgets(palabra,500,fp))
    {
        ingresoPorArchivo(objeto,palabra,mapa_nombre,mapa_marca,mapa_tipo,mapa_tipo_lista,mapa_marca_lista);
//        printf("Nombre:%s \nMarca:%s \nTipo:%s \nStock:%d \nPrecio:%d\n\n", objeto->nombre,objeto->marca,objeto->tipo,objeto->stock,objeto->precio);
//        printf("Nombre:%s \nMarca:%s \nTipo:%s \nStock:%s \nPrecio:%s\n\n", get_csv_field(palabra,1),get_csv_field(palabra,2),get_csv_field(palabra,3),get_csv_field(palabra,4),get_csv_field(palabra,5));
        objeto =(producto *) malloc (sizeof(producto));
    }
    fclose(fp);
    char nombre[500];
    int bandera= 1;

    producto * producto_escogido = NULL;
    printf("Si desea ingresar un producto seleccione 1\n");
    printf("Si desea buscar un producto por su nombre ingrese 2\n");
    printf("Si desea buscar un producto por su marca seleccione 3\n");
    printf("Si desea buscar un producto por su tipo seleccione 4\n");
    printf("Si desea ver todos los productos seleccione 5\n");
    printf("Si desea salir y llevarse la compra seleccione 0\n");
    int opcion = -1;
    char opcionc;

//    printf("Si desea agregar el producto al carrito seleccione 5\n");

    while(bandera)
    {
        opcion = -1;
        scanf("%c", &opcionc);
        if(isdigit(opcionc) == 0){
            if (validacion == 0 ){
            printf("ingrese valor valido\n", opcionc);
            validacion = 1;
            }
            continue;
        }
        else
        {
            validacion = 0;
            opcion = opcionc - 48;
            printf("opcion = %d\n", opcion);
        }

        if (opcion == 1) agregarProductoNuevo(mapa_nombre,mapa_marca,mapa_tipo); // editar esta funcion
        if (opcion == 2){
            printf("Ingrese el nombre del producto\n");
            getchar();
            scanf("%500[^\n]s", nombre);
            producto_escogido = buscarPorNombre(nombre,mapa_nombre);
        }
        if (opcion == 3){
//            buscarPorMarca(mapa_marca);
            buscarPorMarcaLista(mapa_marca_lista);
            opcion = -1;
        }

        if (opcion == 4){
//            buscarPorTipo(mapa_tipo);
            buscarPorTipoLista(mapa_tipo_lista);
        }

        if(opcion == 5) mostrarTodosLosProductos(mapa_nombre);
        if (producto_escogido != NULL){

            printf("Si desea agregar este producto al carrito seleccione 1\n");
            opcion = -2;
            scanf("%d", &opcion);
            if (opcion == 1)agregarAlCarrito(producto_escogido,mapa_carrito);

            opcion = -1;
        }
        if(opcion == 0){
             break;
        }
        producto_escogido = NULL;
        getchar();
//        buscarPorNombre(nombre,mapa_nombre);
    }
    opcion = 1;

    FILE * archivo = fopen("salida.csv","w");

    if(archivo == NULL){
        printf("fallo\n");
        return 1;
    }
    do{
        printf("Ingrese el nombre del carrito\n");
        getchar();
        scanf("%500[^\n]s", nombre);
        concretarCompra(nombre,mapa_carrito,archivo);
        printf("Si desea salir ingrese 0\n");
        scanf("%d", &opcion);
    }while(opcion);
    fclose(archivo);
//    producto * i;
//    for(i=firstMap(mapa_nombre); i != NULL ; i= nextMap(mapa_nombre) ) printf("%s\n", i ->nombre);

}

/*
    int numero=5;
    int keys = (('k' + 'e' + 'y' + 's')%5);
    int need = (('n' + 'e' + 'e' + 'd')%5);
    printf("%d %d\n%d",keys,need,numero);
    return 0;
*/
