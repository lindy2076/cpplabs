#pragma once

#include "Resource.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>

//создаем буфер чтобы туда запихнуть знаки для второго калькулятора
char c2_op1[] = { 0 };
char c2_op2[] = { 1 };

char c3_input[] = { 2 };

char c4_input[] = { 3 };

int num1, num2, num3;

std::string calculate_sum(int num1_, int num2_, int num3_) {
	int sum = num1_ + num2_ + num3_;
	std::string res = std::to_string(sum);
	std::cout << sum;
	return res;
}


std::string good_op(std::string op1) {
	if (op1 == "*") {
		return op1;
	}
	if (op1 == ":") {
		return op1;
	}
	if (op1 == "-") {
		return op1;
	}
	if (op1 == "+") {
		return op1;
	}
	return std::string("0");
}

int priority(std::string op1, std::string op2) {
	int p = 0;
	if (op2 == "*" || op2 == ":") {
		p = 1;
	}
	if (op1 == "*" || op1 == ":") {
		p = 0;
	}
	return p;
}


std::string calculate_second(int n1, int n2, int n3, std::string op1, std::string op2) {
	float res_left = 0;
	float res_right = 0;
	float res = 0;

	if (priority(op1, op2)) { //op2 > op1
		if (op2 == "*") {
			res_right = n2 * n3;
		}
		if (op2 == ":") {
			if (not n3) {
				return std::string("NaN");
			}
			res_right = n2 * 1.0 / n3 * 1.0;
		}
		if (op1 == "+") {
			res = n1 + res_right;
		}
		if (op1 == "-") {
			res = n1 - res_right;
		}
	}
	else {
		if (op1 == "*") {
			res_left = n1 * n2;
		}
		if (op1 == ":") {
			if (not n2) {
				return std::string("NaN");
			}
			res_left = n1 * 1.0 / n2 * 1.0;
		}
		if (op2 == "+") {
			res = res_left + n3;
		}
		if (op2 == "-") {
			res = res_left - n3;
		}
		if (op2 == "*") {
			res = res_left * n3;
		}
		if (op2 == ":") {
			if (not n3) {
				return std::string("NaN");
			}
			res = res_left * 1.0 / n3;
		}
	}
	return std::to_string(res);
}

// 3 calc

struct Stack {
	char c;
	Stack* next;
} *top;

int Prior(char a) { //prior operacii
	switch (a) {
	case '*': case ':': return 3;
	case '-': case '+': return 2;
	case '(': return 1;
	}
	return 0;
}

Stack* InS(Stack* p, char out) { //init
	Stack* t = new Stack;
	t->c = out;
	t->next = p;
	return t;
}

Stack* OutS(Stack* p, char& in) { // v in zapisivajem top stacka
	Stack* t = p;
	in = p->c;
	p = p->next;
	delete t;
	return p;
}


std::string reverse_polish(std::string input) {
	Stack* t, * Op = NULL;
	char a;
	char Out[1000];
	int k = 0, l = 0;
	while (input[k] != '\0') {
		if (input[k] >= '0' && input[k] <= '9' || input[k] == '.') {
			Out[l++] = input[k];
		}
		else if (l >= 0 && Out[l - 1] != ' ') {
			Out[l++] = ' ';
		}
		if (input[k] == '(') {
			Op = InS(Op, input[k]);
		}
		if (input[k] == ')') {
			while ((Op->c) != '(') {
				Op = OutS(Op, a);
				if (!Op) {
					a = '\0';
				}
				Out[l++] = a;
				Out[l++] = ' ';
			}
			t = Op;
			Op = Op->next;
			delete t;
		}
		if (input[k] == '+' || input[k] == '-' || input[k] == '*' || input[k] == ':') {
			while (Op != NULL && Prior(Op->c) >= Prior(input[k])) {
				Op = OutS(Op, a);

				Out[l++] = ' ';
				Out[l++] = a;
			}
			Op = InS(Op, input[k]);
		}
		k++;
	}
	while (Op != NULL) {
		Op = OutS(Op, a);
		Out[l++] = a;
		Out[l++] = ' ';
	}
	Out[l] = '\0';
	return std::string(Out);
}

struct Stack_int {
	float c;
	Stack_int* next;
} *top_;

Stack_int* Push(Stack_int* p, float out) { //init
	Stack_int* t = new Stack_int;
	t->c = out;
	t->next = p;
	return t;
}

Stack_int* Pop(Stack_int* p, float& in) { //
	Stack_int* t = p;
	in = p->c;
	p = p->next;
	delete t;
	return p;
}

int pow(int a, int b) {
	int res = 1;
	for (int i = 0; i < b; i++) {
		res *= a;
	}
	return res;
}


std::string calc_reverse(std::string pol) {
	Stack_int* val_stack = NULL;
	float res;
	float n2, n1;
	float temp_fl = 0.0;
	int k = 0;
	bool reading = false;
	int dotlen = 0;

	while (pol[k] != '\0') {
		if (pol[k] >= '0' && pol[k] <= '9') {
			reading = true;

			temp_fl = temp_fl * 10 + int(pol[k] - '0');
			dotlen++;
		}
		else if (reading) {
			reading = false;
			val_stack = Push(val_stack, temp_fl);
			std::cout << "pushed" << temp_fl << std::endl;
			temp_fl = 0.0;
			dotlen = 0;
		}
		if (pol[k] == '-' || pol[k] == '+' || pol[k] == ':' || pol[k] == '*') {
			val_stack = Pop(val_stack, n2);
			val_stack = Pop(val_stack, n1);

			switch (pol[k]) {
			case '+': res = n1 + n2; break;
			case '-': res = n1 - n2; break;
			case '*': res = n1 * n2; break;
			case ':': res = n1 / n2; break;
			}
			val_stack = Push(val_stack, res);
		}
		k++;
	}
	val_stack = Pop(val_stack, res);
	return std::to_string(res);
}

std::string calc3(std::string input) {
	std::string pol = reverse_polish(input);
	std::string calculated = calc_reverse(pol);
	return calculated;
}

// 4 CALC


std::string generate_op(int deep) {
	std::string OPS = "+-*:";
	std::string res = "";
	int decision = rand() % 10;
	if (deep == 1) {
		return std::to_string(rand() % 100 + 1) + OPS[rand() % 4] + std::to_string(rand() % 100 + 1);
	}
	if (decision == 1) {
		int left_op = rand() % 100 + 1;
		int right_op = rand() % 100 + 1;
		res = std::to_string(left_op) + OPS[rand() % 4] + std::to_string(right_op);
	}
	else {
		int decision2 = rand() % 2; // l or r 
		if (decision2) {
			std::string left_op = "(" + generate_op(deep - 1) + ")";
			int right_op = rand() % 100 + 1;
			res = res + left_op + OPS[rand() % 4] + std::to_string(right_op);
		}
		else {
			std::string right_op = "(" + generate_op(deep - 1) + ")";
			int left_op = rand() % 100 + 1;
			res = std::to_string(left_op) + OPS[rand() % 4] + right_op;
		}
	}

	return res;
}


std::string generate_polish() {
	int len = rand() % 20 + 1;  // kolichestvo operatorov
	std::string result = "";

	//for (int i = 0; i < len; i++) {
	result = generate_op(len);

	//}
	return result;
}

int Generate_govno(std::string generated) {
	generated = generate_polish();
	return 1;
}