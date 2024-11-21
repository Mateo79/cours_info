// Smart Pointer
// Compilation: g++ -o SmartPointer SmartPointer.cpp -Wall

#include <iostream>
#include <cstdlib>

template <typename T> class SmartPointer;

// class CompteurSP
template <typename T> class CompteurSP {
private:
	friend class SmartPointer <T>;
	T *pObjet;
	unsigned int nbReference;

	CompteurSP(T *);
	~CompteurSP();
	void ajouterReference();
	void supprimerReference();
};

template <typename T> CompteurSP<T>::CompteurSP(T *p)
: pObjet(p), nbReference(1)
{
}

template <typename T> CompteurSP<T>::~CompteurSP(){
	std::cout << "suppression compteur" << std::endl;
	delete pObjet;
}

template <typename T> void CompteurSP<T>::ajouterReference(){
	nbReference++;
}

template <typename T> void CompteurSP<T>::supprimerReference(){
	nbReference--;
	if(nbReference == 0) delete this;
}

// class SmartPointer
template <typename T> class SmartPointer {
private:
	CompteurSP <T> * compteur;
public:
	SmartPointer (T *);
	SmartPointer (const SmartPointer &);
	~SmartPointer ();
	SmartPointer <T> & operator = (const SmartPointer &);
	T & operator * ();
	T * operator -> ();
};

template <typename T> SmartPointer<T>::SmartPointer(T *p)
:compteur(NULL)
{
	if (p) compteur = new CompteurSP <T> (p);
}

template <typename T> SmartPointer<T>::SmartPointer(const SmartPointer &s):
compteur(s.compteur){
	if (compteur) compteur->ajouterReference();
}

template <typename T> SmartPointer<T>::~SmartPointer()
{
	if (compteur) compteur->supprimerReference();
}

template <typename T> SmartPointer<T> & SmartPointer<T>::operator = (const SmartPointer &s){
	if(this == &s) return * this; //autoréférence 
	if (compteur != s.compteur){
		compteur = s.compteur;
		if (compteur) compteur->ajouterReference();
	}
	return * this;
}

template <typename T> T & SmartPointer<T>::operator * (){
	return *(compteur->pObjet);
}

template <typename T> T* SmartPointer<T>::operator -> (){
	return compteur->pObjet;
}

struct Point{
	int x,y;
};

using namespace std;

int main()
{
	SmartPointer <int> p1(new int (1));
	SmartPointer <int> p2(new int (2));
	SmartPointer <int> p3(NULL);
	SmartPointer <Point> p4(new Point);
	cout << "valeur: " << *p1 << endl;
	cout << "valeur: " << *p2 << endl;
	p1 = p2;
	cout << "valeur: " << *p1 << endl;
	p4->x=6;
	p4->y=7;
	cout << "valeur: " << p4->x << endl;
	cout << "fin" << endl;

	return EXIT_SUCCESS;
}
