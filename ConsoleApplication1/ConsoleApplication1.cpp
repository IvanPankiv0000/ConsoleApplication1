#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

FILE* f_out, * f_in;

struct car
{
	char mark[56];
	char builder[56];
	char type[56];
	int year;
	int price;
};

void medium1()
{
	//Вывести в файл информацию об авто, срок выпуска которых не менее 5 лет и они выпущены не в Китае;

	car* arr;
	int size, year = 2020;
	string city = "China";

	//количество авто не может быть меньше 1;
	do
	{
		cout << "Введите количество авто, данные которых вы будете вводить: ";
		cin >> size;
	} while (size < 1);

	arr = new car[size];

	for (int i = 0; i < size; i++)
	{
		cout << "Введите марку машины номер " << i + 1 << ": ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].mark, 56);
		cout << endl;

		cout << "Введите производителя: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].builder, 56);
		cout << endl;

		cout << "Введите тип машины: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].type, 56);
		cout << endl;

		do {
			cout << "Введите год выпуска: ";
			cin >> arr[i].year;
			cout << endl;
		} while (arr[i].year < 1900);

		do {
			cout << "Введите стоимость: ";
			cin >> arr[i].price;
			cout << endl;
		} while (arr[i].price <= 0);

		cout << endl;
	}

	//записываем в бин. файл данные;
	ofstream input("medium1_bin_File.bin", ios::binary | ios::out);

	for (int i = 0; i < size; i++)
	{
		if (year - arr[i].year >= 5 && arr[i].builder != city)
		{
			//переводим значения массива к типу char и указываем размер для правильной записи;
			input << "Автомобиль номер " << i + 1 << ":" << endl;
			input.write((char*)&arr[i], sizeof arr[i]) << endl << endl;
		}
	}

	//закрываем файл;
	input.close();

	cout << "Данные записаны в файл" << endl << endl;
}

void medium2()
{
	//Записать в файл двумерный массив 5х5 в двумерном виде, увеличить значения элементов в файле в 2.5 раза. Распечатать массив до и после изменений;

	const int row = 5, col = 6;
	double arr[row][col];

	//говорим программе что запись будет идти в бин. виде;
	f_out = fopen("medium2_numbers_before.bin", "wb");

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j != col - 1)
			{
				//считываем в файл элементы массива;
				arr[i][j] = rand() % 10;
				fwrite(&arr[i][j], sizeof(double), 1, f_out);
			}
			else
			{
				//элемент перехода на новую строку в файле занимает 6-ю колонку массива - ее мы не будем выводить в консоль;
				fwrite(&"\n", sizeof(double), 1, f_out);
			}
		}
	}

	fclose(f_out);

	double new_arr[row][col];

	//считываем с файла данные в новый массив;
	f_in = fopen("medium2_numbers_before.bin", "rb");
	fread(&new_arr, sizeof(double), row * col, f_in);
	fclose(f_in);

	cout << "Массив до изменений: " << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j != col - 1)
			{
				cout << new_arr[i][j] << "\t";
				new_arr[i][j] *= 2.5;
			}
		}
		cout << endl;
	}

	cout << endl;

	//записываем в новый файл уже измененный массив;
	f_out = fopen("medium2_numbers_after.bin", "wb");

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j != col - 1)
			{
				fwrite(&new_arr[i][j], sizeof(double), 1, f_out);
			}
			else
			{
				fwrite(&"\n", sizeof(double), 1, f_out);
			}
		}
	}

	fclose(f_out);

	//выводим новый массив в консоль;
	f_in = fopen("medium2_numbers_after.bin", "rb");
	fread(&new_arr, sizeof(double), row * col, f_in);
	fclose(f_in);

	cout << "Массив после изменений:" << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j != col - 1)
			{
				cout << new_arr[i][j] << "\t";
			}
		}
		cout << endl;
	}

	cout << endl << endl;
}

struct hotel
{
	char name[56];
	double price;
	int room_quantity;
	int free_place;
	int request;
	int days_quantity;
};

