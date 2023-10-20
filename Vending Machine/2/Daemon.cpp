//문제 해결 원리 :
//가상 함수(virtual function)란 파생 클래스에서 재정의할 것으로 기대하는 멤버 함수로 반드시 재정의해야만 하는 함수가 아닌 재정의가 가능한 함수를 가리킨다.
//여기서 반드시 재정의해야 하는 멤버 함수를 순수 가상 함수(pure virtual function)이라고 한다. 함수의 동작을 정의하는 본체를 가지고 있지 않고, 파생 클래스에서 재정의하지 않으면 사용할 수가 없다.
//
//문법은 virtual 멤버 함수의 원형 = 0; 이라고 하고 반드시 오버라이딩 되어야만 하는 함수를 말한다.본체가 없기 때문에 함수 호출은 불가능하다.
//추상 클래스란 하나 이상의 순수 가상 함수를 포함하는 클래스를 말한다.반드시 선언되어야 하는 멤버 함수를 추상 클래스에 순수 가상 함수로 선언해 놓으면 
//이 클래스로부터 파생된 모든 클래스에서는 이 가상 함수를 반드시 재정의해야 한다.추상 클래스는 동작이 정의되지 않은 순수 가상 함수를 포함하고 있기에 인스턴스를 생성할 수 없다.
//먼저 상속을 통해 파생 클래스를 만들고, 만든 파생 클래스에서 순수 가상 함수를 모두 오버라이딩 하고 나서야 파생 클래스의 인스턴스를 생성할 수 있게 된다.
//추상 클래스 타입의 포인터와 참조는 바로 사용할 수 있다. 해당 문제는 VendingMachine에 구현된 기능 중 purchaseProduct()함수를 virtual로 가상함수로 지정한다.
//그리고 해당 함수의 내용을 ClassicVM과 MultiVM 클래스에서 원하는 목적에 맞게 작성을 한다.ClassicVM의 경우 일반적 자판기의 구현을 작성한다.
//물건을 눌렀을 때 바로 반환이 되는 형태로 작성하였다.MultiVM의 경우 멀티 자판기 형식으로 버튼을 눌렀을 때 확인을 눌러야 물건의 판매가 이루어지게 하였다.

//VendingMachine: 자판기
//
//자판기는 관리자 기능으로 입고, 상품 관리 등을 수행하고 사용자 기능은 화폐투입, 제품 구매, 거스름돈 반환 등을 수행한다.
//여기서 VendingMachine은 돈 투입, 음료선택, 음료 판매& 거스름돈 반환한다.여기서 음료 판매 가능한지 아닌지, 음료의 수량을 체크핟고 없으면 채워 넣는다.
//
//여기서 VendingMachine은 기본적인 자판기의 기능을 수행한다.ClassicVM은 VendingMachine을 상속받고 VendingMachine의 순수 가상 함수인 purchaseProduct()를 정의한다.
//이 함수만 정의하면 기본적인 자판기의 기능이고 일반적인 자판기의 판매 과정이다.
//
//MultiVM의 경우 제품의 다이얼 형태의 번호를 누르고 확인을 체크해야 제품 판매가 완료된다.ClassicVM과 판매에서 차이가 있기에 purchaseProduct()를 새로 정의해준다.
//여기서는 제공된 코드에서의 형태와 다르게 do - while ()문을 사용하여 확인 버튼을 누를 때까지 제품 판매를 계속하는데 여기서 minprice와 check 변수를 통해 잔액이 판매 중인 제품 중 최소값보다 
//작다면 판매가 불가능하고 아니라면 사용자가 제품 구매를 완료할 때까지 수행한다.
//
//ButtonVM은  주어진 interface GUI를 바탕으로 작성하였다.마찬가지로 purchaseProduct() 함수를 정의해주는데 MultiVm에 정의된 내용과 비슷하게 구현을 하였다.
//그리고 UI 클래스를 정의하여 버튼의 동작을 수행하게 해주었다.UI 클래스의 멤버 변수인 Button* button1 - 9까지 정의해두었고 해당 버튼을 클릭하였을 때 제품 구매를 표기하도록 작성하였다.

