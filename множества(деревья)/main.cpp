#include <iostream>
#include <stdlib.h>
#include <assert.h>

template <class Atype>
struct node {
    Atype info;
    struct node *left, *right, *parent;
};

class rational {
public:
    rational(int n = 0, int d = 1) : num(n), denom(d) {
        assert(d > 0);
        int x = nod(abs(num), abs(denom));
        
        num /= x;
        denom /= x;
    }
    
    rational(double d) : num(d * 1000), denom(1000){
        int x = nod(abs(num), abs(denom));
        
        num /= x;
        denom /= x;
    }
    int operator <(const rational &x) const;
    int operator >(const rational &x) const;
    int operator ==(const rational &x);
    int operator !=(const rational &x);
    friend std::ostream &operator <<(std::ostream &out, const rational &x);
private:
    int num, denom;
    int nod(int n, int d);
};

int rational::operator <(const rational &x) const{
    return num * x.denom < x.num * denom;
}

int rational::operator >(const rational &x) const{
    return (x < *this);
}

int rational::operator ==(const rational &x) {
    return num * x.denom == x.num * denom;
}

int rational::operator !=(const rational &x) {
    return !(*this == x);
}

int rational::nod(int n, int d) {
    int t;
    while (d != 0) {
        t = n % d;
        n = d;
        d = t;
    }
    
    return n;
}

std::ostream &operator <<(std::ostream &out, const rational &x) {
    out << x.num << "/" << x.denom << " ";
    
    return out;
}

template <class Atype>
class multiplicity {
public:
    multiplicity<Atype>() { root = 0; }
    multiplicity<Atype>(const multiplicity<Atype> &sec);                                     // копирующий конструктор
    ~multiplicity<Atype>() { root = DeleteTree(root); }                                      // деструктор
    multiplicity<Atype> operator + (const multiplicity<Atype> &a);                           // объединение
    multiplicity<Atype> operator ^ (const multiplicity<Atype> &a);                           // пересечение
    multiplicity<Atype> operator - (const multiplicity<Atype> &a);                           // разность
    multiplicity<Atype> operator & (const multiplicity<Atype> &a);                           // симметричная разность
    multiplicity<Atype> operator + (Atype x);                                                // добавить значение в конец
    friend multiplicity<Atype> operator + (Atype x, multiplicity<Atype> &a);                 // добавить значение в начало
    multiplicity<Atype> operator - (Atype x);                                                // удалить значение
    multiplicity<Atype> &operator -- ();                                                     // префикс (удаление первого)
    multiplicity<Atype> &operator -- (int x);                                                // постфикс (удаление последнего)
    int operator < (const multiplicity<Atype> &a) const;                                     // подмножество
    friend int operator < (Atype x, multiplicity<Atype> &a) { return a.IncElem(x, a.root); } // принадлежность элемента к множеству
    int operator == (const multiplicity<Atype> &a) const;                                    // эквивалентность
    //operator int () const;                                                                 // мощность множества
    multiplicity<Atype> &operator = (const multiplicity<Atype> &a);                          // присвоить
    multiplicity<Atype> &operator += (const multiplicity<Atype> &a);                         // + присвоить множество
    multiplicity<Atype> &operator += (Atype x);                                              // + присвоить Atype
    multiplicity<Atype> &operator -= (const multiplicity<Atype> &a);                         // - вычесть
    multiplicity<Atype> &operator -= (Atype x);                                              // - вычесть Atype
    multiplicity<Atype> &operator &= (const multiplicity<Atype> &a);                         // & присвоить
    multiplicity<Atype> &operator ^= (const multiplicity<Atype> &a);                         // ^ присвоить
    friend std::ostream &operator << (std::ostream &out, const multiplicity<Atype> &a) {
        a.LeftPrn(a.root);
        std::cout << std::endl;
        
        return out;
    }
    
private:
    node<Atype> *root;
    node<Atype> *Insert(node<Atype> *root, node<Atype> *par, Atype v); // добавить элемент в дерево
    void LeftPrn(node<Atype> *root) const;                             // проход левый
    void UpDownPrn(node<Atype> *root) const;                           // проход сверху вниз
    void DownUpPrn(node<Atype> *root) const;                           // проход снизу вверх
    node<Atype> *Search(node<Atype> *root, Atype x) const;             // поиск элемента дерева со значением x, возвращает node
    node<Atype> *DeleteTree(node<Atype> *root);                        // удалить дерево
    void Child1(node<Atype> *x);                                       // удаление элемента с одним или 0 потомков
    node<Atype> *SearchMin(node<Atype> *root) const;                   // поиск минимального значения в правом поддереве
    node<Atype> *SearchMax(node<Atype> *root) const;                   // поиск максимального значения в правом поддереве
    void RemoveLeft(node<Atype> **root);                               // удаление корня, когда потомок есть только слева
    void RemoveRight(node<Atype> **root);                              // удаление корня, когда потомок есть только справа
    int RootRemoving(node<Atype> **root);                              // удаление корня, возвращает 1, если удаление совершено, 0 если ничего не изменилось
    node<Atype> *Removing(node<Atype> *r, Atype k);                    // удаление значения из дерева
    node<Atype> *CopyTree(node<Atype> *a, node<Atype> *b);             // скопировать a в b
    int Emptiness(node<Atype> *root) const;                            // пустота
    int Quantitiy(node<Atype> *root, int x) const;                     // кол-во элементов в списке
    node<Atype> *Unite(node<Atype> *a, node<Atype> *const b);          // объединить деревья
    node<Atype> *Crossing(node<Atype> *a, node<Atype> *const b);       // пересечение списков
    node<Atype> *Difference(node<Atype> *a, node<Atype> *const b);     // разность
    node<Atype> *DiffSymm(node<Atype> *a, node<Atype> *const b);       // разность симметричная
    int IncElem(Atype i, node<Atype> *a) const;                        // включен ли элемент в список
    int IncList(node<Atype> *a, node<Atype> *b, int x) const;          // включен ли список в другой список
    int Equi(node<Atype> *const a, node<Atype> *const b) const;        // равенство списков
};

