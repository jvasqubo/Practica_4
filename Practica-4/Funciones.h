
#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

bool existeRouter(const std::map<char, std::map<char, int>>& mapa, char clave1);
void CrearRouter (std::map<char, std::map<char, int>>& Red, char Router);
void procesarArchivo(const std::string& nombreArchivo, std::map<char, std::map<char, int>>& mapa);
void CrearConexion (std::map<char, std::map<char, int>>& Red, char Router1, char Router2, int valor);
void EliminarRouter (std::map<char, std::map<char, int>>& Red, char Router);
void ImprimirRed (std::map<char, std::map<char, int>>& Red);
void MenuRed();
int generarNumeroAleatorio(int min, int max);
void GenerarRedAleatoria (std::map<char, std::map<char, int>>& Red, int nodos, int probabilidad );
char obtenerClaveMinima(const std::map<char, int>* Temporal);
void ModificarRouter (std::map<char,bool>* Visitados, std::map<char,char>* Ruta,std::map<char,char>* RutaTemporal, std::map<char,int>* Temporal, std::map<char,int>* Permanente, char RouterActual, char RouterAnterior );
void ImprimirTemporal (std::map<char,int>* Temporal);
void ImprimirPermanente (std::map<char,int>* Permanente);
void ImprimirRuta (std::map<char,char>* Ruta);
void ImprimirVisitados (std::map<char,bool>* Visitados);
void ImprimirRutaTemporal ( std::map<char,char>* RutaTemporal);
void Dijkstra (std::map<char, std::map<char, int>>& Red, char Router1, char Router2, bool condicion);

#endif // FUNCIONES_H