// Main문에서는 switch-case를 동작하고 원래 있던 출력문에서 case4의 상품구매 부분만 do-while문을 통해서 button의 선택을 반복하게 해주었다.
#include "VendingMachine.h"
#include"ClassicVM.h"
#include"MultiVM.h"
#include"ButtonVM.h"
//VendingMachine* vm;
int main() {
    VendingMachine* vm = new ButtonVM();
    EventQueue& eve = EventQueue::getInstance();
    UI ui;
    int inp = 0;
    int selection; 
    vm->addProduct("코카콜라", 1000, 10, "DeptAI");
    vm->addProduct("코카콜라zero", 1100, 5, "DeptAI");
    vm->addProduct("삼다수", 800, 8, "DeptAI");
    do {
        // Display stock of each product
        cout << "========= 상품 재고 =========" << std::endl;
        vm->displayStock();
        cout << "===============================" << std::endl;

        cout << "========= 자판기 메뉴 =========" << std::endl;
        cout << "1. 상품 추가" << endl;
        cout << "2. 상품 삭제" << endl;
        cout << "3. 입고" << endl;
        cout << "4. 상품 구매" << endl;
        cout << "5. 금액 투입" << endl;
        cout << "6. 잔액 반환" << endl;
        cout << "7. 종료" << endl;
        cout << "===============================" << std::endl;
        cout << "잔액: " << vm->getBalance() << endl;
        cout << "선택: ";
        cin >> selection;
        cin.ignore(); // Ignore the newline character

        string enteredPassword;

        switch (selection) {
        case 1: {
            string productName;
            int price;
            int initialStock;
            cout << "상품 이름: ";
            getline(cin, productName);
            cout << "상품 가격: ";
            cin >> price;
            cout << "초기 재고: ";
            cin >> initialStock;
            cin.ignore(); // Ignore the newline character

            cout << "관리자 비밀번호: ";
            getline(cin, enteredPassword);

            vm->addProduct(productName, price, initialStock, enteredPassword);
            break;
        }
        case 2: {
            string productName;
            cout << "삭제할 상품 이름: ";
            getline(cin, productName);

            cout << "관리자 비밀번호: ";
            getline(cin, enteredPassword);

            vm->removeProduct(productName, enteredPassword);
            break;
        }
        case 3: {
            string productName;
            int additionalStock;
            cout << "입고할 상품 이름: ";
            getline(cin, productName);
            cout << "추가할 재고량: ";
            cin >> additionalStock;
            cin.ignore(); // Ignore the newline character

            cout << "관리자 비밀번호: ";
            getline(cin, enteredPassword);

            vm->updateStock(productName, additionalStock, enteredPassword);
            break;
        }
        case 4: {
            do {
                vm->purchaseProduct();

                while (cin >> skipws >> inp && inp > 0) {
                    vm->purchaseProduct();
                    cout << "(0: 이벤트 입력 종료, -1: 프로그램 종료) >> ";
                    ui.click(inp);
                }

                eve.exeEvent();
                cout << endl;
            } while (inp > -1);

            eve.releaseInstance();
            break;
        }
        case 5: {
            int amount;
            cout << "투입할 금액: ";
            cin >> amount;
            cin.ignore(); // Ignore the newline character
            vm->insertCoin(amount);
            break;
        }
        case 6: {
            vm->returnChange();
            break;
        }
        case 7:
            break;
        }

        system("pause");

    } while (selection != 7);
    //cout << "choice : " << "1. ClassicVM\t" << "2.MultiVM" << endl;
    //int choice = 0;
    //cin >> choice;

    //if (choice == 1) {
    //   vm = new ClassicVM();
    //}
    //else if (choice == 2) {
    //    vm = new MultiVM();
    //}
    //else {
    //    cout << "상품 구매 안 함" << endl;
    //    exit(1);
    //}

    //int selection;

    //vm->addProduct("코카콜라", 1000, 10, "DeptAI");
    //vm->addProduct("코카콜라zero", 1100, 5, "DeptAI");
    //vm->addProduct("삼다수", 800, 8, "DeptAI");
    //do {
    //    // Display stock of each product
    //    cout << "========= 상품 재고 =========" << std::endl;
    //    vm->displayStock();
    //    cout << "===============================" << std::endl;

    //    cout << "========= 자판기 메뉴 =========" << std::endl;
    //    cout << "1. 상품 추가" << endl;
    //    cout << "2. 상품 삭제" << endl;
    //    cout << "3. 입고" << endl;
    //    cout << "4. 상품 구매" << endl;
    //    cout << "5. 금액 투입" << endl;
    //    cout << "6. 잔액 반환" << endl;
    //    cout << "7. 종료" << endl;
    //    cout << "===============================" << std::endl;
    //    cout << "잔액: " << vm->getBalance() << endl;
    //    cout << "선택: ";
    //    cin >> selection;
    //    cin.ignore(); // Ignore the newline character

    //    string enteredPassword;

    //    switch (selection) {
    //    case 1: {
    //        string productName;
    //        int price;
    //        int initialStock;
    //        cout << "상품 이름: ";
    //        getline(cin, productName);
    //        cout << "상품 가격: ";
    //        cin >> price;
    //        cout << "초기 재고: ";
    //        cin >> initialStock;
    //        cin.ignore(); // Ignore the newline character

    //        cout << "관리자 비밀번호: ";
    //        getline(cin, enteredPassword);

    //        vm->addProduct(productName, price, initialStock, enteredPassword);
    //        break;
    //    }
    //    case 2: {
    //        string productName;
    //        cout << "삭제할 상품 이름: ";
    //        getline(cin, productName);

    //        cout << "관리자 비밀번호: ";
    //        getline(cin, enteredPassword);

    //        vm->removeProduct(productName, enteredPassword);
    //        break;
    //    }
    //    case 3: {
    //        string productName;
    //        int additionalStock;
    //        cout << "입고할 상품 이름: ";
    //        getline(cin, productName);
    //        cout << "추가할 재고량: ";
    //        cin >> additionalStock;
    //        cin.ignore(); // Ignore the newline character

    //        cout << "관리자 비밀번호: ";
    //        getline(cin, enteredPassword);

    //        vm->updateStock(productName, additionalStock, enteredPassword);
    //        break;
    //    }
    //    case 4: {
    //        vm->purchaseProduct();
    //        break;
    //    }
    //    case 5: {
    //        int amount;
    //        cout << "투입할 금액: ";
    //        cin >> amount;
    //        cin.ignore(); // Ignore the newline character
    //        vm->insertCoin(amount);
    //        break;
    //    }
    //    case 6: {
    //        vm->returnChange();
    //        break;
    //    }
    //    case 7:
    //        break;
    //    }

    //    system("pause");

    //} while (selection != 7);

    //int selection;
    //button->addProduct("코카콜라", 1000, 10, "DeptAI");
    //button->addProduct("코카콜라zero", 1100, 5, "DeptAI");
    //button->addProduct("삼다수", 800, 8, "DeptAI");
    //do {
    //    cout << "========= 상품 재고 =========" << std::endl;
    //    button->displayStock();
    //    cout << "===============================" << std::endl;

    //    cout << "========= 자판기 메뉴 =========" << std::endl;
    //    cout << "1. 상품 추가" << endl;
    //    cout << "2. 상품 삭제" << endl;
    //    cout << "3. 입고" << endl;
    //    cout << "4. 상품 구매" << endl;
    //    cout << "5. 금액 투입" << endl;
    //    cout << "6. 잔액 반환" << endl;
    //    cout << "7. 종료" << endl;
    //    cout << "===============================" << std::endl;
    //    cout << "잔액: " << vm->getBalance() << endl;
    //    cout << "선택: ";
    //    cin >> selection;
    //    cin.ignore(); // Ignore the newline character

    //    string enteredPassword;

    //    switch (selection) {
    //    case 1: {
    //        string productName;
    //        int price;
    //        int initialStock;
    //        cout << "상품 이름: ";
    //        getline(cin, productName);
    //        cout << "상품 가격: ";
    //        cin >> price;
    //        cout << "초기 재고: ";
    //        cin >> initialStock;
    //        cin.ignore(); // Ignore the newline character

    //        cout << "관리자 비밀번호: ";
    //        getline(cin, enteredPassword);

    //        button->addProduct(productName, price, initialStock, enteredPassword);
    //        break;
    //    }
    //    case 2: {
    //        string productName;
    //        cout << "삭제할 상품 이름: ";
    //        getline(cin, productName);

    //        cout << "관리자 비밀번호: ";
    //        getline(cin, enteredPassword);

    //        button->removeProduct(productName, enteredPassword);
    //        break;
    //    }
    //    case 3: {
    //        string productName;
    //        int additionalStock;
    //        cout << "입고할 상품 이름: ";
    //        getline(cin, productName);
    //        cout << "추가할 재고량: ";
    //        cin >> additionalStock;
    //        cin.ignore(); // Ignore the newline character

    //        cout << "관리자 비밀번호: ";
    //        getline(cin, enteredPassword);

    //        button->updateStock(productName, additionalStock, enteredPassword);
    //        break;
    //    }
    //    case 4: {
    //        button->purchaseProduct();
    //        break;
    //    }
    //    case 5: {
    //        int amount;
    //        cout << "투입할 금액: ";
    //        cin >> amount;
    //        cin.ignore(); // Ignore the newline character
    //        button->insertCoin(amount);
    //        break;
    //    }
    //    case 6: {
    //        button->returnChange();
    //        break;
    //    }
    //    case 7:
    //        break;
    //    }

    //    system("pause");

    //} while (selection != 7);

    //delete vm;
   // delete button;
    return 0;
}