/* ----------------------------- МЕТОДЫ РАБОТЫ С ДЕРЕВОМ START ----------------------------- */

template<class Atype>
node<Atype> *multiplicity<Atype>::Insert(node<Atype> *root, node<Atype> *par, Atype v) { // добавить элемент в дерево, возврщает элемент на корень
    if (root == NULL) {
        root = new node<Atype>;
        root->info = v;
        root->left = root->right = 0;
        root->parent = par;
        
        return root;
    }
    
    if (root->info > v)
        root->left = Insert(root->left, root, v);
    else
        if (root->info < v)
            root->right = Insert(root->right, root, v);
    
    return root;
}

template<class Atype>
void multiplicity<Atype>::LeftPrn(node<Atype> *root) const { // проход левый
    if (root != NULL) {
        LeftPrn(root->left);
        std::cout << root->info << " ";
        LeftPrn(root->right);
    }
}

template<class Atype>
void multiplicity<Atype>::UpDownPrn(node<Atype> *root) const { // проход сверху вниз
    if (root != NULL) {
        std::cout << root->info;
        UpDownPrn(root->left);
        UpDownPrn(root->right);
    }
}

template<class Atype>
void multiplicity<Atype>::DownUpPrn(node<Atype> *root) const { // проход снизу вверх
    if (root != NULL) {
        DownUpPrn(root->left);
        DownUpPrn(root->right);
        std::cout << root->info;
    }
}

template<class Atype>
node<Atype> *multiplicity<Atype>::Search(node<Atype> *root, Atype x) const { // поиск элемента дерева со значением x, возвращает *node
    if (root == NULL || x == root->info)
        return root;
    if (x < root->info)
        return Search(root->left, x);
    else
        return Search(root->right, x);
}

