#include "Funciones.h"
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));
    int opcion_1, opcion_2, valor;
    char router_1, router_2;
    std::map<char, std::map<char, int>>* Red = new std::map<char, std::map<char, int>>();
    cout<<"\tMENU PRINCIAL"<<endl<<endl<<"1. Generar red aleatoria."<<endl<<"2. Cargar red."<<endl<<endl<<"Ingrese una opcion: ";
    cin>>opcion_1;
    if (opcion_1 == 1)
    {
        int nodos, probabilidad;
        cout<<"Ingrese el numero de enrutadores: ";
        cin>>nodos;
        cout<<"Ingrese la probabilidad de conexion (en una escala de 0 a 100 ): ";
        cin>>probabilidad;
        cout<<endl<<endl;
        GenerarRedAleatoria(*Red,nodos,probabilidad);
        ImprimirRed(*Red);
    }
    else if (opcion_1 == 2)
    {
        std::string nombreArchivo;
        cout<<"Ingrese el nombre del archivo: ";
        cin>>nombreArchivo;
        cout<<endl<<endl;
        procesarArchivo(nombreArchivo,*Red);
        ImprimirRed(*Red);        
    }
    opcion_2 = 0;
    while(opcion_2!=7)
    {
        MenuRed();
        cin>>opcion_2;
        if (opcion_2 == 1)
        {
            cout<<"Ingrese el router 1: ";
            cin>>router_1;
            cout<<"Ingrese el router 2: ";
            cin>>router_2;
            CrearConexion(*Red,router_1, router_2,-1);
            ImprimirRed(*Red);
        }
        else if (opcion_2 == 2)
        {
            cout<<"Ingrese el router 1: ";
            cin>>router_1;
            cout<<"Ingrese el router 2: ";
            cin>>router_2;
            cout<<"Ingrese el valor: ";
            cin>>valor;
            CrearConexion(*Red,router_1, router_2,valor);
            ImprimirRed(*Red);
        }
        else if (opcion_2 == 3)
        {
            cout<<"Ingrese el router que desea eliminar: ";
            cin>>router_1;
            EliminarRouter(*Red,router_1);
            ImprimirRed(*Red);
        }
        else if (opcion_2 == 4)
        {
            cout<<"Ingrese el router 1: ";
            cin>>router_1;
            cout<<"Ingrese el router 2: ";
            cin>>router_2;
            Dijkstra(*Red,router_1,router_2, true);
            ImprimirRed(*Red);
        }
        else if (opcion_2 == 5)
        {
            cout<<"Ingrese el router 1: ";
            cin>>router_1;
            cout<<"Ingrese el router 2: ";
            cin>>router_2;
            Dijkstra(*Red,router_1,router_2, false);
            ImprimirRed(*Red);
        }
        else if (opcion_2 == 6)
        {
            cout<<"Ingrese el nombre del router: ";
            cin>>router_1;
            CrearRouter(*Red,router_1);
            ImprimirRed(*Red);
        }
    }
    return 0;
}
