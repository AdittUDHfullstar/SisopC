#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void* factorial(void* arg) {
    int n = *((int*)arg);
    long long hasil = 1;
    for (int i = 1; i <= n; i++) hasil *= i;
    printf("Faktorial dari %d = %lld\n", n, hasil);
    return NULL;
}

void* fibonacci(void* arg) {
    int n = *((int*)arg);
    long long a = 0, b = 1, c;
    printf("Deret Fibonacci (%d angka): ", n);
    for (int i = 0; i < n; i++) {
        printf("%lld ", a);
        c = a + b;
        a = b;
        b = c;
    }
    printf("\n");
   return NULL;
}

void* readFile(void* arg) {
    const char* filename = (const char*)arg;
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Gagal membuka file: %s\n", filename);
    } else {
        printf("Isi file %s:\n", filename);
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    }
   return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    int angkaFaktorial = 5;
    int jumlahFibo = 10;
    const char* namaFile = "Critical.txt";

    pthread_create(&t1, NULL, factorial, (void*)&angkaFaktorial);
    pthread_create(&t2, NULL, fibonacci, (void*)&jumlahFibo);
    pthread_create(&t3, NULL, readFile, (void*)namaFile);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}
