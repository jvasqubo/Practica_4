#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
#include <limits.h>


bool existeRouter(std::map<char, std::map<char, int>>& Red, char Router)
{
    return Red.find(Router) != Red.end();
}

void CrearRouter (std::map<char, std::map<char, int>>& Red, char Router)
{
    (Red)[Router][Router] = 0;
    for (auto& iterador : Red)
    {
        if (iterador.first != Router )
        {
            iterador.second[Router] = -1;
            (Red)[Router][iterador.first] = -1;
        }
    }
}

void CrearConexion (std::map<char, std::map<char, int>>& Red, char Router1, char Router2, int valor)
{
    (Red)[Router1][Router2] = valor;
    (Red)[Router2][Router1] = valor;
}

void EliminarRouter (std::map<char, std::map<char, int>>& Red, char Router)
{
    auto it = Red.find(Router);
    if (it != Red.end())
    {
        Red.erase(it);
    }
    for (auto& iterador : Red)
    {
        auto clave = iterador.second.find(Router);
        if (clave != iterador.second.end())
        {
            iterador.second.erase(clave);
        }
    }
}

void ImprimirRed (std::map<char, std::map<char, int>>& Red)
{
    for (auto& iterador_1 : Red)
    {
        for ( auto& iterador_2:iterador_1.second )
        {
            std::cout<<" \t"<<iterador_2.first<<"\t";
        }
        break;
    }
    std::cout<<std::endl;
    for (auto& iterador_1 : Red)
    {
        std::cout<<iterador_1.first<<"\t";
        for ( auto& iterador_2:iterador_1.second )
        {
            std::cout<<iterador_2.second<<"\t\t";
        }
        std::cout<<std::endl;
    }
}

void procesarArchivo(const std::string& nombreArchivo, std::map<char, std::map<char, int>>& Red)
{
    char Enrutador_1, Enrutador_2;
    int Costo;
    std::ifstream archivo(nombreArchivo);
    if (archivo.is_open())
    {
        std::string linea;
        while (std::getline(archivo, linea))
        {
            std::istringstream iss(linea);
            iss >> Enrutador_1 >> Enrutador_2 >> Costo;
            if (!existeRouter(Red,Enrutador_1))
            {
                CrearRouter(Red,Enrutador_1);
            }
            if (!existeRouter(Red,Enrutador_2))
            {
                CrearRouter(Red,Enrutador_2);
            }
            CrearConexion(Red,Enrutador_1,Enrutador_2,Costo);

        }
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo." << std::endl;
    }
}

void MenuRed()
{
    std::cout<<std::endl<<std::endl<<"\tMENU DE REDES"<<std::endl;
    std::cout<<"1. Eliminar conexion."<<std::endl;
    std::cout<<"2. Modificar conexion."<<std::endl;
    std::cout<<"3. Eliminar Router."<<std::endl;
    std::cout<<"4. Encontrar ruta optima."<<std::endl;
    std::cout<<"5. Valor ruta optima."<<std::endl;
    std::cout<<"6. Crear Router."<<std::endl;
    std::cout<<"7. Salir."<<std::endl<<std::endl<<std::endl;
    std::cout<<"Ingrese una opcion: ";
}

int generarNumeroAleatorio(int min, int max)
{
    int numero_aleatorio = rand() % 100 + 1;
    return numero_aleatorio;
}

void GenerarRedAleatoria (std::map<char, std::map<char, int>>& Red, int nodos, int probabilidad )
{
    int proba,costo,inicial = 65;
    char letra;
    for ( int i =0; i<nodos; i++)
    {
        letra=char(inicial);
        CrearRouter(Red,letra);
        inicial++;
    }
    for (auto& iterador_1 : Red)
    {
        for ( auto& iterador_2:iterador_1.second )
        {
            if (iterador_2.second != 0 )
            {
                proba = generarNumeroAleatorio(1,101);
                if (proba<=probabilidad)
                {
                    costo = (proba*100)/probabilidad;
                    CrearConexion(Red,iterador_1.first,iterador_2.first,costo);
                }
            }
        }
    }
}
char obtenerClaveMinima(const std::map<char, int>* Temporal)
{
    char claveMinima = '\0';
    int valorMinimo = INT_MAX;

    for (const auto& iterador : *Temporal) {
        if (iterador.second < valorMinimo) {
            claveMinima = iterador.first;
            valorMinimo = iterador.second;
        }
    }
    return claveMinima;
}

