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

        Usuario& devolverLibro(Libro* x, string fecha)
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
};

class Biblioteca
{
    private:
        vector <Libro> libros;

    public:
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
                    cout << "Se realizo el prestamo de "<<x.getTitulo();
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
};


int main()
{   
    Libro libro1("Harry Potter I",12345,2001,"J.K Rowling",8);
    Libro libro2("Harry Potter II",54321,2006,"J.K Rowling",1);
    Libro libro3("Bazar de los malos sueños",12345,2001,"Stephen King",0);

    Usuario usuario1("Jose","La Arboleda 507",945876334);
    Biblioteca biblio1;

    biblio1.agregarLibros(libro1).agregarLibros(libro2).agregarLibros(libro3).StockLibros();

    return 0;
}
