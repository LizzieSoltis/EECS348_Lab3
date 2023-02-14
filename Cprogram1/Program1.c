#include <stdio.h>
#include <stdlib.h>

#define MONTHS 12

float* read_data_from(char *file_name) {
	float* month_sales_data = (float*)malloc(sizeof(float) * MONTHS);
	FILE *fp = fopen(file_name, "r+");
	for (int i=0; i < MONTHS; i++) {
        fscanf(fp, "%f\n", &month_sales_data[i]);
    }

    return month_sales_data;
}

void print_data(char *months[], float *sales) {
    printf("Monthly sales report for 2022:\n\n");
    printf("%-15s%-10s\n", "Month", "Sales");
    for(int i=0; i < MONTHS; i++) {
        printf("%-15s$%-10.2f\n", months[i], sales[i]);
    }
    printf("\n");
}

void print_summary(char *months[], float *sales) {
    float min = 999999.99;
    char *min_month = "";
    float max = 0.0;
    char *max_month = "";
    float sum = 0.0;
    for (int i = 0; i < MONTHS; i++) {
        if (sales[i] < min) {
            min = sales[i];
            min_month = months[i];
        }
        if (sales[i] > max) {
            max = sales[i];
            max_month = months[i];
        }
        sum += sales[i];
    }
    float avg = sum /((float) MONTHS);
    printf("Sales Summary:\n\n");
    printf("%-15s$%-10.2f(%s)\n","Minimum Sales:", min, min_month);
    printf("%-15s$%-10.2f(%s)\n","Maximum Sales:", max, max_month);
    printf("%-15s$%-10.2f\n","Average Sales:", avg);
    printf("\n");
}

void print_moving_avg(char *months[], float *sales) {
    printf("Six-Month Moving Average Report:\n\n");
    for (int i=0; i<7; i++) {
        float sum = 0.0;
        char *start_month = months[i];
        char *end_month = months[i+5];
        for (int j=i; j<(i+6); j++) {
            sum += sales[j];
        }
        float moving_avg = sum / 6.0;
        printf("%-10s - %-10s $%-10.2f\n",start_month, end_month, moving_avg);
    }
    printf("\n");
}

void print_sorted_descending(char *months[], float *sales) {
    printf("Sales Report (Highest to Lowest):\n\n");
    printf("%-15s%-10s\n", "Month", "Sales");
    for (int i=0; i<MONTHS; i++) {
        for (int j=0; j<MONTHS-i-1; j++) {
            if (sales[j] < sales[j+1]) {
                float swap = sales[j];
                sales[j] = sales[j+1];
                sales[j+1] = swap;
                char *swap_month = months[j];
                months[j] = months[j+1];
                months[j+1] = swap_month;
            }
        }
    }
    for (int i=0; i<MONTHS; i++) {
        printf("%-15s$%-10.2f\n", months[i], sales[i]);
    }
}


int main() {
    float *sales = read_data_from("data.txt");
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    print_data(months, sales);
    print_summary(months, sales);
    print_moving_avg(months, sales);
    print_sorted_descending(months,sales);
    return 0;
}