template<class Atype>
node<Atype> *multiplicity<Atype>::DeleteTree(node<Atype> *root) { // удалить дерево, возращает NULL
    if (root != NULL) {
        DeleteTree(root->left);
        DeleteTree(root->right);
        delete root;
    }
    
    return NULL;
}

template<class Atype>
void multiplicity<Atype>::Child1(node<Atype> *x) { // удаление элемента с одним или 0 потомков
    node<Atype> *par = x->parent;
    
    /* 0 потомков */
    if (x->right == NULL && x->left == NULL) {
        if (par->left != NULL)
            (par->left->info == x->info) ? (par->left = NULL) : (par->right = NULL);
        else
            (par->right->info == x->info) ? (par->right = NULL) : (par->left = NULL);
        
        delete x;
        return;
    }
    
    /* 1 потомок */
    if (par->right && par->right->info == x->info) { // смотрим с какой стороны от родителя удаляемое (в данном случае справа)
        if (x->right) { // проверяем с какой стороны от удаляемого его потомок (в данном случае справа)
            par->right = x->right;
            par->right->parent = par;
        }
        else { // потомок удаляемого слева
            par->right = x->left;
            par->right->parent = par;
        }
    }
    
    else { // удаляемое слева от родителя
        if (x->right) { // проверяем с какой стороны от удаляемого его потомок (в данном случае справа)
            par->left = x->right;
            par->left->parent = par;
        }
        else { // потомок удаляемого слева
            par->left = x->left;
            par->left->parent = par;
        }
    }
    
    delete x;
}

template<class Atype>
node<Atype> *multiplicity<Atype>::SearchMin(node<Atype> *root) const { // поиск минимального значения в правом поддереве, возращает указатель на минимальный node
    if (root->left == NULL)
        return root;
    return SearchMin(root->left);
}

template<class Atype>
node<Atype> *multiplicity<Atype>::SearchMax(node<Atype> *root) const { // поиск максимального значения, возвращает указатель на максимальный node
    if (root->right == NULL)
        return root;
    return SearchMax(root->right);
}

template<class Atype>
void multiplicity<Atype>::RemoveLeft(node<Atype> **root) { // удаление корня, когда потомок есть только слева
    struct node<Atype> *temp;
    temp = (*root)->left;
    delete *root;
    *root = temp;
    (*root)->parent = *root;
}

template<class Atype>
void multiplicity<Atype>::RemoveRight(node<Atype> **root) { // удаление корня, когда потомок есть только справа
    struct node<Atype> *temp;
    temp = (*root)->right;
    delete *root;
    *root = temp;
    (*root)->parent = *root;
}

template<class Atype>
int multiplicity<Atype>::RootRemoving(node<Atype> **root) { // удаление корня, возвращает 1, если удаление совершено, 0 если ничего не изменилось
    if ((*root)->right == 0 && (*root)->left == 0) { // если у корня нет потомков, то просто удаляем root
        delete *root;
        *root = NULL;
        return 1;
    }
    
    if ((*root)->right && !(*root)->left) { // если от корня идет только ветвь вправо
        RemoveRight(root);
        return 1;
    }
    
    if ((*root)->left && !(*root)->right) { // если от корня идет только ветвь влево
        RemoveLeft(root);
        return 1;
    }
    
    return 0;
}

template<class Atype>
node<Atype> *multiplicity<Atype>::Removing(node<Atype> *r, Atype k) { // удаление значения из дерева, возвращает главный корень дерева
    node<Atype> *udal, *min;
    if (k == r->info) {
        if (RootRemoving(&r)) // если у корня меньше 2ух потомков, то удаление состоится, возвращаем корень
            return r;
        udal = r; // если предыдущее не выполнилось, подготавливаем удаление корня с 2мя потомками
    }
    
    else // если удаляемое - не корень, то ищем удаляемое
        udal = Search(r, k);
    
    if (udal != NULL) { // udal == NULL, если числа в дереве нет
        if (udal->left != NULL && udal->right != NULL) { // два потомка у удаляемого
            min = SearchMin(udal->right); // минимальное из правого поддерева
            udal->info = min->info; // присваиваем удаляемому значение минимального из правого поддерева
            Child1(min);
            return r;
        }
        
        Child1(udal);
        return r;
    }
    
    return r;
}

