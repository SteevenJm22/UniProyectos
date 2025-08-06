//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>	// Para getch() (Windows)

// Estructuras 
typedef struct {
    int id;
    char nombre[50];
    char ubicacion[100];
} Barrio; //Define un barrio

typedef struct {
    int id;
    int id_barrio;
    char tipo[50];
    char fecha[11];
    int nun_victimas;
} Delito; //Define un delito

//Limpia el buffer de entrada
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Menú de opciones para barrio
void gestionarBarrios()
{
    int opcion;
    do
    {
    	system("cls");
        printf("=== GESTIONAR BARRIOS ===\n");
        printf("1. Ingresar nuevo barrio.\n");
        printf("2. Consultar barrios.\n");
        printf("3. Actualizar Barrios.\n");
        printf("4. Eliminar Barrio.\n");
        printf("5. Salir al menu principal.\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            ingresarBarrio();
            break;
        case 2:
            consultarBarrios();
            break;
        case 3:
            actualizarBarrio();
            break;
        case 4:
            eliminarBarrio();
            break;
        case 5:
            break;
        default:
            printf("Opcion invalida! Intente nuevamente.\n");
            getch();
        }
    } while (opcion != 5);
}

// Menú de opciones para delitos
void gestionarDelitos()
{
    int opcion;
    do
    {
    	system("cls");
        printf("=== GESTIONAR DELITOS ===\n");
        printf("1. Ingresar nuevo delito.\n");
        printf("2. Consultar delitos.\n");
        printf("3. Actualizar delito.\n");
        printf("4. Eliminar delito.\n");
        printf("5. Salir al menu principal.\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            ingresarDelito();
            break;
        case 2:
            consultarDelitos();
            break;
        case 3:
            actualizarDelito();
            break;
        case 4:
            eliminarDelito();
            break;
        case 5:
            break;
        default:
            printf("Opcion invalida! Intente nuevamente.\n");
            getch();
        }
    } while (opcion != 5);
}

