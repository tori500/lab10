#include <stdio.h>
#include <locale.h>
#include <math.h>

double f1(double x);
double f2(double x);
double sin_n(double x, int N);
double sin_eps(double x, double eps);

int main()
{
    setlocale(LC_ALL, "RUS");

    int task;

    printf("Выберите задание:\n");
    printf("1) Вычисление F1(x) и F2(x)\n");
    printf("2) Вычисление sin(x) тремя способами\n");
    printf("Ваш выбор: ");
    scanf("%d", &task);

    if (task == 1)
    {
        double x;
        int choice;

        printf("Введите значение x: ");
        scanf("%lf", &x);

        printf("Меню операций:\n");
        printf("1) Вычислить F1(x)\n");
        printf("2) Вычислить F2(x)\n");
        printf("3) Произведение F1(x) * F2(x)\n");
        printf("4) Разность квадратов F1(x)^2 - F2(x)^2\n");
        printf("5) Удвоенная сумма 2 * (F1(x) + F2(x))\n");
        printf("Выберите операцию: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("F1(x) = %lf\n", f1(x));
                break;
            case 2:
                printf("F2(x) = %lf\n", f2(x));
                break;
            case 3:
                printf("Произведение = %lf\n", f1(x) * f2(x));
                break;
            case 4:
                printf("Разность квадратов = %lf\n", f1(x) * f1(x) - f2(x) * f2(x));
                break;
            case 5:
                printf("Удвоенная сумма = %lf\n", 2 * (f1(x) + f2(x)));
                break;
            default:
                printf("Неверный выбор\n");
                break;
        }
    }
    else if (task == 2)
    {
        double x, eps;
        int N;
        double std_sin, my_sin_n, my_sin_eps;

        printf("Введите значение x (в радианах): ");
        scanf("%lf", &x);
        printf("Введите N (число членов ряда): ");
        scanf("%d", &N);
        printf("Введите eps (точность, например 0.0001): ");
        scanf("%lf", &eps);

        std_sin = sin(x);
        my_sin_n = sin_n(x, N);
        my_sin_eps = sin_eps(x, eps);

        printf("Результаты:\n");
        printf("Стандартная функция: %lf\n", std_sin);
        printf("Сумма %d членов:      %lf | Отклонение: %+e\n", N, my_sin_n, my_sin_n - std_sin);
        printf("С точностью %e:       %lf | Отклонение: %+e\n", eps, my_sin_eps, my_sin_eps - std_sin);
    }
    else
    {
        printf("Неверный выбор задания\n");
    }

    return 0;
}

double f1(double x)
{
    if (x <= 3)
    {
        return x * x - 3 * x + 9;
    }
    else
    {
        return 1.0 / (x * x * x + 3);
    }
}

double f2(double x)
{
    return x * exp(sin(x * x));
}

double sin_n(double x, int N)
{
    double sum = 0.0;
    double term = x; // Первый член ряда (k=1)
    int k;

    for (k = 1; k <= N; k++)
    {
        sum += term;
        // Пересчет следующего члена:
        // a_k = a_{k-1} * (-x^2) / ((2k) * (2k+1))
        term *= -x * x / ((2.0 * k) * (2.0 * k + 1.0));
    }

    return sum;
}

double sin_eps(double x, double eps)
{
    double sum = 0.0;
    double term = x;
    int k = 1;

    // Суммируем, пока очередной член по модулю больше или равен eps
    while (fabs(term) >= eps)
    {
        sum += term;
        term *= -x * x / ((2.0 * k) * (2.0 * k + 1.0));
        k++;
    }

    return sum;
}