template<class Atype>
int multiplicity<Atype>::Emptiness(node<Atype> *root) const { // пустота. 0, если пусто, 1, если нет
    if (root == NULL) {
        printf("Tree is empty!\n");
        return NULL;
    }
    
    return 1;
}

template<class Atype>
node<Atype> *multiplicity<Atype>::CopyTree(node<Atype> *a, node<Atype> *b) { // скопировать a в b, возвращает указатель на b
    if (a != NULL) {
        b = CopyTree(a->left, b);
        b = CopyTree(a->right, b);
        b = Insert(b, b, a->info);
    }
    
    return b;
}

template<class Atype>
int multiplicity<Atype>::Quantitiy(node<Atype> *root, int x) const { // возвращает кол-во элементов в списке
    if (root != NULL) {
        x++;
        x = Quantitiy(root->left, x);
        x = Quantitiy(root->right, x);
    }
    
    return x;
}

template<class Atype>
int multiplicity<Atype>::Equi(node<Atype> *const a, node<Atype> *const b) const { // равенство списков, 1, если равны, 0, если нет
    int x = IncList(a, b, 0);
    
    if (x)
        return x == Quantitiy(b, 0);
    
    return 0;
}

/* ----------------------------- МЕТОДЫ РАБОТЫ С ДЕРЕВОМ END ----------------------------- */

/* ----------------------------- МЕТОДЫ ДЛЯ ПЕРЕГРУЗКИ ОПЕРАТОРОВ START ----------------------------- */
template<class Atype>
node<Atype> *multiplicity<Atype>::Unite(node<Atype> *a, node<Atype> *const b) { // объединить деревья, добавляет b в a, возвращает a
    if (b != NULL) { // если дерево по которому идем не пустое
        if (a != NULL)  // если дерево, в которое будем добавлять не пустое
            a = Insert(a, a, b->info);
        
        Unite(a, b->left);
        Unite(a, b->right);
    }
    
    return a;
}

template<class Atype>
node<Atype> *multiplicity<Atype>::Crossing(node<Atype> *a, node<Atype> *const b) { // пересечение списков, пересечение a и b, меняет a, возвращает его же
    if (a != NULL) {
        a->left = Crossing(a->left, b);
        a->right = Crossing(a->right, b);
        
        if (b != NULL) {
            if (Search(b, a->info) == NULL)
                a = Removing(a, a->info);
        }
        else
            a = Removing(a, a->info);
    }
    
    return a;
}

template<class Atype>
node<Atype> *multiplicity<Atype>::Difference(node<Atype> *a, node<Atype> *const b) { // разность, отнимает от a b, меняет a, его и возвращает
    if (b != NULL && a != NULL) {
        a = Difference(a, b->left);
        a = Difference(a, b->right);
        
        if (a != NULL)
            a = Removing(a, b->info);
    }
    
    return a;
}

template<class Atype>
node<Atype> *multiplicity<Atype>::DiffSymm(node<Atype> *a, node<Atype> *const b) { // разность симметричная, меняет a, возвращает его же
    node<Atype> *q = NULL;
    q = CopyTree(b, q);
    
    q = Difference(q, a);
    a = Difference(a, b);
    a = Unite(a, q);
    return a;
}

template<class Atype>
int multiplicity<Atype>::IncElem(Atype i, node<Atype> *a) const { // включен ли элемент в список, возвращает int > 0, если включен, 0, если нет
    return (Search(a, i) != NULL);
}

