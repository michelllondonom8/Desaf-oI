#include <iostream>
#include <fstream>

using namespace std;

void leerArchivo(const char* nombreArchivo) {
    ifstream fin(nombreArchivo);

    if (!fin) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    cout << "Se abrio el archivo correctamente" <<endl;

    fin.close();
}

int main()
{
    leerArchivo("pista1.txt");
    return 0;
}
