#include <iostream>
#include <iomanip>

using namespace std;

struct Node
{
	int key, bf, height;
	Node *left, *right, *p;

};

void debug(string msg, bool active_debbuging=true)
{
	if(active_debbuging)
		cout << msg;
}


class AVL
{
  public:

    Node * root;  // korzeń drzewa
    int count;       // liczba węzłów

    AVL();
    ~AVL();
    Node * RotationRR(Node * A);
    Node * RotationLL(Node * A);
    Node * RotationRL(Node * A);
    Node * RotationLR(Node * A);
    bool   Insert(Node * n);
    Node * Pred(Node * x);
    Node * Search(int key);
    Node * Remove(Node * x);
    void      Preorder(Node * x);
    void      Inorder(Node * x);
    void      Postorder(Node * x);
    void      Walk(Node * x);
    void      CoutAVLcount();
};


// Konstruktor klasy AVL


AVL::AVL()
{
  root = NULL;
  count = 0;
}

// Destruktor klasy AVL

AVL::~AVL()
{
  while(root) delete(Remove(root));
}


// Rotacja RR

Node * AVL::RotationRR(Node * A)
{
	Node * B = A->right, * P = A->p;

	  A->right = B->left;
	  if(A->right) A->right->p = A;
	  B->left = A;
	  B->p = P;
	  A->p = B;
	  if(P)
	  {
	    if(P->left == A) P->left = B;
	    else P->right = B;
	  }
	  else root = B;

	  if(B->bf == -1)
	  {
	    A->bf = B->bf = 0;
	  }
	  else
	  {
	    A->bf = -1; B->bf = 1;
	  }
	  return B;
	}

// Rotacja LL

Node * AVL::RotationLL(Node * A)
{
	Node * B = A->left, * P = A->p;

	  A->left = B->right;
	  if(A->left) A->left->p = A;
	  B->right = A;
	  B->p = P;
	  A->p = B;
	  if(P)
	  {
	    if(P->left == A) P->left = B;
	    else P->right = B;
	  }
	  else root = B;

	  if(B->bf == 1)
	  {
	    A->bf = B->bf = 0;
	  }
	  else
	  {
	    A->bf = 1; B->bf = -1;
	  }

	  return B;
	}

// Rotacja RL

Node * AVL::RotationRL(Node * A)
{
	Node * B = A->right, * C = B->left, * P = A->p;

	  B->left = C->right;
	  if(B->left) B->left->p = B;
	  A->right = C->left;
	  if(A->right) A->right->p = A;
	  C->left = A;
	  C->right = B;
	  A->p = B->p = C;
	  C->p = P;
	  if(P)
	  {
	    if(P->left == A) P->left = C;
	    else P->right = C;
	  }
	  else root = C;

	  A->bf = (C->bf == -1) ?  1 : 0;
	  B->bf = (C->bf ==  1) ? -1 : 0;
	  C->bf = 0;

	  return C;
	}

// Rotacja LR

Node * AVL::RotationLR(Node * A)
{
	Node * B = A->left, * C = B->right, * P = A->p;

	  B->right = C->left;
	  if(B->right) B->right->p = B;
	  A->left = C->right;
	  if(A->left) A->left->p = A;
	  C->right = A;
	  C->left = B;
	  A->p = B->p = C;
	  C->p = P;
	  if(P)
	  {
	    if(P->left == A) P->left = C;
	    else P->right = C;
	  }
	  else root = C;

	  A->bf = (C->bf ==  1) ? -1 : 0;
	  B->bf = (C->bf == -1) ?  1 : 0;
	  C->bf = 0;

	  return C;
	}

// Wstawia element do drzewa

bool AVL::Insert(Node * n)
{
  Node * x = root, * y, * z;

  y = n->left = n->right = NULL;
  n->bf = 0;

  while(x)
  {
    if(x->key == n->key)
    {
      delete n;
      return false;
    }
    y = x;
    x = (n->key < x->key) ? x->left : x->right;
  }

  count++;

  if(!(n->p = y))
  {
    root = n;
    return true;
  }
  if(n->key < y->key) y->left = n;
  else y->right = n;
  if(y->bf)
  {
    y->bf = 0;
    return true;
  }
  y->bf = (y->left == n) ? 1 : -1;
  z = y->p;
  while(z)
  {
    if(z->bf) break;
    z->bf = (z->left == y) ? 1 : -1;
    y = z; z = z->p;
  }

  if(!z) return true;

  if(z->bf == 1)
  {
    if(z->right == y)
    {
      z->bf = 0;
      return true;
    }
    if(y->bf == -1) RotationLR(z);
    else RotationLL(z);
    return true;
  }
  else
  {
    if(z->left == y)
    {
      z->bf = 0;
      return true;
    }
    if(y->bf == 1) RotationRL(z);
    else RotationRR(z);
    return true;
  }
}
// Zwraca wezel poprzednika

Node * AVL::Pred(Node * x)
{

  if(x->left)
  {
	  while(x->right) x = x->right;  // zwraca wezel z maksymalnym kluczem
	  return x;
  }

  Node * y;

  do
  {
    y = x;
    x = x->p;
  } while(x && (x->right != y));

  return x;
}

// Usuwa element z drzewa