template<class Atype>
int multiplicity<Atype>::IncList(node<Atype> *a, node<Atype> *b, int x) const { // включен ли список a в b, возврашает кол-во элементов b, если включен, 0, если нет
    if (b != NULL) { // если дерево по которому идем не пустое
        if (a != NULL) { // если дерево, в которое будем добавлять не пустое
            if (Search(a, b->info) == NULL) // если не нашли элемента b->info в дереве a, то тогда возвращаем 0
                return 0;
            else
                x++;
        }
        
        x = IncList(a, b->left, x);
        x = IncList(a, b->right, x);
    }
    
    return x;
}

/* ----------------------------- МЕТОДЫ ДЛЯ ПЕРЕГРУЗКИ ОПЕРАТОРОВ END ----------------------------- */

/* ----------------------------- ПЕРЕГРУЗКА ОПЕРАТОРОВ ДЛЯ РАБОТЫ С МНОЖЕСТВАМИ START ----------------------------- */
template<class Atype>
multiplicity<Atype>::multiplicity(const multiplicity<Atype> &sec) { // копирующий конструктор
    root = NULL;
    root = CopyTree(sec.root, root);
}

template<class Atype>
multiplicity<Atype> multiplicity<Atype>::operator + (const multiplicity<Atype> &a) { // объединение
    multiplicity<Atype> copy(*this);
    copy += a;
    
    return copy;
}

template<class Atype>
multiplicity<Atype> multiplicity<Atype>::operator ^ (const multiplicity<Atype> &a) { // пересечение
    multiplicity<Atype> copy(*this);
    copy ^= a;
    
    return copy;
}

template<class Atype>
multiplicity<Atype> multiplicity<Atype>::operator - (const multiplicity<Atype> &a) { // разность
    multiplicity<Atype> copy(*this);
    copy -= a;
    
    return copy;
}

template<class Atype>
multiplicity<Atype> multiplicity<Atype>::operator & (const multiplicity<Atype> &a) { // симметричная разность
    multiplicity<Atype> copy(*this);
    copy &= a;
    
    return copy;
}

template<class Atype>
multiplicity<Atype> multiplicity<Atype>::operator + (Atype x) { // добавить значение int
    multiplicity<Atype> copy(*this);
    
    copy.root = copy.Insert(copy.root, copy.root, x);
    return copy;
}

template<class Atype>
multiplicity<Atype> multiplicity<Atype>::operator - (Atype x) { // удалить значение
    multiplicity<Atype> copy(*this);
    
    copy.root = copy.Removing(copy.root, x);
    
    return copy;
}

template<class Atype>
multiplicity<Atype> &multiplicity<Atype>::operator -- () { // префикс (удаление первого)
    if (!root)
        return *this;
    
    root = Removing(root, SearchMin(root)->info);
    
    return *this;
}

template<class Atype>
multiplicity<Atype> &multiplicity<Atype>::operator -- (int x) { // постфикс (удаление последнего)
    if (!root)
        return *this;
    
    root = Removing(root, SearchMax(root)->info);
    
    return *this;
}

template<class Atype>
int multiplicity<Atype>::operator < (const multiplicity<Atype> &a) const { // подмножество
    return IncList(root, a.root, 0);
}

template<class Atype>
int multiplicity<Atype>::operator == (const multiplicity<Atype> &a) const { // эквивалентность
    if (this->root == a.root)
        return 1;
    
    if (root == NULL && a.root == NULL)
        return 1;
    
    if (root == NULL || a.root == NULL)
        return 0;
        
    return Equi(root, a.root);
}

//multiplicity::operator int() const { // сила множества НЕ ЛЕЗЬ
//	return Quantitiy(root, 0);
//}

template<class Atype>
multiplicity<Atype> &multiplicity<Atype>::operator = (const multiplicity<Atype> &a) { // присвоить
    if (this != &a) {
        root = DeleteTree(root);
        root = CopyTree(a.root, root);
    }
    
    return *this;
}

template<class Atype>
multiplicity<Atype> &multiplicity<Atype>::operator += (const multiplicity<Atype> &a) { // + присвоить множество
    if(root == NULL) {
        CopyTree(a.root, root);
        return *this;
    }
    
    if(a.root == NULL)
        return *this;
    
    root = Unite(root, a.root);
    return *this;
}

