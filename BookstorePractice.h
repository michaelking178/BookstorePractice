#ifndef BOOKSTOREPRACTICE_H
#define BOOKSTOREPRACTICE_H

#include <iostream>
#include <string>
#include <vector>

struct Book {
    std::string isbn;
    std::string title;
    double msrp;
};

struct Stock {
    Book book;
    double price;
    int volume;
    int unitsSold;
};

class Bookstore {

    public:
        void AddBook(Book &newBook, double price);
        void AddBook(Book &newBook);
        void Sell(Book &book);
        void SellVolume(Book &book, int vol);
        void PrintInventory();
        void ReceiveShipment(Book &newBook, int vol);
        double ItemTotalRevenue(Book &book);
        double ItemProfits(Book &book);

    private:
        std::vector<Stock> inventory;

    protected:
        
};

#endif