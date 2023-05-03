#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Libro
{
    private:
        string titulo;
        int isbn;
        int publicationyear;
        string autor;
        int stock;

    public:
        Libro() : titulo(" "), isbn(0), publicationyear(0), autor(" "), stock(0) {}
        Libro(string titulo, int isbn, int publicationyear, string autor, int stock)
        {
            this->titulo = titulo;
            this->isbn = isbn;
            this->publicationyear = publicationyear;
            this->autor = autor;
            this->stock = stock;
        }

        void setStock(int newStock)
        {
            stock = newStock;
        }

        int getStock() const
        {
            return stock;
        }

        string getTitulo() const
        {
            return titulo;
        }

        string getAutor() const
        {
            return autor;
        }
    ~Libro(){
        cout<<"Ejecutando destructor..."<<endl;
    }

};

class Usuario
{
    private:
        string nombre;
        string direccion;
        int telefono;
        vector <Libro*> librosPrestados;
        
    public:
        Usuario(string nombre, string direccion, int telefono)
        {
            this->nombre = nombre;
            this->direccion = direccion;
            this->telefono = telefono;
        }

        Usuario& devolverLibro(Libro* x)
        {
            for(int i=0;i < librosPrestados.size(); i++)
            {
                if(librosPrestados[i]->getTitulo() == x->getTitulo())
                {
                    x->setStock(x->getStock()+1);
                    librosPrestados.erase(librosPrestados.begin() + i);
                    break;
                }
                else
                    cout<<"No tienes este libro en prestamo"<<endl;
            }
            return *this;
        }

        void verLibrosEnPrestamo() const
        {
            cout << "Libros que tienes en prestamo: " << endl;
            for(int i=0;i<librosPrestados.size();i++)
            {
                cout<<librosPrestados[i]->getTitulo()<<endl;
            }
        }
        
        void appendLibro(Libro* x)
        {
            librosPrestados.push_back(x);
        }

        Usuario& mostrarlibrosprestamo() 
        {
            cout << "Libros Disponibles: " << endl; 
            for(int i=0; i < librosPrestados.size(); i++)
            {
                cout << "Titulo: " << librosPrestados[i]->getTitulo() << endl;
                cout << "Stock: "<< librosPrestados[i]->getStock() << endl;
                cout << "-----------------------------------" << endl << endl;
            }

            return *this;
        }
        ~Usuario(){
        cout<<"Ejecutando destructor..."<<endl;}
};

class Biblioteca
{

    public:
        vector <Libro> libros;
        Biblioteca() : libros(vector<Libro>()) {}
        Biblioteca& agregarLibros(const Libro& x)
        {
            libros.push_back(x);
            return *this;
        }

        Biblioteca& prestarLibro(Libro& x, Usuario& y)
        {   
            if(x.getStock() > 0)
            {   
                    x.setStock(x.getStock()-1);
                    y.appendLibro(&x);
                    cout << "Se realizo el prestamo de "<<x.getTitulo() <<endl;
            }
            else 
                cout << "No tenemos mas unidades de:" <<x.getTitulo()<<endl;
            return *this;
        }

        Biblioteca& StockLibros() 
        {
            cout << "Libros Disponibles: " << endl; 
            for(int i=0; i < libros.size(); i++)
            {
                cout << "Titulo: " << libros[i].getTitulo() << endl;
                cout << "Stock: "<< libros[i].getStock() << endl;
                cout << "-----------------------------------" << endl << endl;
            }
            return *this;
        }
        ~Biblioteca(){
        cout<<"Ejecutando destructor..."<<endl;}
    

};

int main()
{   
    Libro libros[3] = {{"Harry Potter I",12345,2001,"J.K Rowling",8},
                       {"Harry Potter II",54321,2006,"J.K Rowling",1},
                       {"Bazar de los malos sueños",67890,2015,"Stephen King",0}};

    Usuario usuario1("Jose","La Arboleda 507",945876334);
    Biblioteca biblio1;

    for (int i = 0; i < 3; i++) {
        biblio1.agregarLibros(libros[i]);
    }

    int opcion;
    do {
        cout << "Seleccione una opcion: " << endl;
        cout << "1. Ver libros disponibles" << endl;
        cout << "2. Prestar libro" << endl;
        cout << "3. Devolver libro" << endl;
        cout << "4. Ver libros en prestamo" << endl;
        cout << "0. Salir" << endl;
        cin >> opcion;

        switch(opcion)
        {
            case 1:
                biblio1.StockLibros();
                break;
            case 2:
            {
                int pos;
                cout << "Ingrese la posicion del libro que desea prestar: " << endl;
                cin >> pos;
                if (pos >= 0 && pos < 3) {
                    biblio1.prestarLibro(libros[pos], usuario1);
                } else {
                    cout << "Posicion invalida" << endl;
                }
                break;
            }
            case 3:
            {
                int pos;
                cout << "Ingrese la posicion del libro que desea devolver: " << endl;
                cin >> pos;
                if (pos >= 0 && pos < 3) {
                    usuario1.devolverLibro(&libros[pos]);
                } else {
                    cout << "Posicion invalida" << endl;
                }
                break;
            }
            case 4:
            {
                usuario1.verLibrosEnPrestamo();
                break;
            }
            case 0:
            {
                cout << "Adios!" << endl;
                break;
            }
            default:
            {
                cout << "Opcion invalida" << endl;
                break;
            }
        }
    } while(opcion != 0);

    return 0;
}