//Función para ingresar 
void ingresarBarrio() {
    Barrio nuevo;
    printf("\n\n=== INGRESO DE NUEVO BARRIO/ZONA ===\n");

    int id_existe;
    do {
        printf("ID del barrio: ");
        scanf("%d", &nuevo.id);

		// Validación: ID único
        FILE *archivo = fopen("barrios.dat", "rb");
        Barrio temp;
        id_existe = 0;
        if (archivo != NULL) {
            while (fread(&temp, sizeof(Barrio), 1, archivo)) {
                if (temp.id == nuevo.id) {
                    id_existe = 1;
                    break;
                }
            }
            fclose(archivo);
        }

        if (id_existe) {
            printf("\n[Error] El ID %d ya existe! Ingrese un ID unico.\n", nuevo.id);
        }
    } while (id_existe);

    printf("Nombre del barrio: ");
    limpiarBuffer();
    fgets(nuevo.nombre, 50, stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;

    printf("Ubicacion: ");
    fgets(nuevo.ubicacion, 100, stdin);
    nuevo.ubicacion[strcspn(nuevo.ubicacion, "\n")] = 0;

    FILE *archivo = fopen("barrios.dat", "ab");
    if (archivo == NULL) {
        printf("Error al abrir archivo!");
        return;
    }
    fwrite(&nuevo, sizeof(Barrio), 1, archivo); //Guardar datos en el archivo binario
    fclose(archivo);

    printf("\nBarrio registrado exitosamente! ID: %d\n", nuevo.id);
    printf("\nPresione cualquier tecla para continuar...");
    getch();
}

//Lee y muestra todos los barrios
void consultarBarrios() {
    FILE *archivo = fopen("barrios.dat", "rb");
    Barrio b;
    int encontrados = 0;

    printf("\n\n=== BARRIOS/ZONAS REGISTRADOS ===\n");

    if (archivo == NULL) {
        printf("\nNo hay barrios registrados!\n");
        printf("\nPresione cualquier tecla para continuar...");
        getch();
        return;
    }

    while (fread(&b, sizeof(Barrio), 1, archivo)) {
        printf("\nID: %d", b.id);
        printf("\nBarrio: %s", b.nombre);
        printf("\nUbicacion: %s", b.ubicacion);
        printf("\n---------------------------------\n");
        encontrados++;
    }

    fclose(archivo);

    if (encontrados == 0) {
        printf("\nNo se encontraron registros!\n");
    } else {
        printf("\nTotal registros: %d\n", encontrados);
    }

    printf("\nPresione cualquier tecla para continuar...");
    getch();
}

void actualizarBarrio() {
    int id, n = 0, encontrado = 0;
    Barrio* barrios = NULL;

    FILE* archivo = fopen("barrios.dat", "rb");
    if (archivo != NULL) {
        // Calcular cantidad de registros
        fseek(archivo, 0, SEEK_END);
        long file_size = ftell(archivo);
        n = file_size / sizeof(Barrio);
        fseek(archivo, 0, SEEK_SET);

        // Carga todos los barrios en memoria dinámica
        barrios = (Barrio*)malloc(n * sizeof(Barrio));
        if (barrios == NULL) {
            printf("Error: Memoria insuficiente!\n");
            fclose(archivo);
            return;
        }

        // Leer todos los registros
        fread(barrios, sizeof(Barrio), n, archivo);
        fclose(archivo);
    }
    else {
        printf("\nNo hay barrios registrados!\n");
        printf("\nPresione cualquier tecla para continuar...");
        getch();
        return;
    }

    printf("\n\n=== ACTUALIZAR BARRIO ===\n");
    printf("Ingrese ID del barrio a actualizar: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (barrios[i].id == id) {
            printf("Nuevo nombre: ");
            limpiarBuffer();
            fgets(barrios[i].nombre, 50, stdin);
            barrios[i].nombre[strcspn(barrios[i].nombre, "\n")] = 0;

            printf("Nueva ubicacion: ");
            fgets(barrios[i].ubicacion, 100, stdin);
            barrios[i].ubicacion[strcspn(barrios[i].ubicacion, "\n")] = 0;

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nNo se encontro el ID.\n");
    }
    else {
        archivo = fopen("barrios.dat", "wb");
        // Actualiza datos y reescribe el archivo
        fwrite(barrios, sizeof(Barrio), n, archivo);
        fclose(archivo);
        printf("\nBarrio actualizado correctamente!\n");
    }

    free(barrios);  // Liberar memoria dinámica

    printf("\nPresione cualquier tecla para continuar...");
    getch();
}

//Elimina un barrio por ID
void eliminarBarrio() {
    int id, n = 0, encontrado = 0;
    Barrio* barrios = NULL;

    FILE *archivo = fopen("barrios.dat", "rb");
        if (archivo != NULL) {
        // Calcular cantidad de registros
        fseek(archivo, 0, SEEK_END);
        long file_size = ftell(archivo);
        n = file_size / sizeof(Barrio);
        fseek(archivo, 0, SEEK_SET);

        // Asignar memoria dinámica
        barrios = (Barrio*)malloc(n * sizeof(Barrio));
        if (barrios == NULL) {
            printf("Error: Memoria insuficiente!\n");
            fclose(archivo);
            return;
        }

        // Leer todos los registros
        fread(barrios, sizeof(Barrio), n, archivo);
        fclose(archivo);
    }
    else {
        printf("\nNo hay barrios registrados!\n");
        printf("\nPresione cualquier tecla para continuar...");
        getch();
        return;
    }

    printf("\n\n=== ELIMINAR BARRIO ===\n");
    printf("Ingrese ID del barrio a eliminar: ");
    scanf("%d", &id);

    FILE *nuevo = fopen("barrios.dat", "wb");
    for (int i = 0; i < n; i++) {
        if (barrios[i].id != id) {
            fwrite(&barrios[i], sizeof(Barrio), 1, nuevo);
        } else {
            encontrado = 1;
        }
    }
    fclose(nuevo);

    if (!encontrado) {
        printf("\nNo se encontro el ID.\n");
    } else {
        printf("\nBarrio eliminado correctamente!\n");
    }
    
    free(barrios);

    printf("\nPresione cualquier tecla para continuar...");
    getch();
}

void ingresarDelito() {
    Delito nuevo;
    printf("\n\n=== REGISTRO DE NUEVO DELITO ===\n");

    printf("ID del delito: ");
    scanf("%d", &nuevo.id);

	//Abrir archivo en modo append
    FILE *archivo_delito = fopen("delitos.dat", "rb");
    Delito temp;
    while (archivo_delito && fread(&temp, sizeof(Delito), 1, archivo_delito)) {
        if (temp.id == nuevo.id) {
            printf("\n[Error] El ID ya existe!\n");
            fclose(archivo_delito);
            return;
        }
    }
    if (archivo_delito) fclose(archivo_delito);

    int barrioValido = 0;
    Barrio b;
    FILE *archivo_barrio = fopen("barrios.dat", "rb");

    do {
        printf("ID del barrio donde ocurrio el delito: ");
        scanf("%d", &nuevo.id_barrio);
        barrioValido = 0;

        if (archivo_barrio != NULL) {
            rewind(archivo_barrio);
            // Validación: Barrio existente
            while (fread(&b, sizeof(Barrio), 1, archivo_barrio)) {
                if (b.id == nuevo.id_barrio) {
                    barrioValido = 1;
                    break;
                }
            }
        }

        if (!barrioValido) {
            printf("\n[Error] ID de barrio no valido!\n");
        }
    } while (!barrioValido);

    fclose(archivo_barrio);

    printf("Tipo de delito: ");
    limpiarBuffer();
    fgets(nuevo.tipo, 50, stdin);
    nuevo.tipo[strcspn(nuevo.tipo, "\n")] = 0;

    printf("Fecha (dd/mm/aaaa): ");
    fgets(nuevo.fecha, 11, stdin);
    nuevo.fecha[strcspn(nuevo.fecha, "\n")] = 0;

    printf("Numero de victimas: ");
    scanf("%d", &nuevo.nun_victimas);

    archivo_delito = fopen("delitos.dat", "ab");
    fwrite(&nuevo, sizeof(Delito), 1, archivo_delito);
    fclose(archivo_delito);

    printf("\nDelito registrado correctamente!\n");
    printf("\nPresione cualquier tecla para continuar...");
    getch();
}

// Lista todos los delitos
void consultarDelitos() {
    FILE *archivo = fopen("delitos.dat", "rb");
    Delito d;
    int encontrados = 0;

    printf("\n\n=== DELITOS REGISTRADOS ===\n");

    if (archivo == NULL) {
        printf("\nNo hay delitos registrados!\n");
    } else {
        while (fread(&d, sizeof(Delito), 1, archivo)) {
            printf("\nID: %d", d.id);
            printf("\nBarrio ID: %d", d.id_barrio);
            printf("\nTipo: %s", d.tipo);
            printf("\nFecha: %s", d.fecha);
            printf("\nNumero de victimas: %d", d.nun_victimas);
            printf("\n---------------------------------\n");
            encontrados++;
        }
        fclose(archivo);
    }

    if (encontrados == 0) {
        printf("\nNo se encontraron registros!\n");
    } else {
        printf("\nTotal registros: %d\n", encontrados);
    }

    printf("\nPresione cualquier tecla para continuar...");
    getch();
}

void actualizarDelito() {
    int id, n = 0, encontrado = 0;
    Delito* delitos = NULL;

    FILE *archivo = fopen("delitos.dat", "rb");
    if (archivo != NULL) {
        // Calcular cantidad de registros
        fseek(archivo, 0, SEEK_END);
        long file_size = ftell(archivo);
        n = file_size / sizeof(Delito);
        fseek(archivo, 0, SEEK_SET);

        // Asignar memoria dinámica
        delitos = (Delito*)malloc(n * sizeof(Delito));
        if (delitos == NULL) {
            printf("Error: Memoria insuficiente!\n");
            fclose(archivo);
            return;
        }

        // Leer todos los registros
        fread(delitos, sizeof(Delito), n, archivo);
        fclose(archivo);
    }
    else {
        printf("\nNo hay delitos registrados!\n");
        printf("\nPresione cualquier tecla para continuar...");
        getch();
        return;
    }

    printf("\n\n=== ACTUALIZAR DELITO ===\n");
    printf("Ingrese ID del delito a actualizar: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (delitos[i].id == id) {
            printf("Nuevo tipo: ");
            limpiarBuffer();
            fgets(delitos[i].tipo, 50, stdin);
            delitos[i].tipo[strcspn(delitos[i].tipo, "\n")] = 0;

            printf("Nueva fecha: ");
            fgets(delitos[i].fecha, 11, stdin);
            delitos[i].fecha[strcspn(delitos[i].fecha, "\n")] = 0;

            printf("Nuevo numero de victimas: ");
			scanf("%d", &delitos[i].nun_victimas);

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nNo se encontro el ID.\n");
    } else {
        archivo = fopen("delitos.dat", "wb");
        for (int i = 0; i < n; i++) {
            fwrite(&delitos[i], sizeof(Delito), 1, archivo);
        }
        fclose(archivo);
        printf("\nDelito actualizado correctamente!\n");
    }

    printf("\nPresione cualquier tecla para continuar...");
    getch();
}

void eliminarDelito() {
    int id, n = 0, encontrado = 0;
    Delito* delitos = NULL;

    FILE *archivo = fopen("delitos.dat", "rb");
    if (archivo != NULL) {
        // Calcular cantidad de registros
        fseek(archivo, 0, SEEK_END);
        long file_size = ftell(archivo);
        n = file_size / sizeof(Delito);
        fseek(archivo, 0, SEEK_SET);

        // Asignar memoria dinámica
        delitos = (Delito*)malloc(n * sizeof(Delito));
        if (delitos == NULL) {
            printf("Error: Memoria insuficiente!\n");
            fclose(archivo);
            return;
        }

        // Leer todos los registros
        fread(delitos, sizeof(Delito), n, archivo);
        fclose(archivo);
    }
    else {
        printf("\nNo hay delitos registrados!\n");
        printf("\nPresione cualquier tecla para continuar...");
        getch();
        return;
    }

    printf("\n\n=== ELIMINAR DELITO ===\n");
    printf("Ingrese ID del delito a eliminar: ");
    scanf("%d", &id);

    FILE *nuevo = fopen("delitos.dat", "wb");
    for (int i = 0; i < n; i++) {
        if (delitos[i].id != id) {
            fwrite(&delitos[i], sizeof(Delito), 1, nuevo);
        } else {
            encontrado = 1;
        }
    }
    fclose(nuevo);

    if (!encontrado) {
        printf("\nNo se encontro el ID.\n");
    } else {
        printf("\nDelito eliminado correctamente!\n");
    }

    printf("\nPresione cualquier tecla para continuar...");
    getch();
}

// Pantalla inicial
void mostrarPresentacion()
{
	system("cls");
    printf("==================================================\n");
    printf("||  SISTEMA DE GESTION DE BARRIOS Y DELITOS.    ||\n");
    printf("==================================================\n");
    printf("||  Desarrollado por:                           ||\n");
    printf("||  Steeven Jaramillo                           ||\n");
    printf("||                                              ||\n");
    printf("||  Materia: Fundamentos de Programacion        ||\n");
    printf("||  Paralelo: 'A'                               ||\n");
    printf("==================================================\n");
    printf("||  Descripcion:                                ||\n");
    printf("||  Sistema para gestionar informacion  de      ||\n");
    printf("||  barrios y delitos asociados a cada ubicacion||\n");
    printf("==================================================\n");
    printf("Presione enter para continuar...");
    getch();
}

// Menú principal
void menu() {
    int opcion;
    do
    {
    	system("cls");
        printf("==== MENU PRINCIPAL ====\n");
        printf("1. Gestionar barrios.\n");
        printf("2. Gestionar delitos.\n");
        printf("3. Salir del programa.\n");
        printf("Elija una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            gestionarBarrios();
            break;
        case 2:
            gestionarDelitos();
            break;
        case 3:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opcion invalida! Intente nuevamente.\n");
        }

    } while (opcion != 3);
}

int main() {
	mostrarPresentacion();
    menu();
    return 0;
}

