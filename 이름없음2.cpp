#include <stdio.h>
#include <stdlib.h>

// �����͸� ������ ����ü ����
typedef struct {
    char key[20];
    int values[3];
} Data;

int main() {
    // ���� ���
    const char *file_path = "marbleBoardConfig.txt";  // ���� ��θ� ���� ������ ��η� �ٲ��ּ���.

    // ���� ����
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "������ �� �� �����ϴ�.\n");
        return 1;
    }

    // �����͸� ������ �迭 ���� �Ҵ�
    Data *data_array = (Data*)malloc(sizeof(Data) * 16);  // ���� �����Ͱ� 16���̹Ƿ� ũ�⸦ ����
    if (data_array == NULL) {
        fprintf(stderr, "�޸𸮸� �Ҵ��� �� �����ϴ�.\n");
        fclose(file);
        return 1;
    }

    int index = 0;
    char line[100];  // �� ���� �о�� ����

    // ���Ͽ��� �� ���� �о�� ������ ����ȭ
    while (fgets(line, sizeof(line), file) != NULL && index < 16) {
        sscanf(line, "%s %d %d %d", data_array[index].key, &data_array[index].values[0], &data_array[index].values[1], &data_array[index].values[2]);
        index++;
    }

    // ���� �ݱ�
    fclose(file);
	int temp ;
	
    // ��� ���
    for (int i = 0; i < index; i++) {
        printf("%s: %d %d %d\n", data_array[i].key, data_array[i].values[0], data_array[i].values[1], data_array[i].values[2]);
        if(data_array[i].values[0]==3) temp = data_array[i].values[2];
    }

    // ���� �Ҵ�� �޸� ����
    free(data_array);
	
	printf("%d", temp);
    return 0;
}