template<class Atype>
multiplicity<Atype> &multiplicity<Atype>::operator += (Atype x) { // + присвоить int
    root = Insert(root, root, x);
    return *this;
}

template<class Atype>
multiplicity<Atype> &multiplicity<Atype>::operator -= (const multiplicity<Atype> &a) { // - вычесть
    if (a.root == NULL)
        return *this;
    
    if (root == NULL)
        return *this;
    
    root = Difference(root, a.root);
    return *this;
}

template<class Atype>
multiplicity<Atype> &multiplicity<Atype>::operator -= (Atype x) { // - вычесть int
    root = Removing(root, x);
    return *this;
}

template<class Atype>
multiplicity<Atype> &multiplicity<Atype>::operator &= (const multiplicity<Atype> &a) { // & присвоить
    if (a.root == NULL)
        return *this;
    
    if (root == NULL) {
        root = CopyTree(a.root, root);
        return *this;
    }

    root = DiffSymm(root, a.root);
    return *this;
}

template<class Atype>
multiplicity<Atype> &multiplicity<Atype>::operator ^= (const multiplicity<Atype> &a) { // ^ присвоить
    if (root == NULL)
        return *this;
        
    if (a.root == NULL) {
        root = DeleteTree(root);
        return *this;
    }
        
    root = Crossing(root, a.root);
    return *this;
}

template<class Atype>
multiplicity<Atype> operator + (int x, multiplicity<Atype> &a) { // добавить значение в начало
    multiplicity<Atype> copy(a);
    
    copy.root = copy.Insert(copy.root, copy.root, x);
    return copy;
}

/* ----------------------------- ПЕРЕГРУЗКА ОПЕРАТОРОВ ДЛЯ РАБОТЫ С МНОЖЕСТВАМИ END ----------------------------- */

int main() {
    multiplicity<int> a, b, c;
    
    a += 5;
    a += 2;
    a += 7;
    a += 1;
    a = a + 4;
    
    b += 0;
    b += 6;
    b += 1;
    b += 15;
    b += 76;
    b += 56;
    b = b - 56;
    
    c += 5;
    c += 2;
    c += 7;
    c += 1;
    c += 4;
    
    std::cout << "a: " << a;
    std::cout << "b: " << b;
    std::cout << "c: " << c;
    std::cout << "a + b: " << (a + b);
    std::cout << "b - a: " << (b - a);
    std::cout << "a - b: " << (a - b);
    std::cout << "a ^ b: " << (a ^ b);
    std::cout << "a & b: " << (a & b);
    std::cout << "a < c: " << (a < c) << std::endl;
    std::cout << "4 < a: " << (4 < a) << std::endl;
    std::cout << "6 < a: " << (6 < a) << std::endl;
    std::cout << "c == c: " << (c == c) << std::endl;
    
    multiplicity<rational> x, y;
    int n, d;
    double f;
    
/*
    1 10
    7 8
    99 100
    2 13
    25 100
 
    8 9
    12 16
    1 10
    33 100
    100 33
 
 0.5
 0.1
 0.7
 0.2
 0.6
 0.16
 0.86
 0.13
 0.98
 0.12
*/
    
    for (int i = 0; i < 5; i++) {
        std::cin >> f;
        rational r(f);
        x += r;
    }
    
    for (int i = 0; i < 5; i++) {
        std::cin >> f;
        rational r(f);
        y += r;
    }
    
    rational z(2, 13);
    rational u(34, 15);
    
    std::cout << "x: " << x;
    std::cout << "y: " << y;
    std::cout << "x + y: " << (x + y);
    std::cout << "y - x: " << (y - x);
    std::cout << "x - y: " << (x - y);
    std::cout << "x ^ y: " << (x ^ y);
    std::cout << "x & y: " << (x & y);
    std::cout << "z < x: " << (z < x) << std::endl;
    std::cout << "u < x: " << (u < x) << std::endl;
    std::cout << "x == x: " << (x == x) << std::endl;
}
