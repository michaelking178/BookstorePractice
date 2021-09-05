#include "BookstorePractice.h"

void PrintHeader(std::string headerText);

int main()
{
    Book book1 = Book { "155462248675", "The Hobbit", 14.99 };
    Book book2 = Book { "448651238895", "Don Quixote", 10.99 };
    Book book3 = Book { "896615934586", "The Secret Garden", 11.99 };
    Book book4 = Book { "155735945684", "Dune", 19.99 };

    Bookstore bookstore;

    bookstore.AddBook(book1, 15.49);
    bookstore.AddBook(book2);
    bookstore.AddBook(book3);

    PrintHeader("PRINT INITIAL INVENTORY");
    bookstore.PrintInventory();

    PrintHeader("ADD SHIPMENT TO INVENTORY");
    bookstore.ReceiveShipment(book2, 12);
    bookstore.PrintInventory();

    PrintHeader("SELL A BOOK");
    bookstore.Sell(book1);
    bookstore.PrintInventory();

    PrintHeader("SELL A VOLUME OF BOOKS");
    bookstore.SellVolume(book2, 7);
    bookstore.PrintInventory();

    PrintHeader("CHECK REVENUE AND PROFIT FOR SALE");
    std::cout << "Revenue: " << bookstore.ItemTotalRevenue(book2) << std::endl;
    std::cout << "Total profit: " << bookstore.ItemProfits(book2) << std::endl;

    PrintHeader("ADD A VOLUME OF NEW BOOKS");
    bookstore.ReceiveShipment(book4, 20);
    bookstore.PrintInventory();
}

void Bookstore::AddBook(Book &newBook)
{
    double suggestedPrice = newBook.msrp + 2.0;
    AddBook(newBook, suggestedPrice);
}

void Bookstore::AddBook(Book &newBook, double price)
{
    if (inventory.size() == 0) {
        Stock newStock = Stock { newBook, price, 1, 0 };
        inventory.push_back(newStock);
        return;
    }

    for (Stock &stock : inventory) {
        if (stock.book.isbn == newBook.isbn) {
            stock.volume++;
            return;
        }
    }

    Stock newStock = Stock { newBook, price, 1, 0 };
    inventory.push_back(newStock);
}

void Bookstore::PrintInventory()
{
    if (inventory.size() == 0)
    {
        std::cout << "No Inventory Data Available";
        return;
    }
    for (Stock &stock : inventory)
    {
        std::cout << stock.book.isbn << "    " << stock.book.title << "    MSRP: " << stock.book.msrp << "    Price: " << stock.price << "    In Stock: " << stock.volume << "    Units Sold: " << stock.unitsSold << std::endl;
    }
}

void Bookstore::ReceiveShipment(Book &newBook, int vol)
{
    std::cout << "Received " << newBook.title << " x" << vol << std::endl;
    for (int i = 0; i < vol; i++)
    {
        AddBook(newBook);
    }
}

double Bookstore::ItemTotalRevenue(Book &book)
{
    for (Stock &stock : inventory)
    {
        if (stock.book.isbn == book.isbn)
        {
            return stock.price * stock.unitsSold;
        }
    }
    std::cout << "Cannot find ItemTotalRevenue() for " << book.title << "(" << book.isbn << ")" << std::endl;
    return 0;
}

void Bookstore::Sell(Book &book)
{
    for (Stock &stock : inventory)
    {
        if (stock.book.isbn == book.isbn)
        {
            if (stock.volume == 0)
            {
                std::cout << "Cannot sell, out of stock!";
                return;
            }
            stock.unitsSold++;
            stock.volume--;
            std::cout << "Sold " << stock.book.title << " for $" << stock.price << std::endl;
            return;
        }
    }
    std::cout << "Cannot find " << book.title << "(" << book.isbn << ") in Inventory!";
}

void Bookstore::SellVolume(Book &book, int vol)
{
    for (int i = 0; i < vol; i++)
    {
        Sell(book);
    }
}

double Bookstore::ItemProfits(Book &book)
{
    for (Stock &stock : inventory)
    {
        if (stock.book.isbn == book.isbn)
        {
            double saleTotal = (double)stock.unitsSold * stock.price;
            double msrpTotal = (double)stock.unitsSold * stock.book.msrp;
            return saleTotal - msrpTotal;
        }
    }
    std::cout << "Cannot find ItemProfits for " << book.title << "(" << book.isbn << ")" << std::endl;
    return 0;
}

void PrintHeader(std::string headerText)
{
    std::cout << std::endl;
    std::cout << "--- " << headerText << " ---" << std::endl;
}