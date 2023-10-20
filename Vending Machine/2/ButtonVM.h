#ifndef BUTTONVM_H
#define BUTTONVM_H
#include<deque>
#include<string>
#include<iomanip>
#include "VendingMachine.h"

// InterfaceGUI 예제를 참조하여 작성하였다. Button 클래스에 Button* button 1부터 9까지의 버튼을 정의해주었고 해당 버튼을 입력하였다. 버튼의 입력을 받아서 물건을 판매해준다. 
// 여기서 MultiVM의 purchaseProduct()의 함수를 참조하긴 하였지만 do - while문은 없애고 구현하였다. ui.click(-)을 통해서 원하는 물건이 할당된 button을 클릭하여 물건 판매를 해준다.
// 누른다의 instance는 EventQueue에 정의되어 있고 Queue를 통해 물건의 입출력이 이루어진다.
// button의 입력이 ui.click()을 통해 접근한다. button에는 각 번호에 대한 값이 들어오는 것을 "0001"처럼 new Button("0001")로 통해 할당해준다. EventQueue를 통해서 button의 입력과 출력을 저장해준다.
// main문에서 EventQueue의 역할이 끝나면 List항목 순을 보여준다.

class ButtonListenable {
public:
	virtual void onButtonClick(string eid) const = 0;
	virtual ~ButtonListenable() {}
};
class EventQueue {
public:
	static EventQueue& getInstance() {
		if (instance == nullptr) {
			instance = new EventQueue();
		}
		return *instance;
	}

	static void releaseInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}

	void addEvent(string id) {
		eve.push_back(id);
	}
	void addListener(ButtonListenable* lsn, string type_id) {
		lsner_type_id.push_back(type_id);
		lsner.push_back(lsn);
	}

	void exeEvent() {
		cout << "Event List in EventQueue: ";
		for (string e : eve) {
			cout << e << ", ";
		}
		cout << endl;

		while (!eve.empty()) {
			string eve_id = *(eve.begin());
			deque<ButtonListenable*>::iterator lsn_it = lsner.begin();
			for (deque<string>::iterator it = lsner_type_id.begin(); it != lsner_type_id.end(); it++) {
				if (eve_id == *it) {
					(*lsn_it)->onButtonClick(eve_id);
					eve.pop_front();
					break;
				}
				lsn_it++;
			}
		}
	}

private:
	EventQueue() {}
	~EventQueue() {}

	static EventQueue* instance;

private:
	deque<string> eve;

	deque<string> lsner_type_id;
	deque<ButtonListenable*> lsner;
};

EventQueue* EventQueue::instance = nullptr;


class Button {
private:
	string id;
	EventQueue& eve;

public:
	Button(string _id) : id(_id), eve(EventQueue::getInstance()) {}

	void addClickListener(ButtonListenable* lsner) {
		eve.addListener(lsner, "Button" + id);
	}

	void buttonClick() const {
		eve.addEvent("Button" + id);
	}

	string getId() {
		return id;
	}
};
class UI : public ButtonListenable {
public:
	UI() {
		button1 = new Button("0001");
		button2 = new Button("0002");
		button3 = new Button("0003");
		button4 = new Button("0004");
		button5 = new Button("0005");
		button6 = new Button("0006");
		button7 = new Button("0007");
		button8 = new Button("0008");
		button9 = new Button("0009");

		button1->addClickListener(this);
		button2->addClickListener(this);
		button3->addClickListener(this);
		button4->addClickListener(this);
		button5->addClickListener(this);
		button6->addClickListener(this);
		button7->addClickListener(this);
		button8->addClickListener(this);
		button9->addClickListener(this);
	}

	~UI() {
		delete button1;
		delete button2;
		delete button3;
		delete button4;
		delete button5;
		delete button6;
		delete button7;
		delete button8;
		delete button9;

	}
	void onButtonClick(string eid) const override {
		string btn_id = eid.substr(6);
		if (btn_id == "00001") {
			cout << "1번째 제품 선택" << endl;
		}
		else if (btn_id == "00002") {
			cout << "2번째 제품 선택" << endl;
		}
		else if (btn_id == "00003") {
			cout << "3번째 제품 선택" << endl;
		}
		else if (btn_id == "0004") {
			cout << "4번째 제품 선택" << endl;
		}
		else if (btn_id == "0005") {
			cout << "5번째 제품 선택" << endl;
		}
		else if (btn_id == "0006") {
			cout << "6번째 제품 선택" << endl;
		}
		else if (btn_id == "0007") {
			cout << "7번째 제품 선택" << endl;
		}
		else if (btn_id == "0008") {
			cout << "8번째 제품 선택" << endl;
		}
		else if (btn_id == "0009") {
			cout << "9번째 제품 선택" << endl;
		}
		else if (btn_id == "0010") {
			cout << "확인" << endl;
		}
		
	}
	void click(int inp) {
		switch (inp) {
		case 1:
			button1->buttonClick();
			break;
		case 2:
			button2->buttonClick();
			break;
		case 3:
			button3->buttonClick();
			break;
		case 4:
			button4->buttonClick();
			break;
		case 5:
			button5->buttonClick();
			break;
		case 6:
			button6->buttonClick();
			break;
		case 7:
			button7->buttonClick();
			break;
		case 8:
			button8->buttonClick();
			break;
		case 9:
			button9->buttonClick();
			break;
		}
	}

private:
	Button* button1;
	Button* button2;
	Button* button3;
	Button* button4;
	Button* button5;
	Button* button6;
	Button* button7;
	Button* button8;
	Button* button9;
};


class ButtonVM : public VendingMachine {
public:
	ButtonVM() :VendingMachine() {}

	void purchaseProduct() override {
		int minprice = INT_MAX;
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
		ui.click(selection);

		cout << "자판기 메뉴로 돌아가기 (inp -1 입력)" << endl;
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
		}
	}

private:
	UI ui;
};



#endif // BUTTONVM_H