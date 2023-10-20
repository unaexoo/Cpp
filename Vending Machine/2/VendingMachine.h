#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class VendingMachine {
protected:  // private -> protected
    string products[20];    // 물건의 번호   
    int prices[20];         // 물건의 가격
    int stock[20];          // 재고
    int numProducts;        // 물건의 수량
    int balance;            // 잔액
    string password = "DeptAI"; // 관리자 비밀번호

public:
    VendingMachine() : numProducts(0), balance(0) {
        for (int i = 0; i < 20; ++i) {
            prices[i] = 0;
            stock[i] = 0;
        }
    }

    bool checkPassword(string _password) {  // 관리자 비밀번호 체크
        if (password != _password) {
            cout << "관리자 비밀번호가 잘못되었습니다." << std::endl;
            return false;
        }

        return true;
    }

    void addProduct(const string& productName, int price, int initialStock, const string& _password) {  // 상품 추가
        if (!checkPassword(_password)) return;

        if (numProducts < 20) {
            products[numProducts] = productName;
            prices[numProducts] = price;
            stock[numProducts] = initialStock;
            numProducts++;
            cout << "상품 추가: " << productName << endl;
        }
        else {
            cout << "더 이상 상품을 추가할 수 없습니다." << endl;
        }
    }

    void removeProduct(const string& productName, const string& _password) {    // 상품 삭제
        if (!checkPassword(_password)) return;

        for (int i = 0; i < numProducts; ++i) {
            if (products[i] == productName) {
                for (int j = i; j < numProducts - 1; ++j) {
                    products[j] = products[j + 1];
                    prices[j] = prices[j + 1];
                    stock[j] = stock[j + 1];
                }
                numProducts--;
                cout << "상품 삭제: " << productName << endl;
                return;
            }
        }
        cout << "상품을 찾을 수 없습니다." << endl;
    }

    void checkStock(const string& productName) {    
        for (int i = 0; i < numProducts; ++i) {
            if (products[i] == productName) {
                cout << "재고 확인: " << products[i] << " - " << stock[i] << "개" << endl;
                return;
            }
        }
        cout << "상품을 찾을 수 없습니다." << endl;
    }

    void updateStock(const string& productName, int newStock, string _password) {
        if (!checkPassword(_password)) return;

        for (int i = 0; i < numProducts; ++i) {
            if (products[i] == productName) {
                stock[i] = newStock;
                cout << "재고 업데이트: " << products[i] << " - " << stock[i] << "개" << endl;
                return;
            }
        }
        cout << "상품을 찾을 수 없습니다." << endl;
    }

    void displayStock() {
        cout << right << setw(8) << "상품명";
        for (int i = 0; i < numProducts; i++) {
            cout << setw(15) << products[i];
        }

        cout << endl << setw(8) << "가격";
        for (int i = 0; i < numProducts; i++) {
            cout << setw(15) << prices[i];
        }

        cout << endl << setw(8) << "판매중";
        for (int i = 0; i < numProducts; i++) {
            cout << setw(15) << (stock[i] > 0 ? "O" : "X");
        }

        cout << endl << setw(8) << "선택가능";
        for (int i = 0; i < numProducts; i++) {
            cout << setw(15) << (stock[i] > 0 && balance >= prices[i] ? "O" : "X");
        }

        cout << endl;
    }

    void insertCoin(int amount) {
        balance += amount;
    }

    void returnChange() {
        int bal = balance;
        cout << endl << "잔액 " << balance << "원을 반환합니다." << endl;
        int weight[] = { 50000, 10000, 5000, 1000, 500, 100, 50, 10 };
        int amount;
        for (int i = 0; i < 8; i++) {
            amount = bal / weight[i];
            bal %= weight[i];
            if (amount) {
                cout << weight[i] << "원권 " << amount << "개 반환, ";
                cout << "잔액: " << bal << "원" << endl;
            }
        }
        balance = 0;
        cout << "잔액 반환이 완료 되었습니다." << endl << endl;
    }

    virtual void purchaseProduct() = 0;

    int getBalance() const {
        return balance;
    }
};
#endif // VENDINGMACHINE_H