Node * AVL::Remove(Node * x)
{
Node * t, * y, * z;
  bool nest;
  if((x->left) && (x->right))
  {
    y = Remove(Pred(x));

    count++;

    nest = false;


  }
  else
  {
    if(x->left)
    {
      y = x->left; x->left = NULL;
    }
    else
    {
      y = x->right; x->right = NULL;
    }
    x->bf = 0;
    nest = true;
  }

  if(y)
  {
    y->p = x->p;
    if(y->left  = x->left)  y->left->p  = y;
    if(y->right = x->right) y->right->p = y;
    y->bf = x->bf;
  }

  if(x->p)
  {
    if(x->p->left == x) x->p->left = y; else x->p->right = y;
  }
  else root = y;

  if(nest)
  {
    z = y;
    y = x->p;
    while(y)
    {
      if(!(y->bf))
      {


        y->bf = (y->left == z) ? -1 : 1;
        break;
      }
      else
      {
        if(((y->bf ==  1) && (y->left  == z)) || ((y->bf == -1) && (y->right == z)))
        {


          y->bf = 0;
          z = y; y = y->p;
        }
        else
        {
          t = (y->left == z) ? y->right : y->left;
          if(!(t->bf))
          {


            if(y->bf == 1) RotationLL(y); else RotationRR(y);
            break;
          }
          else if(y->bf == t->bf)
          {


            if(y->bf == 1) RotationLL(y); else RotationRR(y);
            z = t; y = t->p;
          }
          else
          {


            if(y->bf == 1) RotationLR(y); else RotationRL(y);
            z = y->p; y = z->p;
          }
        }
      }
    }
  }
  count--;
  return x;
}


void AVL::Preorder(Node * x)
{
  if(x)
  {
    cout << x->key << endl;  // tutaj przetwarzamy bieżący węzeł
    Preorder(x->left);
    Preorder(x->right);
  }
}


void AVL::Inorder(Node * x)
{
  if(x)
  {
    Inorder(x->left);
    cout << x->key << endl;  // tutaj przetwarzamy bieżący węzeł
    Inorder(x->right);
  }
}


void AVL::Postorder(Node * x)
{
  if(x)
  {
    Postorder(x->left);
    Postorder(x->right);
    cout << x->key << endl;  // tutaj przetwarzamy bieżący węzeł
  }
}


// Wyszukuje element
//-------------------------------------

Node * AVL::Search(int key)
{
  Node * x = root;

  while((x) && (x->key != key))
    x = (key < x->key) ? x->left : x->right;

  return x;
}

// Wypisuje informacje o wezlach
//---------------------------------------------------

void AVL::Walk(Node * x)
{
  cout << x->key << " : bf = " << setw(2) << x->bf << " : Left Child = ";
  if(x->left) cout << setw(3) << x->left->key;
  else        cout << "NIL";
  cout << ", Right Child = ";
  if(x->right) cout << setw(3) << x->right->key;
  else         cout << "NIL";
  cout << " : Parent = ";
  if(x->p) cout << setw(3) << x->p->key;
  else     cout << "NIL";
  cout << endl;
  if(x->left)  Walk(x->left);
  if(x->right) Walk(x->right);
}



// Wypisuje do cout liczbę węzłów drzewa AVL
//------------------------------------------

void AVL::CoutAVLcount()
{
  cout << "\nLiczba wezlow drzewa AVL : " << count << endl << endl;
}


// Dodaje nowe węzły
//--------------------------------

void Add(AVL * T)
{
  cout << "Dodawanie nowych wezlow do drzewa AVL\n"
          "-------------------------------------\n\n";
  T->CoutAVLcount();
  cout << "Podaj liczbe wezlow do utworzenia, a nastepnie wprowadz odpowiednia\n"
          "liczbe kluczy nowych wezlow.\n\n";

  int i,n;

  Node * x;

  cin >> n;
  for(i = 0; i < n; i++)
  {
    x = new Node;
    cin >> x->key;
    T->Insert(x);
  }

  cout << endl;
  T->Walk(T->root);
  T->CoutAVLcount();
}

// Usuwa węzeł
//-----------------------------

void Del(AVL * T)
{
  cout << "Usuwanie wezla drzewa AVL o zadanym kluczu\n"
          "------------------------------------------\n\n";
  T->CoutAVLcount();

  Node * x;
  int key;

  cout << "Podaj klucz usuwanego wezla : "; cin >> key;

  x = T->Search(key);

  if(x)
  {
    delete T->Remove(x);
    cout << endl;
    if(T->root) T->Walk(T->root);
    T->CoutAVLcount();
  }
  else cout << "\nBrak wezla o takim kluczu\n";
}


void Preorder(AVL * T)
{
  cout << "Przechodzenie drzewa AVL algorytmem preorder\n"
          "--------------------------------------------\n\n";
  T->Preorder(T->root);
}


void Inorder(AVL * T)
{
  cout << "Przechodzenie drzewa AVL algorytmem inorder\n"
          "-------------------------------------------\n\n";
  T->Inorder(T->root);
}


void Postorder(AVL * T)
{
  cout << "Przechodzenie drzewa AVL algorytmem postorder\n"
          "---------------------------------------------\n\n";
  T->Postorder(T->root);
}

int main()
{
	AVL * T = new AVL();
	  int choice;

	  do
	  {
	    system("cls");

	    cout << "Test funkcji obslugi drzew AVL\n"
	            "==============================\n\n"
	            "Wybor Funkcja\n"
	            "-------------\n"
	    		" [0]  Koniec\n"
	    		" [1]  Dodaj wezly\n"
	    		" [2]  Usun wezel\n"
	            " [3]  Preorder\n"
	            " [4]  Inorder\n"
	            " [5]  Postorder\n"
	            "--------------\n"
	            "Twoj wybor : ";

	    cin >> choice;

	    system("cls");

	    switch(choice)
	    {
	      case 1 : Add(T);       break;
	      case 2 : Del(T);       break;
	      case 3 : Preorder(T);  break;
	      case 4 : Inorder(T);   break;
	      case 5 : Postorder(T); break;
	    }

	    if((choice >= 1) && (choice <= 5))
	    {
	      cout << endl;
	      system("pause");
	    }

	  } while(choice);

	  delete T;
	}

