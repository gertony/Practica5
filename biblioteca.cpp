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

        int getStock()
        {
            return stock;
        }

        string getTitulo()
        {
            return titulo;
        }

        string getAutor()
        {
            return autor;
        }

};

class Autor
{
    private:
        string nombre;
        string nacionalidad;
        vector <Libro> librosEscritos;

    public:
        Autor(string nombre, string nacionalidad)
        {
            this->nombre = nombre;
            this->nacionalidad = nacionalidad;
        }

        void identificarLibros(vector <Libro> x, int tamaño)
        {   
            for(int i=0; i<tamaño; i++ )
            {
                if(x[i].getAutor() == nombre)
                {
                    librosEscritos.push_back(lista[i]);
                    cout << "El libro " << lista[i].getTitulo() << " es de autoria de " << nombre << endl;
                }
            }
        }
};

class Usuario
{
    private:
        string nombre;
        string direccion;
        int telefono;
        vector <Libro> librosPrestados;
        
    public:
        Usuario(string nombre, string direccion, int telefono)
        {
            this->nombre = nombre;
            this->direccion = direccion;
            this->telefono = telefono;
        }

        void devolverLibro(Libro* x, string fecha)
        {
            for(int  i=0;i < librosPrestados.size(); i++)
            {
                if(librosPrestados[i].getTitulo() == x->getTitulo())
                {
                    x->setStock(x->getStock()+1);
                    librosPrestados.erase(librosPrestados.begin() + i);
                    break;
                }
                else
                    cout<<"No tienes este libro en prestamo";
            }
        }

        void verLibrosEnPrestamo()
        {
            cout << "Libros que tienes en prestamo: " << endl;
            for(int i=0;i<librosPrestados.size();i++)
            {
                cout<<librosPrestados[i].getTitulo()<<endl;
            }
        }

        vector <Libro> getLibroPrestados()
        {
            return librosPrestados;
        }
        
        void appendLibro(Libro x)
        {
            librosPrestados.push_back(x);
        }
};

class Biblioteca
{
    private:
        vector <Libro> libros;

    public:
        void agregarLibros(Libro libros_[], int tamaño)
        {
            for(int i=0; i<tamaño; i++)
            {
                libros.push_back(libros_[i]);
            }
        }

        void prestarLibro(Libro* x, Usuario* y,string fecha)
        {   
            if(x->getStock() > 0)
            {   
                    x->setStock(x->getStock()-1);
                    y->appendLibro(*x);
                    cout << "Se realizo el prestamo de "<<x->getTitulo()<<" el: "<<fecha<<endl;
            }
            else 
                cout << "No tenemos mas unidades de:" <<x->getTitulo()<<endl;
        }
};

int main()
{   
    Libro libros[3] = {
        Libro("Harry Potter I",12345,2001,"J.K Rowling",8),
        Libro("Harry Potter II",54321,2006,"J.K Rowling",1),
        Libro("Bazar de los malos sueños",12345,2001,"Stephen King",0)
    };

    Autor autores[2] = {
        Autor("J.K Rowling","Britanica"),
        Autor("Stephen King","Estadounidense")
    };

    Usuario usuario1("Jose","La Arboleda 507",945876334);
    Biblioteca biblio1;

    biblio1.agregarLibros(libros,3);
    autores[0].identificarLibros(libros, 3);
    autores[1].identificarLibros(libros, 3);
    cout << libros[0].getStock() << endl;
    biblio1.prestarLibro(&libros[0],&usuario1, "16/04/2023");
    biblio1.prestarLibro(&libros[2],&usuario1, "16/04/2023");
     usuario1.verLibrosEnPrestamo();
    cout << libros[0].getStock() << endl;
    usuario1.devolverLibro(&libros[0],"17/04/2023");
    cout << libros[0].getStock() << endl;
    usuario1.verLibrosEnPrestamo();
    return 0;  
}