void medium3()
{
	//Уменьшить стоимость номера на 5%, если кол-во дней для проживания по пред. оплате равно 10, и на 10%, если кол-во дней больше 20;

	hotel* arr;
	int size;

	//количество гостиниц не может быть меньше 1;
	do
	{
		cout << "Введите количество гостиниц, данные которых вы будете вводить: ";
		cin >> size;
	} while (size < 1);

	arr = new hotel[size];

	for (int i = 0; i < size; i++)
	{
		cout << "Введите название гостиницы номер " << i + 1 << ": ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].name, 56);
		cout << endl;

		cout << "Введите стоимость номера: ";
		cin >> arr[i].price;
		cout << endl;

		do {
			cout << "Введите кол-во комнат в номере: ";
			cin >> arr[i].room_quantity;
			cout << endl;
		} while (arr[i].room_quantity > 3);

		do {
			cout << "Введите кол-во свободных мест в номере: ";
			cin >> arr[i].free_place;
			cout << endl;
		} while (arr[i].free_place > 6);

		do {
			cout << "Введите кол-во заявок на проживание в номере: ";
			cin >> arr[i].request;
			cout << endl;
		} while (arr[i].request > 100);

		do {
			cout << "Введите кол-во дней для проживания по предв. оплате: ";
			cin >> arr[i].days_quantity;
			cout << endl;
		} while (arr[i].days_quantity > 50);

		cout << endl;
	}

	// после записи открываем файл и считываем данные в новый массив;
	f_out = fopen("medium3_hotel_before.bin", "wb");
	fwrite(arr, sizeof(hotel), size, f_out);
	fclose(f_out);

	hotel* new_arr = new hotel[size];

	f_in = fopen("medium3_hotel_before.bin", "rb");
	fread(new_arr, sizeof(hotel), size, f_in);
	fclose(f_in);

	cout << "Данные из файла перед изменением:" << endl << endl;

	for (int i = 0; i < size; i++)
	{
		cout << "Отель номер " << i + 1 << ": " << new_arr[i].name << endl;
		cout << "Стоимость номера: " << new_arr[i].price << endl;
		cout << "Кол-во комнат в номере: " << new_arr[i].room_quantity << endl;
		cout << "Кол-во свободных мест в номере: " << new_arr[i].free_place << endl;
		cout << "Кол-во заявок на проживание: " << new_arr[i].request << endl;
		cout << "Кол-во дней для проживания по предв. оплате: " << new_arr[i].days_quantity << endl << endl;
	}

	for (int i = 0; i < size; i++)
	{
		if (new_arr[i].days_quantity == 10)
		{
			new_arr[i].price = new_arr[i].price / 100 * 95;
		}
		if (new_arr[i].days_quantity > 20)
		{
			new_arr[i].price = new_arr[i].price / 100 * 90;
		}
	}

	//после изменения данных снова считываем данные в консоль;
	f_out = fopen("medium3_hotel_after.bin", "wb");
	fwrite(new_arr, sizeof(hotel), size, f_out);
	fclose(f_out);

	f_in = fopen("medium3_hotel_after.bin", "rb");
	fread(new_arr, sizeof(hotel), size, f_in);
	fclose(f_in);

	cout << "Данные из файла после изменения:" << endl << endl;

	for (int i = 0; i < size; i++)
	{
		cout << "Отель номер " << i + 1 << ": " << new_arr[i].name << endl;
		cout << "Стоимость номера: " << new_arr[i].price << endl;
		cout << "Кол-во комнат в номере: " << new_arr[i].room_quantity << endl;
		cout << "Кол-во свободных мест в номере: " << new_arr[i].free_place << endl;
		cout << "Кол-во заявок на проживание: " << new_arr[i].request << endl;
		cout << "Кол-во дней для проживания по предв. оплате: " << new_arr[i].days_quantity << endl << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "RU");
	
	int a;
	int count = 0;

	do
	{
		cout << "Введите номер задания(medium1 - 1, medium2 - 2, medium3 - 3): ";

		cin >> a;

		cout << endl;

		if (a == 1)
		{
			medium1();
			count++;
		}

		if (a == 2)
		{
			medium2();
			count++;
		}

		if (a == 3)
		{
			medium3();
			count++;
		}

	} while (count == 0);

	int b;

	do
	{

		count = 0;

		cout << "Продолжить ввод? Да - 1, Нет - 2: ";

		cin >> b;

		cout << endl;

		if (b == 1)
		{
			count++;
			main();
		}

		if (b == 2)
		{
			cout << "Вы решили не продолжать";
			count++;
			break;
		}

	} while (count == 0);
}