void ModificarRouter (std::map<char,bool>* Visitados, std::map<char,char>* Ruta,std::map<char,char>* RutaTemporal, std::map<char,int>* Temporal, std::map<char,int>* Permanente, char RouterActual, char RouterAnterior )
{
    (*Visitados)[RouterActual]=true;
    (*Ruta)[RouterActual]=(*RutaTemporal)[RouterActual];
    (*Permanente)[RouterActual]=(*Temporal)[RouterActual];
    Temporal->erase(RouterActual);
    RutaTemporal->erase(RouterActual);
}

void ImprimirTemporal (std::map<char,int>* Temporal)
{
    std::cout<<"Temporal: ";
    for (const auto& Iterador : *Temporal)
    {
        std::cout<<"( "<<Iterador.first<<", "<<Iterador.second<<" ),";
    }
    std::cout<<std::endl;
}

void ImprimirPermanente (std::map<char,int>* Permanente)
{
    std::cout<<"Permanente: ";
    for (const auto& Iterador : *Permanente)
    {
        std::cout<<"( "<<Iterador.first<<", "<<Iterador.second<<" ),";
    }
    std::cout<<std::endl;
}

void ImprimirRuta (std::map<char,char>* Ruta)
{
    std::cout<<"Ruta: ";
    for (const auto& Iterador : *Ruta)
    {
        std::cout<<"( "<<Iterador.first<<", "<<Iterador.second<<" ),";
    }
    std::cout<<std::endl;
}

void ImprimirVisitados (std::map<char,bool>* Visitados)
{
    std::cout<<"Visitados: ";
    for (const auto& Iterador : *Visitados)
    {
        std::cout<<"( "<<Iterador.first<<", "<<Iterador.second<<" ),";
    }
    std::cout<<std::endl;
}

void ImprimirRutaTemporal ( std::map<char,char>* RutaTemporal)
{
    std::cout<<"Ruta Temporal : ";
    for (const auto& Iterador : *RutaTemporal)
    {
        std::cout<<"( "<<Iterador.first<<", "<<Iterador.second<<" ),";
    }
    std::cout<<std::endl;
}

void Dijkstra (std::map<char, std::map<char, int>>& Red, char Router1, char Router2, bool condicion)
{
    std::map<char,bool>* Visitados = new std::map<char,bool>();
    std::map<char,char>* Ruta = new std::map<char,char>();
    std::map<char,char>* RutaTemporal = new std::map<char,char>();
    std::map<char,int>* Temporal = new std::map<char,int>();
    std::map<char,int>* Permanente = new std::map<char,int>();
    char RouterAct, RouterAnt;
    int CostoRuta;

    for (const auto& Iterador : Red[Router1])
    {
        char clave = Iterador.first;
        (*Visitados)[clave]=false;
        (*Ruta)[clave]=' ';
        (*RutaTemporal)[clave]=' ';
        (*Permanente)[clave]=0;
        (*Temporal)[clave]=INT_MAX;
    }

    (*Temporal)[Router1]=0;
    (*RutaTemporal)[Router1]=Router1;
    RouterAct = '\0';
    RouterAnt = obtenerClaveMinima(Temporal);
    while ((*Visitados)[Router2]==false)
    {
        RouterAct = obtenerClaveMinima(Temporal);
        ModificarRouter(Visitados,Ruta,RutaTemporal,Temporal,Permanente,RouterAct,RouterAnt);
        if (RouterAct == Router2) break;
        for (const auto& Iterador : Red[RouterAct])
        {
            char clave = Iterador.first;
            int valor = Iterador.second;
            if (valor>0 && clave != RouterAct && (*Visitados)[clave]==false)
            {
                CostoRuta = (*Permanente)[RouterAct] + valor;
                if (CostoRuta < (*Temporal)[clave])
                {
                    (*Temporal)[clave]=CostoRuta;
                    (*RutaTemporal)[clave]=RouterAct;
                }
            }
        }
        RouterAnt = RouterAct;
    }

    if (condicion == false)
    {
        std::cout<<"El costo minimo para llegar de "<<Router1<<" a "<<Router2<<" es de "<<(*Permanente)[Router2]<<std::endl;
    }
    else if (condicion == true)
    {
        std::cout<<"El ruta optima para llegar de "<<Router1<<" hasta "<<Router2<<" es: "<<std::endl;
        char ruta1, ruta2;
        ruta1 = Router2;
        ruta2 = (*Ruta)[ruta1];
        std::cout<<ruta1;
        while (ruta1 != ruta2)
        {
            std::cout<<"<-"<<ruta2;
            ruta1 = ruta2;
            ruta2 = (*Ruta)[ruta1];
        }
        std::cout<<std::endl;
    }
    delete Visitados;
    delete Ruta;
    delete RutaTemporal;
    delete Temporal;
    delete Permanente;
}
