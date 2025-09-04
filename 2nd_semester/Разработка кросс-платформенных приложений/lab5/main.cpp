#include <QCoreApplication>
#include <QList>
#include <list>
#include <iterator>

template <typename Container>
void display(Container &list){
    qDebug() << list;
}

//работает только для положительных чисел, тк у отрицательного начальный бит 1
int countLeadingZeroBits(quint32 v) {
    int count = 0;
    for (quint32 mask = 0x80000000; mask != 0; mask >>= 1) {
        if (mask & v) break;
        count++;
    }
    return count;
}

//бинарный поиск
template <typename Container, typename T>
typename Container::const_iterator binaryFind(const Container &container, const T& v){
    auto left = container.begin();
    auto right = container.end();
    while(left != right){
        auto mid = std::next(left, std::distance(left, right) / 2);
        if(v == *mid) return mid;
        else if(v > *mid) left = std::next(mid);
        else right = mid;
    }
    return container.end();
}

template <typename Container, typename T>
void addToEnd(Container &container, const T &num){
    container.push_back(num);
}

template <typename Container, typename T>
void addToBegin(Container &container, const T &num){
    container.push_front(num);
}

template <typename Container, typename T>
void deleteEl(Container &container, const T &num){
    container.remove(num);
}

int main(int argc, char* argv[]){
    QCoreApplication app(argc, argv);
    QTextStream cin(stdin);

    //из qlist в list
    QList<qint32> qlist = {6, 2, 9, 1, 5};
    std::list<int> stdlist(qlist.begin(), qlist.end());

    //из list в qlist
    std::list<qint32> stdlist2 = {6, 7, 8, 9, 0};
    QList<qint32> qlist2(stdlist2.begin(), stdlist2.end());

    stdlist.sort();
    display(stdlist);

    auto it = binaryFind(stdlist, 6);
    int index = 0;
    for(auto begin = stdlist.begin(); begin != it; begin++) index++;
    qDebug() << index;
    qDebug() << countLeadingZeroBits(7);
    qDebug() << qCountLeadingZeroBits(7);
    addToEnd(stdlist, 25);
    display(stdlist);

    deleteEl(stdlist, 5);
    display(stdlist);
    return app.exec();
}
