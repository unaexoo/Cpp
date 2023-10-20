#ifndef CLASSICVM_H
#define CLASSICVM_H

#include <iostream>
#include <iomanip>
#include <string>
#include"VendingMachine.h"

using namespace std;
// ClassicVM : VendingMachine에 원래 구현되어 있던 purchaseProduct()함수를 적어주었다. 일반적 형태의 상품구매를 시행해준다.
class ClassicVM : public VendingMachine {
public:
    ClassicVM() :VendingMachine(){}
    void purchaseProduct() override {
        cout << "========= 구매 가능한 상품 =========" << endl;
        cout << right << setw(4) << "번호";
        cout << setw(20) << "상품명";
        cout << setw(20) << "가격" << endl;
        for (int i = 0; i < numProducts; i++) {
            if (stock[i] > 0 && balance >= prices[i]) {
                cout << setw(4) << (i + 1);
                cout << setw(20) << products[i];
                cout << setw(20) << prices[i] << endl;
            }
        }
        cout << "===================================" << endl;

        cout << "구매할 상품 번호를 선택하세요 (뒤로 가려면 0 입력): ";
        int selection;
        cin >> selection;
        cin.ignore(); // Ignore the newline character

        if (selection == 0) {
            cout << "구매를 취소합니다." << endl;
            return;
        }

        if (selection < 1 || selection > numProducts) {
            cout << "유효하지 않은 상품 번호입니다." << endl;
            return;
        }

        int productIndex = selection - 1;
        if (stock[productIndex] == 0) {
            cout << "해당 상품의 재고가 없습니다." << endl;
            return;
        }

        if (balance < prices[productIndex]) {
            cout << "잔액이 부족하여 해당 상품을 구매할 수 없습니다." << endl;
            return;
        }

        // Perform the purchase
        cout << "상품 구매 완료: " << products[productIndex] << endl;
        balance -= prices[productIndex];
        stock[productIndex]--;
    }
};

#endif // VENDINGMACHINE_H#pragma once
