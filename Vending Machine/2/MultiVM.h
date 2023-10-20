#ifndef MULTIVM_H
#define MULTIVM_H

#include "VendingMachine.h"

// MultVM : VendingMachine을 상속받아서 purchaseProduct()의 가상함수를 정의해주었다. int check 변수는 do-while문을 계속 반복할지를 확인하는데 물건의 구매를 계속할 것인지의 확인 버튼의 이미이다.
//          int minprice = INT_MAX로 초기화 해주고 minprice에 현재 있는 상품의 최소값을 저장하여 상품을 계속해서 구매할 수 있는지 여부를 체크한다. 남은 돈을 화면에 출력하여 상품을 고를 수 있는 범위를 
//          나타내준다. 상품을 더 이상 구매하지 못한다면 break을 해준다.
class MultiVM : public VendingMachine {
public:
	MultiVM() : VendingMachine(){}
    void purchaseProduct() override {
        int check = 0;
        int minprice = INT_MAX;
        do {
            cout << "========= 구매 가능한 상품 =========" << endl;
            cout << right << setw(4) << "번호";
            cout << setw(20) << "상품명";
            cout << setw(20) << "가격" << endl;
            for (int i = 0; i < numProducts; i++) {
                if (stock[i] > 0 && balance >= prices[i]) {
                    cout << setw(4) << (i + 1);
                    cout << setw(20) << products[i];
                    cout << setw(20) << prices[i] << endl;

                    if (prices[i] < minprice) {
                        minprice = prices[i];
                    }
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

            cout << "===================================" << endl;
            cout << "남은 돈 : " << balance << endl;
            cout << "===================================" << endl;
            if (balance < minprice) {
                cout << "상품을 더 이상 구매할 수 없습니다." << endl;
                break;
            }

            cout << "계속해서 상품을 구매하시겠습니까? (예: 0, 아니오: 1): ";
            cin >> check;
            cin.ignore(); // Ignore the newline character

        } while (check != 1);
    }

};

#endif